 #include"ShaderProgram.h" // почему в кавычках?
#include<iostream>
#include"external/glm/gtc/type_ptr.hpp"



namespace RenderEngine {

	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) 
	{
		GLuint vertexShaderID = 0; 
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID = 0;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
			glDeleteShader(vertexShaderID); // создается же динам объект на видеокарте поэтому обязательно удаляем чтоб без утечек и прочей хуйни
			return;
		}
		
		m_ID = glCreateProgram();
		glAttachShader(m_ID,vertexShaderID);
		glAttachShader(m_ID,fragmentShaderID);
		glLinkProgram(m_ID);
		 
		GLint success;
		glGetProgramiv(m_ID, GL_COMPILE_STATUS, &success); 
		if (!success) 
		{
			GLchar infoLog[1024]; 
			glGetProgramInfoLog(m_ID, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl; 
			//?return;
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(fragmentShaderID);
		glDeleteShader(vertexShaderID);
		
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		if (this == &shaderProgram) return *this;

		glDeleteProgram(m_ID);

		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;
		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{

		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str(); // что делает эта функция??
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
	
	   GLint success; 
	   glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);//флаг для проверки всех ошибок в шейдере//2 флаг: что мы хотим проверить(в данном случае скомпилировался или нет) 2 куда запишется результат функции
	  // теперь если есть ошибка смотрим чо как
	   if (!success) //как я int смог в скобки взять? 
	   {
		   GLchar infoLog[1024]; //1kb //почему пишем массив а не обычную строчку?
		   glGetShaderInfoLog(shaderID, sizeof(infoLog)/*mb oshibka*/, nullptr, infoLog); // id, размер в байтах, nullptr тк фиксированный размер буфреа(*length), буфер куда будем писать
		   std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl; // что такое cerr?
		   return false;
	   }
	   return true;
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::unuse() const {
		glUseProgram(0);
	}
	 void ShaderProgram::use() const  {
		 glUseProgram(m_ID);
	  }
	 void ShaderProgram::setInt(const std::string& name, const GLint value)
	 {
		 glUniform1i(glGetUniformLocation(m_ID,name.c_str()), value);
	 }

	 void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix)
	 {
		 glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix)); // v- vec f - floatr
	 }
	
	 
}