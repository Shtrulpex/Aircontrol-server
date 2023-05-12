#include <thread>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#include "socket.h"
#include "database.h"

/*
std::vector<Point> flight_path (const Airport&, const Airport&) 
{ std::cout << "path 2D" << std::endl; return { Point{} }; }
std::vector<Point> flight_path (const Airport&, const Airport&, const Plane&)
{ std::cout << "path 3D" << std::endl; return { Point{} }; }
double path_length (const Airport&, const Airport&) 
{ std::cout << "path len" << std::endl; return 10; }
*/

void stop_fun()
{
    std::string s;
    while (1)
    {
        std::cin >> s;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if (s == "stop")
            exit(0);
    }
}


int main()
{
    std::thread stop_th (stop_fun);
    stop_th.detach();

    Socket S ("127.11.0.1", 2034);
    S.listen (10);

    while (1)
    {
        S.accept();
        QueryType t;
        S >> t;
        switch (t)
        {
          case PLANE:
          {
            std::thread plane_th ([](Socket D)
            {
                PlaneQuery pq;
                D >> pq;
                std::this_thread::sleep_for(std::chrono::seconds(10));
                std::vector<Plane> res = run_query(pq);
                D << res;
            }, std::ref(S));
            plane_th.detach();
          } break;

          case AIRPORT:
          {
            std::thread airport_th ([](Socket D)
            {
                AirportQuery aq;
                D >> aq;
                std::vector<Airport> res = run_query(aq);
                D << res;
            }, std::ref(S));
            airport_th.detach();
          } break;

          case PATH_LEN:
          {
            std::thread path_len_th ([](Socket D)
            {
                Airport a1;
                Airport a2;
                D >> a1 >> a2;
                double l = path_length (a1, a2);
                D << l;
            }, std::ref(S));
            path_len_th.detach();
          } break;

          case PATH_2D:
          {
            std::thread path_2D_th ([](Socket D)
            {
                Airport a1;
                Airport a2;
                D >> a1 >> a2;
                std::vector<Point> res = flight_path (a1, a2);
                D << res;
            }, std::ref(S));
            path_2D_th.detach();
          } break;

          case PATH_3D:
          {
            std::thread path_3D_th ([](Socket D)
            {
                Airport a1;
                Airport a2;
                Plane p;
                D >> a1 >> a2 >> p;
                std::vector<Point> res = flight_path (a1, a2, p);
                D << res;
            }, std::ref(S));
            path_3D_th.detach();
          } break;

        }
    }

    return 0;
}
