#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

#include <iostream>
#include <random>

using namespace std;

int random_num_func(int lb, int ub){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(lb,ub);
    return distr(gen);
}

#endif