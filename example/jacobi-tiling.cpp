// use AVX 指令集，编译器自动向量化
// 单时间步jacobi测试baseline和框型分块优化
// capacity=6MB

#include <omp.h>
#include <iostream>

#include "../myWrapper.hpp"

const size_t RANGE = 256 * 256 * 256;
const size_t H = 256 * 16, W = 256 * 16;
const size_t Z = 256, Y = 256, X = 256;

const size_t TS2d = 256; // Tile Size for 2d
const size_t TS3d = 40; // Tile Size for 3d

float wf[RANGE], rf[RANGE];

// 内核执行器
// @param mape memory_access_per_element
// @param ope operations_per_element
inline void kernel_exec(void (*kernel)(), const double & mape, const double & ope);

// 读访问loc=0.25
inline void jacobi_2d5pt_baseline();
inline void jacobi_2d5pt_tiled();

// 读访问loc=0.125
inline void jacobi_2d9pt_baseline();
inline void jacobi_2d9pt_tiled();

// 读访问loc=1/18=0.06
inline void jacobi_3d19pt_baseline();
inline void jacobi_3d19pt_tiled();

int main()
{
    std::cout << "----------------jacobi_2d5pt_baseline----------------" << std::endl;
    kernel_exec(jacobi_2d5pt_baseline, sizeof(float) * 2, 4.0);
    std::cout << "----------------jacobi_2d5pt_tiled----------------" << std::endl;
    kernel_exec(jacobi_2d5pt_tiled, sizeof(float) * 2, 4.0);

    std::cout << std::endl;
    std::cout << "----------------jacobi_2d9pt_baseline----------------" << std::endl;
    kernel_exec(jacobi_2d9pt_baseline, sizeof(float) * 2, 8.0);
    std::cout << "----------------jacobi_2d9pt_tiled----------------" << std::endl;
    kernel_exec(jacobi_2d9pt_tiled, sizeof(float) * 2, 8.0);

    std::cout << std::endl;
    std::cout << "----------------jacobi_3d19pt_baseline----------------" << std::endl;
    kernel_exec(jacobi_3d19pt_baseline, sizeof(float) * 2, 18.0);
    std::cout << "----------------jacobi_3d19pt_tiled----------------" << std::endl;
    kernel_exec(jacobi_3d19pt_tiled, sizeof(float) * 2, 18.0);

    return 0;
}

inline void kernel_exec(void (*kernel)(), const double & mape, const double & ope)
{
    // 初始化数据
    fillAll(wf, RANGE, 0.0);
    fillAll(rf, RANGE, 2.0);

    // 清洗cache
    flushCache(RANGE);

    Timer timer;
    timer.start();

    // kernel
    kernel();
    
    const double runtime = timer.end_s();
    print_performance(runtime, mape * (double)RANGE, ope * (double)RANGE, RANGE);
}

inline void jacobi_2d5pt_baseline()
{
    const size_t HH = H - 1, WW = W - 1;
    // baseline
    #pragma omp parallel for
    for (size_t h = 1; h < HH; h++)
        for (size_t w = 1; w < WW; w++)
            wf[h * W + w] = 0.25 * (
                rf[(h - 1) * W + w] + rf[(h + 1) * W + w] +
                rf[h * W + w - 1] + rf[h * W + w + 1]
            );
}

inline void jacobi_2d5pt_tiled()
{
    const size_t TH = H / TS2d;
    const size_t TW = W / TS2d;
    // tile
    #pragma omp parallel for
    for (size_t th = 0; th < TH; th++)
    {
        const size_t hs = th * TS2d + 1;
        size_t he = hs + TS2d;
        if (he >= H) he = H - 1;
        for (size_t tw = 0; tw < TW; tw++)
        {
            const size_t ws = tw * TS2d + 1;
            size_t we = ws + TS2d;
            if (we >= W) we = W - 1;
            for (size_t h = hs; h < he; h++)
                for (size_t w = ws; w < we; w++)
                    wf[h * W + w] = 0.25 * (
                        rf[(h - 1) * W + w] + rf[(h + 1) * W + w] +
                        rf[h * W + w - 1] + rf[h * W + w + 1]
                    );
        }
    }
}

inline void jacobi_2d9pt_baseline()
{
    const size_t HH = H - 1, WW = W - 1;
    // baseline
    #pragma omp parallel for
    for (size_t h = 1; h < HH; h++)
        for (size_t w = 1; w < WW; w++)
            wf[h * W + w] = 0.125 * (
                rf[(h - 1) * W + w] + rf[(h + 1) * W + w] +
                rf[h * W + w - 1] + rf[h * W + w + 1] + 
                rf[(h - 1) * W + w - 1] + rf[(h - 1) * W + w + 1] + 
                rf[(h + 1) * W + w - 1] + rf[(h + 1) * W + w + 1]
            );
}

