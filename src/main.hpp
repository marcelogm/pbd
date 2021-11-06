#pragma once
#pragma GCC optimize("O1")
#pragma warning(disable:6011)

#include <iostream>
#include "gui/gui.hpp"
#include "scene/scene.hpp"

class Debug {
private:
	static Debug* instance;
	Debug();

	double framerate;
	double frametime;

	double lastFrameTime = 0.0;
	double currentFrameTime = 0.0;
	double timeFrameDiff = 0.0;
	size_t frameCounter = 0;
public:
	static Debug* getInstance();
	void countFrame();
	double getFramerate();
	double getFrametime();
};

class Application {
private:
	GLuint vertexArray;
	WindowEngine* window;
public:
	void loop();
	void detroy();
	Application();
};