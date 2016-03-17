#include "RenderNode.h"

RenderNode::RenderNode(std::string name) : ProcessNode(name, { "tex" }) { }

void RenderNode::update(int frame)
{
	setData("tex", getInputData("tex", frame));
}
