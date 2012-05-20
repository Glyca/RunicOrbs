#ifndef TORCHBLOCK_H
#define TORCHBLOCK_H

#include "BlockDescriptor.h"

class TorchBlock : public BlockDescriptor
{
public:
	TorchBlock(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true, int weight = 0) : BlockDescriptor(id, name, breakable, canPassThrough, weight) {}

	virtual void setTexture(const QRectF& texturePos, float ratio);

	virtual void loadModel(const QString& modelFolder);

	virtual void render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet) const;
};

#endif // TORCHBLOCK_H
