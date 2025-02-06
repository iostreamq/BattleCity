#pragma once
#include <string>
#include <memory>
#include <map>
#include "../Renderer/ShaderProgram.h" 
#include "../Renderer/Texture2D.h" 
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include <vector>
class ResourceManager {

public:
	static void setExecutablePath(const std::string& executablePath);
	static void unloadAllResources();
	
	~ResourceManager() = delete;
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	static std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
	static std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);
	static std::shared_ptr<Renderer::Sprite> loadSprites(const std::string& spriteName,
														 const std::string& textureName,
														 const std::string& shaderName,
													     const unsigned int spriteWidth, 
														 const unsigned int spriteHeight,
														 std::string&& subTextureName = "DEFAULT");

	static std::shared_ptr<Renderer::Sprite> getSprite(std::string&& spriteName);

	static std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprites(const std::string& spriteName,
																	     const std::string& textureName,
																	     const std::string& shaderName,
																	     const unsigned int spriteWidth,
																	     const unsigned int spriteHeight,
																	     std::string&& subTextureName = "DEFAULT");

	static std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(std::string&& spriteName);

	static std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(std::string&& textureName,
															     std::string&& texturePath,
															     std::vector<std::string> vecNamesOfSubTex,
															     const unsigned int subTextureWidth,
															     const unsigned int subTextureHeight);
private:
	static std::string getFileString(const std::string& AdditionalPath); //////////почему статик
	static std::string m_Path;
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap; // как будто юзлес нахуй она вообще только если статик делать или только для имени 
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpritesMap;
	static ShaderProgramsMap m_shaderPrograms;
	static TexturesMap m_TexturesMap;
	static SpritesMap m_SpritesMap;
	static AnimatedSpritesMap m_AnimatedSpritesMap;
};
