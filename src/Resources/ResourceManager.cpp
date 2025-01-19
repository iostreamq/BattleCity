#include "ResourceManager.h"
#include <sstream>
#include <fstream>
#include <iostream>


ResourceManager::ResourceManager(const std::string& executablePath)
{
	 size_t found = executablePath.find_last_of("/\\");
	 m_Path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexShader = getFileString(vertexPath);
	if (vertexPath.empty()) {
		std::cerr << "ERR::STR-SHR-VERTEX IS EMPTY" << std::endl;
		return nullptr;
	}
	std::string fragmentShader = getFileString(fragmentPath);
	if (fragmentPath.empty()) {
		std::cerr << "ERR::STR-SHR-FRAGMENT IS EMPTY" << std::endl;
		return nullptr;
	}
			
	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexShader, fragmentShader)).first->second;
	
	if (newShader->isCompiled()) {
			return newShader;
		}
		else
		{
			std::cerr << "ERR::ShaderProgram-Compile" << std::endl;
		}

      return nullptr;
}

std::string ResourceManager::getFileString(const std::string& AdditionalPath)
{
	std::ifstream shaderStr;
	shaderStr.open(m_Path + AdditionalPath, std::ios::in | std::ios::binary); 
	if (!shaderStr.is_open()) {
		std::cerr << "ERR::FILE_STR:File-open error" << std::endl;
		return std::string{};
	}
	std::stringstream bufShader; 
	bufShader << shaderStr.rdbuf();
	return bufShader.str();
}
