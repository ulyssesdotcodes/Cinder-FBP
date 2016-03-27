#pragma once

#include "FBPNode.h"

class DataNode : public FBPNode {
private:
	boost::any mData;

public:
	DataNode(boost::any data);
	boost::any getData(std::string id, int frame);
	boost::any getData(std::string id);
};