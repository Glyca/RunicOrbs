#include "BlockDescriptor.h"

void BlockDescriptor::setTexture(const QRectF& texturePos, float ratio)
{
	m_texturePos = texturePos; m_textureRatio = ratio;
}

const QRectF& BlockDescriptor::texture() const
{
	return m_texturePos;
}

void BlockDescriptor::setItemImage(const QImage& image)
{
	qim_item = image;
}

const QImage& BlockDescriptor::itemImage() const
{
	return qim_item;
}

void BlockDescriptor::loadModel(const QString& modelFolder)
{
	/* do not load any model for an undefined block */
	Q_UNUSED(modelFolder);
}

void BlockDescriptor::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& position, const World& workingWorld) const
{
	/* do nothing for an undefined block */
	Q_UNUSED(targetBuffer); Q_UNUSED(blockSet); Q_UNUSED(position); Q_UNUSED(workingWorld);
}
