#include "AudioNode.h"

void AudioNode::update(int frame)
{

	mAccumulatedSound = 0.0;

	auto ctx = audio::Context::master();

	mInputNode = ctx->createInputDeviceNode();

	auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
	mMonitor = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

	mInputNode >> mMonitor;

	mInputNode->enable();
	ctx->enable();

	app::getWindow()->setTitle(mInputNode->getDevice()->getName());

	mMult = 2.0;
}

AudioNode::AudioNode()
{
}
