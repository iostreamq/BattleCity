#include "Renderer.h"


void RenderEngine::Renderer::draw(const VertexArray& vertexArray, const indexBuffer& indBufffer, const ShaderProgram& shaderProgram)
{
	shaderProgram.use();
	vertexArray.bind();
   
	glDrawElements(GL_TRIANGLES, indBufffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void RenderEngine::Renderer::setCleatColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void RenderEngine::Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);////////////////////////////////////
}

void RenderEngine::Renderer::setViewport(unsigned int leftOffset, unsigned int BottomOffset, unsigned int width, int height)
{
	glViewport(leftOffset, BottomOffset, width, height);
}

 const std::string RenderEngine::Renderer::getRendererStr()   ////////// возврат по ссылке просто делает другой нейм? в каких случаях он вернет оригинал а не копию
{
	return (char*)glGetString(GL_RENDERER);
}

 const std::string RenderEngine::Renderer::getVersionStr()
{
	 return (char*)glGetString(GL_VERSION);

}
