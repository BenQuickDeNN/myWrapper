/*************************************************
 * @author Bin Qu
 * @email benquickdenn@foxmail.com
*************************************************/

#ifndef CONFIGURE_HPP

#define CONFIGURE_HPP

#if defined(_WIN32)

#include <intrin.h> // Windows intrinsics header file
#include <Windows.h>

#elif defined(__linux__)

#include <x86intrin.h> // Linux intrinsics header file
#include <sys/time.h>

#endif

#include <cstdlib>

// 强制内联
#define force_inline inline __attribute__((always_inline))

// single and double type definition
#if defined(__AVX512F__)
typedef __m512 mmf;
typedef __m512d mmd;
#define STRIDEF 16
#define STRIDED 8
#define _vloadf(arr) _mm512_loadu_ps(arr)
#define _vloadd(arr) _mm512_loadu_pd(arr)
#define _vstoref(arr, mm) _mm512_storeu_ps(arr, mm)
#define _vstored(arr, mm) _mm512_storeu_pd(arr, mm)
#define _vset1f(f) _mm512_set1_ps(f)
#define _vset1d(d) _mm512_set1_pd(d)
#define _vsetrf(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15) _mm512_setr_ps(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15)
#define _vsetrd(d0, d1, d2, d3, d4, d5, d6, d7) _mm512_setr_pd(d0, d1, d2, d3, d4, d5, d6, d7)
#define _vaddf(mm1, mm2) _mm512_add_ps(mm1, mm2)
#define _vaddd(mm1, mm2) _mm512_add_pd(mm1, mm2)
#define _vsubf(mm1, mm2) _mm512_sub_ps(mm1, mm2)
#define _vsubd(mm1, mm2) _mm512_sub_pd(mm1, mm2)
#define _vmulf(mm1, mm2) _mm512_mul_ps(mm1, mm2)
#define _vmuld(mm1, mm2) _mm512_mul_pd(mm1, mm2)
#define _vdivf(mm1, mm2) _mm512_div_ps(mm1, mm2)
#define _vdivd(mm1, mm2) _mm512_div_pd(mm1, mm2)
#define _vreduce_addd(mm) _mm512_reduce_add_pd(mm)
#define _vreduce_addf(mm) _mm512_reduce_add_ps(mm)
#elif defined(__AVX__)
typedef __m256 mmf;
typedef __m256d mmd;
#define STRIDEF 8
#define STRIDED 4
#define _vloadf(arr) _mm256_loadu_ps(arr)
#define _vloadd(arr) _mm256_loadu_pd(arr)
#define _vstoref(arr, mm) _mm256_storeu_ps(arr, mm)
#define _vstored(arr, mm) _mm256_storeu_pd(arr, mm)
#define _vset1f(f) _mm256_set1_ps(f)
#define _vset1d(d) _mm256_set1_pd(d)
#define _vsetrf(f0, f1, f2, f3, f4, f5, f6, f7) _mm256_setr_ps(f0, f1, f2, f3, f4, f5, f6, f7)
#define _vsetrd(d0, d1, d2, d3) _mm256_setr_pd(d0, d1, d2, d3)
#define _vaddf(mm1, mm2) _mm256_add_ps(mm1, mm2)
#define _vaddd(mm1, mm2) _mm256_add_pd(mm1, mm2)
#define _vsubf(mm1, mm2) _mm256_sub_ps(mm1, mm2)
#define _vsubd(mm1, mm2) _mm256_sub_pd(mm1, mm2)
#define _vmulf(mm1, mm2) _mm256_mul_ps(mm1, mm2)
#define _vmuld(mm1, mm2) _mm256_mul_pd(mm1, mm2)
#define _vdivf(mm1, mm2) _mm256_div_ps(mm1, mm2)
#define _vdivd(mm1, mm2) _mm256_div_pd(mm1, mm2)
#define _vreduce_addd(mm) _mm256_reduce_add_pd(mm)
#define _vreduce_addf(mm) _mm256_reduce_add_ps(mm)
#elif defined(__SSE__)
typedef __m128 mmf;
typedef __m128d mmd;
#define STRIDEF 4
#define STRIDED 2
#define _vloadf(arr) _mm_loadu_ps(arr)
#define _vloadd(arr) _mm_loadu_pd(arr)
#define _vstoref(arr, mm) _mm_storeu_ps(arr, mm)
#define _vstored(arr, mm) _mm_storeu_pd(arr, mm)
#define _vset1f(f) _mm_set1_ps(f)
#define _vset1d(d) _mm_set1_pd(d)
#define _vsetrf(f0, f1, f2, f3) _mm_setr_ps(f0, f1, f2, f3)
#define _vsetrd(d0, d1) _mm_setr_pd(d0, d1)
#define _vaddf(mm1, mm2) _mm_add_ps(mm1, mm2)
#define _vaddd(mm1, mm2) _mm_add_pd(mm1, mm2)
#define _vsubf(mm1, mm2) _mm_sub_ps(mm1, mm2)
#define _vsubd(mm1, mm2) _mm_sub_pd(mm1, mm2)
#define _vmulf(mm1, mm2) _mm_mul_ps(mm1, mm2)
#define _vmuld(mm1, mm2) _mm_mul_pd(mm1, mm2)
#define _vdivf(mm1, mm2) _mm_div_ps(mm1, mm2)
#define _vdivd(mm1, mm2) _mm_div_pd(mm1, mm2)
#define _vreduce_addd(mm) _mm_reduce_add_pd(mm)
#define _vreduce_addf(mm) _mm_reduce_add_ps(mm)
#else
typedef float mmf;
typedef double mmd;
#define STRIDEF 1
#define STRIDED 1
#define _vloadf(arr) *(arr)
#define _vloadd(arr) *(arr)
#define _vstoref(arr, mm) *(arr) = mm
#define _vstored(arr, mm) *(arr) = mm
#define _vset1f(f) f
#define _vset1d(d) d
#define _vsetrf(f) f
#define _vsetrd(d) d
#define _vaddf(mm1, mm2) mm1 + mm2
#define _vaddd(mm1, mm2) mm1 + mm2
#define _vsubf(mm1, mm2) mm1 - mm2
#define _vsubd(mm1, mm2) mm1 - mm2
#define _vmulf(mm1, mm2) mm1 *mm2
#define _vmuld(mm1, mm2) mm1 *mm2
#define _vdivf(mm1, mm2) mm1 / mm2
#define _vdivd(mm1, mm2) mm1 / mm2
#define _vreduce_addd(mm) mm
#define _vreduce_addf(mm) mm
#endif

#endif