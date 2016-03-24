#define WEBSOCKETPP_CPP11_CHRONO
#define WEBSOCKETPP_NO_EXCEPT

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "Graph.h"
#include "NodeFactory.h"
#include "RenderNode.h"
#include "ImageNode.h"
#include "VideoNode.h"
#include "WebSocketServer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class FBPApp : public App {
  public:
	void setup() override;
	void loadJson();
	void update() override;
	void draw() override;
	void onMessage(std::string msg);

private:
	Graph mGraph;
	std::shared_ptr<NodeFactory> mNodeFactory;
	gl::Texture2dRef mCurrentTex;
	params::InterfaceGlRef mParams;
	WebSocketServer mServer;
	boolean mRendering;
};

void FBPApp::setup()
{
	mRendering = false;
	mNodeFactory = make_shared<NodeFactory>();
	mGraph = Graph(mNodeFactory);

	//mGraph.setJson("C:\\Users\\Ulysses\\Development\\FBP_3\\assets\\texture.json", mNodeFactory);

	mParams = params::InterfaceGl::create(getWindow(), "Load json", toPixels(ivec2(200, 300)));

	mParams->addButton("Load json", bind(&FBPApp::loadJson, this));

	mServer.connectMessageEventHandler(bind(&FBPApp::onMessage, this, std::placeholders::_1));

	mServer.connectOpenEventHandler([&]() {
		app::console() << "Opened" << std::endl;
	});

	mServer.connectSocketInitEventHandler([&](websocketpp::connection_hdl handle) {
		//asio::ip::tcp::socket* socket = mServer.getSocket();
		auto con = mServer.getServer().get_con_from_hdl(mServer.getHandle());
		std::vector<std::string> sps = con->get_requested_subprotocols();
		if (sps.size() > 0) {
			con->select_subprotocol(sps[0]);
		}
		//if (socket != nullptr) {
		//	asio::error_code ec;
		//	asio::ip::address address = socket->remote_endpoint().address();
		//	app::console() << "Connected: " << address.to_string() << socket->remote_endpoint().port() << std::endl;
		//}
	});

	mServer.listen(3569);
}

void FBPApp::loadJson()
{
	fs::path path = getOpenFilePath("");
	mGraph.setJson(path);
}

void FBPApp::update()
{
	mServer.poll();

	boost::any tex = mGraph.getData("tex", app::getElapsedFrames());
	if (tex.empty()) {
		mRendering = false;
	}
	else {
		mRendering = true;
		mCurrentTex = boost::any_cast<gl::Texture2dRef>(tex);
	}

}

void FBPApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 

	if (!mRendering) {
		return;
	}

	gl::ScopedViewport vp(ivec2(0), mCurrentTex->getSize());
	gl::pushMatrices();
	gl::setMatricesWindow(mCurrentTex->getSize());

	ci::gl::clear(ci::Color(0, 0, 0));

	gl::drawSolidRect(mCurrentTex->getBounds());

	gl::pushMatrices();

	gl::draw(mCurrentTex);

	gl::popMatrices();
}

void FBPApp::onMessage(std::string msg)
{
	JsonTree json = JsonTree(msg); 
	mGraph.handleMessage(JsonTree(msg), bind(&WebSocketServer::write, &mServer, std::placeholders::_1));
}

CINDER_APP( FBPApp, RendererGl )
