#include <cstdio>
#include <jni.h>
#include <find.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     JNIFind
 * Method:    create_search_pool
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_JNIFind_create_1search_1pool
(JNIEnv *env, jobject obj, jfloatArray arr, jint dimen, jint size) {
    jfloat *body = env->GetFloatArrayElements(arr, 0);
    pool *p = create_search_pool((float*)body, dimen, size);
    return (jlong)p;
}

/*
 * Class:     JNIFind
 * Method:    destroy_search_pool
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_JNIFind_destroy_1search_1pool
(JNIEnv * env, jobject obj, jlong poolLong) {
    pool *p = (pool*)poolLong;
    destroy_search_pool(p);
}

/*
 * Class:     JNIFind
 * Method:    find_0
 * Signature: ([FJ)I
 */
JNIEXPORT jint JNICALL Java_JNIFind_find_10
(JNIEnv * env, jobject obj, jfloatArray array, jlong poolL) {
    pool *p = (pool*)poolL;
    jfloat *body = env->GetFloatArrayElements(array, 0);
    return find0((float*)body, p);
}

/*
 * Class:     JNIFind
 * Method:    find_1
 * Signature: ([FJ)I
 */
JNIEXPORT jint JNICALL Java_JNIFind_find_11
(JNIEnv * env, jobject obj, jfloatArray array, jlong poolL) {
    pool *p = (pool*)poolL;
    jfloat *body = env->GetFloatArrayElements(array, 0);
    return find1((float*)body, p);
}

/*
 * Class:     JNIFind
 * Method:    find_2
 * Signature: ([FJ)I
 */
JNIEXPORT jint JNICALL Java_JNIFind_find_12
(JNIEnv * env, jobject obj, jfloatArray array, jlong poolL) {
    pool *p = (pool*)poolL;
    jfloat *body = env->GetFloatArrayElements(array, 0);
    return find2((float*)body, p);
}

/*
 * Class:     JNIFind
 * Method:    find_3
 * Signature: ([FJ)I
 */
JNIEXPORT jint JNICALL Java_JNIFind_find_13
(JNIEnv * env, jobject obj, jfloatArray array, jlong poolL) {
    pool *p = (pool*)poolL;
    jfloat *body = env->GetFloatArrayElements(array, 0);
    return find3((float*)body, p);
}

#ifdef __cplusplus
}
#endif
