#include "../ew/external/glad.h"
#include "shader.h"
#include <iostream>

using namespace std;

namespace shaderLib {
	string loadShaderSourceFromFile(const string& filePath) {
		ifstream fstream(filePath);
		if (!fstream.is_open()) {
			cout << "Failed to load file " << filePath;
			return {};
		}
		stringstream buffer;
		buffer << fstream.rdbuf();
		return buffer.str();
	}

	unsigned int createShader(GLenum shaderType, const char* sourceCode) {
		//Create a new vertex shader object
		unsigned int shader = glCreateShader(shaderType);
		//Supply the shader object with source code
		glShaderSource(shader, 1, &sourceCode, NULL);
		//Compile the shader object
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			//512 is an arbitrary length, but should be plenty of characters for our error message.
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
		//Attach each stage
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//Link all the stages together
		glLinkProgram(shaderProgram);
		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("Failed to link shader program: %s", infoLog);
		}
		//The linked program now contains our compiled code, so we can delete these intermediate objects
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return shaderProgram;
	}

	//// SHADER CLASS
	//ShaderLibrary::ShaderLibrary(const string& vertexShader, const string& fragmentShader) {
	//	string vertexShaderSource = loadShaderSourceFromFile(vertexShader.c_str());
	//	string fragmentShaderSource = loadShaderSourceFromFile(fragmentShader.c_str());
	//	m_id = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	//}

	//void ShaderLibrary::use() {
	//	glUseProgram(m_id);
	//}

	//void ShaderLibrary::setInt(const string& name, int v) const {
	//	glUniform1i(glGetUniformLocation(m_id, name.c_str()), v);
	//}

	//void ShaderLibrary::setFloat(const string& name, float v) const {
	//	glUniform1f(glGetUniformLocation(m_id, name.c_str()), v);
	//}

	//void setVec2(const string& name, float x, float y) const {
	//	glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
	//}

	//void setVec3(const string& name, float x, float y, float z) const {
	//	glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
	//}

	//void setVec4(const string& name, float x, float y, float z, float w) const {
	//	glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
	//}
}
