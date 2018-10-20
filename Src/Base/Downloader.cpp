#include "Downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(finish(QNetworkReply*)));
}

void Downloader::setUrl(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(progres(qint64,qint64)));
}

void Downloader::progres(qint64 r, qint64 t)
{
    if(t <= 0)
        return;
    emit downloadProgress(100 * r/t);
}

void Downloader::finish(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError){
        qDebug() << "Error download";
        emit error();
    }else{
        qDebug() << "Done download";
        emit done(reply->url(), reply->readAll());
        emit done(reply->readAll());

    }
}
