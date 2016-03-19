#include "Graph.h"

#include "cinder/app/App.h"
#include "cinder/DataSource.h"

using namespace ci;

Graph::Graph() { }

Graph::Graph(std::shared_ptr<NodeFactory> nodeFactory)
{
	mNodeFactory = nodeFactory;
}

void Graph::setJson(ci::fs::path path)
{
	mProcesses.clear();

	mData = JsonTree(loadFile(path));

	// Generate the processes

	const JsonTree processes = mData["processes"];
	for (int i = 0; i < processes.getNumChildren(); ++i) {
		JsonTree process = processes[i];
		std::string name = process.getKey();
		std::string type = process.getValueForKey("component");
		mProcesses[name] = mNodeFactory->createInstance(type, name);
	}


	// Generate the connections
	const JsonTree connections = mData["connections"];
	for (int i = 0; i < connections.getNumChildren(); ++i) {

		if (connections[i].hasChild("data")) {
			// Deal with a data child
			JsonTree tgt = connections[i]["tgt"];

			FBPInputNode FBPInputNode = { "data", mNodeFactory->createDataNode(connections[i].getValueForKey("data")) };

			mProcesses[tgt.getValueForKey("process")]->setInput(tgt.getValueForKey("port"), FBPInputNode);
			continue;
		}

		JsonTree src = connections[i]["src"];
		FBPInputNode srcNode = { src.getValueForKey("port"), mProcesses[src.getValueForKey("process")] };


		JsonTree tgt = connections[i]["tgt"];
		mProcesses[tgt.getValueForKey("process")]->setInput(tgt.getValueForKey("port"), srcNode);
	}

	const JsonTree outports = mData["outports"];
	for (int i = 0; i < outports.getNumChildren(); ++i) {
		FBPInputNode srcNode = { outports[i].getValueForKey("port"), mProcesses[outports[i].getValueForKey("process")] };
		mOutputs[outports[i].getKey()] = srcNode;
	}
}

void Graph::addNode(JsonTree payload)
{
	std::string name = payload.getValueForKey("id");
	std::string type = payload.getValueForKey("component");
	mProcesses[name] = mNodeFactory->createInstance(type, name);
}

void Graph::addData(JsonTree payload)
{
	JsonTree tgt = payload["tgt"];

	FBPInputNode FBPInputNode = { "data", mNodeFactory->createDataNode(payload.getValueForKey("src.data")) };

	mProcesses[tgt.getValueForKey("node")]->setInput(tgt.getValueForKey("port"), FBPInputNode);
}

void Graph::addEdge(JsonTree payload)
{
		JsonTree src = payload["src"];
		FBPInputNode srcNode = { src.getValueForKey("port"), mProcesses[src.getValueForKey("node")] };

		JsonTree tgt = payload["tgt"];
		mProcesses[tgt.getValueForKey("node")]->setInput(tgt.getValueForKey("port"), srcNode);
}

void Graph::addOutput(ci::JsonTree payload)
{
	FBPInputNode srcNode = { payload.getValueForKey("port"), mProcesses[payload.getValueForKey("node")] };
	mOutputs[payload.getValueForKey("public")] = srcNode;
}

void Graph::handleMessage(ci::JsonTree message, std::function<void(std::string)> write)
{
	std::string command = message.getValueForKey("command");
	if (command.compare("getruntime") == 0) {
		JsonTree resp = JsonTree(app::loadAsset("runtimeResponse.json"));
		write(resp.serialize());

		JsonTree clear = JsonTree::makeObject();
		clear.addChild(JsonTree("protocol", "graph"));
		clear.addChild(JsonTree("command", "clear"));
		
		JsonTree payload = JsonTree::makeObject("payload");
		payload.addChild(JsonTree("id", "cinder-graph"));

		clear.addChild(payload);

		write(clear.serialize());
	}
	else if (command.compare("list") == 0) {

		JsonTree components = JsonTree(app::loadAsset("components.json"));
		for (int i = 0; i < components.getNumChildren(); ++i) {
			write(components[i].serialize());
		}

		JsonTree componentsReady = JsonTree::makeObject();
		componentsReady.addChild(JsonTree("protocol", "component"));
		componentsReady.addChild(JsonTree("command", "componentsready"));

		write(componentsReady.serialize());
	}
	else if (command.compare("addnode") == 0) {
		addNode(message["payload"]);
	}
	else if (command.compare("addinitial") == 0) {
		addData(message["payload"]);
	}
	else if (command.compare("addedge") == 0) {
		addEdge(message["payload"]);
	}
	else if (command.compare("addoutport") == 0) {
		addOutput(message["payload"]);
	}
}

boost::any Graph::getData(std::string id, int frame)
{
	if (mOutputs.find(id) == mOutputs.end()) {
		return boost::any();
	}
	return mOutputs[id].node->getData(mOutputs[id].id, frame);
}
