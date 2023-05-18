#include <iostream>
#include "flight_path.cpp"


int main(){
    Point start{52.000000,-0.500000, 0}; //Лондон-Лутон
    Point finish{-33.779147331286474,150.9840973570325, 0}; // Сидней

    Point start1{60.0, 50.0, 0};
    Point finish1{80.0, 130.0, 0};
    

    std::vector<Point> vec = flight_path(start1, finish1);
    std::cout << path_length (start1, finish1) << std::endl;


    for (int i = 0; i < vec.size(); i += 5)
    {
        std::cout << i << " : " << vec[i].latitude << " , " << vec[i].longtitude << std::endl;
    }
}