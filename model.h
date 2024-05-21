#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <vector>
#include <string>
#include <sstream>

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "world_transform.h"
#include "camera.h"
#include "shader.h"

using namespace glm;

typedef struct {
	glm::vec3 emissive;
	glm::vec3 ambient;  // Ka
	glm::vec3 diffuse;  // kd
	glm::vec3 specular; // ke
	float shininess;    // Expoente de reflex�o especular
} Material;

class Model {
public:
	void BindShader(Shader* shader) { shader_ = shader; }
	void Delete();

	void Render(vec3 position, vec3 orientation);
	void Install(bool);
	void AttribPointer() const;

	void Load(const std::string& obj_model_filepath);

	void SetCameraPosition(float x, float y, float z) { camera_.SetPosition(x, y, z); }

	VertexArray vao_;

	VertexBuffer vertex_buffer_;
	VertexBuffer color_buffer_;
	VertexBuffer normal_buffer_;
	IndexBuffer index_buffer_;
private:
	Shader* shader_ = nullptr;
	Material material;
	Camera camera_;

	std::vector<vec3> vertexes;
	std::vector<vec3> colors;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	mat4 projection = perspective(radians(45.0f), (float)640 / (float)480, 1.0f, 100.0f);
};
