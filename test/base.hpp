#ifndef __BASE_HPP__
#define __BASE_HPP__

#define DIM_NUM 128     //特征向量的维数
#define MAX     1000    //随机数的最大值
#define DFT_NUM 1000    //默认的数据规模
#define TEST_NUM 10000

/**
 * 生成一个随机向量
 */    
extern void gen_one(float* res);

/**
 * 从标准输入读取num个向量
 */
extern float *read_data(int num);

/**
 * 从文件num.txt读取num个向量
 */
extern float *read_file(int num);

/**
 * 向标准输出输出一个特征向量
 */
extern void print_one(float* res);
    
#endif
