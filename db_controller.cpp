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


QString get_query(const AirportQuery& airport_query)
{

}


QString get_query(const PlaneQuery& plane_query)
{
    return QString("SELECT * FROM airports WHERE iso_code = 'RU'");
}

std::vector<Airport> get_airports(const QSqlQuery& q_query)
{
    QSqlRecord record = q_query.record(); // infromation about query
    std::vector<Airport> airports{};
    while (q_query.next())
    {
        airports.push_back(get_airport());
        qDebug() << q_query.value(record.indexOf("name_rus"));
    }
    return airports;
}



std::vector<Airport> run_query(const AirportQuery& airport_query)
{
    QSqlDatabase sdb = connect(SQL_DRIVER, DB_FILEPATH);

    QSqlQuery q_query;
    QString sql_query = get_query(airport_query);
    bool successful_query = q_query.exec(sql_query);
    if (!successful_query)
    {
        qDebug() << "Can't run query: " << sql_query;
    }

    return get_airports(q_query);
}
