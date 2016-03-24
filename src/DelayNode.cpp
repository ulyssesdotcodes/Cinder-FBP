#include "DelayNode.h"

using namespace ci;

DelayNode::DelayNode(std::string name) : TextureNode(name, { "tex" })
{
}

void DelayNode::update(int frame)
{
	gl::Texture2dRef tex = getInputTexture(frame, getData("tex", frame));
	if (tex == nullptr) {
		setData("tex", boost::any());
		return;
	}

	setData("tex", tex);

	draw();
}
