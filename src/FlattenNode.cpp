#include "FlattenNode.h"

using namespace ci;

FlattenNode::FlattenNode(std::string name) : TextureNode(name, { "tex" })
{

	mShader = gl::GlslProg::create(app::loadAsset("shaders/passthru.vert"), app::loadAsset("shaders/flatten.frag"));
}

void FlattenNode::update(int frame)
{
	gl::Texture2dRef tex = getInputTexture(frame, getInputData("tex", frame));
	if (tex == nullptr) {
		setData("tex", boost::any());
		return;
	}
	

	mShader->uniform("i_resolution", getSize());

	gl::ScopedTextureBind texBind(tex, 0);
	mShader->uniform("tex", 0);

	ci::gl::ScopedGlslProg glsl(mShader);

	draw();

	setData("tex", getTexture());
}
