#ifndef OTTER_SEARCHESMANAGER_H
#define OTTER_SEARCHESMANAGER_H

#include <QtCore/QFile>
#include <QtGui/QIcon>
#include <QtNetwork/QNetworkAccessManager>

namespace Otter
{

struct SearchUrl
{
	QString url;
	QString enctype;
	QString method;
	QHash<QString, QString> parameters;
};

struct SearchInformation
{
	QString identifier;
	QString title;
	QString description;
	QString shortcut;
	QString encoding;
	QString selfUrl;
	SearchUrl searchUrl;
	SearchUrl suggestionsUrl;
	QIcon icon;
};

class SearchesManager : public QObject
{
	Q_OBJECT

public:
	static void createInstance(QObject *parent = NULL);
	static SearchesManager* getInstance();
	static SearchInformation* getEngine(const QString &identifier);
	static QStringList getEngines();
	static QStringList getShortcuts();
	static bool setupQuery(const QString &query, const QString &engine, QNetworkRequest *request, QNetworkAccessManager::Operation *method, QByteArray *body);

protected:
	static bool addSearch(QIODevice *device, const QString &identifier);

private:
	explicit SearchesManager(QObject *parent = NULL);

	static SearchesManager *m_instance;
	static QStringList m_order;
	static QStringList m_shortcuts;
	static QHash<QString, SearchInformation*> m_engines;

signals:
	void searchAdded(SearchInformation *search);
	void searchModified(SearchInformation *search);
	void searchRemoved(SearchInformation *search);
};

}

#endif