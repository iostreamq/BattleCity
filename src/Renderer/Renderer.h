#pragma once
#include "VertexArray.h"
#include "indexBuffer.h"
#include "ShaderProgram.h"
#include <string>

namespace RenderEngine {
	class Renderer {
	public:
		static void draw(const VertexArray& vertexArray, const indexBuffer& indBufffer, const ShaderProgram& shaderProgram);
		static void setCleatColor(float r, float g, float b, float a);
		static void clear();
		static void setViewport(unsigned int leftOffset, unsigned int BottomOffset, unsigned int width, int height);
		const static std::string getRendererStr();
		const static std::string getVersionStr();
	};
}