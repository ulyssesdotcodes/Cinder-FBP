#pragma once

#include "TextureNode.h"
#include "cinder/gl/gl.h"

class DelayNode : public TextureNode {
public:
	DelayNode(std::string name);
protected:
	void update(int frame);
};