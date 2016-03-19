#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "ProcessNode.h"

class ScaleByNode : public ProcessNode {
private:
	ci::gl::FboRef mFbo;
	ci::gl::GlslProgRef mShader;
	float mWidth, mHeight;
	ci::vec2 mScale, mPivot;

public:
	ScaleByNode(std::string name);

protected:
	void update(int frame) override;
};
