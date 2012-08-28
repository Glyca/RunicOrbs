#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QLabel>

class ServerConnector;

/*! This widget is displayed when loading a world and loads it */
class LoadingWidget : public QLabel
{
	Q_OBJECT
public:
	explicit LoadingWidget();
	virtual ~LoadingWidget();

	bool loadSoloGame();
	bool loadMultiplayerGame(const QString &hostName, quint16 port, const QString& nickName);

public slots:
	void startGame();
private:
	ServerConnector* m_connectorToBeUsed;
};

#endif // LOADINGWIDGET_H
