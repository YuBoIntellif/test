#ifndef __FIND_HPP__
#define __FIND_HPP__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pool {
    float *data;
    int   dimen;
    int   size;
    void *ctx;
} pool;

    pool *create_search_pool(float *data, int dimen, int size);
    void destroy_search_pool(pool* p);

    int find0(float *target, pool *p, float *d);
    int find1(float *target, pool *p, float *d);
    int find2(float *target, pool *p, float *d);
    int find3(float *target, pool *p, float *d);

#ifdef __cplusplus
}
#endif

#endif
