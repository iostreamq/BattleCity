#pragma once 
#include<string>
#include<glad/glad.h> // voprsik pochemu glad
#include"external/glm/mat4x4.hpp"

namespace RenderEngine{ 

	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader); // constr на вход соурс код шейдеров // какая разница передаеи string или char??
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const; //влючении наших шейдеров
		void setInt(const std::string& name, const GLint value);
		void setMatrix4(const std::string& name, const glm::mat4& matrix); // а если передам единичную

		ShaderProgram() = delete; // запрещаем конструктор без параметров чтобы не создал шейдер без сурс кода
		ShaderProgram(ShaderProgram&) = delete; //запрещаем конструировать(копи констр) одну шейдернуб программу из другой шейдерной программы(потом в деструкторе проблема из 2 шейдеров с одним m_ID)
		ShaderProgram& operator = (const ShaderProgram&) = delete; // тоже самое что и 2-ое
		ShaderProgram& operator=(ShaderProgram&&) noexcept;
		ShaderProgram(ShaderProgram&&) noexcept;
		void ShaderProgram::unuse() const;

	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID); // shaderID перадем m_ID и по референсу записываем значение id... , GLenum?? 
		bool m_isCompiled = false; // проверка линковки
		GLuint m_ID = 0; // ID SHARED PROGRAM
	};

}
