/*************************************************
 * @author Bin Qu
 * @email benquickdenn@foxmail.com
*************************************************/

#ifndef VEC_HPP
#define VEC_HPP

#include "../utilities/configure.hpp"

// 向量类
template <typename T> 
struct Vec
{
};

// 单精度向量类
template <>
class Vec<float>
{
private:
    mmf _mm;
public:
    Vec(){}
    Vec(const mmf & _mm) { this->_mm = _mm; }
    ~Vec(){}

    force_inline mmf mm() const { return _mm; }
    void setmm(const mmf& _mm) { this->_mm = _mm; }
    static size_t mmsize();

    void load(const float *_arr) { _mm = _vloadf(_arr); }
    void store(float *_arr) { _vstoref(_arr, _mm); }

    force_inline Vec<float> & operator = (const Vec<float> & v) { this->_mm = v.mm(); return *this; }
    force_inline Vec<float> & operator = (const mmf & _mm) { this->_mm = _mm; return *this; }
//#if mmf!=float
    Vec(const float & f) { _mm = _vset1f(f); }
    force_inline Vec<float> & operator = (const float & f) { _mm = _vset1f(f); return *this; }
//#endif
};

// 向量加
static force_inline Vec<float> operator + (const Vec<float> & v1, const Vec<float> & v2)
{ return Vec<float>(_vaddf(v1.mm(), v2.mm())); }

static force_inline Vec<float> operator + (const Vec<float> & v1, const mmf & v2)
{ return Vec<float>(_vaddf(v1.mm(), v2)); }

static force_inline Vec<float> operator + (const mmf & v1, const Vec<float> & v2)
{ return Vec<float>(_vaddf(v1, v2.mm())); }

static force_inline Vec<float> operator + (const Vec<float> & v1, const float & f)
{ return Vec<float>(_vaddf(v1.mm(), _vset1f(f))); }

static force_inline Vec<float> operator + (const float & f, const Vec<float> & v2)
{ return Vec<float>(_vaddf(_vset1f(f), v2.mm())); }

// 向量减
static force_inline Vec<float> operator - (const Vec<float> & v1, const Vec<float> & v2)
{ return Vec<float>(_vsubf(v1.mm(), v2.mm())); }

static force_inline Vec<float> operator - (const Vec<float> & v1, const mmf & v2)
{ return Vec<float>(_vsubf(v1.mm(), v2)); }

static force_inline Vec<float> operator - (const mmf & v1, const Vec<float> & v2)
{ return Vec<float>(_vsubf(v1, v2.mm())); }

static force_inline Vec<float> operator - (const Vec<float> & v1, const float & f)
{ return Vec<float>(_vsubf(v1.mm(), _vset1f(f))); }

static force_inline Vec<float> operator - (const float & f, const Vec<float> & v2)
{ return Vec<float>(_vsubf(_vset1f(f), v2.mm())); }

// 向量乘
static force_inline Vec<float> operator * (const Vec<float> & v1, const Vec<float> & v2)
{ return Vec<float>(_vmulf(v1.mm(), v2.mm())); }

static force_inline Vec<float> operator * (const Vec<float> & v1, const mmf & v2)
{ return Vec<float>(_vmulf(v1.mm(), v2)); }

static force_inline Vec<float> operator * (const mmf & v1, const Vec<float> & v2)
{ return Vec<float>(_vmulf(v1, v2.mm())); }

static force_inline Vec<float> operator * (const Vec<float> & v1, const float & f)
{ return Vec<float>(_vmulf(v1.mm(), _vset1f(f))); }

static force_inline Vec<float> operator * (const float & f, const Vec<float> & v2)
{ return Vec<float>(_vmulf(_vset1f(f), v2.mm())); }

// 向量除
static force_inline Vec<float> operator / (const Vec<float> & v1, const Vec<float> & v2)
{ return Vec<float>(_vdivf(v1.mm(), v2.mm())); }

static force_inline Vec<float> operator / (const Vec<float> & v1, const mmf & v2)
{ return Vec<float>(_vdivf(v1.mm(), v2)); }

static force_inline Vec<float> operator / (const mmf & v1, const Vec<float> & v2)
{ return Vec<float>(_vdivf(v1, v2.mm())); }

static force_inline Vec<float> operator / (const Vec<float> & v1, const float & f)
{ return Vec<float>(_vdivf(v1.mm(), _vset1f(f))); }

static force_inline Vec<float> operator / (const float & f, const Vec<float> & v2)
{ return Vec<float>(_vdivf(_vset1f(f), v2.mm())); }

// 双精度向量类
template <>
class Vec<double>
{
private:
    mmd _mm;
public:
    Vec(){}
    Vec(const mmd & _mm) { this->_mm = _mm; }
    ~Vec(){}

