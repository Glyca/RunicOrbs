#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "BlockDescriptor.h"

/*! BlockDescriptor of cubes */
class CubeBlock : public BlockDescriptor
{
public:
	CubeBlock(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true)
	{
		i_id = id;
		s_name = name;
		b_breakable = breakable;
		b_canPassThrough = canPassThrough;
	}

	inline virtual bool isCube() const {return true;}
	virtual void render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& position, const World& workingWorld) const;
};

#endif // CUBEBLOCK_H
