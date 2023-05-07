#ifndef QUERY_H
#define QUERY_H

#include <string>
#include "support.h"


struct AirportQuery
{
    Point location;
    double max_radius{0.0};
    double min_runway_length{0.0};
    std::string iata_code{""};
    std::string icao_code{""};
    Name name;
    Name city;
    Name country;
    double gnt{0.0};
};


struct PlaneQuery
{
    double min_flight_length{0.0};
    double min_flight_height{0.0};
    double min_velocity{0.0};
    double max_required_runway_length{0.0};  // соответственно и тут поменял
    double min_cargo_weight{0.0};
    Name name;
};


#endif // QUERY_H
