#include "class.h"

/* 
        Класс Airport должен включать как минимум координаты (широта (latitude), 
    долгота (longtitude)) в виде точки Point.

        Функции angular_path_length() и path_length() определяют угловую (в радианах) 
    и обычную (в метрах) длину пути соответственно.

        Функция  latitude_function() это функция широты от долготы на заданном пути
    (нач. и кон. точки определяют путь).

        Функция  flight_path() определяет путь (вектор Point(широта, долгота)) 
    по аэропортам start и finish при разбиении пути на count точек (включая концы).

*/


constexpr double Earth_radius{6371000};
constexpr double delta{1000}; // разбиение пути
constexpr double w{M_PI / 180}; // преобразование в радианы 



double angular_path_length (Point, Point);
double angular_path_length(const Airport&, const Airport&);

double path_length (double angular);
double path_length (Point, Point);
double path_length (const std::vector<Point>&);
double path_length(const Airport&, const Airport&);
double path_length(const Airport&, const Airport&, const Plane&);

std::vector<Point> flight_path (Point, Point);
std::vector<Point> flight_path (const Airport&, const Airport&); // without high
std::vector<Point> flight_path (const Airport&, const Airport&, const Plane&);  // with high //нет реализации


bool is_current_plane(const Airport&, const Airport&, const Plane&); // without high


double high(Point); // не реализации