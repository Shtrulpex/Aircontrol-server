#include <iostream>
#include "flight_path.cpp"


int main(){
    Point start{52.000000,-0.500000, 0}; //Лондон-Лутон
    Point finish{-33.779147331286474,150.9840973570325, 0}; // Сидней

    Point start1{-33.000000,-130.500000, 0};

    std::vector<Point> vec = flight_path(start1, finish);
    std::cout << path_length (start1, finish) << std::endl;


    for (int i = 0; i < vec.size(); i += 5)
    {
        std::cout << i << " : " << vec[i].latitude << " , " << vec[i].longtitude << std::endl;
    }
}