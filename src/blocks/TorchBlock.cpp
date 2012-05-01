#include "TorchBlock.h"
#include "gui/OpenGLBuffer.h"
#include "gui/OpenGLVertice.h"
#include "Log.h"

void TorchBlock::setTexture(const QRectF& texturePos)
{
	BlockDescriptor::setTexture(texturePos);
	if(m_model != NULL) {
		m_model->adjustTextures(texturePos);
	}
}

void TorchBlock::loadModel(const QString& modelFolder)
{
	m_model = new OpenGLBuffer(modelFolder + name() + ".obj");
	linfo(Channel_OpenGL, "torch model loaded");
}

void TorchBlock::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& bp, const World& workingWorld) const
{
	OpenGLBuffer translatedModel(*m_model);
	translatedModel.translate3f(bp.x, bp.y, bp.z);
	targetBuffer.append(translatedModel);
}
