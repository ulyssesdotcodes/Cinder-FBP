#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FBPApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void FBPApp::setup()
{
}

void FBPApp::mouseDown( MouseEvent event )
{
}

void FBPApp::update()
{
}

void FBPApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( FBPApp, RendererGl )
