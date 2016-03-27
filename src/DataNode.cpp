#include "DataNode.h"

DataNode::DataNode(boost::any data)
{
	mData = data;
}

boost::any DataNode::getData(std::string id, int frame)
{
	return getData(id);
}

boost::any DataNode::getData(std::string id)
{
	return mData;
}
