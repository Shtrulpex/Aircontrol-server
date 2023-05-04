#ifndef DATA_OBJECT_H
#define DATA_OBJECT_H

#include "support.h"


struct Airport
{
    Point locaction;
    double runway_length;
    std::string iata_code;
    std::string icao_code;
    Name name;
    Name city;
    Name country;
    double gmt; // нужно ли привязывать к аэропорту или лучше к городу? (внимание, это дабл)
};


struct Plane
{
    double flight_length;
    double flight_height;
    double velocity;
    double cargo_weight;
    double required_runway_length;  // отклонился от договорённости
    Name name;
};


#endif // DATA_OBJECT_H
