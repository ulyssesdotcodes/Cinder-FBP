#pragma once

#include <boost/any.hpp>

class Node {
public:
	virtual boost::any getData(std::string id, int frame) = 0;
};
