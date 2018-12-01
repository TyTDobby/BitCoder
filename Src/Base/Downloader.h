#pragma once

#include <QObject>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = NULL);

    void setUrl(const QUrl &url);

private:
    QNetworkAccessManager *manager;

signals:
    void downloadProgress(int);
    void done(const QUrl&, const QByteArray&);
    void done(const QByteArray&);
    void error();

private slots:
    void progres(qint64 r, qint64 t);
    void finish(QNetworkReply*);

};

