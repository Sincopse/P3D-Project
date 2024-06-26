#include "shader.h"

namespace objr {

	void Shader::Create(ShaderInfo* shaders)
	{
		// Compile and Load shaders to program (c�digo feito pelo stor)
		program_ = LoadShaders(shaders);
		if (!program_) exit(EXIT_FAILURE);
		glUseProgram(program_);
	}

	// Uniform mat4
	void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value) const {
		glProgramUniformMatrix4fv(program_, GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
	}

	// Uniform mat3
	void Shader::SetUniformMatrix3fv(const std::string& name, glm::mat3 value) const {
		glProgramUniformMatrix3fv(program_, GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
	}

	// Uniform vec3
	void Shader::SetUniform3fv(const std::string& name, glm::vec3 value) const {
		glProgramUniform3fv(program_, GetUniformLocation(name), 1, value_ptr(value));
	}

	// Uniform float
	void Shader::SetUniform1f(const std::string& name, float value) const {
		glProgramUniform1f(program_, GetUniformLocation(name), value);
	}

	// Pegar a localiza��o do uniform
	unsigned int Shader::GetUniformLocation(const std::string& name) const {
		GLint location = glGetProgramResourceLocation(program_, GL_UNIFORM, name.c_str());

		if (location == -1) std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
		return location;
	}


	GLchar* Shader::ReadShader(const char* filename) {
		// Abre o ficheiro 'filename' em bin�rio, e coloca-se na �ltima posi��o do ficheiro.
		std::ifstream ficheiro(filename, std::ifstream::ate | std::ifstream::binary);
		// Se o ficheiro foi aberto.
		if (ficheiro.is_open()) {
			// Leitura da pr�xima posi��o de leitura.
			std::streampos tamanhoDoFicheiroEmBytes = ficheiro.tellg();
			// Reposiciona a leitura do ficheiro no seu in�cio.
			ficheiro.seekg(0, std::ios::beg);

			// Aloca��o de espa�o de mem�ria para dados do ficheiro.
			GLchar* source = new GLchar[int(tamanhoDoFicheiroEmBytes) + 1];
			// Leitura do ficheiro para o array 'source'.
			ficheiro.read(source, tamanhoDoFicheiroEmBytes);
			// Fecha a string.
			source[tamanhoDoFicheiroEmBytes] = 0;

			// Fecha o ficheiro.
			ficheiro.close();

			// Retorna o endere�o da string alocada.
			return const_cast<GLchar*>(source);
		}
		else {
			std::cerr << "Erro ao abrir o ficheiro '" << filename << "'" << std::endl;
		}

		return nullptr;
	}

	GLuint Shader::LoadShaders(ShaderInfo* shaders) {
		if (shaders == nullptr) return 0;

		// Cria um objeto de programa
		GLuint program = glCreateProgram();

		for (GLint i = 0; shaders[i].type != GL_NONE; i++) {
			// Cria um objeto shader
			shaders[i].shader = glCreateShader(shaders[i].type);

			// Efetua a leitura do c�digo do shader
			const GLchar* source = ReadShader(shaders[i].filename);
			// Se n�o conseguir ler o c�digo
			if (source == NULL) {
				DestroyShaders(shaders);

				return 0;
			}

			// Carrega o c�digo do shader
			glShaderSource(shaders[i].shader, 1, &source, NULL);
			delete[] source;

			// Compila o shader
			glCompileShader(shaders[i].shader);

			// Verifica o estado da compila��o
			GLint compiled;
			glGetShaderiv(shaders[i].shader, GL_COMPILE_STATUS, &compiled);
			// Em caso de erro na compila��o
			if (!compiled) {
				DestroyShaders(shaders);

				return 0;
			}

			// Anexa o shader ao programa
			glAttachShader(program, shaders[i].shader);
		}

		// Linka o programa
		glLinkProgram(program);

		// Verifica o estado do processo de linkagem
		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		// Em caso de erro na linkagem
		if (!linked) {
			DestroyShaders(shaders);

			return 0;
		}

		return program;
	}

	void Shader::DestroyShaders(ShaderInfo* shaders) {
		// Destr�i os shaders que tinham criados
		for (int j = 0; shaders[j].type != GL_NONE; j++) {
			// Se tem um shader v�lido (i.e., != 0)
			if (shaders[j].shader != 0)
				glDeleteShader(shaders[j].shader);
			shaders[j].shader = 0;
		}
	}
}