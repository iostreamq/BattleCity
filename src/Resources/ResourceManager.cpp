#include "ResourceManager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG = //что ето ;
#include "stb_image.h"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include "../Game/Levels.h"
//#include "external/glm/vec2.hpp"

ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::m_TexturesMap;
ResourceManager::SpritesMap ResourceManager::m_SpritesMap;
ResourceManager::AnimatedSpritesMap ResourceManager::m_AnimatedSpritesMap;
std::string ResourceManager::m_Path;
std::vector<std::vector<std::string>> ResourceManager::m_levels;


 void ResourceManager::setExecutablePath(const std::string& executablePath)
{
	 size_t found = executablePath.find_last_of("/\\");
	 m_Path = executablePath.substr(0, found);
}

 void ResourceManager::unloadAllResources()
 {
	 m_shaderPrograms.clear(); /// зачемм
	 m_TexturesMap.clear();
	 m_SpritesMap.clear();
	 m_AnimatedSpritesMap.clear();
 }

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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
			
	std::shared_ptr<RenderEngine::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram>(vertexShader, fragmentShader)).first->second;
	
	if (newShader->isCompiled()) {
			return newShader;
		}
		else
		{
			std::cerr << "ERR::ShaderProgram-Compile" << std::endl;
		}

      return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
		return it->second;

	std::cerr << "Can`t find shader" << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	// Устанавливаем флаг для переворота изображения по вертикали
	stbi_set_flip_vertically_on_load(true);

	// Загружаем изображение. stbi_load вернет указатель на данные пикселей
	unsigned char* pixels = stbi_load(std::string(m_Path + texturePath).c_str(), &width, &height, &channels, 0);

	// Если не удалось загрузить изображение, выводим ошибку и возвращаем nullptr
	if (!pixels) {
		std::cerr << "Can`t load image: " << texturePath << std::endl;
		return nullptr;
	}

	// Создаем текстуру с загруженными данными и добавляем её в карту
	std::shared_ptr<RenderEngine::Texture2D>& DefaultTexture = m_TexturesMap.emplace(textureName, std::make_shared<RenderEngine::Texture2D>(width, height,
																					pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	// Если текстура не была создана, выводим ошибку
	if (!DefaultTexture) {
		std::cerr << "Problem with shared_ptr! " << DefaultTexture << std::endl;
		return nullptr;
	}

	// Освобождаем память, занятую пиксельными данными
	stbi_image_free(pixels);

	// Возвращаем ссылку на созданную текстуру
	return DefaultTexture;
}


std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_TexturesMap.find(textureName);
	if (it != m_TexturesMap.end())
		return it->second;

	std::cerr << "Can`t find texture" << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprites(const std::string& spriteName, 
															   const std::string& textureName,
															   const std::string& shaderName,
															   std::string&& subTextureName)
{
	std::shared_ptr<RenderEngine::Texture2D> pTexture = getTexture(textureName);
	if (!pTexture) {
		std::cerr << "Can`t find texture" << textureName <<"for the sprite" << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram> pShader = getShaderProgram(shaderName);

	if (!pShader) {
		std::cerr << "Can`t find shader" << shaderName << "for the sprite" << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Sprite>& DefaultSprite = m_SpritesMap.emplace(spriteName, 
																	        std::make_shared<RenderEngine::Sprite>(pTexture, 
																			std::move(subTextureName),
																			pShader																		
																			)).first->second; 
	return DefaultSprite; 
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManager::loadAnimatedSprites(const std::string& spriteName, 
														 				       const std::string& textureName, 
																			   const std::string& shaderName, 
																			   std::string&& subTextureName)
{
	std::shared_ptr<RenderEngine::Texture2D> pTexture = getTexture(textureName);
	if (!pTexture) {
		std::cerr << "Can`t find texture" << textureName << "for the sprite" << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram> pShader = getShaderProgram(shaderName);

	if (!pShader) {
		std::cerr << "Can`t find shader" << shaderName << "for the sprite" << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::AnimatedSprite>& DefaultSprite = m_AnimatedSpritesMap.emplace(spriteName,
		std::make_shared<RenderEngine::AnimatedSprite>(pTexture,
			std::move(subTextureName),
			pShader
			)).first->second;
	return DefaultSprite;
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManager::getAnimatedSprite(std::string&& spriteName)
{
	auto it = m_AnimatedSpritesMap.find(spriteName);
	if (it != m_AnimatedSpritesMap.end()) {
		return it->second;
	}
	std::cerr << "Can`t find this animated sprite" << spriteName << std::endl;
	return nullptr;
}


std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(std::string&& spriteName)
{
	SpritesMap::const_iterator it = m_SpritesMap.find(spriteName);
	if (it != m_SpritesMap.end()) {
		return it->second;
	}
	std::cerr << "Can`t find the sprite" << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(std::string&& textureName,
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

bool ResourceManager::loadJSONResources(const std::string&& JSONPath)
{
	const std::string JSONString = getFileString(JSONPath);
	if (JSONString.empty()) {
		std::cerr << "No JSON resources file" << std::endl;
		return false;
	}

	rapidjson::Document document; // документ который обозначает весь этот файл
	rapidjson::ParseResult parseResult = document.Parse(JSONString.c_str()); // EROOOOOOOOOOOOORSS
	if (!parseResult)
	{
		std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) <<"(" << parseResult.Offset() << ")" <<std::endl; //читабельный вид
		std::cerr << "In jasonFile: " << JSONString << std::endl;
		return false;
	}

	auto shadersIt = document.FindMember("shaders");
	if (shadersIt != document.MemberEnd()) 
	{
		for (const auto& currentShader : shadersIt->value.GetArray()) //animatedSpritesIt — это итератор на пару {ключ, значение},animatedSpritesIt->value — значение 
		{
			const std::string name = currentShader["name"].GetString();
			const std::string filePath_v = currentShader["filePath_v"].GetString();
			const std::string filePath_f = currentShader["filePath_f"].GetString();
			loadShaders(name, filePath_v, filePath_f);
		}
	}

	auto textureAtlasesIt = document.FindMember("textureAtlases");
	if (textureAtlasesIt != document.MemberEnd())
	{
		for (const auto& currentTextureAtlas : textureAtlasesIt->value.GetArray())
		{
			std::string name = currentTextureAtlas["name"].GetString();
			std::string filePath = currentTextureAtlas["filePath"].GetString();
			const unsigned int subTextureWidth = currentTextureAtlas["subTextureWidth"].GetUint();
			const unsigned int subTextureHeight = currentTextureAtlas["subTextureHeight"].GetUint();
			const auto subTexturesArray = currentTextureAtlas["subTexture"].GetArray();
			std::vector<std::string> subTextures;
			subTextures.reserve(subTexturesArray.Size());
			for (const auto& currentSubTexture : subTexturesArray) {

				subTextures.emplace_back(currentSubTexture.GetString());

			}
			loadTextureAtlas(std::move(name), std::move(filePath), std::move(subTextures), subTextureWidth, subTextureHeight);

		}
	}

	auto spritesIt = document.FindMember("sprites");
	if (spritesIt != document.MemberEnd()) {
		for (const auto& currentSprite : spritesIt->value.GetArray())
		{
			loadSprites(currentSprite["name"].GetString(), currentSprite["textureAtlas"].GetString(),
						currentSprite["shader"].GetString(), currentSprite["subTextureName"].GetString());
		}
	}

	auto animatedSpritesIt = document.FindMember("animatedSprites");
	if (animatedSpritesIt != document.MemberEnd())
	{
		for (const auto& currentAnimatedSprite : animatedSpritesIt->value.GetArray()) {

			const std::string name = currentAnimatedSprite["name"].GetString();
			const std::string textureAtlas = currentAnimatedSprite["textureAtlas"].GetString();
			const std::string shader = currentAnimatedSprite["shader"].GetString();
			std::string initialSubTexture = currentAnimatedSprite["initialSubTexture"].GetString();

			auto pAnimatedSprite = loadAnimatedSprites(name, textureAtlas, shader, std::move(initialSubTexture));
			if (!pAnimatedSprite) {
				
				std::cerr << "Can`t load an animated sprite" << name << std::endl;
				continue;
			}
			const auto statesArray = currentAnimatedSprite["states"].GetArray();
			for (const auto& currentState : statesArray) {

				std::string stateName = currentState["stateName"].GetString();				
				std::vector<std::pair<std::string, uint64_t>> frames;
				const auto framesArray = currentState["frames"].GetArray();
				frames.reserve(framesArray.Size());
				for (const auto& currentFrame : framesArray) {
					frames.emplace_back(std::make_pair<std::string, uint64_t>(currentFrame["subTexture"].GetString(), currentFrame["duration"].GetUint64()));
				}
				pAnimatedSprite->insertState(std::move(stateName), std::move(frames));
			}

		}
		
	}

	auto levelIt = document.FindMember("levels");
	if (levelIt != document.MemberEnd()) {
		for (const auto& currentLevel : levelIt->value.GetArray()) {
			
			std::vector<std::string> description;
			for (const auto& currentDescription : currentLevel["description"].GetArray())
			{
				description.emplace_back(currentDescription.GetString());
			}
			m_levels.emplace_back(std::move(description));
			
		}
	}

	return true;
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
