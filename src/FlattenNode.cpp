#include "FlattenNode.h"

using namespace ci;

FlattenNode::FlattenNode(std::string name) : ProcessNode(name, { "tex" })
{

	mShader = gl::GlslProg::create(app::loadAsset("shaders/passthru.vert"), app::loadAsset("shaders/flatten.frag"));
}

void FlattenNode::update(int frame)
{
	boost::any texInput = getInputData("tex", frame);
	if (texInput.empty()) {
		setData("tex", texInput);
		return;
	}

	gl::Texture2dRef tex = boost::any_cast<gl::Texture2dRef>(texInput);

	if (tex->getWidth() != mWidth || tex->getHeight() != mHeight) {
		mWidth = tex->getWidth();
		mHeight = tex->getHeight();

		mFbo = gl::Fbo::create(mWidth, mHeight);

		mShader->uniform("i_resolution", vec2(mWidth, mHeight));
	}

	gl::ScopedTextureBind texBind(tex, 0);

	mShader->uniform("tex", 0);

	ci::gl::ScopedFramebuffer fb(mFbo);

	gl::ScopedViewport vp(ivec2(0), mFbo->getSize());
	gl::pushMatrices();
	gl::setMatricesWindow(mFbo->getSize());

	gl::ScopedGlslProg glsl(mShader);

	ci::gl::clear(ci::Color(0, 0, 0));

	gl::drawSolidRect(mFbo->getBounds());

	gl::pushMatrices();

	setData("tex", mFbo->getColorTexture());
}
