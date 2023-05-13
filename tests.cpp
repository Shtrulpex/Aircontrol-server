#include "tests.h"


void print_airports(const std::vector<Airport>& airports)
{
    std::cout << "------------------------------------------------------------------------" << std::endl;
    for(auto a : airports)
    {
        std::cout << a.country.eng << " | " << a.country.rus << " | " <<
                     a.city.eng << " | " << a.city.rus << " | " <<
                     a.name.eng << " | " << a.name.rus << " | " <<
                     a.icao_code << " | " << a.iata_code << " | " << a.iso_code << " | " << a.gmt << " | " <<
                     a.loc.latitude << " | " << a.loc.longitude << " | " <<
                     a.runway_length << " | " << a.loc.height << std::endl;
    }
    std::cout << "------------------------------------------------------------------------" << std::endl;
}


void print_planes(const std::vector<Plane>& planes)
{
    std::cout << "------------------------------------------------------------------------" << std::endl;
    for(auto a : planes)
    {
        std::cout << a.name.eng << " | " << a.name.rus << " | " <<
                     a.velocity << " | " << a.flight_length  << " | " << a.flight_height << " | " <<
                     a.required_runway_length << " | " << a.weight_capacity << std::endl;
    }
    std::cout << "------------------------------------------------------------------------" << std::endl;
}


// only how forme sqlquery
void test_1()
{
    AirportQuery example;
    example.country.eng = "Russian Federation";
    example.max_radius = 100; // ищем в радиусе 100 км
    example.loc.latitude = 55.7522; // широта Москвы
    example.loc.longitude = 37.6156; // долгота Москвы

    std::cout << get_sqlquery(example).toStdString() << std::endl;;
}


// only by country
void test_2()
{
    AirportQuery example;
    example.country.eng = "Russian Federation";
    print_airports(run_query(example));
}


// search airports by substring in name of its city
void test_3()
{
    AirportQuery example;
    example.city.eng = "mos";
    print_airports(run_query(example));
}


// only how forme sqlquery
void test_4()
{
    PlaneQuery example;
//    example.min_velocity = 600;
//    example.min_flight_height = 8000;
    example.name.eng = "tu";
    std::cout << get_sqlquery(example).toStdString() << std::endl;
}

// only by min_velocity
void test_5()
{
     PlaneQuery example;
     example.min_velocity = 1000;
     print_planes(run_query(example));
}

// search planes by substring in its name
void test_6()
{
    PlaneQuery example;
    example.name.eng = "tu";
    print_planes(run_query(example));
}
