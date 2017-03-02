#include <iostream>
#include <jni.h>
#include <find.hpp>

using namespace std;

/*
 * Class:     JNIFind
 * Method:    create_search_pool
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_JNIFind_create_1search_1pool
(JNIEnv * env, jobject obj, jint dimen, jint size) {
    pool *p = create_search_pool(NULL, dimen, size);
    return (jlong)p;
}

/*
 * Class:     JNIFind
 * Method:    destroy_search_pool
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_JNIFind_destroy_1search_1pool
(JNIEnv * env, jobject obj, jlong pool) {
    pool *p = (pool*)pool;
    destroy_search_pool(p);
}

/*
 * Class:     JNIFind
 * Method:    add_one
 * Signature: (J[F)V
 */
JNIEXPORT void JNICALL Java_JNIFind_add_1one
(JNIEnv * env, jobject obj, jlong pool, jfloatArray array) {
    pool *p = (pool*)pool;
    cout << "add" << p->dimen << " " << p->size << endl;
}

/*
 * Class:     JNIFind
 * Method:    find_0
 * Signature: ([FJ)I
 */
JNIEXPORT jint JNICALL Java_JNIFind_find_10
(JNIEnv * env, jobject obj, jfloatArray array, jlong pool) {
    pool *p = (pool*)pool;
    cout << "find" << p->dimen << " " << p->size << endl;
    return 0;
}
