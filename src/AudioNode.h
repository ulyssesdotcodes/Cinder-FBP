#pragma once

#include "Node.h"

class AudioNode : Node {

protected:
	void update(int frame);

public:
	AudioNode();
};