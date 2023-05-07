#ifndef TESTS_H
#define TESTS_H

#include "db_controller.h"
#include <iostream>
#include <QtSql>
#include <string>


void print_airports(const std::vector<Airport>& airports);

void test_1(); //only country
void test_2(); //only how formed sqlquery


#endif // TESTS_H
