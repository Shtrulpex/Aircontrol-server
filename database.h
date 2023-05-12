#ifndef DB_INTERFACE_H
#define DB_INTERFACE_H

#include <string>
#include "data_struct.h"


const std::string DB_FILEPATH = "../Aircontrol-server/resources/air-planner.sqlite";


std::vector<Airport> run_query(const AirportQuery& query, const std::string& db_filepath=DB_FILEPATH);
std::vector<Plane> run_query(const PlaneQuery& query, const std::string& db_filepath=DB_FILEPATH);


#endif // DB_INTERFACE_H
