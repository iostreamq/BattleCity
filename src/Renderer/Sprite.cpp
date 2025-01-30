#include "Sprite.h"
#include "external/glm/mat4x4.hpp"
#include "external/glm/gtc/matrix_transform.hpp"
#include "external/glm/gtc/type_ptr.hpp"


namespace Renderer {
	Sprite::Sprite(std::shared_ptr<Renderer::Texture2D> pTexture,
		std::string&& initialSubTexture,
		std::shared_ptr<Renderer::ShaderProgram> pShaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation):
		
		m_pTexture(std::move(pTexture)), 
		m_pShaderProgram(std::move(pShaderProgram)),
		m_position(position), 
		m_size(size),
		m_rotation(rotation)
	{

		const GLfloat vertexCoords[] = {
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture)); 
		
		const GLfloat textureCoords[] = {
		  subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		  subTexture.leftBottomUV.x,  subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x, subTexture.rightTopUV.y,

		  subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		  subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		}; /////// всегда же x y

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao); 

		glGenBuffers(1, &vertexs_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexs_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	
		glGenBuffers(1, &textureCrds_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, textureCrds_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &vertexs_vbo);
		glDeleteBuffers(1, &textureCrds_vbo);
		glDeleteVertexArrays(1, &m_vao);
	}


	void Sprite::Render() const
	{
		m_pShaderProgram->use();
		glm::mat4 model(1.f);

	    model = glm::translate(model, glm::vec3(m_position,0.f)); 
	    model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f)); 
		model = glm::rotate(model, glm::radians(m_rotation),glm::vec3(0.f,0.f,1)); 
		model = glm::translate(model, glm::vec3(-0.5f* m_size.x, -0.5f*m_size.y, 0.f)); 
		model = glm::scale(model, glm::vec3(m_size, 1.f));
	
		glBindVertexArray(m_vao);
		m_pShaderProgram->setMatrix4("modelMatrix", model);
		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6); 
		glBindVertexArray(0);
	}

	void Sprite::setPosition(const glm::vec2& position)
	{
		m_position = position;
	}

	void Sprite::setSize(const glm::vec2& size)
	{
		m_size = size;
	}


	void Sprite::setRotation(const float rotation)
	{
		m_rotation = rotation;
	}

}