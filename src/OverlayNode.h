#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "ProcessNode.h"

class OverlayNode : public ProcessNode {
private:
	ci::gl::GlslProgRef mShader;
	ci::gl::FboRef mFbo;
	int mWidth, mHeight;
protected:
	void update(int frame) override;
public:
	OverlayNode(std::string name);
};
