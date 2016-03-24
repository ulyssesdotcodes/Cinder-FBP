#pragma once

#include "TextureNode.h"

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

class DotsNode : public ProcessNode {
private:
	ci::gl::GlslProgRef mShader;
	ci::vec2 mScale, mPivot;
	ci::gl::FboRef mFbo;

public:
	DotsNode(std::string name);

protected:
	void update(int frame) override;
};
