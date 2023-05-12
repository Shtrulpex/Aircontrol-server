#include "db_controller.h"
#include "db_controller.hpp"
#include <cmath>


const QString SQL_DRIVER = "QSQLITE";

// Geographic constants
const double meridian = 40008.548;
const double equator = 40075.696;
const double kilometer = 1000;


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
        conditions.push_back(QString("iata_code LIKE '\%%1\%'").arg(QString::fromStdString(aq.iata_code)));
    if (aq.icao_code != "")
        conditions.push_back(QString("icao_code LIKE '\%%1\%'").arg(QString::fromStdString(aq.icao_code)));
    if (aq.iso_code != "")
        conditions.push_back(QString("iso_code LIKE '\%%1\%'").arg(QString::fromStdString(aq.iso_code)));
    if (aq.loc.latitude != 0.0 && aq.loc.longitude != 0.0)
    {
        if (aq.max_radius != 0.0)
        {
            // рассчёт коэф. перевода градусов широты и долготы в метры в окрестности искомой координаты:
            // градус широты в метрах:
            double latitude_coef = meridian / 360;
            // градус долготы в метрах:
            double longitude_coef = cos(aq.loc.latitude) * equator / 360;

            // отбор по квадрату, затем по Пифагору
            conditions.push_back(QString("(latitude > %1 AND latitude < %3) AND "
                                         "(longitude > %4 AND longitude < %6) AND "
                                         "((latitude - %2) * %8)*((latitude - %2) * %8) + "
                                         "((longitude - %5) * %9)*((longitude - %5) * %9) < %7").
                                 arg(QString::number(aq.loc.latitude - aq.max_radius / latitude_coef),
                                     QString::number(aq.loc.latitude),
                                     QString::number(aq.loc.latitude + aq.max_radius / latitude_coef),
                                     QString::number(aq.loc.longitude - aq.max_radius / longitude_coef),
                                     QString::number(aq.loc.longitude),
                                     QString::number(aq.loc.longitude + aq.max_radius / longitude_coef),
                                     QString::number(std::pow(aq.max_radius * kilometer, 2)),
                                     QString::number(latitude_coef),
                                     QString::number(longitude_coef)
                                     ));
        }
        else
        {
            conditions.push_back(QString("latitude = '%1' and longitude = '%2'").
                                 arg(aq.loc.latitude,
                                     aq.loc.longitude));
        }
    }
    if (aq.name.eng != "")
        conditions.push_back(QString("name_eng LIKE '\%%1\%'").arg(QString::fromStdString(aq.name.eng)));
    if (aq.name.rus != "")
        conditions.push_back(QString("name_rus LIKE '\%%1\%'").arg(QString::fromStdString(aq.name.rus)));
    if (aq.country.eng != "")
        conditions.push_back(QString("country_eng LIKE '\%%1\%'").arg(QString::fromStdString(aq.country.eng)));
    if (aq.country.rus != "")
        conditions.push_back(QString("country_rus LIKE '\%%1\%'").arg(QString::fromStdString(aq.country.rus)));
    if (aq.city.eng != "")
        conditions.push_back(QString("city_eng LIKE '\%%1\%'").arg(QString::fromStdString(aq.city.eng)));
    if (aq.city.rus != "")
        conditions.push_back(QString("city_rus LIKE '\%%1\%'").arg(QString::fromStdString(aq.city.rus)));

    if (conditions.size() > 0)
    {
        sqlquery += " WHERE ";
        sqlquery += join(conditions.begin(), conditions.end(), std::string(" AND "));
    }

    return sqlquery;
}


QString get_sqlquery(const PlaneQuery& pq)
{
    QString sqlquery{"SELECT * FROM planes"};
    std::vector<QString> conditions;
    if (pq.min_flight_length != 0.0)
        conditions.push_back(QString("flight_length >= '%1'").arg(pq.min_flight_length));
    if (pq.min_flight_height != 0.0)
        conditions.push_back(QString("flight_height >= %1").arg(pq.min_flight_height));
    if (pq.min_velocity != 0.0)
        conditions.push_back(QString("velocity >= '%1'").arg(pq.min_velocity));
    if (pq.min_weight_capacity != 0.0)
        conditions.push_back(QString("weight_capacity >= '%1'").arg(pq.min_weight_capacity));
    if (pq.max_required_runway_length != 0.0)
        conditions.push_back(QString("required_runway_length <= '%1'").arg(pq.max_required_runway_length));

    if (pq.name.eng != "")
        conditions.push_back(QString("name_eng LIKE '\%%1\%'").arg(QString::fromStdString(pq.name.eng)));
    if (pq.name.rus != "")
        conditions.push_back(QString("name_rus LIKE '\%%1\%'").arg(QString::fromStdString(pq.name.rus)));

    if (conditions.size() > 0)
    {
        sqlquery += " WHERE ";
        sqlquery += join(conditions.begin(), conditions.end(), std::string(" AND "));
    }

    return sqlquery;
}


