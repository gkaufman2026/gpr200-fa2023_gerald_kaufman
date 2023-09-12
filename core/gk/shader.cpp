#include "shader.h"
#include "ew/external/glad.h"

using namespace std;

namespace shaderLibrary {
	string shader::loadShaderSourceFromFile(const string& filePath) {
		ifstream fstream(filePath);
		if (!fstream.is_open()) {
			printf("Failed to load file %s", filePath);
			return {};
		}
		stringstream buffer;
		buffer << fstream.rdbuf();
		return buffer.str();
	}

	unsigned int createShader(GLenum shaderType, const char* sourceCode) {
		unsigned int shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &sourceCode, NULL);
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			printf("Failed to compile shader: %s", infoLog);
		}
		return shader;
	}

	unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
		unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		unsigned int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("Failed to link shader program: %s", infoLog);
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return shaderProgram;
	}

	Shader::Shader(const string& vertexShader, const string& fragmentShader) {
		string vertexShaderSource = loadShaderSourceFromFile(vertexShader.c_str());
		string fragmentShaderSource = loadShaderSourceFromFile(fragmentShader.c_str());
		m_id = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	}

	void Shader::use() {
		glUseProgram(m_id);
	}

	void Shader::setInt(const string& name, int v) const {
		glUniform1i(glGetUniformLocation(m_id, name.c_str()), v);
	}

	void Shader::setFloat(const string& name, float v) const {
		glUniform1f(glGetUniformLocation(m_id, name.c_str()), v);
	}

	void setVec2(const string& name, float x, float y) const {
		glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
	}

	void setVec3(const string& name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
	}

	void setVec4(const string& name, float x, float y, float z, float w) const {
		glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
	}
}