#include "BlockDescriptor.h"

void BlockDescriptor::loadModel(const QString& modelFolder)
{
	/* do not load any model for an undefined block */
}

void BlockDescriptor::render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& position, const World& workingWorld) const
{
	/* do nothing for an undefined block */
}
