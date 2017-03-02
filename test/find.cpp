#define _POSIX_C_SOURCE 199309L

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <find.hpp>

#include "base.hpp"

int main(int argc, char *argv[]) {
    int num = DFT_NUM;
    
    //(1) read argv[1] as data size
    if (argc == 2) {
        num = atoi(argv[1]);
    }

    //(2) read data
    printf("now read data\n");
    float *data = read_file(num);
    printf("data %p", data);
    //(3) test
    printf("now test\n");
    float target[DIM_NUM];
    int rdx = 0;
    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);

    printf("now create pool\n");
    pool *p = create_search_pool(data, DIM_NUM, num);
    for (int i = 0; i < TEST_NUM; i++) {
        gen_one(target);
#if ALG==0
        rdx += find0(target, p);
#elif ALG==1
        rdx += find1(target, p);
#elif ALG==2
        rdx += find2(target, p);
#elif ALG==3
        rdx += find3(target, p);
#endif
    }
    struct timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    long accum = ( end.tv_sec - start.tv_sec ) * 1000
        + ( end.tv_nsec - start.tv_nsec ) / (1E6);
    printf("totaltime: %ldms \n"
           "throughput: %fcps\n"
           "rdx: %d\n",
           accum,
           (float)TEST_NUM / (float)(accum) * 1000,
           rdx);

    return 0;
}
