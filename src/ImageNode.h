#pragma once

#include "ProcessNode.h"

class ImageNode : public ProcessNode {
private:
	std::string mPath;

protected:
	void update(int frame) override;

public:
	ImageNode(std::string name);
};