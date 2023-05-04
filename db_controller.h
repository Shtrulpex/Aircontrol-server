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


#endif // DB_CONTROLLER_H
