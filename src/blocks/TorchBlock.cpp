#include "TorchBlock.h"
#include "gui/OpenGLBuffer.h"
#include "gui/OpenGLVertice.h"
#include "Log.h"

void TorchBlock::setTexture(const QRectF& texturePos, float ratio)
{
	Q_UNUSED(ratio);
	if(m_model != NULL) {
		m_model->adjustTextures(texturePos);
	}
}

void TorchBlock::loadModel(const QString& modelFolder)
{
	m_model = new OpenGLBuffer(modelFolder + name() + ".obj");
}

void TorchBlock::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet) const
{
	OpenGLBuffer translatedModel(*m_model);
	translatedModel.translate3f(blockSet.position.x, blockSet.position.y, blockSet.position.z);
	targetBuffer.append(translatedModel);
}
