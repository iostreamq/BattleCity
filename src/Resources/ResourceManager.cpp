#include "ResourceManager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG //что ето 
#include "stb_image.h"
//#include "external/glm/vec2.hpp"

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

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
		return it->second;

	std::cerr << "Can`t find shader" << std::endl;
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

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_TexturesMap.find(textureName);
	if (it != m_TexturesMap.end())
		return it->second;

	std::cerr << "Can`t find texture" << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::loadSprites(const std::string& spriteName, 
															   const std::string& textureName,
															   const std::string& shaderName,
															   const unsigned int spriteWidth, 
															   const unsigned int spriteHeight,
															   std::string&& subTextureName)
{
	std::shared_ptr<Renderer::Texture2D> pTexture = getTexture(textureName);
	if (!pTexture) {
		std::cerr << "Can`t find texture" << textureName <<"for the sprite" << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderProgram> pShader = getShaderProgram(shaderName);

	if (!pShader) {
		std::cerr << "Can`t find shader" << shaderName << "for the sprite" << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Sprite>& DefaultSprite = m_SpritesMap.emplace(spriteName, 
																	        std::make_shared<Renderer::Sprite>(pTexture, 
																			std::move(subTextureName),
																			pShader,																			
																			glm::vec2(0.f, 0.f),
																		    glm::vec2(spriteWidth, spriteHeight))).first->second;
	return DefaultSprite; 
}


std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTextureAtlas(std::string&& textureName,
																	  std::string&& texturePath, 
																	  std::vector<std::string> vecNamesOfSubTex,
																	  const unsigned int subTextureWidth, 
																	  const unsigned int subTextureHeight)
{
	auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));
	if (pTexture) 
	{
		 unsigned int textureWidth = pTexture->getWidth();
		 unsigned int textureHeight = pTexture->getHeight();
		 unsigned int currentSubTextureOffsetX = 0;
		 unsigned int currentSubTextureOffsetY = textureHeight;

		 for (auto&& currentSubTextureName : vecNamesOfSubTex) 
		 {
			 glm::vec2 leftBottomUV(static_cast<float>(currentSubTextureOffsetX) / textureWidth, static_cast<float>(currentSubTextureOffsetY - subTextureHeight) / textureHeight); // переводим в нормированные коорды(ну и все равно нам потом накладывать на объект который уже в clip space так что по-любому нормированные)
			 glm::vec2 rightTopUV(static_cast<float>(currentSubTextureOffsetX + subTextureWidth) / textureWidth, static_cast<float>(currentSubTextureOffsetY) / textureHeight); 
			 pTexture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

			 currentSubTextureOffsetX += subTextureWidth;	
			 if (currentSubTextureOffsetX >= textureWidth) {
				 
				 currentSubTextureOffsetX = 0;
				 currentSubTextureOffsetY -= subTextureHeight;
			 }

		 }

	}
	return pTexture;
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
