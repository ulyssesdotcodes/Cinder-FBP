#include "ScaleByNode.h"

using namespace ci;

ScaleByNode::ScaleByNode(std::string name) : ProcessNode(name, { "scalex", "scaley", "pivotx", "pivoty", "tex" })
{
	mShader = gl::GlslProg::create(app::loadAsset("shaders/passthru.vert"), app::loadAsset("shaders/scale_by.frag"));
}

void ScaleByNode::update(int frame)
{
	boost::any texInput = getInputData("tex", frame);
	if (texInput.empty()) {
		setData("tex", boost::any());
		return;
	}

	float scaleX = getInputData("scalex", frame).empty() ? 1 : getInputDataAsFloat("scalex", frame);
	float scaleY = getInputData("scaley", frame).empty() ? 1 : getInputDataAsFloat("scaley", frame);
	vec2 scale = vec2(scaleX, scaleY);

	float pivotX = getInputData("pivotx", frame).empty() ? 0.5 : getInputDataAsFloat("pivotx", frame);
	float pivotY = getInputData("pivoty", frame).empty() ? 0.5 : getInputDataAsFloat("pivoty", frame);
	vec2 pivot = vec2(pivotX, pivotY);

	gl::Texture2dRef tex = boost::any_cast<gl::Texture2dRef>(texInput);

	if (tex->getWidth() * scaleX != mWidth || tex->getHeight() * scaleY != mHeight) {
		mWidth = tex->getWidth() ;
		mHeight = tex->getHeight();

		mFbo = gl::Fbo::create(mWidth, mHeight);

		mShader->uniform("i_resolution", vec2(mWidth, mHeight));
	}

	mShader->uniform("i_scale", scale);
	mShader->uniform("i_pivot", pivot);

	gl::ScopedTextureBind texBind(tex, 0);
	mShader->uniform("tex", 0);

	ci::gl::ScopedFramebuffer fb(mFbo);

	gl::ScopedViewport vp(ivec2(0), mFbo->getSize());
	gl::pushMatrices();
	gl::setMatricesWindow(mFbo->getSize());

	gl::ScopedGlslProg glsl(mShader);

	ci::gl::clear(ci::Color(0, 0, 0));

	gl::drawSolidRect(mFbo->getBounds());

	gl::popMatrices();

	setData("tex", mFbo->getColorTexture());
}
