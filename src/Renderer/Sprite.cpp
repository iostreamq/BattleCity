#include "Sprite.h"
#include "VertexBufferLayout.h"
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
			1.f, 0.f
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture)); 
		
		const GLfloat textureCoords[] = {
		  subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		  subTexture.leftBottomUV.x,  subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		  subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
	
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


		m_IndexBuffer.init(&indices, 6 * sizeof(GLuint));
        
		m_vertexArray.unbind();
		//m_vertexsCoordsBuffer.unbind();
		//m_textureCoordsBuffer.unbind();
		m_IndexBuffer.unbind();
	}

	Sprite::~Sprite()
	{		
		
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
	   
		m_vertexArray.bind();
		m_pShaderProgram->setMatrix4("modelMatrix", model);
		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

	    

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // mode сколько индексов тип и оффсет	
		m_vertexArray.unbind();
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