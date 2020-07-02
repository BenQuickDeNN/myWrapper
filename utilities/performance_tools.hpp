#ifndef PERFORMANCE_TOOL_H
#define PERFORMANCE_TOOL_H
#include <iostream>
/**
 * @brief 
 * 
 * @param RunTime           内核运行时间      单位：s
 * @param NoMA              内存IO数据量      单位：Byte
 * @param NoDF              浮点运算次数      单位：Flops
 */
void print_performance(double RunTime, double NoMA, double NoDF, size_t GridSize)
{
    using namespace std;

    double AvgGFlops = NoDF / (1000 * 1000 * 1000) / RunTime;
    double AvgBW = NoMA / (1024 * 1024 * 1024) / RunTime;
    double OperIntensity = NoDF / NoMA;
    cout << "*************************************************************" << endl;
    cout << "The kernel runing time    : " << RunTime << " s." << endl;
    cout << "FP operations per second  : " << AvgGFlops << " GFlops/s." << endl;
    cout << "BandWidth                 : " << AvgBW << " GB/s." << endl;
    cout << "Operational Intensity(OI) : " << OperIntensity << " GFlops/GB" << endl;

    // cout << "FP operations per element : " << NoDF / (GridSize) << " Flops" << endl;
    // cout << "Memory Access per element : " << NoMA / (GridSize) << " Byte" << endl;
    cout << "*************************************************************" << endl;
}

static void flushCache(size_t len)
{
    long int Data_Len = len / 8;
    double *Data = new double[Data_Len];
    for (long int i = 0; i < Data_Len; i++)
        Data[i] = (double)i;
    delete Data;
}

void fillAll(double *ptr, size_t size, double value)
{
    for (size_t i = 0; i < size; i++)
    {
        ptr[i] = value;
    }
}

void fillAll(float *ptr, size_t size, float value)
{
    for (size_t i = 0; i < size; i++)
    {
        ptr[i] = value;
    }
}

#endif