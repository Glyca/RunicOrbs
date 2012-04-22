#include "TorchBlock.h"
#include "gui/OpenGLBuffer.h"
#include "gui/OpenGLVertice.h"

void TorchBlock::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& bp, const World& workingWorld) const
{
	const GLfloat TOP_LIGHT = 1.0f;
	const GLfloat SIDE_LIGHT_NORMAL = 0.85f;
	const GLfloat BOTTOM_COLOR = 0.45f;

	const GLfloat XMIN = 0.45f;
	const GLfloat XMAX = 0.55f;
	const GLfloat YMIN = 0.0f;
	const GLfloat YMAX = 0.90f;
	const GLfloat ZMIN = 0.45f;
	const GLfloat ZMAX = 0.55f;

	// Front face
	{
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + XMIN, bp.y + YMIN, bp.z + ZMIN); // 0.0f,0.0f,0.0f,
		v1.setColors(SIDE_LIGHT_NORMAL);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + XMAX, bp.y + YMIN, bp.z + ZMIN); // 1.0f,0.0f,0.0f,
		v2.setColors(SIDE_LIGHT_NORMAL);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + XMAX, bp.y + YMAX, bp.z + ZMIN); //  1.0f,1.0f,0.0f,
		v3.setColors(TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + XMIN, bp.y + YMAX, bp.z + ZMIN); //  0.0f,1.0f,0.0f,
		v4.setColors(TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Left face
	{
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + XMIN, bp.y + YMIN, bp.z + ZMAX); // 0.0f,0.0f,1.0f,
		v1.setColors(SIDE_LIGHT_NORMAL);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + XMIN, bp.y + YMIN, bp.z + ZMIN); // 0.0f,0.0f,0.0f,
		v2.setColors(SIDE_LIGHT_NORMAL);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + XMIN, bp.y + YMAX, bp.z + ZMIN); // 0.0f,1.0f,0.0f,
		v3.setColors(TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + XMIN, bp.y + YMAX, bp.z + ZMAX); // 0.0f,1.0f,1.0f,
		v4.setColors(TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Bottom face
	{
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + XMIN, bp.y + YMIN, bp.z + ZMAX); // 0.0f,0.0f,1.0f,
		v1.setColors(BOTTOM_COLOR);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + XMAX, bp.y + YMIN, bp.z + ZMAX); // 1.0f,0.0f,1.0f,
		v2.setColors(BOTTOM_COLOR);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + XMAX, bp.y + YMIN, bp.z + ZMIN); // 1.0f,0.0f,0.0f,
		v3.setColors(BOTTOM_COLOR);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + XMIN, bp.y + YMIN, bp.z + ZMIN); // 0.0f,0.0f,0.0f,
		v4.setColors(BOTTOM_COLOR);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Right face
	{
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + XMAX, bp.y + YMIN, bp.z + ZMIN); // 1.0f,0.0f,0.0f,
		v1.setColors(SIDE_LIGHT_NORMAL);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + XMAX, bp.y + YMIN, bp.z + ZMAX); // 1.0f,0.0f,1.0f,
		v2.setColors(SIDE_LIGHT_NORMAL);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + XMAX, bp.y + YMAX, bp.z + ZMAX); // 1.0f,1.0f,1.0f,
		v3.setColors(TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + XMAX, bp.y + YMAX, bp.z + ZMIN); // 1.0f,1.0f,0.0f,
		v4.setColors(TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Top face
	{
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + XMIN, bp.y + YMAX, bp.z + ZMIN); // 0.0f,1.0f,0.0f,
		v1.setColors(TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + XMAX, bp.y + YMAX, bp.z + ZMIN); // 1.0f,1.0f,0.0f,
		v2.setColors(TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + XMAX, bp.y + YMAX, bp.z + ZMAX); // 1.0f,1.0f,1.0f,
		v3.setColors(TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + XMIN, bp.y + YMAX, bp.z + ZMAX); // 0.0f,1.0f,1.0f,
		v4.setColors(TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Back face
	{
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + XMAX, bp.y + YMIN, bp.z + ZMAX); // 1.0f,0.0f,1.0f,
		v1.setColors(SIDE_LIGHT_NORMAL);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + XMIN, bp.y + YMIN, bp.z + ZMAX); // 0.0f,0.0f,1.0f,
		v2.setColors(SIDE_LIGHT_NORMAL);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + XMIN, bp.y + YMAX, bp.z + ZMAX); // 0.0f,1.0f,1.0f,
		v3.setColors(TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + XMAX, bp.y + YMAX, bp.z + ZMAX); // 1.0f,1.0f,1.0f,
		v4.setColors(TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
}
