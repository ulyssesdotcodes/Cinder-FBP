#include "TransformNode.h"

TransformNode::TransformNode(std::string name) : ProcessNode(name, { "scale", "translate", "rotate", "pivot" })
{
}

void TransformNode::update(int frame)
{
}
