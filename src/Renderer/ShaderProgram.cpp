 #include"ShaderProgram.h" // почему в кавычках?
#include<iostream>


namespace Renderer {

	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) 
	{

	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint shaderID) {

		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str(); // что делает эта функция??
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
	
	   GLint success; // отличие GLint от GLuint?
	   glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);//флаг для проверки всех ошибок в шейдере//2 флаг: что мы хотим проверить(в данном случае скомпилировался или нет) 2 куда запишется результат функции
	  // теперь если есть ошибка смотрим чо как
	   if (!success) //как я int смог в скобки взять? 
	   {
		   GLchar infoLog[1024]; //1kb //почему пишем массив а не обычную строчку?
		   glGetShaderInfoLog(shaderID, sizeof(infoLog)/*mb oshibka*/, nullptr, infoLog); // id, размер в байтах, nullptr тк фиксированный размер буфреа(*length), буфер куда будем писать
		   std::cerr << "ERROR::SHADER: Compile time error:\n" << infoLog << std::endl; // что такое cerr?
		   return false;
	   }
	   return true;
	}
}