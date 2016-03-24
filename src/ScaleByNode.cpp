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

	float scaleX = getInputData("scalex", frame).empty() ? 1 : getInputDataAsFloat("scalex", frame);
	float scaleY = getInputData("scaley", frame).empty() ? 1 : getInputDataAsFloat("scaley", frame);
	vec2 scale = vec2(scaleX, scaleY);

	float pivotX = getInputData("pivotx", frame).empty() ? 0.5 : getInputDataAsFloat("pivotx", frame);
	float pivotY = getInputData("pivoty", frame).empty() ? 0.5 : getInputDataAsFloat("pivoty", frame);
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