    force_inline mmd mm() const { return _mm; }
    void setmm(const mmd& _mm) { this->_mm = _mm; }
    static size_t mmsize();

    void load(const double *_arr) { _mm = _vloadd(_arr); }
    void store(double *_arr) { _vstored(_arr, _mm); }

    force_inline Vec<double> & operator = (const Vec<double> & v) { this->_mm = v.mm(); return *this; }
    force_inline Vec<double> & operator = (const mmd & _mm) { this->_mm = _mm; return *this; }
//#if mmd!=double
    Vec(const double & d) { _mm = _vset1d(d); }
    force_inline Vec<double> & operator = (const double & d) { _mm = _vset1d(d); return *this; }
//#endif
};

// 向量加
static force_inline Vec<double> operator + (const Vec<double> & v1, const Vec<double> & v2)
{ return Vec<double>(_vaddd(v1.mm(), v2.mm())); }

static force_inline Vec<double> operator + (const Vec<double> & v1, const mmd & v2)
{ return Vec<double>(_vaddd(v1.mm(), v2)); }

static force_inline Vec<double> operator + (const mmd & v1, const Vec<double> & v2)
{ return Vec<double>(_vaddd(v1, v2.mm())); }

static force_inline Vec<double> operator + (const Vec<double> & v1, const double & d)
{ return Vec<double>(_vaddd(v1.mm(), _vset1d(d))); }

static force_inline Vec<double> operator + (const double & d, const Vec<double> & v2)
{ return Vec<double>(_vaddd(_vset1d(d), v2.mm())); }

// 向量减
static force_inline Vec<double> operator - (const Vec<double> & v1, const Vec<double> & v2)
{ return Vec<double>(_vsubd(v1.mm(), v2.mm())); }

static force_inline Vec<double> operator - (const Vec<double> & v1, const mmd & v2)
{ return Vec<double>(_vsubd(v1.mm(), v2)); }

static force_inline Vec<double> operator - (const mmd & v1, const Vec<double> & v2)
{ return Vec<double>(_vsubd(v1, v2.mm())); }

static force_inline Vec<double> operator - (const Vec<double> & v1, const double & d)
{ return Vec<double>(_vsubd(v1.mm(), _vset1d(d))); }

static force_inline Vec<double> operator - (const double & d, const Vec<double> & v2)
{ return Vec<double>(_vsubd(_vset1d(d), v2.mm())); }

// 向量乘
static force_inline Vec<double> operator * (const Vec<double> & v1, const Vec<double> & v2)
{ return Vec<double>(_vmuld(v1.mm(), v2.mm())); }

static force_inline Vec<double> operator * (const Vec<double> & v1, const mmd & v2)
{ return Vec<double>(_vmuld(v1.mm(), v2)); }

static force_inline Vec<double> operator * (const mmd & v1, const Vec<double> & v2)
{ return Vec<double>(_vmuld(v1, v2.mm())); }

static force_inline Vec<double> operator * (const Vec<double> & v1, const double & d)
{ return Vec<double>(_vmuld(v1.mm(), _vset1d(d))); }

static force_inline Vec<double> operator * (const double & d, const Vec<double> & v2)
{ return Vec<double>(_vmuld(_vset1d(d), v2.mm())); }

// 向量除
static force_inline Vec<double> operator / (const Vec<double> & v1, const Vec<double> & v2)
{ return Vec<double>(_vdivd(v1.mm(), v2.mm())); }

static force_inline Vec<double> operator / (const Vec<double> & v1, const mmd & v2)
{ return Vec<double>(_vdivd(v1.mm(), v2)); }

static force_inline Vec<double> operator / (const mmd & v1, const Vec<double> & v2)
{ return Vec<double>(_vdivd(v1, v2.mm())); }

static force_inline Vec<double> operator / (const Vec<double> & v1, const double & d)
{ return Vec<double>(_vdivd(v1.mm(), _vset1d(d))); }

static force_inline Vec<double> operator / (const double & d, const Vec<double> & v2)
{ return Vec<double>(_vdivd(_vset1d(d), v2.mm())); }

#if defined(__AVX512F__)
size_t Vec<float>::mmsize() { return 16; }
size_t Vec<double>::mmsize() { return 8; }
#elif defined(__AVX__)
size_t Vec<float>::mmsize() { return 8; }
size_t Vec<double>::mmsize() { return 4; }
#elif defined(__SSE__)
size_t Vec<float>::mmsize() { return 4; }
size_t Vec<double>::mmsize() { return 2; }
#else
size_t Vec<float>::mmsize() { return 1; }
size_t Vec<double>::mmsize() { return 1; }
#endif

#endif