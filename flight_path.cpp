#include <cmath>
#include "flight_path.h"


static constexpr double w{M_PI / 180}; // преобразование в радианы 


double angular_path_length (Point A, Point B)
{
    return acos(sin(A.latitude*w)*sin(B.latitude*w) + 
                cos(A.latitude*w)*cos(B.latitude*w)*cos(B.longitude*w-A.longitude*w));
}


double angular_path_length(const Airport& start, const Airport& finish)
{
    return angular_path_length (start.loc, finish.loc);
}


double path_length (double angular_path_length)
{
    return Earth_radius * angular_path_length;
}


double path_length (Point A, Point B)
{
    return Earth_radius * angular_path_length(A, B);
}


double path_length (const std::vector<Point>& path){
    double result_len{0};
    for (int i = 0; i < path.size() - 1; i++)
    {
        result_len += path_length(path[i], path[i+1]);
    }
    return result_len;
}


double path_length(const Airport& start, const Airport& finish)
{
    return path_length (angular_path_length(start, finish));
}


double latitude_function(Point A, Point B, double longitude)
{
    if (A.longitude > B.longitude) std::swap(A, B);
    return atan((tan(A.latitude*w)*sin(B.longitude*w - longitude*w) + 
                 tan(B.latitude*w)*sin(longitude*w - A.longitude*w)) /
                 sin(B.longitude*w - A.longitude*w))/w;
}
    
double latitude_function(const Airport& start, const Airport& finish,
                         double longitude)
{
    return latitude_function(start.loc, finish.loc, 
                             longitude);
}

// [-360; 360] -> [-180; 180]
double right_longitude (double longitude)
{
    if (std::abs(longitude) <= 180) return longitude;
    return (longitude > 0) ? longitude - 360.0 : longitude + 360.0;
}

// [-180; 180] -> [-90; 90]
double right_latitude (double latitude)
{
    if (std::abs(latitude) <= 90) return latitude;
    return (latitude > 0) ? 180.0 - latitude : -180.0 - latitude;
}

//  разница между долготами
double delta_longitude (Point A, Point B)
{
    double delta_A_B{B.longitude - A.longitude};

    if (std::abs(delta_A_B) <= 180) return delta_A_B;
    return (A.longitude > 0) ? delta_A_B + 360.0 : delta_A_B - 360.0;
}

//  разница между широтами
double delta_latitude (Point A, Point B)
{
    if (A.longitude == B.longitude) return B.latitude - A.latitude;

    //if (abs(A.longitude - B.longitude) == 180)
    return (A.longitude > 0) ? 180.0 - (A.latitude + B.latitude) :
                               -180.0 - (A.latitude + B.latitude);
}

// применяется при одинаковой долготе у Point A и Point B 
std::vector<Point> single_flight_path (Point A, Point B)
{
    std::vector<Point> path(delta);
    path[0] = A;
    path[delta-1] = B;

    double current_latitude{A.latitude};

    for (int i = 1; i < delta - 1; i++)
    {
        current_latitude += delta_latitude(A, B) / (delta - 1);

        Point p; 
        p.latitude = current_latitude;
        p.longitude = A.longitude;

        path[i] = p;
    }
    return path;
}

// применяется при долготах с разностью в +-180  
std::vector<Point> communicating_longitudes(Point A, Point B)
{
    std::vector<Point> path(delta);
    path[0] = A;
    path[delta-1] = B;

    double current_latitude{A.latitude};
    double current_longitude{A.longitude};

    for (int i = 1; i < delta - 1; i++)
    {
        current_latitude += delta_latitude(A, B) / (delta - 1);

        if (current_latitude != right_latitude(current_latitude))
            current_longitude = B.longitude;

        Point p; 
        p.latitude = right_latitude(current_latitude);
        p.longitude = current_longitude;

        path[i] = p;
        
    }
    return path;
}   


std::vector<Point> flight_path (Point A, Point B)
{
    if (A.longitude == B.longitude) 
        return single_flight_path(A, B);
    if (std::abs(A.longitude - B.longitude) == 180.0)
        return  communicating_longitudes(A, B);

    std::vector<Point> path(delta);

    path[0] = A;
    path[delta-1] = B;

    double current_longitude{A.longitude};
    double current_latitude{A.latitude};

    double delta_long{delta_longitude (A, B)};

    for (int i = 1; i < delta - 1; i++)
    {
        current_longitude = right_longitude (current_longitude +
                                               delta_long / (delta - 1));
        current_latitude = latitude_function (A, B, 
                                              current_longitude);

        Point p; 
        p.latitude = current_latitude;
        p.longitude = current_longitude;
        path[i] = p;
    }
    return path;
}


std::vector<Point> flight_path (const Airport& start, const Airport& finish)
{
    return flight_path (start.loc, finish.loc);
}


// double path_length(const Airport& start, const Airport& finish, const Plane& plane)
// {
//     std::vector<Point> path = flight_path(start, finish, plane);
//     return path_length(path);
// }


bool is_current_plane(const Airport& start, const Airport& finish, const Plane& plane)
{
    if (plane.flight_length < path_length(start, finish)) return false;
    if ((plane.required_runway_length > start.runway_length) ||
        (plane.required_runway_length > finish.runway_length)) 
            return false;
    return true;
}

std::vector<Airport> reached_Airports(const Airport& start, const Plane& plane, 
                                      const std::vector<Airport>& Airports)
{
    std::vector<Airport> vec;

    for (int i = 0; i < Airports.size(); i++)
    {
        if (is_current_plane(start, Airports[i], plane))
            vec.push_back(Airports[i]);
    }
    return vec;
}


std::vector<Airport*> reached_Airports(const Airport& start, const Plane& plane, 
                                      const std::vector<Airport*>& Airports)
{
    std::vector<Airport*> vec;

    for (int i = 0; i < Airports.size(); i++)
    {
        if (is_current_plane(start, *(Airports[i]), plane))
            vec.push_back(Airports[i]);
    }
    return vec;
}