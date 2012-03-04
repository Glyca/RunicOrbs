#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QHash>
#include <QPair>

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
	~World();

	inline PhysicEngine* physicEngine() const {return m_physicEngine;}

	Chunk* chunk(QPair<int, int> postion);
	Chunk* chunk(const Vector& postion);

	static void vector2int(Vector& vector, int& ix, int& iy, int& iz);
	BlockInfo* block(const Vector& position);

	void render3D();

signals:

public slots:

private:
	QHash<QPair<int, int>, Chunk*> * m_chunks;
	QList<Entity> m_entities;
	PhysicEngine* m_physicEngine;
	int i_time;
	int i_seed;

};

#endif // WORLD_H
