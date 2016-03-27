#pragma once

#include <boost/any.hpp>

class FBPNode {
public:
	virtual boost::any getData(std::string id, int frame) = 0;
	virtual boost::any getData(std::string id) = 0;
};
