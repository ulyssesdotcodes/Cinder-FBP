#define WEBSOCKETPP_CPP11_CHRONO
#define WEBSOCKETPP_NO_EXCEPT

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "Graph.h"
#include "NodeFactory.h"
#include "RenderNode.h"
#include "TextureNode.h"
#include "VideoNode.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FBPApp : public App {
  public:
	void setup() override;
	void loadJson();
	void update() override;
	void draw() override;

private:
	Graph mGraph;
	NodeFactory mNodeFactory;
	gl::Texture2dRef mCurrentTex;
	params::InterfaceGlRef mParams;
};

void FBPApp::setup()
{
	mGraph.setJson("C:\\Users\\Ulysses\\Development\\FBP_2\\assets\\texture.json", mNodeFactory);

	mParams = params::InterfaceGl::create(getWindow(), "Load json", toPixels(ivec2(200, 300)));

	mParams->addButton("Load json", bind(&FBPApp::loadJson, this));
}

void FBPApp::loadJson()
{
	fs::path path = getOpenFilePath("");
	mGraph.setJson(path, mNodeFactory);
}

void FBPApp::update()
{
	mCurrentTex = boost::any_cast<gl::Texture2dRef>(mGraph.getData("tex", app::getElapsedFrames()));
}

void FBPApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	gl::draw(mCurrentTex);

	mParams->draw();
}

CINDER_APP( FBPApp, RendererGl )
