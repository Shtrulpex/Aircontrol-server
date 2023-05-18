#include <iostream>
#include "flight_path.cpp"


int main(){
    Point start{52.000000,-0.500000, 0}; //Лондон-Лутон
    Point finish{-33.779147331286474,150.9840973570325, 0}; // Сидней
    Point finish1{-33.779147331286474, -0.500000, 0};
    Point ecv_start{50, -0.500000, 0};
    Point ecv_finish{50, 150.9840973570325, 0};

    std::vector<Point> vec = flight_path(ecv_finish, ecv_start);
    std::cout << path_length (ecv_finish, ecv_start) << std::endl;


    for (int i = 0; i < vec.size(); i += 5)
    {
        std::cout << i << " : " << vec[i].latitude << " , " << vec[i].longtitude << std::endl;
    }
}