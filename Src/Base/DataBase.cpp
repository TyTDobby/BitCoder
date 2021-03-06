#include "DataBase.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    nameDataBase =  QApplication::applicationDirPath();
//    if () {
        db = QSqlDatabase::addDatabase("QSQLITE");
//    }
}

DataBase::~DataBase()
{
    db.close();
}

void DataBase::connectToDataBase(QString bit)
{
    nameDataBase = bit;

//    if(nameDataBase.count("/" + bit + ".db") > 1)
//        nameDataBase.remove("/" + bit + ".db");
    if(!QFile::exists(nameDataBase)) {
        qDebug() << "Error: data base does not exist!";
    }
    else {
        this->openDataBase();
    }
}

void DataBase::removeConnection()
{

}

QStringList DataBase::readCryatslInfo(QString crystal, QString seria)
{
    QStringList list;
    QSqlQuery query = QSqlQuery(db);
    QSqlRecord rec;
    if(!query.exec("SELECT * FROM " + seria + " WHERE NUMBER = '" + crystal + "';")){
        qWarning() << query.lastError().text();
    }else{
        while(query.next()){
            rec = query.record();
        }
        for(int i = 0; i < rec.count(); i++){
            list << rec.value(i).toString();
        }
        query.clear();
    }

    return list;
}

QStringList DataBase::readSeria(QString seria)
{
    QStringList list;
    QSqlQuery query = QSqlQuery(db);
    if(!query.exec("SELECT * FROM " + seria)){
        qDebug() << query.lastError().text();
    }else{
        while(query.next()){
            list << query.value("NUMBER").toString();

        }
        query.clear();
    }
    return list;
}

QStringList DataBase::loadCoreSTM32(QString table, QString core)
{
    QStringList list;
    QSqlQuery query = QSqlQuery(db);
    if(!query.exec("SELECT * FROM " + table + " WHERE CORE='" + core + "'")){
        qDebug() << query.lastError().text();
    }else{
        while(query.next()){
            list << query.value("NUMBER").toString();

        }
        query.clear();
    }
    return list;
}

void DataBase::openDataBase()
{
    db.setDatabaseName(nameDataBase);
    if(!db.open()){
        qDebug() << db.lastError().text();
    }
    else{
        qDebug() << "Connect data base: Done!";
    }
}

void DataBase::closeDataBase()
{
    QString connection = db.connectionName();
    db.close();
    db = QSqlDatabase();
    db.removeDatabase(connection);
}
