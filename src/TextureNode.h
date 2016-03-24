#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "ProcessNode.h"

class TextureNode : public ProcessNode {
private:
	ci::gl::FboRef mFbo;
	int mWidth, mHeight;
protected:
	ci::gl::Texture2dRef getInputTexture(int frame, boost::any texInput);
	void draw();
	ci::gl::Texture2dRef getTexture();
	ci::vec2 getSize();
public:
	TextureNode(std::string name, std::vector<std::string> inputIds);
};
