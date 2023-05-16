#include <cmath>
#include "flight_path.h"


double angular_path_length (Point A, Point B)
{
    return acos(sin(A.latitude)*sin(B.latitude) + 
                cos(A.latitude)*cos(B.latitude)*cos(B.longitude-A.longitude));
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
    return atan((tan(A.latitude)*sin(B.longitude - longitude) + 
                 tan(B.latitude)*sin(longitude - A.longitude)) /
                 sin(B.longitude - A.longitude));
}


double latitude_function(const Airport& start, const Airport& finish,
                         double longitude)
{
    return latitude_function(start.loc, finish.loc, 
                             longitude);
}



std::vector<Point> flight_path (const Airport& start, const Airport& finish)
{
    double Length{path_length(start, finish)};


    std::vector<Point> path(delta);

    path[0] = start.loc;

    path[delta-1] = finish.loc;


    double current_longitude{path[0].longitude};
    double current_latitude{path[0].latitude};

    for (int i = 1; i < delta - 1; i++)
    {
        current_longitude += Length / (delta - 1);
        current_latitude = latitude_function (start, finish, 
                                              current_longitude);

        path[i] = Point{current_latitude, current_longitude, -1};
    }
    return path;
}

/*
double path_length(const Airport& start, const Airport& finish, const Plane& plane)
{
    std::vector<Point> path = flight_path(start, finish, plane);
    return path_length(path);
}
*/


bool is_current_plane(const Airport& start, const Airport& finish, const Plane& plane)
{
    if (plane.flight_length < path_length(start, finish)) return false;
    if (plane.required_runway_length > start.runway_length ||
        plane.required_runway_length > finish.runway_length)
            return false;
    return true;
}


