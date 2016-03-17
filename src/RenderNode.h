#pragma once

#include "ProcessNode.h"
#include <memory>

class RenderNode : public ProcessNode {
public:
	RenderNode(std::string name);
	void update(int frame) override;
};