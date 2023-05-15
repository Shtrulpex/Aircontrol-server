#ifndef DB_INTERFACE_H
#define DB_INTERFACE_H

#include <string>
#include "data_struct.h"


std::vector<Airport> run_query(const AirportQuery& query, const std::string& db_filepath);
std::vector<Plane> run_query(const PlaneQuery& query, const std::string& db_filepath);

#endif
