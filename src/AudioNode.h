#pragma once

#include "ProcessNode.h"

#include "cinder/audio/audio.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

class AudioNode : public ProcessNode {
public:
	AudioNode(std::string name);

protected:
	void update(int frame);

private:
	ci::audio::InputDeviceNodeRef mFBPInputNode;
	ci::audio::MonitorSpectralNodeRef mMonitor;
	float mAccumulatedVolume;
};