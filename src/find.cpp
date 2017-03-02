#define _POSIX_C_SOURCE 199309L

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <math.h>
#include <time.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <mmintrin.h>
#include <pthread.h>

#include "tbb/parallel_for.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"

#include "find.hpp"

#define TEST_NUM 10000

using namespace tbb;
using namespace std;

float compare0(const float *a, const float *b, int dimen) {
    float cross = 0;
    float sq1 = 0;
    float sq2 = 0;

    for (int i = 0; i < dimen; i++) {
        cross += a[i] * b[i];
        sq1 += a[i] * a[i];
        sq2 += b[i] * b[i];
    }

    return cross / (sqrt(sq1) * sqrt(sq2));
}


float compare1(const float* pVect1, const float* pVect2, int dimen) {
    const float* pEnd = pVect1 + dimen;

    __m256 v1, v2;
    __m256 sum_prod    = _mm256_set1_ps(0);
    __m256 sum_square1 = sum_prod;
    __m256 sum_square2 = sum_prod;

    /* 现在只处理dimen可以被32整除的情况 */
    while (pVect1 < pEnd) {
        v1 = _mm256_loadu_ps(pVect1); pVect1 += 8;
        v2 = _mm256_loadu_ps(pVect2); pVect2 += 8;
        sum_prod    = _mm256_add_ps(sum_prod,    _mm256_mul_ps(v1, v2));
        sum_square1 = _mm256_add_ps(sum_square1, _mm256_mul_ps(v1, v1));
        sum_square2 = _mm256_add_ps(sum_square2, _mm256_mul_ps(v2, v2));

        v1 = _mm256_loadu_ps(pVect1); pVect1 += 8;
        v2 = _mm256_loadu_ps(pVect2); pVect2 += 8;
        sum_prod    = _mm256_add_ps(sum_prod,    _mm256_mul_ps(v1, v2));
        sum_square1 = _mm256_add_ps(sum_square1, _mm256_mul_ps(v1, v1));
        sum_square2 = _mm256_add_ps(sum_square2, _mm256_mul_ps(v2, v2));

        v1 = _mm256_loadu_ps(pVect1); pVect1 += 8;
        v2 = _mm256_loadu_ps(pVect2); pVect2 += 8;
        sum_prod    = _mm256_add_ps(sum_prod,    _mm256_mul_ps(v1, v2));
        sum_square1 = _mm256_add_ps(sum_square1, _mm256_mul_ps(v1, v1));
        sum_square2 = _mm256_add_ps(sum_square2, _mm256_mul_ps(v2, v2));

        v1 = _mm256_loadu_ps(pVect1); pVect1 += 8;
        v2 = _mm256_loadu_ps(pVect2); pVect2 += 8;
        sum_prod    = _mm256_add_ps(sum_prod,    _mm256_mul_ps(v1, v2));
        sum_square1 = _mm256_add_ps(sum_square1, _mm256_mul_ps(v1, v1));
        sum_square2 = _mm256_add_ps(sum_square2, _mm256_mul_ps(v2, v2));
    }

    __m256 t1 = _mm256_hadd_ps(sum_prod,sum_prod);
    __m256 t2 = _mm256_hadd_ps(t1,t1);
    __m128 t3 = _mm256_extractf128_ps(t2,1);
    __m128 t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
    float sum = _mm_cvtss_f32(t4);

    t1 = _mm256_hadd_ps(sum_square1, sum_square1);
    t2 = _mm256_hadd_ps(t1, t1);
    t3 = _mm256_extractf128_ps(t2, 1);
    t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
    float s1 = _mm_cvtss_f32(t4);

    t1 = _mm256_hadd_ps(sum_square2, sum_square2);
    t2 = _mm256_hadd_ps(t1,t1);
    t3 = _mm256_extractf128_ps(t2,1);
    t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
    float s2 = _mm_cvtss_f32(t4);

    return sum / sqrt(s1 * s2);
}

pool *create_search_pool(float *data, int dimen, int size) {
    pool *p = (pool*)malloc(sizeof(pool));
    p->data = data;
    p->dimen = dimen;
    p->size = size;

    return p;
}

void destroy_search_pool(pool* p) {
    free(p);
}

int find0(float *target, pool *p, float *d) {
    float best = -1.0F;
    int idx = 0;

    for (int i = 0; i < p->size; i++) {
        float dis = compare0(target, p->data + i * p->dimen, p->dimen);
        if (dis > best) {
            idx = i;
            best = dis;
        }
    }

    *d = best;
    return idx;
}

int find1(float *target, pool *p, float *d) {
    float best = -1.0F;
    float dis;
    int idx = 0;

    for (int i = 0; i < p->size ; i++) {
        dis = compare1(target, p->data + i * p->dimen, p->dimen);
        if (dis > best) {
            idx = i;
            best = dis;
        }
    }

    *d = best;
    return idx;
}

class Foo {
    float *data;
    int   dimen;
    float *target;
    float (*cmp)(const float*, const float*, int);

public:
    int best_idx;
    float best_val;
    void operator()(const blocked_range<size_t>& r) {
        for (size_t i = r.begin(); i != r.end(); i++) {
            float dis = cmp(target, data + i * dimen, dimen);
            if (dis > best_val) {
                best_idx = i;
                best_val = dis;
            }
        }
    }
    void join(const Foo & y) {
        if (y.best_val > best_val) {
            best_val = y.best_val;
            best_idx = y.best_idx;
        }
    }
    Foo(Foo & x, split) {
        data = x.data;
        dimen = x.dimen;
        target = x.target;
        cmp = x.cmp;
        best_idx = 0;
        best_val = -1.0f;
    }
    Foo(float *d, int dim, float *t, float (*cmpf)(const float*, const float*, int)) {
        data = d;
        dimen = dim;
        target = t;
        cmp = cmpf;
        best_idx = 0;
        best_val = -1.0f;
    }
};

int find2(float *target, pool *p, float *d) {
    Foo foo(p->data, p->dimen, target, compare0);
    //tbb::task_scheduler_init tsi(4);
    parallel_reduce(blocked_range<size_t>(0, p->size),
                    foo, auto_partitioner());
    *d = foo.best_val;
    return foo.best_idx;
}

int find3(float *target, pool *p, float *d) {
    Foo foo(p->data, p->dimen, target, compare1);
    //tbb::task_scheduler_init tsi(4);
    parallel_reduce(blocked_range<size_t>(0, p->size),
                    foo, auto_partitioner());
    *d = foo.best_val;
    return foo.best_idx;
}
