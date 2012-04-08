#ifndef BLOCKDESCRIPTOR_H
#define BLOCKDESCRIPTOR_H

#include <QColor>
#include <QString>

#include "Vector.h"
#include "gui/TextureManager.h" // TextureCoordinates

class BlockInfo;

/*! Holds informations about a type of block such as texture, resistance, name... */
class BlockDescriptor
{
public:
	BlockDescriptor(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true, const bool isCube = true)
		: i_id(id), s_name(name), b_breakable(breakable), b_canPassThrough(canPassThrough), b_isCube(isCube) {}

	inline int id() const {return i_id;}
	inline const char* name() {return s_name;}
	inline bool isBreakable() const {return b_breakable;}
	inline bool canPassThrough() const {return b_canPassThrough;}
	inline bool isCube() const {return b_isCube;}

	/*! Set the texture coordinates of the block */
	inline void setTexture(const TexCoords& texture1, const TexCoords& texture2, const TexCoords& texture3, const TexCoords& texture4) {
		m_texturePos[0] = texture1; m_texturePos[1] = texture2; m_texturePos[2] = texture3; m_texturePos[3] = texture4;
	}

	inline TexCoords* getTexture() {return m_texturePos;}

private:
	// General
	int i_id;
	const char* s_name;

	// Properties
	bool b_breakable;
	bool b_canPassThrough;

	// Apparence
	bool b_isCube;
	TexCoords m_texturePos[4];
};


inline bool operator==(const BlockDescriptor& blockDescriptor, const BlockInfo& blockInfo) {
	return (blockInfo.id() == blockDescriptor.id());
}

inline bool operator==(const BlockInfo& blockInfo, const BlockDescriptor& blockDescriptor) {
	return (blockInfo.id() == blockDescriptor.id());
}

inline bool operator!=(const BlockDescriptor& blockDescriptor, const BlockInfo& blockInfo) {
	return !(blockDescriptor == blockInfo);
}

inline bool operator!=(const BlockInfo& blockInfo, const BlockDescriptor& blockDescriptor) {
	return !(blockDescriptor == blockInfo);
}


#endif // BLOCKDESCRIPTOR_H
