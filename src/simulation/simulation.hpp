#pragma once
#include "../entity/entity.hpp"
#include "../scene/scene.hpp"
#include "../configuration/config.hpp"

class Gravity {
private:
	const float ACCELERATION = 9.80665f;
public:
	void apply(vector<Entity*>*);
};

class Frametime {
private:
	static Frametime* instance;
	Frametime();

	double framerate;
	double frametime;

	double lastFrameTime = 0.0;
	double currentFrameTime = 0.0;
	double timeFrameDiff = 0.0;
	size_t frameCounter = 0;
public:
	static Frametime* getInstance();
	void countFrame();
	double getFramerate();
	double getFrametime();
	double getDelta();
};

class Simulator {
private:
	size_t iterations = 25;
public:
	void update(Scene* scene);
};