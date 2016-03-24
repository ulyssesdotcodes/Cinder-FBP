#pragma once

#include "ProcessNode.h"
#include "cinder/gl/gl.h"

class SplitSpectrumNode : public ProcessNode {
public:
	SplitSpectrumNode(std::string name);
protected:
	void update(int frame);
private:
	std::vector<float> mSplits;
};
