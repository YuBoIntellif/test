#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>

#include "base.hpp"

using namespace std;

void gen_one(float* res) {
    for (int i = 0; i < DIM_NUM; i++) {
        res[i] = ((float)rand()/(float)(RAND_MAX)) * MAX;
    }
}

static void read_one(float* res) {
    int v;
    for (int i = 0; i < DIM_NUM; i++) {
        v = scanf("%f ", &res[i]);
    }
}

float *read_data(int num) {
//    float *res = (float*)aligned_alloc(32, sizeof(float) * DIM_NUM * num);
    float *res = (float*)malloc(sizeof(float) * DIM_NUM * num);
    for (int i = 0; i < num; i++) {
        read_one(res + i * DIM_NUM);
    }

    return res;
}

static void read_one_file(FILE *f, float* res) {
    int v;
    for (int i = 0; i < DIM_NUM; i++) {
        v = fscanf(f, "%f ", &res[i]);
    }
}

float *read_file(int num) {
    char filename[1000];
    sprintf(filename, "%d.txt", num);
    FILE *f = fopen(filename, "r");
    float *res = (float*)aligned_alloc(128, sizeof(float) * DIM_NUM * num);
    for (int i = 0; i < num; i++) {
        read_one_file(f, res + i * DIM_NUM);
    }
    fclose(f);
    return res;
}

void print_one(float* res) {
    for (int i = 0; i < DIM_NUM; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}

