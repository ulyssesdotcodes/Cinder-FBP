#include "VideoNode.h"

#include "cinder/app/App.h"

using namespace ci;

VideoNode::VideoNode(std::string name) : ProcessNode(name, { "path" }) { }


void VideoNode::update(int frame)
{
	std::string path = boost::any_cast<std::string>(getInputData("path", frame));
	if (path.compare(mPath) != 0) {
		setVideoFile(path);
		mPath = path;
	}

	mVideo.update();

	ci::gl::ScopedFramebuffer fb(mFbo);

	ci::gl::clear(ci::Color(0, 0, 0));

	mVideo.draw(0, 0);

	setData("tex", mFbo->getColorTexture());
}

void VideoNode::setVideoFile(std::string path)
{
	mVideo.loadMovie(path);

	gl::Texture::Format txfmt;
	txfmt.loadTopDown(true);

	gl::Fbo::Format fmt;
	fmt.setColorTextureFormat(txfmt);

	mFbo = gl::Fbo::create(mVideo.getWidth(), mVideo.getHeight(), fmt);

	mVideo.play();
}
