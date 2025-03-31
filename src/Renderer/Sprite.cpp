#include "Sprite.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "external/glm/gtc/type_ptr.hpp"
#include <iostream>


namespace RenderEngine {
	Sprite::Sprite(std::shared_ptr<RenderEngine::Texture2D> pTexture,
		std::string&& initialSubTexture,
		std::shared_ptr<RenderEngine::ShaderProgram> pShaderProgram
		):		
		m_pTexture(std::move(pTexture)), 
		m_pShaderProgram(std::move(pShaderProgram))		
	{
		

		const GLfloat vertexCoords[] = {
			0.f, 0.f, 
			0.f, 1.f,
			1.f, 1.f,
			1.f, 0.f
		};
		
		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture)); 
		
		const GLfloat textureCoords[] = {
		  subTexture.leftBottomUV.x,	subTexture.leftBottomUV.y,
		  subTexture.leftBottomUV.x,	subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x,		subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x,		subTexture.leftBottomUV.y,
	
		}; 

		// по аналогии с коордами мы задаем индексы, которые соотносятся с моими коордами
		const GLuint indices[] = {
			  0,1,2,
			  2,3,0	
		};

         
		m_vertexArray.bind(); // how does it work without binding
		m_vertexsCoordsBuffer.init(&vertexCoords, 2 * 4 * sizeof(GLfloat)); 
		VertexBufferLayout vertexCoordsLayout;
		vertexCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_vertexsCoordsBuffer, vertexCoordsLayout);
	
		m_textureCoordsBuffer.init(&textureCoords, 2 * 4 * sizeof(GLfloat)); 
		VertexBufferLayout textureCoordsLayout;
		textureCoordsLayout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);


		m_IndexBuffer.init(&indices, 6);
        
		m_vertexArray.unbind();
		//m_vertexsCoordsBuffer.unbind();
		//m_textureCoordsBuffer.unbind();
		m_IndexBuffer.unbind();
	}

	Sprite::~Sprite()
	{		
		
	}



	void Sprite::Render(const glm::vec2& position
					  , const glm::vec2& size
					  , const float rotation
					  , const float layer
					  , const size_t frameId) const
	{
		if(!m_framesDescription.empty())
		{
			const FramesDescription& currentFrameDescription = m_framesDescription[frameId];

			const GLfloat textureCoords[] = {
			 currentFrameDescription.leftBottomUV.x, currentFrameDescription.leftBottomUV.y,
			 currentFrameDescription.leftBottomUV.x,  currentFrameDescription.rightTopUV.y,
			 currentFrameDescription.rightTopUV.x, currentFrameDescription.rightTopUV.y,
			 currentFrameDescription.rightTopUV.x, currentFrameDescription.leftBottomUV.y,
			}; // чтоб не мучаться делай 2 буфера. если бы мы не меняли корды текстур то все было бы в одном буфере(sprite.cpp)

			m_textureCoordsBuffer.update(&textureCoords, 2 * 4 * sizeof(GLfloat)); // передает определенные данные которые обновляют тек буфер
		}

		m_pShaderProgram->use();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
		model = glm::scale(model, glm::vec3(size, 1.f));

		m_pShaderProgram->setMatrix4("modelMatrix", model);
		m_pShaderProgram->setFloat("layer", layer);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		Renderer::draw(m_vertexArray, m_IndexBuffer, *m_pShaderProgram);
	}

	void Sprite::insertFrames(std::vector<FramesDescription> framesDescriptions)
	{
		m_framesDescription = std::move(framesDescriptions);
	}

	double Sprite::GetTotalDuration() const
	{
	
		if (m_framesDescription.empty()) return 0;

		double totalDuration = 0;

		for (size_t currentDurationOfFrame = 0; currentDurationOfFrame < m_framesDescription.size(); currentDurationOfFrame++)
		{
			totalDuration += m_framesDescription[currentDurationOfFrame].duration;
		}
		return totalDuration;
	}

	double Sprite::GetFrameDuration(const size_t frameId) const
	{
		return m_framesDescription[frameId].duration;
	}
	size_t Sprite::GetFramesCount()
	{
		return m_framesDescription.size();
	}
}