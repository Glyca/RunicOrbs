#include "CubeBlock.h"
#include "gui/OpenGLBuffer.h"
#include "gui/OpenGLVertice.h"
#include "World.h"

void CubeBlock::render(OpenGLBuffer& targetBuffer, const BlockInfo& blockInfo, const BlockPosition& bp, const World& workingWorld) const
{
	BlockInfo* frontBlock = workingWorld.block(BlockPosition(bp.x, bp.y, bp.z - 1));
	BlockInfo* leftBlock = workingWorld.block(BlockPosition(bp.x - 1, bp.y, bp.z));
	BlockInfo* bottomBlock = workingWorld.block(BlockPosition(bp.x, bp.y - 1, bp.z));
	BlockInfo* rightBlock = workingWorld.block(BlockPosition(bp.x + 1, bp.y, bp.z));
	BlockInfo* topBlock = workingWorld.block(BlockPosition(bp.x, bp.y + 1, bp.z));
	BlockInfo* backBlock = workingWorld.block(BlockPosition(bp.x, bp.y, bp.z + 1));

	BlockInfo* topFrontBlock = workingWorld.block(BlockPosition(bp.x, bp.y + 1, bp.z - 1));
	BlockInfo* topLeftBlock = workingWorld.block(BlockPosition(bp.x - 1, bp.y + 1, bp.z));
	BlockInfo* topRightBlock = workingWorld.block(BlockPosition(bp.x + 1, bp.y + 1, bp.z));
	BlockInfo* topBackBlock = workingWorld.block(BlockPosition(bp.x, bp.y + 1, bp.z + 1));

	BlockInfo* topFrontLeftBlock = workingWorld.block(BlockPosition(bp.x - 1, bp.y + 1, bp.z - 1));
	BlockInfo* topFrontRightBlock = workingWorld.block(BlockPosition(bp.x + 1, bp.y + 1, bp.z - 1));
	BlockInfo* topBackLeftBlock = workingWorld.block(BlockPosition(bp.x - 1, bp.y + 1, bp.z + 1));
	BlockInfo* topBackRightBlock = workingWorld.block(BlockPosition(bp.x + 1, bp.y + 1, bp.z + 1));

	/* How we must draw a face to fit the texture :
	v4----v3
	|     |
	|     |
	v1----v2
  */
	const GLfloat TOP_LIGHT = 1.0f;
	const GLfloat SIDE_LIGHT_NORMAL = 0.75f;
	const GLfloat SIDE_LIGHT_OCCLUSION = 0.75f;
	const GLfloat BOTTOM_LIGHT = 0.45f;

	// Front face
	if(!frontBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockInfo.descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y, bp.z); // 0.0f,0.0f,0.0f,
		v1.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y, bp.z); // 1.0f,0.0f,0.0f,
		v2.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y + 1.0f, bp.z); //  1.0f,1.0f,0.0f,
		v3.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y + 1.0f, bp.z); //  0.0f,1.0f,0.0f,
		v4.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Left face
	if(!leftBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockInfo.descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y, bp.z + 1.0f); // 0.0f,0.0f,1.0f,
		v1.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x, bp.y, bp.z); // 0.0f,0.0f,0.0f,
		v2.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x, bp.y + 1.0f, bp.z); // 0.0f,1.0f,0.0f,
		v3.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y + 1.0f, bp.z + 1.0f); // 0.0f,1.0f,1.0f,
		v4.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Bottom face
	if(bp.y != 0 && (!bottomBlock->descriptor().isCube())) {
		TexCoords* texCoords = blockInfo.descriptor().getTexture();

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
	if(!rightBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockInfo.descriptor().getTexture();

		OpenGLVertice v1(bp.x + 1.0f, bp.y, bp.z); // 1.0f,0.0f,0.0f,
		v1.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y, bp.z + 1.0f); // 1.0f,0.0f,1.0f,
		v2.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y + 1.0f, bp.z + 1.0f); // 1.0f,1.0f,1.0f,
		v3.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + 1.0f, bp.y + 1.0f, bp.z); // 1.0f,1.0f,0.0f,
		v4.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Top face
	if(!topBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockInfo.descriptor().getTexture();

		OpenGLVertice v1(bp.x, bp.y + 1.0f, bp.z); // 0.0f,1.0f,0.0f,
		v1.setColors((topFrontBlock->descriptor().isCube() || topLeftBlock->descriptor().isCube() || topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x + 1.0f, bp.y + 1.0f, bp.z); // 1.0f,1.0f,0.0f,
		v2.setColors((topFrontBlock->descriptor().isCube() || topRightBlock->descriptor().isCube() || topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x + 1.0f, bp.y + 1.0f, bp.z + 1.0f); // 1.0f,1.0f,1.0f,
		v3.setColors((topBackBlock->descriptor().isCube() || topRightBlock->descriptor().isCube() || topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x, bp.y + 1.0f, bp.z + 1.0f); // 0.0f,1.0f,1.0f,
		v4.setColors((topBackBlock->descriptor().isCube() || topLeftBlock->descriptor().isCube() || topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Back face
	if(!backBlock->descriptor().isCube()) {
		TexCoords* texCoords = blockInfo.descriptor().getTexture();

		OpenGLVertice v1(bp.x + 1.0f, bp.y, bp.z + 1.0); // 1.0f,0.0f,1.0f,
		v1.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(texCoords[0].tx, texCoords[0].ty);

		OpenGLVertice v2(bp.x, bp.y, bp.z + 1.0f); // 0.0f,0.0f,1.0f,
		v2.setColors((bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(texCoords[1].tx, texCoords[1].ty);

		OpenGLVertice v3(bp.x, bp.y + 1.0f, bp.z + 1.0f); // 0.0f,1.0f,1.0f,
		v3.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(texCoords[2].tx, texCoords[2].ty);

		OpenGLVertice v4(bp.x + 1.0f, bp.y + 1.0f, bp.z + 1.0f); // 1.0f,1.0f,1.0f,
		v4.setColors((topBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(texCoords[3].tx, texCoords[3].ty);

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
}
