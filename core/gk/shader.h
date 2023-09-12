#pragma once
#include <sstream>
#include <fstream>

using namespace std;

namespace shaderLibrary {
	string loadShaderSourceFromFile(const string& filePath);

	class Shader {
	public:
		Shader(const string& vertexShader, const string& fragmentShader);
		void use();
		void setInt(const string& name, int v) const;
		void setFloat(const string& name, float v) const;
		void setVec2(const string& name, float x, float y) const;
		void setVec3(const string& name, float x, float y, float z) const;
		void setVec4(const string& name, float x, float y, float z, float w) const;
	private:
		// OPENGL program handle
		unsigned int m_id;
	};
}