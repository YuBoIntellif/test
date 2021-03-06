#define _POSIX_C_SOURCE 199309L

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <find.hpp>

#include "base.hpp"

#define TEST_NUM 10000

int main(int argc, char *argv[]) {
    int num = DFT_NUM;
    
    //(1) read argv[1] as data size
    if (argc == 2) {
        num = atoi(argv[1]);
    }

    //(2) read data
    float best;
    printf("readdata...\n");
    float *data = read_file(num);
    //(3) test
    printf("testing...\n");
    float target[DIM_NUM];
    struct timespec start;
    clock_gettime(CLOCK_REALTIME, &start);
    pool *p = create_search_pool(data, DIM_NUM, num);
    for (int i = 0; i < TEST_NUM; i++) {
        gen_one(target);
#if ALG==0
        find0(target, p, &best);
#elif ALG==1
        find1(target, p, &best);
#elif ALG==2
        find2(target, p, &best);
#elif ALG==3
        find3(target, p, &best);
#elif ALG==4
        float ba, bb, bc, bd;
        int a = find0(target, p, &ba);
        int b = find1(target, p, &bb);
        int c = find2(target, p, &bc);
        int d = find3(target, p, &bd);
        if (a != b || a != c || a!= d) {
            printf("check fail...%d %d %d %d\n", a, b, c, d);
            printf("             %f %f %f %f\n", ba, bb, bc, bd);
        }
#endif
    }
    struct timespec end;
    clock_gettime(CLOCK_REALTIME, &end);
    long accum = ( end.tv_sec - start.tv_sec ) * 1000
        + ( end.tv_nsec - start.tv_nsec ) / (1E6);
    printf("totaltime: %ldms \n"
           "throughput: %fcps\n",
           accum,
           (float)TEST_NUM / (float)(accum) * 1000);

    return 0;
}