inline void jacobi_2d9pt_tiled()
{
    const size_t TH = H / TS2d;
    const size_t TW = W / TS2d;
    // tile
    #pragma omp parallel for
    for (size_t th = 0; th < TH; th++)
    {
        const size_t hs = th * TS2d + 1;
        size_t he = hs + TS2d;
        if (he >= H) he = H - 1;
        for (size_t tw = 0; tw < TW; tw++)
        {
            const size_t ws = tw * TS2d + 1;
            size_t we = ws + TS2d;
            if (we >= W) we = W - 1;
            for (size_t h = hs; h < he; h++)
                for (size_t w = ws; w < we; w++)
                    wf[h * W + w] = 0.125 * (
                        rf[(h - 1) * W + w] + rf[(h + 1) * W + w] +
                        rf[h * W + w - 1] + rf[h * W + w + 1] + 
                        rf[(h - 1) * W + w - 1] + rf[(h - 1) * W + w + 1] + 
                        rf[(h + 1) * W + w - 1] + rf[(h + 1) * W + w + 1]
                    );
        }
    }
}

inline void jacobi_3d19pt_baseline()
{
    const size_t ZZ = Z - 1;
    const size_t YY = Y - 1;
    const size_t XX = X - 1;
    const size_t YX = Y * X;
    const float scalar = 1.0f / 18.0f;
    #pragma omp parallel for
    for (size_t z = 1; z < ZZ; z++)
        for (size_t y = 1; y < YY; y++)
            for (size_t x = 1; x < XX; x++)
                wf[z * YX + y * X + x] = scalar * (
                    rf[(z - 1) * YX + y * X + x] + rf[(z + 1) * YX + y * X + x] +
                    rf[z * YX + (y - 1) * X + x] + rf[z * YX + (y + 1) * X + x] +
                    rf[z * YX + y * X + x - 1] + rf[z * YX + y * X + x + 1] +
                    rf[z * YX + (y - 1) * X + x - 1] + rf[z * YX + (y - 1) * X + x + 1] +
                    rf[z * YX + (y + 1) * X + x - 1] + rf[z * YX + (y + 1) + x + 1] +
                    rf[(z - 1) * YX + y * X + x - 1] + rf[(z - 1) * YX + y * X + x + 1] +
                    rf[(z + 1) * YX + y * X + x - 1] + rf[(z + 1) * YX + y * X + x + 1] +
                    rf[(z - 1) * YX + (y - 1) * X + x] + rf[(z - 1) * YX + (y + 1) * X + x] +
                    rf[(z + 1) * YX + (y - 1) * X + x] + rf[(z + 1) * YX + (y + 1) * X + x]
                );
}

inline void jacobi_3d19pt_tiled()
{
    const size_t TZ = Z / TS3d;
    const size_t TY = Y / TS3d;
    const size_t TX = X / TS3d;
    const size_t YX = Y * X;
    const float scalar = 1.0f / 18.0f;
    #pragma omp parallel for
    for (size_t tz = 0; tz < TZ; tz++)
    {
        const size_t zs = tz * TS3d + 1;
        size_t ze = zs + TS3d;
        if (ze >= Z) ze = Z - 1;
        for (size_t ty = 0; ty < TY; ty++)
        {
            const size_t ys = ty * TS3d + 1;
            size_t ye = ys + TS3d;
            if (ye >= Y) ye = Y - 1;
            for (size_t tx = 0; tx < TX; tx++)
            {
                const size_t xs = tx * TS3d + 1;
                size_t xe = xs + TS3d;
                if (xe >= X) xe = X - 1;
                for (size_t z = zs; z < ze; z++)
                    for (size_t y = ys; y < ye; y++)
                        for (size_t x = xs; x < xe; x++)
                            wf[z * YX + y * X + x] = scalar * (
                                rf[(z - 1) * YX + y * X + x] + rf[(z + 1) * YX + y * X + x] +
                                rf[z * YX + (y - 1) * X + x] + rf[z * YX + (y + 1) * X + x] +
                                rf[z * YX + y * X + x - 1] + rf[z * YX + y * X + x + 1] +
                                rf[z * YX + (y - 1) * X + x - 1] + rf[z * YX + (y - 1) * X + x + 1] +
                                rf[z * YX + (y + 1) * X + x - 1] + rf[z * YX + (y + 1) + x + 1] +
                                rf[(z - 1) * YX + y * X + x - 1] + rf[(z - 1) * YX + y * X + x + 1] +
                                rf[(z + 1) * YX + y * X + x - 1] + rf[(z + 1) * YX + y * X + x + 1] +
                                rf[(z - 1) * YX + (y - 1) * X + x] + rf[(z - 1) * YX + (y + 1) * X + x] +
                                rf[(z + 1) * YX + (y - 1) * X + x] + rf[(z + 1) * YX + (y + 1) * X + x]
                            );
            }
        }
    }
}