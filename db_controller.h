#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QtSql>
#include "data_object.h"
#include "query.h"
#include <vector>
#include <string>


std::vector<Plane> run_query(const PlaneQuery&);
std::vector<Airport> run_query(const AirportQuery&);

QSqlDatabase connect(const QString& driver, const QString& filepath);

QString get_query(const PlaneQuery&);
QString get_query(const AirportQuery&);

std::vector<Airport> get_airports(const QSqlQuery& q_query);
std::vector<Plane> get_planes(const QSqlQuery& q_query);


#endif // DB_CONTROLLER_H
