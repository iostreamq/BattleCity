#pragma once
#include <string>
#include <memory>
#include <map>
#include "../Renderer/ShaderProgram.h" 
#include "../Renderer/Texture2D.h" 

class ResourceManager {

public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
private:
	std::string getFileString(const std::string& AdditionalPath);
	std::string m_Path;
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap; // как будто юзлес нахуй она вообще только если статик делать или только для имени 
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	ShaderProgramsMap m_shaderPrograms;
	TexturesMap m_TexturesMap;
};
