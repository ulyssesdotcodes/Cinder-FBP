#include "Graph.h"

#include "cinder/app/App.h"
#include "cinder/DataSource.h"

using namespace ci;

void Graph::setJson(ci::fs::path path, const NodeFactory& nodeFactory)
{
	mProcesses.clear();

	mData = JsonTree(loadFile(path));

	// Generate the processes

	const JsonTree processes = mData["processes"];
	for (int i = 0; i < processes.getNumChildren(); ++i) {
		JsonTree process = processes[i];
		std::string name = process.getKey();
		std::string type = process.getValueForKey("component");
		mProcesses[name] = nodeFactory.createInstance(type, name);
	}


	// Generate the connections
	const JsonTree connections = mData["connections"];
	for (int i = 0; i < connections.getNumChildren(); ++i) {

		if (connections[i].hasChild("data")) {
			// Deal with a data child
			JsonTree tgt = connections[i]["tgt"];

			InputNode inputNode = { "data", nodeFactory.createDataNode(connections[i].getValueForKey("data")) };

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

boost::any Graph::getData(std::string id, int frame)
{
	return mOutputs[id].node->getData(mOutputs[id].id, frame);
}
