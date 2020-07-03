// use AVX 指令集

#include <omp.h>
#include <iostream>

#include "../myWrapper.hpp"
#include "vecclass/vectorclass.h"

const size_t RANGE = 1024 * 1024;
const size_t STEP = 100;

float wf[RANGE], rf[RANGE];
double wd[RANGE], rd[RANGE];

// 内核执行器
// @param mape memory_access_per_element
// @param ope operations_per_element
inline void kernel_exec(void (*kernel)(), const double & mape, const double & ope);

// 定义内核
// 单精度，每元素操作次数 2
inline void auto_vec_2f();
inline void vecclass_2f();
inline void my_2f();

// 单精度，每元素操作次数 5
inline void auto_vec_5f();
inline void vecclass_5f();
inline void my_5f();

// 单精度，每元素操作次数 9
inline void auto_vec_9f();
inline void vecclass_9f();
inline void my_9f();

// 双精度，每元素操作次数 2
inline void auto_vec_2d();
inline void vecclass_2d();
inline void my_2d();

// 双精度，每元素操作次数 5
inline void auto_vec_5d();
inline void vecclass_5d();
inline void my_5d();

// 双精度，每元素操作次数 9
inline void auto_vec_9d();
inline void vecclass_9d();
inline void my_9d();

int main()
{
    std::cout << "range = " << RANGE << std::endl;
    std::cout << "step = " << STEP << std::endl;
    std::cout << "----------------auto_vec_f----------------" << std::endl; 
    kernel_exec(auto_vec_2f, sizeof(float) * 2.0, 2.0);
    kernel_exec(auto_vec_5f, sizeof(float) * 2.0, 5.0);
    kernel_exec(auto_vec_5f, sizeof(float) * 2.0, 9.0);

    std::cout << "----------------vecclass_f----------------" << std::endl; 
    kernel_exec(vecclass_2f, sizeof(float) * 2.0, 2.0);
    kernel_exec(vecclass_5f, sizeof(float) * 2.0, 5.0);
    kernel_exec(vecclass_5f, sizeof(float) * 2.0, 9.0);

    std::cout << "----------------my_f----------------" << std::endl;
    kernel_exec(my_2f, sizeof(float) * 2.0, 2.0);
    kernel_exec(my_5f, sizeof(float) * 2.0, 5.0);
    kernel_exec(my_5f, sizeof(float) * 2.0, 9.0);

    std::cout << "----------------auto_vec_d----------------" << std::endl; 
    kernel_exec(auto_vec_2d, sizeof(double) * 2.0, 2.0);
    kernel_exec(auto_vec_5d, sizeof(double) * 2.0, 5.0);
    kernel_exec(auto_vec_5d, sizeof(double) * 2.0, 9.0);

    std::cout << "----------------vecclass_d----------------" << std::endl; 
    kernel_exec(vecclass_2d, sizeof(double) * 2.0, 2.0);
    kernel_exec(vecclass_5d, sizeof(double) * 2.0, 5.0);
    kernel_exec(vecclass_5d, sizeof(double) * 2.0, 9.0);

    std::cout << "----------------my_d----------------" << std::endl;
    kernel_exec(my_2d, sizeof(double) * 2.0, 2.0);
    kernel_exec(my_5d, sizeof(double) * 2.0, 5.0);
    kernel_exec(my_5d, sizeof(double) * 2.0, 9.0);

    return 0;
}

inline void kernel_exec(void (*kernel)(), const double & mape, const double & ope)
{
    // 初始化数据
    fillAll(wf, RANGE, 0.0);
    fillAll(rf, RANGE, 2.0);
    fillAll(wd, RANGE, 0.0);
    fillAll(rd, RANGE, 2.0);

    // 清洗cache
    flushCache(RANGE);

    Timer timer;
    timer.start();

    // kernel
    kernel();
    
    const double runtime = timer.end_s();
    print_performance(runtime / (double)STEP, mape * (double)RANGE, ope * (double)RANGE, RANGE);
}

inline void auto_vec_2f()
{
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for
        for (size_t i = 0; i < RANGE; i++)
            wf[i] = 1.0f * rf[i] + 0.5f;
    }
}

inline void auto_vec_5f()
{
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for
        for (size_t i = 0; i < RANGE; i++)
            wf[i] = 2.0f * rf[i] * rf[i] + 3.0f * rf[i] + 1.0f;
    }
}

inline void auto_vec_9f()
{
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for
        for (size_t i = 0; i < RANGE; i++)
            wf[i] = 3.0f * rf[i] * rf[i] * rf[i] + 2.0f * rf[i] * rf[i] + 1.0f * rf[i] + 0.5f;
    }
}

inline void vecclass_2f()
{
    // -msse
    Vec8f mm1;
    Vec8f mm2(1.0f);
    Vec8f mm3(0.5f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += 8)
        {
            mm1.load(rf + i);
            mm1 = mm2 * mm1 + mm3;
            mm1.store(wf + i);
        }
    }
}

inline void vecclass_5f()
{
    // -msse
    Vec8f mm1;
    Vec8f mm2(2.0f);
    Vec8f mm3(3.0f);
    Vec8f mm4(1.0f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += 8)
        {
            mm1.load(rf + i);
            mm1 = mm2 * mm1 * mm1 + mm3 * mm1 + mm4;
            mm1.store(wf + i);
        }
    }
}

inline void vecclass_9f()
{
    // -msse
    Vec8f mm1;
    Vec8f mm2(3.0f);
    Vec8f mm3(2.0f);
    Vec8f mm4(1.0f);
    Vec8f mm5(0.5f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += 8)
        {
            mm1.load(rf + i);
            mm1 = mm2 * mm1 * mm1 * mm1 + mm3 * mm1 * mm1 + mm4 * mm1 + mm5;
            mm1.store(wf + i);
        }
    }
}

