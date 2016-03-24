#include "FadeNode.h"

FadeNode::FadeNode(std::string name) : ProcessNode(name, { "tex", "prevTex" }) { }

void FadeNode::update(int frame)
{
}
