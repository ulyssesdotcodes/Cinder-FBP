#pragma once

#include <boost/function.hpp>
#include "DataNode.h"
#include "ProcessNode.h"

class NodeFactory {
private:
	std::map<std::string, boost::function<std::shared_ptr<ProcessNode>(std::string)>> mClassMap;

public:
	NodeFactory();
	std::shared_ptr<ProcessNode> createInstance(std::string className, std::string instanceName) const;
	std::shared_ptr<DataNode> createDataNode(boost::any data) const;
};