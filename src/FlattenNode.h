#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "ProcessNode.h"


class FlattenNode : public ProcessNode {
private:
	ci::gl::FboRef mFbo;
	ci::gl::GlslProgRef mShader;
	int mWidth, mHeight;
protected:
	void update(int frame) override;
public:
	FlattenNode(std::string name);
};
