#ifndef CHUNKDRAWER_H
#define CHUNKDRAWER_H

#include <QThread>
#include "OpenGL.h"

class BlockInfo;
struct BlockSet;
class Chunk;
class OpenGLBuffer;

/*! Class to render Chunk geometry into a OpenGLBuffer.
	Vertex array is computed in a separate thread when called throught the slot generateVBO(),
	but the effective render (ie. OpenGL calls) is done in the render() method, and MUST be called from the main thread */
class ChunkDrawer : public QObject
{
	Q_OBJECT

public:
	ChunkDrawer(Chunk* chunkToDraw);
	~ChunkDrawer();

	/*! Render the Vertex Buffer Object of the Chunk
		\warning This method DO OpenGL calls, so it must not be called through a thread slot */
	void render();

public slots:

	/*! Generates the Vertex Buffer Object of the Chunk
		\warning This method must not have OpenGL calls, so it can be called in a thread */
	void generateVBO();

private:
	/*! Put all topBlocks of the blokSet in block and alls blocks in BottomsBlocks.
	  Doing this to iterate over Y avoids a lot of block access in the world */
	void pushBlockSetUpwards(BlockSet& blockSet) const;

	Chunk* m_chunkToDraw;
	OpenGLBuffer* m_oglBuffer;
	QThread* m_workingThread;
};

#endif // CHUNKDRAWER_H
