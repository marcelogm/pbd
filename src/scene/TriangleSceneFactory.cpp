#include "scene.hpp"

Scene* TriangleSceneFactory::build() {
	ObjectProvider provider = ObjectProvider();
	vector<ShaderInfo> shaders = {
			{ GL_VERTEX_SHADER, "resources/shaders/shader.vert" },
			{ GL_FRAGMENT_SHADER, "resources/shaders/shader.frag" },
			{ GL_NONE, NULL }
	};
	auto f1 = vec3(-1.f, 0.f, 0.0f);
	auto f2 = vec3(1.0f, 0.f, 1.0f);
	Configuration::getInstance()->getSimulationParams()->iterations = 30; 
	Configuration::getInstance()->getSimulationParams()->stiffness = 0.99;
	Entity* b1 = getDebugBox(f1, 0.2, shaders);
	Entity* b2 = getDebugBox(f2, 0.2, shaders);
	Entity* triangle = new Entity(
		provider.get("resources/triangle.obj"),
		shaders,
		vec4(0.39f, 0.83f, 0.71f, 1.0f),
		mat4(1),
		true,
		1.0f,
		false
	);
	vector<Entity*> entities = { triangle, b1, b2 };
	vector<Constraint*> constraints = vector<Constraint*>();
	vector<Constraint*> rigid = RidigBodyConstraintFactory().create(triangle);
	constraints.push_back(new AnchorConstraint(triangle, 0, f1));
	constraints.push_back(new AnchorConstraint(triangle, 1, f2));
	constraints.insert(constraints.end(), rigid.begin(), rigid.end());
	triangle->getObject()->getVertices()->at(2) = vec3(2.0f, 2.0f, 2.0f);
	Scene* scene = new Scene(
		entities,
		new Camera(vec3(0.4f, -1.0f, 4.75f), vec3(-0.4f, 0.0f, -0.92), -113, 0),
		constraints
	);
	return scene;
}

Entity* TriangleSceneFactory::getDebugBox(vec3 position, float scale, vector<ShaderInfo> shaders) {
	ObjectProvider provider = ObjectProvider();
	return new Entity(
		provider.get("resources/sphere.obj"),
		shaders,
		vec4(0.f, 0.10f, 0.20f, 1.0f),
		glm::scale(glm::translate(mat4(1), position), vec3(scale)),
		false,
		1.0f,
		false
	);
}
