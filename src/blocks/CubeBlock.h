#ifndef CUBEBLOCK_H
#define CUBEBLOCK_H

#include "BlockDescriptor.h"

/*! BlockDescriptor of cubes */
class CubeBlock : public BlockDescriptor
{
public:
	CubeBlock(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true, int weight = 0) : BlockDescriptor(id, name, breakable, canPassThrough, weight) {}

	inline virtual bool isCube() const {return true;}

	virtual void setTexture(const QRectF& texturePos, float ratio);

	virtual void render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet) const;

private:
	enum CubeFace {
		CubeFace_Front,
		CubeFace_Left,
		CubeFace_Bottom,
		CubeFace_Right,
		CubeFace_Top,
		CubeFace_Back
	};

	QRectF m_faceTexturesPosition[6]; //!< 6 faces, 6 texture coordinates
};

#endif // CUBEBLOCK_H
