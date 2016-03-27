#include "SplitSpectrumNode.h"

SplitSpectrumNode::SplitSpectrumNode(std::string name) : ProcessNode(name, { "spectrum", "splits", "sectionStart", "sectionPercent", "damping" })
{
}

void SplitSpectrumNode::update(int frame)
{
	if (getInputData("spectrum", frame).empty() || getInputData("splits", frame).empty()) {
		setData("splits", boost::any());
		return;
	}

	std::vector<float> buffer = boost::any_cast<std::vector<float>>(getInputData("spectrum", frame));
	float binCount = boost::any_cast<float>(getInputDataAsFloat("splits", 0, frame));
	float sectionStart = boost::any_cast<float>(getInputDataAsFloat("sectionStart", 0, frame));
	float sectionPercent = boost::any_cast<float>(getInputDataAsFloat("sectionPercent", 0.5, frame));
	float damping = boost::any_cast<float>(getInputDataAsFloat("damping", 0, frame));
	std::vector<float> prevBins(binCount);
	if (!getData("splits").empty()) {
		prevBins = boost::any_cast<std::vector<float>>(getData("splits"));
		if (prevBins.size() != binCount) {
			prevBins = std::vector<float>(binCount);
		}
	}
	std::vector<float> bins(binCount);
	int binSize = buffer.size() * sectionPercent / binCount;
	int offset = buffer.size() * sectionStart;

	for (std::vector<float>::size_type i = 0; i < buffer.size() * sectionPercent; i++) {
		int bin = i / binSize;

		// Just discard the last one if it fits perfectly.
		if(bin < bins.size() && i + offset < buffer.size()) {
			bins[bin] += glm::pow(buffer[i + offset], 2.0 - ((float) i / (float) buffer.size()));
		}
	}

	for (std::vector<float>::size_type i = 0; i < binCount; i++) {
		if (bins[i] < prevBins[i]) {
			bins[i] += (prevBins[i] - bins[i]) * damping;
		}
	}

	setData("splits", bins);
}

