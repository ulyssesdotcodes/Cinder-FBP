#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "TextureNode.h"


class FlattenNode : public TextureNode {
private:
	ci::gl::GlslProgRef mShader;
protected:
	void update(int frame) override;
public:
	FlattenNode(std::string name);
};
