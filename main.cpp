#include <iostream>
#include "flight_path.cpp"


int main(){
    Point start{52.000000,-0.500000, 0}; //Лондон-Лутон
    Point finish{-33.779147331286474,150.9840973570325, 0}; // Сидней

    std::vector<Point> vec = flight_path(start, finish);
    std::cout << path_length (start, finish) << std::endl;


    for (int i = 0; i < vec.size(); i += 50)
    {
        std::cout << i << " : " << vec[i].latitude << " , " << vec[i].longtitude << std::endl;
    }
}