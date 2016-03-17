#include "TextureNode.h"

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

TextureNode::TextureNode(std::string name) : ProcessNode(name, {"path"}) { }

void TextureNode::update(int frame)
{
	std::string path = boost::any_cast<std::string>(getInputData("path", frame));
	if (path.compare(mPath) != 0) {
		setData("tex", ci::gl::Texture2d::create(ci::loadImage(ci::app::loadAsset(path))));
		mPath = path;
	}
}
