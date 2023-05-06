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

QString get_sqlquery(const AirportQuery& aq)
{
    QString sqlquery{"SELECT * FROM airports"};
    std::vector<QString> conditions;
    if (aq.gnt != 0.0)
        conditions.push_back(QString("gnt = '%1'").arg(aq.gnt));
    if (aq.min_runway_length != 0.0)
        conditions.push_back(QString("runway_length >= %1").arg(aq.min_runway_length));
    if (aq.iata_code != "")
        conditions.push_back(QString("iata_code = '%1'").arg(QString::fromStdString(aq.iata_code)));
    if (aq.icao_code != "")
        conditions.push_back(QString("icao_code = '%1'").arg(QString::fromStdString(aq.icao_code)));
    if (aq.location.latitude != 0.0 && aq.location.longitude != 0.0)
    {
        if (aq.max_radius != 0.0)
        {
            // отбор по квадрату, затем по Пифагору
            conditions.push_back(QString("(latitude < %1 AND latitude > %3) AND "
                                         "(longitude < %4 AND longitude > %6) AND "
                                         "POW((latitude - %2) * 111153, 2) + "
                                         "POW((longitude - %5) * 62555.252801631, 2) < %7").
                                 arg(QString::number(aq.location.latitude * 0.99965),
                                     QString::number(aq.location.latitude),
                                     QString::number(aq.location.latitude * 1.00035),
                                     QString::number(aq.location.longitude * 0.99915),
                                     QString::number(aq.location.longitude),
                                     QString::number(aq.location.longitude * 1.00085),
                                     QString::number(std::pow(aq.max_radius, 2))
                                     ));
        }
        else
        {
            conditions.push_back(QString("latitude = '%1' and longitude = '%2'").
                                 arg(aq.location.latitude,
                                     aq.location.longitude));
        }
    }
    if (aq.name.eng != "")
        conditions.push_back(QString("name_eng = '%1'").arg(QString::fromStdString(aq.name.eng)));
    if (aq.name.rus != "")
        conditions.push_back(QString("name_rus = '%1'").arg(QString::fromStdString(aq.name.rus)));
    if (aq.country.eng != "")
        conditions.push_back(QString("country_eng = '%1'").arg(QString::fromStdString(aq.country.eng)));
    if (aq.country.rus != "")
        conditions.push_back(QString("country_rus = '%1'").arg(QString::fromStdString(aq.country.rus)));
    if (aq.city.eng != "")
        conditions.push_back(QString("city_eng = '%1'").arg(QString::fromStdString(aq.city.eng)));
    if (aq.city.rus != "")
        conditions.push_back(QString("city_rus = '%1'").arg(QString::fromStdString(aq.city.rus)));

    if (conditions.size() > 0)
    {
        sqlquery += " WHERE ";
        sqlquery += join(conditions.begin(), conditions.end(), " and ");
    }

    return sqlquery;
}
