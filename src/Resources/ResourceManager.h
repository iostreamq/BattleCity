#pragma once
#include <string>
#include <memory>
#include <map>
#include "../Renderer/ShaderProgram.h" 

class ResourceManager {

public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName,const std::string& vertexPath, const std::string& fragmentPath);
private:
	std::string getFileString(const std::string& AdditionalPath);
	std::string m_Path;
	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap; // как будто юзлес нахуй она вообще только если статик делать или только для имени  
	ShaderProgramsMap m_shaderPrograms;
};
