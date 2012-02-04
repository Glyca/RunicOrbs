#ifndef WORLD_H
#define WORLD_H

#include <QObject>

#include "BlockInfo.h"
#include "Chunk.h"
#include "Entity.h"
#include "PhysicEngine.h"
#include "Vector3.h"

class World : public QObject
{
	Q_OBJECT
public:
	explicit World(QObject *parent = 0);

	BlockInfo* block(Vector3& position);
	
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
