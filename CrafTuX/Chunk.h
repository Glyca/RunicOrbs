#ifndef CHUNK_H
#define CHUNK_H

#include <QObject>
#include <QList>

#include "BlockInfo.h"

class Chunk : public QObject
{
	Q_OBJECT
public:
	explicit Chunk(QObject *parent = 0);
	
signals:
	
public slots:
	
};

#endif // CHUNK_H
