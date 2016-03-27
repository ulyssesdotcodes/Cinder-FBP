#include "TextureNode.h"

TextureNode::TextureNode(std::string name, std::vector<std::string> inputIds) : ProcessNode(name, inputIds)
{
	mFbo = ci::gl::Fbo::create(ci::app::getWindowWidth(), ci::app::getWindowHeight());
}

ci::gl::Texture2dRef TextureNode::getInputTexture(int frame, boost::any texInput)
{
	if (texInput.empty()) {
		return nullptr;
	}

	ci::gl::Texture2dRef tex = boost::any_cast<ci::gl::Texture2dRef>(texInput);

	if (tex->getWidth() != mWidth || tex->getHeight() != mHeight) {
		mWidth = tex->getWidth();
		mHeight = tex->getHeight();

		mFbo = ci::gl::Fbo::create(mWidth, mHeight);
	}

	return tex;
}

void TextureNode::draw()
{
	ci::gl::ScopedFramebuffer fb(mFbo);

	ci::gl::ScopedViewport vp(ci::ivec2(0), mFbo->getSize());
	ci::gl::pushMatrices();
	ci::gl::setMatricesWindow(mFbo->getSize());

	ci::gl::clear(ci::Color(0, 0, 0));

	ci::gl::drawSolidRect(mFbo->getBounds());

	ci::gl::popMatrices();
}

ci::gl::Texture2dRef TextureNode::getTexture()
{
	return mFbo->getColorTexture();
}

ci::vec2 TextureNode::getSize()
{
	return ci::vec2(mWidth, mHeight);
}

