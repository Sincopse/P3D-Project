#pragma once

#include <iostream>
#include <fstream>
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include <GL/glew.h>
#include <string>

/*****************************************************************************
					 GLuint LoadShaders(ShaderInfo*);

Descri��o:
----------
Recebe um array de estruturas ShaderInfo.
Cada estrutura cont�m:
- tipo de shader. No OpenGL 4.x poder� ser um dos seguintes valores:
  - GL_COMPUTE_SHADER
  - GL_VERTEX_SHADER
  - GL_TESS_CONTROL_SHADER
  - GL_TESS_EVALUATION_SHADER
  - GL_GEOMETRY_SHADER
  - GL_FRAGMENT_SHADER
- apontador para uma C-string, que cont�m o nome do ficheiro com c�digo do shader
- valor que referencia o objeto shader criado

O array de estruturas dever� terminar com o valor GL_NONE no campo 'type'.
Exemplo:
ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER, "triangles.vert" },
	{ GL_FRAGMENT_SHADER, "triangles.frag" },
	{ GL_NONE, NULL }
};

Retorno:
--------
Em caso de sucesso, a fun��o retorna o valore que referencia o objeto programa.
Em caso de erro, ser� retornado o valor zero (0).

*****************************************************************************/
typedef struct {
	GLenum      type;
	const char* filename;
	GLuint      shader;
} ShaderInfo;

class Shader {
private:
	GLuint program_;

public:
	void Create(ShaderInfo* shaders);

	void Bind() { glUseProgram(program_); }

	void SetUniformMatrix4fv(const std::string& name, glm::mat4 mat);

	unsigned int GetUniformLocation(const std::string& name);

	GLchar* ReadShader(const char* filename);
	GLuint LoadShaders(ShaderInfo* shaders);
	void DestroyShaders(ShaderInfo* shaders);
};