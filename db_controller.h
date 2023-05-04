#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QtSql>
#include "data_object.h"
#include "query.h"
#include <vector>


std::vector<Plane> run_query(PlaneQuery);
std::vector<Airport> run_query(AirportQuery);


#endif // DB_CONTROLLER_H
