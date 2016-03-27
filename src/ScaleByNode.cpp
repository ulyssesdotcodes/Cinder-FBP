#include "ScaleByNode.h"

using namespace ci;

ScaleByNode::ScaleByNode(std::string name) : TextureNode(name, { "scalex", "scaley", "pivotx", "pivoty", "tex" })
{
	mShader = gl::GlslProg::create(app::loadAsset("shaders/passthru.vert"), app::loadAsset("shaders/scale_by.frag"));
}

void ScaleByNode::update(int frame)
{
	gl::Texture2dRef tex = getInputTexture(frame, getInputData("tex", frame));
	if (tex == nullptr) {
		setData("tex", boost::any());
		return;
	}

	float scaleX = getInputDataAsFloat("scalex", 1, frame);
	float scaleY = getInputDataAsFloat("scaley", 1, frame);
	vec2 scale = vec2(scaleX, scaleY);

	float pivotX = getInputDataAsFloat("pivotx", 0.5, frame);
	float pivotY = getInputDataAsFloat("pivoty", 0.5, frame);
	vec2 pivot = vec2(pivotX, pivotY);

	mShader->uniform("i_resolution", getSize());
	mShader->uniform("i_scale", scale);
	mShader->uniform("i_pivot", pivot);

	gl::ScopedTextureBind texBind(tex, 0);
	mShader->uniform("tex", 0);
	gl::ScopedGlslProg glsl(mShader);

	draw();

	setData("tex", getTexture());
}
