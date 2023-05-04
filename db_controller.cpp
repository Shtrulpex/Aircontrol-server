#include "db_controller.h"


const QString SQL_DRIVER = "QSQLITE";
const QString DB_FILEPATH = "../Aircontrol-server/resources/air-planner.sqlite";


QSqlDatabase connect(const QString& driver, const QString& filepath)
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase(driver);
    sdb.setDatabaseName(filepath);

    if (!sdb.open())
    {
           qDebug() << "Can't connect to DB" << sdb.lastError().text();
    }
    return sdb;
}


std::vector<Airport> run_query(const AirportQuery&)
{
    QSqlDatabase sdb = connect(SQL_DRIVER, DB_FILEPATH);
}
