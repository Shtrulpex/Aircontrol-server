#ifndef TESTS_H
#define TESTS_H

#include "db_controller.h"
#include <iostream>
#include <QtSql>
#include <string>


void print_airports(const std::vector<Airport>& airports);
void print_planes(const std::vector<Plane>& planes);

// airports query
void test_1(); // only how forme sqlquery
void test_2(); // only by country
void test_3(); // search airports by substring in name of its city

// planes query
void test_4(); // only how forme sqlquery
void test_5(); // only by min_velocity
void test_6(); // search planes by substring in its name


#endif // TESTS_H
