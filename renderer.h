#pragma once

#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "shader.h"
#include "model.h"
#include "camera.h"
#include "world_transform.h"

using namespace glm;

class Renderer {
public:
	void BindShader(Shader* shader) { shader_ = shader; }
	void BindModel(Model* model) { model_ = model; }

	void Render(vec3 position, vec3 orientation);
	void Install(void);
	void Load(const std::string obj_model_filepath);

	void SetCameraPosition(float x, float y, float z) { camera_.SetPosition(x, y, z); }

private:
	Shader* shader_ = nullptr;
	Model* model_ = nullptr;
	Camera camera_;

	std::vector<float> vertices;
	std::vector<float> colors;
	std::vector<float> normals;
	std::vector<int> indexes;

	mat4 projection = perspective(radians(45.0f), (float)(640 / 480), 1.0f, 100.0f);
};