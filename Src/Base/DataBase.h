#pragma once

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QApplication>
#include <QStandardItem>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    void connectToDataBase(QString bit);
    void removeConnection();

    QStringList readCryatslInfo(QString crystal, QString seria);
    QStringList readSeria(QString seria);
    QStringList loadCoreSTM32(QString table, QString core);
    void closeDataBase();

private:
    QSqlDatabase db;
    QString nameDataBase;

    void openDataBase();

};
