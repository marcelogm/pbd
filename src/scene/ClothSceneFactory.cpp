#include "scene.hpp"

Scene* ClothSceneFactory::build() {
	ObjectProvider provider = ObjectProvider();
	vector<ShaderInfo> shaders = {
			{ GL_VERTEX_SHADER, "resources/shaders/shader.vert" },
			{ GL_FRAGMENT_SHADER, "resources/shaders/shader.frag" },
			{ GL_NONE, NULL }
	};
	Entity* bar = new Entity(
		provider.get("resources/bar.obj"),
		shaders,
		vec4(0.39f, 0.83f, 0.71f, 1.0f),
		mat4(1),
		true,
		1.0f
	);
	Entity* floor = new Entity(
		provider.get("resources/plane.obj"),
		shaders,
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::translate(mat4(1), vec3(0.0f, -10.0f, 0.0f)),
		false,
		0.0f
	);
	vector<Entity*> entities = { floor, bar };
	vector<Constraint*> constraints = vector<Constraint*>();
	vector<Constraint*> rigid = RidigBodyConstraintFactory().create(bar);
	constraints.push_back(new AnchorConstraint(bar, 1, vec3(-0.100000, -0.100000, 2.000000)));
	constraints.push_back(new AnchorConstraint(bar, 3, vec3(-0.100000, 0.100000, 2.000000)));
	constraints.push_back(new AnchorConstraint(bar, 5, vec3(0.100000, -0.100000, 2.000000)));
	constraints.push_back(new AnchorConstraint(bar, 7, vec3(0.100000, 0.100000, 2.000000)));
	constraints.insert(constraints.end(), rigid.begin(), rigid.end());
	Scene* scene = new Scene(
		entities,
		new Camera(vec3(3.9f, 0.0f, 0.0f), vec3(-1.f, 0.0f, 8.7), -180, 0),
		constraints
	);
	return scene;
}