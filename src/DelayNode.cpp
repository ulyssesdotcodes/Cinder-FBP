#include "DelayNode.h"

using namespace ci;

DelayNode::DelayNode(std::string name) : TextureNode(name, { "tex" })
{
	mShader = gl::getStockShader(gl::ShaderDef().texture());
}

void DelayNode::update(int frame)
{
	gl::Texture2dRef tex = getInputTexture(frame, getInputData("tex"));
	if (tex == nullptr) {
		setData("tex", getTexture());
		return;
	}

	gl::ScopedTextureBind texBind(tex);

	gl::ScopedGlslProg scopeProg(mShader);

	draw();

	setData("tex", getTexture());
}
