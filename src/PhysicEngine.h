#ifndef PHYSICENGINE_H
#define PHYSICENGINE_H

#include <QObject>
#include <QList>
#include <QElapsedTimer>
#include "PhysicObject.h"

/*! Holds PhysicObject s of a Word */
class PhysicEngine : public QObject
{
	Q_OBJECT
public:
	explicit PhysicEngine(World* world, QObject *parent = 0);

	PhysicObject* createPhysicObject(preal mass = f_defaultMass);

	inline void attach(PhysicObject* po) {m_physicObjects.append(po);}

	void processMoves();

signals:

public slots:

private:

	QElapsedTimer m_elapsedTimer;
	QList<PhysicObject*> m_physicObjects;
	World* m_workingWorld;
};

#endif // PHYSICENGINE_H
