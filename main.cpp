#include <thread>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "socket.h"
#include "database.h"
#include "flight_path.h"


std::string DB_FILEPATH = "../resources/air-planner.sqlite";


void control_fun(std::string ip, int port)
{
    std::string s;
    std::cout << "Type 'h' or 'help' for command list" << std::endl;
    while (1)
    {
        std::cout << "> " << std::flush;
        std::getline(std::cin, s);
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if (s == "") {}
        else if (s == "stop")
        {
            std::cout << "Are you sure want to stop the server? (type 'y' or 'n') " << std::flush;
            while (1)
            {
                std::string ans;
                std::getline(std::cin, ans);
                transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
                if (ans == "y" || ans == "yes")
                    exit(0);
                else if (ans != "n" && ans != "no")
                    std::cout << "Enter correct value ('y' or 'n') " << std::flush;
                else 
                    break;
            }
        }
        else if (s == "change database")
        {
            std::cout << "Enter database path: " << std::flush;
            std::getline(std::cin, DB_FILEPATH);
            std::cout << "Database set: '" << DB_FILEPATH << "'" << std::endl;
        }
        else if (s == "current database")
            std::cout << "Current database: '" << DB_FILEPATH << "'" << std::endl;
        else if (s == "address")
            std::cout << "ip = " << ip << "\n" << "port = " << port << std::endl;
        else if (s == "help" || s == "h")
        {
            std::cout << "Available commands: \n"
                      << " - Stop\n"
                      << " - Change database\n"
                      << " - Current database\n"
                      << " - Address\n"
                      << std::flush;
        }
        else 
            std::cout << "Unknown command: '" << s << "'" << std::endl;
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Incorrect number of arguments (expected ip and port)" << std::endl;
        return 0;
    }

    std::string ip = argv[1];
    int port;
    {
        std::istringstream iss(argv[2]);
        iss >> port;
    }

    Socket S;
    try
    {
        Socket P (ip, port);
        S = P;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 0;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
    std::cout << "ip = " << ip << "\n" << "port = " << port << std::endl;
    S.listen (10);
    
    std::thread control_th (control_fun, ip, port);
    control_th.detach();

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
                std::vector<Plane> res = run_query(pq, DB_FILEPATH);
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
                std::vector<Airport> res = run_query(aq, DB_FILEPATH);
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

/*        case PATH_3D:
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
*/
        }
    }

    return 0;
}

