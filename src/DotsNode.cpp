#include "DotsNode.h"

using namespace ci;

DotsNode::DotsNode(std::string name) : ProcessNode(name, { "splits", "accumulatedVolume" })
{
	mShader = gl::GlslProg::create(app::loadAsset("shaders/passthru.vert"), app::loadAsset("shaders/dots.frag"));
	mShader->uniform("i_resolution", (vec2) app::getWindowSize());

	mFbo = ci::gl::Fbo::create(app::getWindowWidth(), app::getWindowHeight());
}

void DotsNode::update(int frame)
{
	if (getInputData("accumulatedVolume", frame).empty() || getInputData("splits", frame).empty()) {
		return setData("tex", boost::any());
	}

	mShader->uniform("i_time", (float) app::getElapsedSeconds());
	mShader->uniform("i_accumulatedVolume", boost::any_cast<float>(getInputDataAsFloat("accumulatedVolume", frame)));
	std::vector<float> splits = boost::any_cast<std::vector<float>>(getInputData("splits", frame));
	mShader->uniform("i_splits", splits.data(), splits.size());

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
