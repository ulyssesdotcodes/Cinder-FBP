#include "NodeFactory.h"

#include "AudioNode.h"
#include "DataNode.h"
#include "DotsNode.h"
#include "FlattenNode.h"
#include "ScaleByNode.h"
#include "SplitSpectrumNode.h"
#include "RenderNode.h"
#include "ImageNode.h"
#include "VideoNode.h"

NodeFactory::NodeFactory()
{
	mClassMap["AudioNode"] = [](std::string name) { return std::make_shared<AudioNode>(name); };
	mClassMap["DotsNode"] = [](std::string name) { return std::make_shared<DotsNode>(name); };
	mClassMap["FlattenNode"] = [](std::string name) { return std::make_shared<FlattenNode>(name); };
	mClassMap["ImageNode"] = [](std::string name) { return std::make_shared<ImageNode>(name); };
	mClassMap["ScaleByNode"] = [](std::string name) { return std::make_shared<ScaleByNode>(name); };
	mClassMap["SplitSpectrumNode"] = [](std::string name) { return std::make_shared<SplitSpectrumNode>(name); };
	mClassMap["RenderNode"] = [](std::string name) { return std::make_shared<RenderNode>(name); };
	mClassMap["VideoNode"] = [](std::string name) { return std::make_shared<VideoNode>(name); };
}

std::shared_ptr<ProcessNode> NodeFactory::createInstance(std::string className, std::string instanceName) const
{
	return mClassMap.at(className)(instanceName);
}

std::shared_ptr<DataNode> NodeFactory::createDataNode(boost::any data) const
{
	return std::make_shared<DataNode>(data);
}
