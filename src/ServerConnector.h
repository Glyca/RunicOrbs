#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>

#include "Me.h"
#include "World.h"

class ServerConnector : public QObject
{
	Q_OBJECT
public:
	explicit ServerConnector(QObject *parent = 0);

	virtual World& world();

	inline Me* me() const {return m_me;}

	inline void pickBlock(const BlockPosition& blockPosition) {emit wantPickBlock(blockPosition);}
	inline void useBlock(const BlockPosition& blockPosition) {emit wantUseBlock(blockPosition);}

signals:
	void wantPickBlock(const BlockPosition& blockPosition);
	void wantUseBlock(const BlockPosition& blockPosition);

public slots:

protected:
	Me* m_me;
};

#endif // SERVERCONNECTOR_H
