#pragma once

#include <boost/any.hpp>
#include <map>
#include <memory>
#include <vector>
#include "Node.h"

struct InputNode {
	std::string id;
	std::shared_ptr<Node> node;
};

class ProcessNode : public Node{
private:
	std::map<std::string, boost::any> mData;
	std::map<std::string, InputNode> mInputs;
	int mLastFrame;
	std::string mName;


protected:
	std::vector<std::string> mInputIds;
	void setData(std::string id, boost::any data);
	boost::any getInputData(std::string id, int frame);
	float getInputDataAsFloat(std::string id, int frame);
	virtual void update(int frame) = 0;

public:
	ProcessNode(std::string name, std::vector<std::string> inputIds);
	void setInput(std::string inputId, InputNode node);
	boost::any getData(std::string id, int frame);
};