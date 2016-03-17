#pragma once

#include "Node.h"

class DataNode : public Node {
private:
	boost::any mData;

public:
	DataNode(boost::any data);
	boost::any getData(std::string id, int frame);
};