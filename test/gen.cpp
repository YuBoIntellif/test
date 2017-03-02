#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string.h>

#include "base.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int num = DFT_NUM;
    
    //(1) read arg
    if (argc == 2) {
        num = atoi(argv[1]);
    }

    //(2) output data
    srand((unsigned int)time(NULL));
    float res[DIM_NUM];
    for (int i = 0; i < num; i++) {
        gen_one(res);
        print_one(res);
    }
}
