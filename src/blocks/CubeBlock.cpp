#include "CubeBlock.h"
#include "Log.h"
#include "gui/OpenGLBuffer.h"
#include "gui/OpenGLVertice.h"
#include "World.h"

void CubeBlock::setTexture(const QRectF& texturePos, float ratio)
{
	BlockDescriptor::setTexture(texturePos, ratio);

	// See documentation for details
	// 1:1 -> All faces
	if(m_textureRatio == 1.0f) { // This must be exactly 1, no approaching value
		m_faceTexturesPosition[CubeFace_Front] = texturePos;
		m_faceTexturesPosition[CubeFace_Left] = texturePos;
		m_faceTexturesPosition[CubeFace_Bottom] = texturePos;
		m_faceTexturesPosition[CubeFace_Right] = texturePos;
		m_faceTexturesPosition[CubeFace_Top] = texturePos;
		m_faceTexturesPosition[CubeFace_Back] = texturePos;
	}
	// 1:2 -> top&bottom, side
	else if(m_textureRatio == 0.5f) {
		QRectF texture1 = QRectF(QPointF(texturePos.topLeft()),
								 QSizeF(texturePos.width(),texturePos.height() / 2.0f));
		QRectF texture2 = QRectF(QPointF(texturePos.x(), texturePos.y() + texturePos.height() / 2.0f),
								 QSizeF(texturePos.width(), texturePos.height() / 2.0f));
		m_faceTexturesPosition[CubeFace_Front] = texture2;
		m_faceTexturesPosition[CubeFace_Left] = texture2;
		m_faceTexturesPosition[CubeFace_Bottom] = texture1;
		m_faceTexturesPosition[CubeFace_Right] = texture2;
		m_faceTexturesPosition[CubeFace_Top] = texture1;
		m_faceTexturesPosition[CubeFace_Back] = texture2;
	}
	// 1:3 -> top, side, bottom
	else if(qFuzzyCompare(m_textureRatio, 1.0f/3.0f)) {
		QRectF texture1 = QRectF(QPointF(texturePos.topLeft()),
								 QSizeF(texturePos.width(),texturePos.height() / 3.0f));
		QRectF texture2 = QRectF(QPointF(texturePos.x(), texturePos.y() + texturePos.height() / 3.0f),
								 QSizeF(texturePos.width(), texturePos.height() / 3.0f));
		QRectF texture3 = QRectF(QPointF(texturePos.x(), texturePos.y() + 2 * texturePos.height() / 3.0f),
								 QSizeF(texturePos.width(), texturePos.height() / 3.0f));
		m_faceTexturesPosition[CubeFace_Front] = texture2;
		m_faceTexturesPosition[CubeFace_Left] = texture2;
		m_faceTexturesPosition[CubeFace_Bottom] = texture3;
		m_faceTexturesPosition[CubeFace_Right] = texture2;
		m_faceTexturesPosition[CubeFace_Top] = texture1;
		m_faceTexturesPosition[CubeFace_Back] = texture2;
	}
	// 2:3 -> top, left&right, front&back, bottom
	else if(qFuzzyCompare(m_textureRatio, 2.0f/3.0f)) {
		QRectF textureLR = QRectF(QPointF(texturePos.x(), texturePos.y() + texturePos.height() / 3.0f),
								 QSizeF(texturePos.width() / 2.0f, texturePos.height() / 3.0f));
		QRectF textureT = QRectF(QPointF(texturePos.x() + texturePos.width() / 2.0f, texturePos.y() + texturePos.height() / 3.0f),
								 QSizeF(texturePos.width() / 2.0f, texturePos.height() / 3.0f));
		QRectF textureFB = QRectF(QPointF(texturePos.x() + texturePos.width() / 2.0f, texturePos.y() + 2 * texturePos.height() / 3.0f),
								 QSizeF(texturePos.width() / 2.0f, texturePos.height() / 3.0f));
		QRectF textureB = QRectF(QPointF(texturePos.x() + texturePos.width() / 2.0f, texturePos.y() + 2 * texturePos.height() / 3.0f),
								 QSizeF(texturePos.width() / 2.0f, texturePos.height() / 3.0f));

		m_faceTexturesPosition[CubeFace_Front] = textureFB;
		m_faceTexturesPosition[CubeFace_Left] = textureLR;
		m_faceTexturesPosition[CubeFace_Bottom] = textureB;
		m_faceTexturesPosition[CubeFace_Right] = textureLR;
		m_faceTexturesPosition[CubeFace_Top] = textureT;
		m_faceTexturesPosition[CubeFace_Back] = textureFB;
	}
	// 4:3 -> top, left, right, front, back, bottom
	else if(qFuzzyCompare(m_textureRatio, 4.0f/3.0f)) {
		QSizeF faceSize = QSizeF(texturePos.width() / 4.0f, texturePos.height() / 3.0f);

		QRectF textureL = QRectF(QPointF(texturePos.x(), texturePos.y() + texturePos.height() / 3.0f), faceSize);
		QRectF textureT = QRectF(QPointF(texturePos.x() + texturePos.width() / 4.0f, texturePos.y()), faceSize);
		QRectF textureF = QRectF(QPointF(texturePos.x() + texturePos.width() / 4.0f, texturePos.y() + texturePos.height() / 3.0f), faceSize);
		QRectF textureBo = QRectF(QPointF(texturePos.x() + texturePos.width() / 4.0f, texturePos.y() + 2 * texturePos.height() / 3.0f), faceSize);
		QRectF textureR = QRectF(QPointF(texturePos.x() + 2 * texturePos.width() / 4.0f, texturePos.y() + texturePos.height() / 3.0f), faceSize);
		QRectF textureBa = QRectF(QPointF(texturePos.x() + 3 * texturePos.width() / 4.0f, texturePos.y() + texturePos.height() / 3.0f), faceSize);

		m_faceTexturesPosition[CubeFace_Front] = textureF;
		m_faceTexturesPosition[CubeFace_Left] = textureL;
		m_faceTexturesPosition[CubeFace_Bottom] = textureBo;
		m_faceTexturesPosition[CubeFace_Right] = textureR;
		m_faceTexturesPosition[CubeFace_Top] = textureT;
		m_faceTexturesPosition[CubeFace_Back] = textureBa;
	}
	else {
		QRectF texture = QRectF(QPointF(0.0f, 0.0f), QSizeF(0.0f,0.0f));
		lerror(Channel_Textures, QString("Texture dimensions are weird! Can't load texture for block ") + name());
		m_faceTexturesPosition[CubeFace_Front] = texture;
		m_faceTexturesPosition[CubeFace_Left] = texture;
		m_faceTexturesPosition[CubeFace_Bottom] = texture;
		m_faceTexturesPosition[CubeFace_Right] = texture;
		m_faceTexturesPosition[CubeFace_Top] = texture;
		m_faceTexturesPosition[CubeFace_Back] = texture;
	}
}

