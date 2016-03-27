#include "OverlayNode.h"

using namespace ci;

OverlayNode::OverlayNode(std::string name) : ProcessNode(name, { "tex1", "tex2" })
{
	mShader = gl::GlslProg::create(app::loadAsset("shaders/passthru.vert"), app::loadAsset("shaders/overlay.frag"));
	mShader->uniform("i_resolution", (vec2) app::getWindowSize());

	mFbo = ci::gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
}

void OverlayNode::update(int frame)
{
	boost::any tex1Data = getInputData("tex1", frame);
	boost::any tex2Data = getInputData("tex2", frame);

	if (tex1Data.empty() || tex2Data.empty()) {
		setData("tex", boost::any());
		return;
	}

	gl::Texture2dRef tex1 = boost::any_cast<gl::Texture2dRef>(tex1Data);
	gl::Texture2dRef tex2 = boost::any_cast<gl::Texture2dRef>(tex2Data);

	gl::ScopedTextureBind tex1Scope(tex1, 0);
	mShader->uniform("tex1", 0);
	
	gl::ScopedTextureBind tex2Scope(tex2, 1);
	mShader->uniform("tex2", 1);

	gl::ScopedGlslProg glsl(mShader);

	ci::gl::ScopedFramebuffer fb(mFbo);

	ci::gl::ScopedViewport vp(ci::ivec2(0), mFbo->getSize());
	ci::gl::pushMatrices();
	ci::gl::setMatricesWindow(mFbo->getSize());

	ci::gl::clear(ci::Color(0, 0, 0));

	ci::gl::drawSolidRect(mFbo->getBounds());

	ci::gl::popMatrices();

	setData("tex", mFbo->getColorTexture());
}
