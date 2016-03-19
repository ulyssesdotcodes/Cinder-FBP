#include "NodeFactory.h"

#include "AudioNode.h"
#include "DataNode.h"
#include "FlattenNode.h"
#include "ScaleByNode.h"
#include "RenderNode.h"
#include "TextureNode.h"
#include "VideoNode.h"

NodeFactory::NodeFactory()
{
	mClassMap["AudioNode"] = [](std::string name) { return std::make_shared<AudioNode>(name); };
	mClassMap["FlattenNode"] = [](std::string name) { return std::make_shared<FlattenNode>(name); };
	mClassMap["ScaleByNode"] = [](std::string name) { return std::make_shared<ScaleByNode>(name); };
	mClassMap["RenderNode"] = [](std::string name) { return std::make_shared<RenderNode>(name); };
	mClassMap["TextureNode"] = [](std::string name) { return std::make_shared<TextureNode>(name); };
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