void CubeBlock::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet) const
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

		OpenGLVertice v1(blockSet.position.x, blockSet.position.y, blockSet.position.z); // 0.0f,0.0f,0.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(m_faceTexturesPosition[CubeFace_Front].left(), m_faceTexturesPosition[CubeFace_Front].bottom());

		OpenGLVertice v2(blockSet.position.x + 1.0f, blockSet.position.y, blockSet.position.z); // 1.0f,0.0f,0.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(m_faceTexturesPosition[CubeFace_Front].right(), m_faceTexturesPosition[CubeFace_Front].bottom());

		OpenGLVertice v3(blockSet.position.x + 1.0f, blockSet.position.y + 1.0f, blockSet.position.z); //  1.0f,1.0f,0.0f,
		v3.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(m_faceTexturesPosition[CubeFace_Front].right(), m_faceTexturesPosition[CubeFace_Front].top());

		OpenGLVertice v4(blockSet.position.x, blockSet.position.y + 1.0f, blockSet.position.z); //  0.0f,1.0f,0.0f,
		v4.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(m_faceTexturesPosition[CubeFace_Front].left(), m_faceTexturesPosition[CubeFace_Front].top());

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Left face
	if(!blockSet.leftBlock->descriptor().isCube()) {

		OpenGLVertice v1(blockSet.position.x, blockSet.position.y, blockSet.position.z + 1.0f); // 0.0f,0.0f,1.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(m_faceTexturesPosition[CubeFace_Left].left(), m_faceTexturesPosition[CubeFace_Left].bottom());

		OpenGLVertice v2(blockSet.position.x, blockSet.position.y, blockSet.position.z); // 0.0f,0.0f,0.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(m_faceTexturesPosition[CubeFace_Left].right(), m_faceTexturesPosition[CubeFace_Left].bottom());

		OpenGLVertice v3(blockSet.position.x, blockSet.position.y + 1.0f, blockSet.position.z); // 0.0f,1.0f,0.0f,
		v3.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(m_faceTexturesPosition[CubeFace_Left].right(), m_faceTexturesPosition[CubeFace_Left].top());

		OpenGLVertice v4(blockSet.position.x, blockSet.position.y + 1.0f, blockSet.position.z + 1.0f); // 0.0f,1.0f,1.0f,
		v4.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(m_faceTexturesPosition[CubeFace_Left].left(), m_faceTexturesPosition[CubeFace_Left].top());

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Bottom face
	if(blockSet.position.y != 0 && (!blockSet.bottomBlock->descriptor().isCube())) {

		OpenGLVertice v1(blockSet.position.x, blockSet.position.y, blockSet.position.z + 1.0f); // 0.0f,0.0f,1.0f,
		v1.setColors(BOTTOM_LIGHT);
		v1.setTextures(m_faceTexturesPosition[CubeFace_Bottom].left(), m_faceTexturesPosition[CubeFace_Bottom].bottom());

		OpenGLVertice v2(blockSet.position.x + 1.0f, blockSet.position.y, blockSet.position.z + 1.0f); // 1.0f,0.0f,1.0f,
		v2.setColors(BOTTOM_LIGHT);
		v2.setTextures(m_faceTexturesPosition[CubeFace_Bottom].right(), m_faceTexturesPosition[CubeFace_Bottom].bottom());

		OpenGLVertice v3(blockSet.position.x + 1.0f, blockSet.position.y, blockSet.position.z); // 1.0f,0.0f,0.0f,
		v3.setColors(BOTTOM_LIGHT);
		v3.setTextures(m_faceTexturesPosition[CubeFace_Bottom].right(), m_faceTexturesPosition[CubeFace_Bottom].top());

		OpenGLVertice v4(blockSet.position.x, blockSet.position.y, blockSet.position.z); // 0.0f,0.0f,0.0f,
		v4.setColors(BOTTOM_LIGHT);
		v4.setTextures(m_faceTexturesPosition[CubeFace_Bottom].left(), m_faceTexturesPosition[CubeFace_Bottom].top());

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Right face
	if(!blockSet.rightBlock->descriptor().isCube()) {

		OpenGLVertice v1(blockSet.position.x + 1.0f, blockSet.position.y, blockSet.position.z); // 1.0f,0.0f,0.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(m_faceTexturesPosition[CubeFace_Right].left(), m_faceTexturesPosition[CubeFace_Right].bottom());

		OpenGLVertice v2(blockSet.position.x + 1.0f, blockSet.position.y, blockSet.position.z + 1.0f); // 1.0f,0.0f,1.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(m_faceTexturesPosition[CubeFace_Right].right(), m_faceTexturesPosition[CubeFace_Right].bottom());

		OpenGLVertice v3(blockSet.position.x + 1.0f, blockSet.position.y + 1.0f, blockSet.position.z + 1.0f); // 1.0f,1.0f,1.0f,
		v3.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(m_faceTexturesPosition[CubeFace_Right].right(), m_faceTexturesPosition[CubeFace_Right].top());

		OpenGLVertice v4(blockSet.position.x + 1.0f, blockSet.position.y + 1.0f, blockSet.position.z); // 1.0f,1.0f,0.0f,
		v4.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(m_faceTexturesPosition[CubeFace_Right].left(), m_faceTexturesPosition[CubeFace_Right].top());

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Top face
	if(!blockSet.topBlock->descriptor().isCube()) {

		OpenGLVertice v1(blockSet.position.x, blockSet.position.y + 1.0f, blockSet.position.z); // 0.0f,1.0f,0.0f,
		v1.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topFrontLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(m_faceTexturesPosition[CubeFace_Top].left(), m_faceTexturesPosition[CubeFace_Top].bottom());

		OpenGLVertice v2(blockSet.position.x + 1.0f, blockSet.position.y + 1.0f, blockSet.position.z); // 1.0f,1.0f,0.0f,
		v2.setColors((blockSet.topFrontBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topFrontRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(m_faceTexturesPosition[CubeFace_Top].right(), m_faceTexturesPosition[CubeFace_Top].bottom());

		OpenGLVertice v3(blockSet.position.x + 1.0f, blockSet.position.y + 1.0f, blockSet.position.z + 1.0f); // 1.0f,1.0f,1.0f,
		v3.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(m_faceTexturesPosition[CubeFace_Top].right(), m_faceTexturesPosition[CubeFace_Top].top());

		OpenGLVertice v4(blockSet.position.x, blockSet.position.y + 1.0f, blockSet.position.z + 1.0f); // 0.0f,1.0f,1.0f,
		v4.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(m_faceTexturesPosition[CubeFace_Top].left(), m_faceTexturesPosition[CubeFace_Top].top());

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
	// Back face
	if(!blockSet.backBlock->descriptor().isCube()) {

		OpenGLVertice v1(blockSet.position.x + 1.0f, blockSet.position.y, blockSet.position.z + 1.0); // 1.0f,0.0f,1.0f,
		v1.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v1.setTextures(m_faceTexturesPosition[CubeFace_Back].left(), m_faceTexturesPosition[CubeFace_Back].bottom());

		OpenGLVertice v2(blockSet.position.x, blockSet.position.y, blockSet.position.z + 1.0f); // 0.0f,0.0f,1.0f,
		v2.setColors((blockSet.bottomBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v2.setTextures(m_faceTexturesPosition[CubeFace_Back].right(), m_faceTexturesPosition[CubeFace_Back].bottom());

		OpenGLVertice v3(blockSet.position.x, blockSet.position.y + 1.0f, blockSet.position.z + 1.0f); // 0.0f,1.0f,1.0f,
		v3.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topLeftBlock->descriptor().isCube() || blockSet.topBackLeftBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v3.setTextures(m_faceTexturesPosition[CubeFace_Back].right(), m_faceTexturesPosition[CubeFace_Back].top());

		OpenGLVertice v4(blockSet.position.x + 1.0f, blockSet.position.y + 1.0f, blockSet.position.z + 1.0f); // 1.0f,1.0f,1.0f,
		v4.setColors((blockSet.topBackBlock->descriptor().isCube() || blockSet.topRightBlock->descriptor().isCube() || blockSet.topBackRightBlock->descriptor().isCube()) ? SIDE_LIGHT_OCCLUSION : TOP_LIGHT);
		v4.setTextures(m_faceTexturesPosition[CubeFace_Back].left(), m_faceTexturesPosition[CubeFace_Back].top());

		targetBuffer.addVertices(v1, v2, v3, v4);
	}
}
