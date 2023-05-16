#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>


enum QueryType
{
    PLANE = 0,
    AIRPORT = 1,
    PATH_LEN = 2,
    PATH_2D = 3,
//  PATH_3D = 4
};


struct Point
{
    double longitude{0.0};
    double latitude{0.0};
    double height{0.0};
};


struct Name
{
    std::string eng{""};
    std::string rus{""};
};


struct Airport
{
    Point loc;
    double runway_length{0.0};
    double gmt{0.0};
    std::string iata_code{""};
    std::string icao_code{""};
    std::string iso_code{""};
    Name name;
    Name city;
    Name country;
};


struct Plane
{
    double flight_length{0.0};
    double flight_height{0.0};
    double velocity{0.0};
    double weight_capacity{0.0};
    double required_runway_length{0.0};
    Name name;
};


struct AirportQuery
{
    Point loc;
    double max_radius{0.0};
    double min_runway_length{0.0};
    std::string iata_code{""};
    std::string icao_code{""};
    std::string iso_code{""};
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
    double min_weight_capacity{0.0};
    double max_required_runway_length{0.0};
    Name name;
};


#endif // DATA_STRUCT_H
