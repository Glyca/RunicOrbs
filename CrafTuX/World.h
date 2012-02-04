#ifndef WORLD_H
#define WORLD_H

#include <QObject>

#include "BlockInfo.h"
#include "Chunk.h"
#include "Entity.h"
#include "PhysicEngine.h"
#include "Vector.h"

class World : public QObject
{
	Q_OBJECT
public:
	explicit World(QObject *parent = 0);

	static void vector2int(Vector& vector, int& ix, int& iy, int& iz);
	BlockInfo* block(Vector& position);
	
signals:
	
public slots:

private:
	QList<Chunk*> m_chunks;
	QList<Entity*> m_entities;
	PhysicEngine* m_physicEngine;
	int i_time;
	int i_seed;

	
};

#endif // WORLD_H
