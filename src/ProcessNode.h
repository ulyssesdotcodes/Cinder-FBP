#pragma once

#include <boost/any.hpp>
#include <map>
#include <memory>
#include <vector>
#include "FBPNode.h"

struct FBPInputNode {
	std::string id;
	std::shared_ptr<FBPNode> node;
};

class ProcessNode : public FBPNode{
private:
	std::map<std::string, boost::any> mData;
	std::map<std::string, FBPInputNode> mInputs;
	int mLastFrame;
	std::string mName;


protected:
	std::vector<std::string> mInputIds;
	void setData(std::string id, boost::any data);
	boost::any getInputData(std::string id, int frame);
	boost::any getInputData(std::string id);
	float getInputDataAsFloat(std::string id, float default, int frame);
	virtual void update(int frame) = 0;

public:
	ProcessNode(std::string name, std::vector<std::string> inputIds);
	void setInput(std::string inputId, FBPInputNode node);
	boost::any getData(std::string id, int frame);
	boost::any getData(std::string id);
};