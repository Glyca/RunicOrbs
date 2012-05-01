#ifndef BLOCKDESCRIPTOR_H
#define BLOCKDESCRIPTOR_H

#include <QRectF>
#include <QImage>
#include "BlockInfo.h"

class OpenGLBuffer;
class World;

/*! Holds informations about a type of block such as texture, resistance, name... */
class BlockDescriptor
{
public:
	BlockDescriptor(const int id = 0, const char* name = "undefined", const bool breakable = true, const bool canPassThrough = true)
		: i_id(id), s_name(name), b_breakable(breakable), b_canPassThrough(canPassThrough), m_model(NULL) {}

	inline int id() const {return i_id;}
	inline const char* name() const {return s_name;}
	inline bool isBreakable() const {return b_breakable;}
	inline bool canPassThrough() const {return b_canPassThrough;}
	inline virtual bool isCube() const {return false;} //!< Whether the block is a cube or not

	/*! Set the texture coordinates of the block */
	inline virtual void setTexture(const QRectF& texturePos) {m_texturePos = texturePos;}
	inline QRectF& texture() {return m_texturePos;}

	inline void setItemImage(const QImage& image) {qim_item = image;}
	inline QImage& itemImage() {return qim_item;}

	/*! Load the 3d model of the block from a file in modelFolder */
	virtual void loadModel(const QString& modelFolder);

	/*! Draw block geometry at position using blockInfo, in the targetBuffer */
	virtual void render(OpenGLBuffer& targetBuffer, const BlockSet& blockSet, const BlockPosition& position, const World& workingWorld) const;

protected:
	// General
	int i_id;
	const char* s_name;

	// Properties
	bool b_breakable;
	bool b_canPassThrough;

	// Appearance
	OpenGLBuffer* m_model; //!< The 3D model of the block (when not NULL)
	QRectF m_texturePos; //!< The position of the texture of the block in the atlas
	QImage qim_item;
};

#endif // BLOCKDESCRIPTOR_H
