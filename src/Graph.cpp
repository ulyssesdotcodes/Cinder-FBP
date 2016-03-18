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

			InputNode inputNode = { "data", mNodeFactory->createDataNode(connections[i].getValueForKey("data")) };

			mProcesses[tgt.getValueForKey("process")]->setInput(tgt.getValueForKey("port"), inputNode);
			continue;
		}

		JsonTree src = connections[i]["src"];
		InputNode srcNode = { src.getValueForKey("port"), mProcesses[src.getValueForKey("process")] };


		JsonTree tgt = connections[i]["tgt"];
		mProcesses[tgt.getValueForKey("process")]->setInput(tgt.getValueForKey("port"), srcNode);
	}

	const JsonTree outports = mData["outports"];
	for (int i = 0; i < outports.getNumChildren(); ++i) {
		InputNode srcNode = { outports[i].getValueForKey("port"), mProcesses[outports[i].getValueForKey("process")] };
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

	InputNode inputNode = { "data", mNodeFactory->createDataNode(payload.getValueForKey("src.data")) };

	mProcesses[tgt.getValueForKey("node")]->setInput(tgt.getValueForKey("port"), inputNode);
}

void Graph::addEdge(JsonTree payload)
{
		JsonTree src = payload["src"];
		InputNode srcNode = { src.getValueForKey("port"), mProcesses[src.getValueForKey("node")] };

		JsonTree tgt = payload["tgt"];
		mProcesses[tgt.getValueForKey("node")]->setInput(tgt.getValueForKey("port"), srcNode);
}

void Graph::addOutput(ci::JsonTree payload)
{
	InputNode srcNode = { payload.getValueForKey("port"), mProcesses[payload.getValueForKey("node")] };
	mOutputs[payload.getValueForKey("public")] = srcNode;
}

boost::any Graph::getData(std::string id, int frame)
{
	if (mOutputs.find(id) == mOutputs.end()) {
		return boost::any();
	}
	return mOutputs[id].node->getData(mOutputs[id].id, frame);
}
