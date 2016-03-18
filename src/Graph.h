#pragma once

#include "cinder/Json.h"
#include "DataNode.h"
#include "NodeFactory.h"
#include "ProcessNode.h"

class Graph : public Node{
private:
	std::map<std::string, std::shared_ptr<ProcessNode>> mProcesses;
	ci::JsonTree mData;
	std::map<std::string, InputNode> mOutputs;

public:
	Graph();
	Graph(std::shared_ptr<NodeFactory> nodeFactory);
	void setJson(ci::fs::path path);
	void addNode(ci::JsonTree payload);
	void addData(ci::JsonTree payload);
	void addEdge(ci::JsonTree payload);
	void addOutput(ci::JsonTree payload);

	std::shared_ptr<NodeFactory> mNodeFactory;

	boost::any getData(std::string id, int frame);
};