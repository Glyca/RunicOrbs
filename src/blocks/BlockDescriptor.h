#ifndef BLOCKDESCRIPTOR_H
#define BLOCKDESCRIPTOR_H

#include "BlockInfo.h"
#include "gui/TextureManager.h" // TextureCoordinates

class OpenGLBuffer;
class World;

/*! Holds informations about a type of block such as texture, resistance, name... */
class BlockDescriptor
{
public:
	BlockDescriptor(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true)
		: i_id(id), s_name(name), b_breakable(breakable), b_canPassThrough(canPassThrough) {}

	inline int id() const {return i_id;}
	inline const char* name() const {return s_name;}
	inline bool isBreakable() const {return b_breakable;}
	inline bool canPassThrough() const {return b_canPassThrough;}
	inline virtual bool isCube() const {return false;} //!< Whether the block is a cube or not

	/*! Set the texture coordinates of the block */
	inline void setTexture(const TexCoords& texture1, const TexCoords& texture2, const TexCoords& texture3, const TexCoords& texture4) {
		m_texturePos[0] = texture1; m_texturePos[1] = texture2; m_texturePos[2] = texture3; m_texturePos[3] = texture4;
	}

	inline TexCoords* getTexture() {return m_texturePos;}

	/*! Draw block geometry at position using blockInfo, in the targetBuffer */
	inline virtual void render(OpenGLBuffer& targetBuffer, const BlockInfo& blockInfo, const BlockPosition& position, const World& workingWorld) const {/* draw nothing */}

protected:
	// General
	int i_id;
	const char* s_name;

	// Properties
	bool b_breakable;
	bool b_canPassThrough;

	// Apparence
	TexCoords m_texturePos[4];
};

#endif // BLOCKDESCRIPTOR_H
