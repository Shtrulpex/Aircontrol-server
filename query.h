#ifndef QUERY_H
#define QUERY_H

#include <string>
#include "support.h"


struct AirportQuery
{
    Point location;
    double max_radius;
    double min_runway_length;
    std::string iata_code;
    std::string icao_code;
    Name name;
    Name city;
    Name country;
    double gnt;
};


struct PlaneQuery
{
    double min_flight_length;
    double min_flight_height;
    double min_velocity;
    double max_required_runway_length;  // соответственно и тут поменял
    double min_cargo_weight;
    Name name;
};


#endif // QUERY_H
