#include "CubeBlock.h"
#include "gui/OpenGLBuffer.h"
#include "gui/OpenGLVertice.h"
#include "World.h"

void CubeBlock::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& bp, const World& workingWorld) const
{
	/* How we must draw a face to fit the texture :
	v4----v3
	|     |
	|     |
	v1----v2
  */
	const GLfloat TOP_LIGHT = 1.0f;
	const GLfloat SIDE_LIGHT_OCCLUSION = 0.85f;
	const GLfloat BOTTOM_LIGHT = 0.65f;

	// Front face
	if(!blockSet.frontBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y, bp.z); // 0.0f,0.0f,0.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y, bp.z); // 1.0f,0.0f,0.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y + 1.0f, bp.z); //  1.0f,1.0f,0.0f,
		v3.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y + 1.0f, bp.z); //  0.0f,1.0f,0.0f,
		v4.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Left face
	if(!blockSet.leftBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y, bp.z + 1.0f); // 0.0f,0.0f,1.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x, bp.y, bp.z); // 0.0f,0.0f,0.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x, bp.y + 1.0f, bp.z); // 0.0f,1.0f,0.0f,
		v3.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y + 1.0f, bp.z + 1.0f); // 0.0f,1.0f,1.0f,
		v4.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Bottom face
	if(bp.y != 0 && (!blockSet.bottomBlock->descriptor().isCube())) {
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y, bp.z + 1.0f); // 0.0f,0.0f,1.0f,
		v1.setColors(BOTTOM_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y, bp.z + 1.0f); // 1.0f,0.0f,1.0f,
		v2.setColors(BOTTOM_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y, bp.z); // 1.0f,0.0f,0.0f,
		v3.setColors(BOTTOM_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y, bp.z); // 0.0f,0.0f,0.0f,
		v4.setColors(BOTTOM_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Right face
	if(!blockSet.rightBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + 1.0f, bp.y, bp.z); // 1.0f,0.0f,0.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y, bp.z + 1.0f); // 1.0f,0.0f,1.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y + 1.0f, bp.z + 1.0f); // 1.0f,1.0f,1.0f,
		v3.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + 1.0f, bp.y + 1.0f, bp.z); // 1.0f,1.0f,0.0f,
		v4.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Top face
	if(!blockSet.topBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y + 1.0f, bp.z); // 0.0f,1.0f,0.0f,
		v1.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y + 1.0f, bp.z); // 1.0f,1.0f,0.0f,
		v2.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y + 1.0f, bp.z + 1.0f); // 1.0f,1.0f,1.0f,
		v3.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y + 1.0f, bp.z + 1.0f); // 0.0f,1.0f,1.0f,
		v4.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Back face
	if(!blockSet.backBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockSet.block->descriptor().getTexture();

		OpenGLVertice v1(bp.x + 1.0f, bp.y, bp.z + 1.0); // 1.0f,0.0f,1.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x, bp.y, bp.z + 1.0f); // 0.0f,0.0f,1.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x, bp.y + 1.0f, bp.z + 1.0f); // 0.0f,1.0f,1.0f,
		v3.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + 1.0f, bp.y + 1.0f, bp.z + 1.0f); // 1.0f,1.0f,1.0f,
		v4.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
}
