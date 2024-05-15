#pragma once

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "model.h"
#include "camera.h"

using namespace glm;

class Renderer {
public:
	Renderer();
	~Renderer();

	void BindModel(Model* model);

	void Render(vec3 position, vec3 orientation);
	void Install(void);
	void Load(const std::string obj_model_filepath);

private:
	Model* model_;
	Camera camera_;

	mat4 projection = perspective(radians(45.0f), (float)(640 / 480), 1.0f, 100.0f);
};