#pragma once

#include "ProcessNode.h"

class TextureNode : public ProcessNode {
private:
	std::string mPath;

protected:
	void update(int frame) override;

public:
	TextureNode(std::string name);
};