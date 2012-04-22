#ifndef TORCHBLOCK_H
#define TORCHBLOCK_H

#include "BlockDescriptor.h"

class TorchBlock : public BlockDescriptor
{
public:
	TorchBlock(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true)
	{
		i_id = id;
		s_name = name;
		b_breakable = breakable;
		b_canPassThrough = canPassThrough;
	}

	virtual void render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& position, const World& workingWorld) const;
};

#endif // TORCHBLOCK_H
