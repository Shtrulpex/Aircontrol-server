#ifndef DATA_OBJECT_H
#define DATA_OBJECT_H

#include "support.h"


struct Airport
{
    Point location;
    double runway_length{0.0};
    double gmt{0.0}; // нужно ли привязывать к аэропорту или лучше к городу? (внимание, это дабл)
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
    double cargo_weight{0.0};
    double required_runway_length{0.0};  // отклонился от договорённости
    Name name;
};


#endif // DATA_OBJECT_H
