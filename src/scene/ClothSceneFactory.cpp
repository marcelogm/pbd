#include "scene.hpp"

Scene* ClothSceneFactory::build() {
	ObjectProvider provider = ObjectProvider();
	vector<ShaderInfo> shaders = {
			{ GL_VERTEX_SHADER, "resources/shaders/shader.vert" },
			{ GL_FRAGMENT_SHADER, "resources/shaders/shader.frag" },
			{ GL_NONE, NULL }
	};
	Entity* flag = new Entity(
		provider.get("resources/cloth.obj"),
		shaders,
		vec4(0.39f, 0.83f, 0.71f, 1.0f),
		mat4(1),
		false,
		2.0f
	);
	Entity* floor = new Entity(
		provider.get("resources/plane.obj"),
		shaders,
		vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::translate(mat4(1), vec3(0.0f, -10.0f, 0.0f)),
		false,
		2.0f
	);
	vector<Entity*> entities = { floor, flag };
	vector<Constraint*> c = vector<Constraint*>();

	vector<Constraint*> bendable = BendConstraintFactory().create(flag, {});
	c.insert(c.end(), bendable.begin(), bendable.end());
	vector<Constraint*> rigid = RidigBodyConstraintFactory().create(flag);
	c.insert(c.end(), rigid.begin(), rigid.end());
	Scene* scene = new Scene(
		entities,
		new Camera(vec3(12.0f, 0.0f, 13.0f), vec3(-0.5f, 0.0f, -0.7), -130, 0),
		c
	);
	return scene;
}