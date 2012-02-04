#ifndef PHYSICENGINE_H
#define PHYSICENGINE_H

#include <QObject>
#include <QList>
#include <QElapsedTimer>
#include "PhysicObject.h"

// Singloton class
class PhysicEngine : public QObject
{
	Q_OBJECT
public:
	explicit PhysicEngine(QObject *parent = 0);

	static class PhysicEngine* c_PhysicEngine;
	static PhysicEngine* getPhysicEngine();

	PhysicObject* createPhysicObject(preal mass = f_defaultMass);

	void processMoves();

signals:

public slots:

private:

	QElapsedTimer m_elapsedTimer;
	QList<PhysicObject*> m_physicObjects;

};

#define GlobalPhysicEngine (PhysicEngine::getPhysicEngine())

#endif // PHYSICENGINE_H
