#pragma once

#include "ProcessNode.h"

#include "ciWMFVideoPlayer.h"

class VideoNode : public ProcessNode {
private:
	ciWMFVideoPlayer mVideo;
	ci::gl::GlslProgRef			mGlslVideoTexture;
	ci::gl::FboRef mFbo;
	std::string mPath;
	void setVideoFile(std::string path);

protected:
	void update(int frame) override;

public:
	VideoNode(std::string name);
};