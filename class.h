#include <math.h>
#include <vector>
#include <string>
#include <algorithm>



struct Point
{
    double latitude;
    double longtitude;
    double height;
};

struct Name{
    std::string rus;
    std::string eng;
};


struct Airport
{
    Point location;

    Airport(Point p)
        : location{p} {}

    double runway_length;
    std::string iata_code;
    std::string icao_code;
    Name city;
    Name country;
    int gmt;
};


struct Plane{
    double flight_height;
    double velocity;
    double flight_length;
    double runway_length;
    double cargo_weight;
    Name name;
};