#include "ResourceManager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG //что ето 
#include "stb_image.h"

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

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true); // нужный порядок байтов
	unsigned char* pixels/*почему char*/ = stbi_load(std::string/*почему явно преобразовываем в стринег если m_Path и так стринг??*/(m_Path + texturePath).c_str(), &width, &height, &channels, 0);// 0- сколько каналов мы собираемся получить
	if (!pixels) {
		std::cerr << "Can`t load image: " << texturePath << std::endl;
		return nullptr;
	}
	std::shared_ptr<Renderer::Texture2D>& DefaultTexture = m_TexturesMap.emplace(textureName,std::make_shared<Renderer::Texture2D>(width, height, pixels, 
		                                                                         channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;
	if (!DefaultTexture) {
		std::cerr << "Problem with shared_ptr! " << DefaultTexture << std::endl;
		return nullptr;
	}

	stbi_image_free(pixels);
	return DefaultTexture;
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
