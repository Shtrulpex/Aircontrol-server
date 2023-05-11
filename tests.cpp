#include "tests.h"


void print_airports(const std::vector<Airport>& airports)
{
    for(auto a : airports)
    {
        std::cout << a.country.eng << " | " << a.country.rus << " | " <<
                     a.city.eng << " | " << a.city.rus << " | " <<
                     a.name.eng << " | " << a.name.rus << " | " <<
                     a.icao_code << " | " << a.iata_code << " | " << a.iso_code << " | " << a.gmt << " | " <<
                     a.loc.latitude << " | " << a.loc.longitude << " | " <<
                     a.runway_length << " | " << a.loc.height << std::endl;
    }
}


void test_1()
{
    AirportQuery example;
    example.country.eng = "Russian Federation";
    print_airports(run_query(example));
}


void test_2()
{
    AirportQuery example;
    example.country.eng = "Russian Federation";
    example.max_radius = 100; // ищем в радиусе 100 км
    example.loc.latitude = 55.7522; // широта Москвы
    example.loc.longitude = 37.6156; // долгота Москвы

    std::cout << get_sqlquery(example).toStdString();
}


