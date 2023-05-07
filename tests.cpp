#include "tests.h"


std::ostream &operator<<(std::ostream &o, const Airport &a)
{
    o << a.country.eng << " | " << a.city.eng << " | " << a.name.eng << " | " <<
         a.icao_code << " | " << a.iata_code << " | " <<
         a.locaction.latitude << " | " << a.locaction.longitude << endl;
    return o;
}


void print_airports(const std::vector<Airport>& airports)
{
    for(int i; i < airports.size(); i++)
    {
        std::cout << airports[i] << std::endl;
    }
}


void test_1()
{
    AirportQuery example;
    example.country.eng = "Russian Federation";
//    print_airports(run_query(example));
}


void test_2()
{
    AirportQuery example;
    example.country.eng = "Russian Federation";
    example.max_radius = 1e5;
    example.location.latitude = 41.40338;
    example.location.longitude = 2.17403;

    std::cout << get_sqlquery(example).toStdString();
}


