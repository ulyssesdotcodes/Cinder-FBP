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
	void setJson(ci::fs::path path, const NodeFactory& nodeFactory);

	boost::any getData(std::string id, int frame);
};