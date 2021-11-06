#include "main.hpp"

Application::Application() {
	this->window = new WindowEngine();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
}

void Application::loop() {
	ObjectProvider provider = ObjectProvider();
	vector<ShaderInfo> shaders = {
			{ GL_VERTEX_SHADER, "resources/shaders/shader.vert" },
			{ GL_FRAGMENT_SHADER, "resources/shaders/shader.frag" },
			{ GL_NONE, NULL }
	};
	vector<Entity> entities = {
		Entity(
			provider.get("resources/bar.obj"),
			shaders, 
			vec4(0.39f, 0.83f, 0.71f, 1.0f),
			glm::translate(mat4(1), vec3(0.5, 1.0, 1.0))
		),
		Entity(
			provider.get("resources/box.obj"), 
			shaders, 
			vec4(0.81f, 0.64f, 0.6f, 1.0f),
			glm::scale(mat4(1), vec3(0.5f, 0.5f, 0.5f))
		)
	};
	Scene* scene = new Scene(entities);
	CommandService::getInstance()->setCamera(scene->getCamera());
	while (this->window->shouldClose()) {
		scene->render();
		this->window->render();
		Debug::getInstance()->countFrame();
	}
}

void Application::detroy() {
	// kill them all
}

