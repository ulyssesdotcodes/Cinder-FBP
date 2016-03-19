#include "AudioNode.h"

using namespace ci;

AudioNode::AudioNode(std::string name) : ProcessNode(name, {}), mAccumulatedVolume(0)
{
	auto ctx = audio::Context::master();
	mFBPInputNode = ctx->createInputDeviceNode();
	mMonitor = ctx->makeNode(new audio::MonitorSpectralNode(audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024)));

	mFBPInputNode >> mMonitor;

	mFBPInputNode->enable();
	audio::Context::master()->enable();
}

void AudioNode::update(int frame)
{
	float volume = mMonitor->getVolume();
	setData("volume", volume);

	mAccumulatedVolume += volume;
	setData("accumulatedVolume", mAccumulatedVolume);

	std::vector<float> spectrum = mMonitor->getMagSpectrum();
	setData("fft", spectrum);

	const float* bufferData = mMonitor->getBuffer().getData();
	std::vector<float> buffer{ bufferData, bufferData + mMonitor->getBuffer().getSize() };
	setData("buffer", buffer);

	float texSpectrum[1024 * 4];

	for (int i = 0; i < spectrum.size(); i++) {
		texSpectrum[i * 4] = spectrum[i];
		texSpectrum[i * 4 + 1] = buffer[i];
		texSpectrum[i * 4 + 2] = 0.0f;
		texSpectrum[i * 4 + 3] = 256.0f;
	}

	gl::Texture2dRef audioTex = gl::Texture::create(Surface32f(texSpectrum, 1024, 1, 4, SurfaceChannelOrder::RGBA));
	setData("audioTex", audioTex);
}
