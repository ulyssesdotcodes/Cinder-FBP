#include "SplitSpectrumNode.h"

SplitSpectrumNode::SplitSpectrumNode(std::string name) : ProcessNode(name, { "spectrum", "splits" })
{
}

void SplitSpectrumNode::update(int frame)
{
	std::vector<float> buffer = boost::any_cast<std::vector<float>>(getInputData("spectrum", frame));
	float binCount = boost::any_cast<float>(getInputDataAsFloat("splits", frame));
	std::vector<float> bins(binCount);
	int binSize = buffer.size() * 0.5 / binCount;

	for (std::vector<float>::size_type i = 0; i < buffer.size() * 0.5; i++) {
		int bin = i / binSize;

		// Just discard the last one if it fits perfectly.
		if(bin < bins.size()) {
			bins[bin] += glm::pow(buffer[i], 2.0 - ((float) i / (float) buffer.size()));
		}
	}

	for (std::vector<float>::iterator it = bins.begin(); it != bins.end(); ++it) {
		*it = *it * 1 / binSize;
	}

	setData("splits", bins);
}

