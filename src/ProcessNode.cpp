#include "ProcessNode.h"

#include "cinder/app/App.h"

ProcessNode::ProcessNode(std::string name, std::vector<std::string> inputIds) : mLastFrame(-1), mName(name), mInputIds(inputIds) {}

void ProcessNode::setData(std::string id, boost::any data)
{
	mData[id] = data;
}

boost::any ProcessNode::getInputData(std::string id, int frame)
{
	InputNode in = mInputs[id];

	return in.node->getData(in.id, frame);
}

void ProcessNode::setInput(std::string id, InputNode inputNode) 
{
	if (std::find(mInputIds.begin(), mInputIds.end(), id) == mInputIds.end()) {
		ci::app::console() << "You tried to set input " << id << " on " << mName << " where there isn't such an input.";
		throw;
	}

	mInputs[id] = inputNode;
}

boost::any ProcessNode::getData(std::string id, int frame)
{
	if (frame > mLastFrame) {
		update(frame);
		mLastFrame = frame;
	}

	return mData[id];
}