inline void my_2f()
{
    mmf mm1, mm2, mm3;
    mm2 = _vset1f(1.0f);
    mm3 = _vset1f(0.5f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += STRIDEF)
        {
            mm1 = _vloadf(rf + i);
            mm1 = _vaddf(_vmulf(mm1, mm2), mm3);
            _vstoref(wf + i, mm1);
        }
    }
}

inline void my_5f()
{
    mmf mm1, mm2, mm3, mm4;
    mm2 = _vset1f(2.0f);
    mm3 = _vset1f(3.0f);
    mm4 = _vset1f(1.0f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += STRIDEF)
        {
            mm1 = _vloadf(rf + i);
            mm1 = _vaddf(
                    _vmulf(mm2, _vmulf(mm1, mm1)), 
                    _vaddf(
                        _vmulf(mm3, mm1), 
                        mm4
                        )
                );
            _vstoref(wf + i, mm1);
        }
    }
}

inline void my_9f()
{
    mmf mm1, mm2, mm3, mm4, mm5;
    mm2 = _vset1f(3.0f);
    mm3 = _vset1f(2.0f);
    mm4 = _vset1f(1.0f);
    mm5 = _vset1f(0.5f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += STRIDEF)
        {
            mm1 = _vloadf(rf + i);
            mm1 = _vaddf(
                    _vaddf(
                        _vmulf(
                            mm2,
                            _vmulf(
                                mm1,
                                _vmulf(
                                    mm1,
                                    mm1
                                )
                            )
                        ),
                        _vmulf(
                            mm3,
                            _vmulf(
                                mm1,
                                mm1
                            )
                        )
                    ),
                    _vaddf(
                        _vmulf(
                            mm4,
                            mm1
                        ),
                        mm5
                    )
                );
            _vstoref(wf + i, mm1);
        }
    }
}

inline void auto_vec_2d()
{
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for
        for (size_t i = 0; i < RANGE; i++)
            wd[i] = 1.0 * rd[i] + 0.5;
    }
}

inline void auto_vec_5d()
{
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for
        for (size_t i = 0; i < RANGE; i++)
            wd[i] = 2.0 * rd[i] * rd[i] + 3.0 * rd[i] + 1.0;
    }
}

inline void auto_vec_9d()
{
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for
        for (size_t i = 0; i < RANGE; i++)
            wd[i] = 3.0 * rd[i] * rd[i] * rd[i] + 2.0 * rd[i] * rd[i] + 1.0 * rd[i] + 0.5;
    }
}

inline void vecclass_2d()
{
    // -mavx
    Vec4d mm1, mm2(1.0), mm3(0.5);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += 4)
        {
            mm1.load(rd + i);
            mm1 = mm2 * mm1 + mm3;
            mm1.store(wd + i);
        }
    }
}

inline void vecclass_5d()
{
    // -mavx
    Vec4d mm1, mm2(2.0), mm3(3.0), mm4(1.0);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += 4)
        {
            mm1.load(rd + i);
            mm1 = mm2 * mm1 * mm1 + mm3 * mm1 + mm4;
            mm1.store(wd + i);
        }
    }
}

inline void vecclass_9d()
{
    // -mavx
    Vec4d mm1, mm2(3.0), mm3(2.0), mm4(1.0), mm5(0.5);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += 4)
        {
            mm1.load(rd + i);
            mm1 = mm2 * mm1 * mm1 * mm1 + mm3 * mm1 * mm1 + mm4 * mm1 + mm5;
            mm1.store(wd + i);
        }
    }
}

inline void my_2d()
{
    mmd mm1, mm2, mm3;
    mm2 = _vset1d(1.0);
    mm3 = _vset1d(0.5);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += STRIDED)
        {
            mm1 = _vloadd(rd + i);
            mm1 = _vaddd(_vmuld(mm1, mm2), mm3);
            _vstored(wd + i, mm1);
        }
    }
}

inline void my_5d()
{
    mmd mm1, mm2, mm3, mm4;
    mm2 = _vset1d(2.0);
    mm3 = _vset1d(3.0);
    mm4 = _vset1d(1.0);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += STRIDED)
        {
            mm1 = _vloadd(rd + i);
            mm1 = _vaddd(
                    _vmuld(mm2, _vmuld(mm1, mm1)), 
                    _vaddd(
                        _vmuld(mm3, mm1), 
                        mm4
                        )
                );
            _vstored(wd + i, mm1);
        }
    }
}

inline void my_9d()
{
    mmd mm1, mm2, mm3, mm4, mm5;
    mm2 = _vset1d(3.0f);
    mm3 = _vset1d(2.0f);
    mm4 = _vset1d(1.0f);
    mm5 = _vset1d(0.5f);
    for (size_t t = 0; t < STEP; t++)
    {
        //#pragma omp parallel for private(mm1)
        for (size_t i = 0; i < RANGE; i += STRIDED)
        {
            mm1 = _vloadd(rd + i);
            mm1 = _vaddd(
                    _vaddd(
                        _vmuld(
                            mm2,
                            _vmuld(
                                mm1,
                                _vmuld(
                                    mm1,
                                    mm1
                                )
                            )
                        ),
                        _vmuld(
                            mm3,
                            _vmuld(
                                mm1,
                                mm1
                            )
                        )
                    ),
                    _vaddd(
                        _vmuld(
                            mm4,
                            mm1
                        ),
                        mm5
                    )
                );
            _vstored(wd + i, mm1);
        }
    }
}