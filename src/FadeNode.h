#pragma once

#include "ProcessNode.h"
#include "cinder/gl/gl.h"

class FadeNode : public ProcessNode {
public:
	FadeNode(std::string name);
protected:
	void update(int frame);
private:
	ci::gl::FboRef mFbo;
	int mWidth, mHeight;
};