QSqlQuery run_sqlquery(const QString& sqlquery, const QSqlDatabase& sdb)
{
    QSqlQuery qquery(sdb);
    bool success_run = qquery.exec(sqlquery);
    if (!success_run)
    {
        qDebug() << "Can't run query: " << sqlquery << " " << qquery.lastError();
    }
    return qquery;
}


std::vector<Airport> get_airports(QSqlQuery qquery)
{
    std::vector<Airport> airports;
    QSqlRecord record = qquery.record();

    Point loc;
    double runway_length;
    double gmt;
    std::string iata_code;
    std::string icao_code;
    std::string iso_code;
    Name name;
    Name city;
    Name country;

    double longitude;
    double latitude;
    double height;
    std::string name_eng;
    std::string name_rus;
    std::string city_eng;
    std::string city_rus;
    std::string country_eng;
    std::string country_rus;

    while (qquery.next())
    {
        longitude = qquery.value(record.indexOf("longitude")).toDouble();
        latitude = qquery.value(record.indexOf("latitude")).toDouble();
        height = qquery.value(record.indexOf("runway_elevation")).toDouble();
        loc = Point{longitude, latitude, height};

        runway_length = qquery.value(record.indexOf("runway_length")).toDouble();
        gmt = qquery.value(record.indexOf("gmt_offset")).toDouble();
        iata_code = qquery.value(record.indexOf("iata_code")).toString().toStdString();
        icao_code = qquery.value(record.indexOf("icao_code")).toString().toStdString();
        iso_code = qquery.value(record.indexOf("iso_code")).toString().toStdString();

        name_eng = qquery.value(record.indexOf("name_eng")).toString().toStdString();
        name_rus = qquery.value(record.indexOf("name_rus")).toString().toStdString();
        city_eng = qquery.value(record.indexOf("city_eng")).toString().toStdString();
        city_rus = qquery.value(record.indexOf("city_rus")).toString().toStdString();
        country_eng = qquery.value(record.indexOf("country_eng")).toString().toStdString();
        country_rus = qquery.value(record.indexOf("country_rus")).toString().toStdString();
        name = {name_eng, name_rus};
        city = {city_eng, city_rus};
        country = {country_eng, country_rus};

        airports.push_back({loc,
                           runway_length,
                            gmt,
                            iata_code,
                            icao_code,
                            iso_code,
                            name,
                            city,
                            country
                           });
    }
    return airports;
}


std::vector<Plane> get_planes(QSqlQuery qquery)
{
    std::vector<Plane> planes;
    QSqlRecord record = qquery.record();

    double flight_length;
    double flight_height;
    double velocity;
    double weight_capacity;
    double required_runway_length;
    Name name;

    std::string name_eng;
    std::string name_rus;

    while (qquery.next())
    {
        flight_length = qquery.value(record.indexOf("flight_length")).toDouble();
        flight_height = qquery.value(record.indexOf("flight_height")).toDouble();
        velocity = qquery.value(record.indexOf("velocity")).toDouble();
        weight_capacity = qquery.value(record.indexOf("weight_capacity")).toDouble();
        required_runway_length = qquery.value(record.indexOf("required_runway_length")).toDouble();

        name_eng = qquery.value(record.indexOf("name_eng")).toString().toStdString();
        name_rus = qquery.value(record.indexOf("name_rus")).toString().toStdString();
        name = {name_eng, name_rus};

        planes.push_back({flight_length,
                          flight_height,
                          velocity,
                          weight_capacity,
                          required_runway_length,
                          name});
    }

    return planes;

}


std::vector<Airport> run_query(const AirportQuery& query, const std::string& db_filepath)
{
    QSqlDatabase sdb = connect(SQL_DRIVER, QString::fromStdString(db_filepath));
    QString sqlquery = get_sqlquery(query);
    QSqlQuery qquery = run_sqlquery(sqlquery, sdb);
    return get_airports(qquery);
}


std::vector<Plane> run_query(const PlaneQuery& query, const std::string& db_filepath)
{
    QSqlDatabase sdb = connect(SQL_DRIVER, QString::fromStdString(db_filepath));
    QString sqlquery = get_sqlquery(query);
    QSqlQuery qquery = run_sqlquery(sqlquery, sdb);
    return get_planes(qquery);
}
