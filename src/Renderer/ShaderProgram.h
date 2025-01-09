#pragma once 
#include<string>
#include<glad/glad.h> // voprsik pochemu glad

namespace Renderer{ // для чего namespace?
	
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader); // constr на вход соурс код шейдеров
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		bool use() const; //влючении наших шейдеров

	private:
		bool m_isCompiled = false; // проверка компиляции или линковки
		GLuint m_ID = 0; // ID SHARED PROGRAM
	};

}
