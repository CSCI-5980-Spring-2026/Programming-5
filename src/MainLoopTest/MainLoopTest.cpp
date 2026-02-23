/* Programming 5: Cameras, Materials, and Shaders
 * CSCI 5980, Spring 2026, University of Minnesota
 * Instructor: Evan Suma Rosenberg <suma@umn.edu>
 * License: Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
 */ 


#include "TestCube.hpp"

#include <GopherEngine/Core/MainLoop.hpp>
#include <GopherEngine/Resource/MeshFactory.hpp>
using namespace GopherEngine;

#include <iostream>
using namespace std;

// A simple subclass of MainLoop to test that the main loop is working
// and the window, scene, and node classes are functioning correctly
class MainLoopTest: public MainLoop
{
	public:
		// Constructor and destructor
		MainLoopTest();
		~MainLoopTest();

	private:

		// Override the pure virtual functions from MainLoop
		void configure() override;
		void initialize() override;
		void update(float delta_time) override;
};


MainLoopTest::MainLoopTest() {

}

MainLoopTest::~MainLoopTest() {

}

void MainLoopTest::configure() {

	window_.set_title("CSCI 5980 Programming 5");
}

void MainLoopTest::initialize() {
	
	scene_->create_default_camera();
	
	// Create a single node in the scene to test that the update and draw functions are working
	auto node = scene_->create_node();

	// Add a cube drawable
	node->add_component(make_shared<TestCube>());
	
}

void MainLoopTest::update(float delta_time) {

}

int main()
{
	// Create an instance of the MainLoop subclass and start the main game loop
	MainLoopTest app;
	return app.run();
}