/*
 * Copyright 2011-2013 Blender Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __UTIL_MATH_H__
#define __UTIL_MATH_H__

/* Math
 *
 * Basic math functions on scalar and vector types. This header is used by
 * both the kernel code when compiled as C++, and other C++ non-kernel code. */

#ifndef __KERNEL_GPU__
#  include <cmath>
#endif


#ifndef __KERNEL_OPENCL__

#include <float.h>
#include <math.h>
#include <stdio.h>

#endif

#include "util/util_types.h"

CCL_NAMESPACE_BEGIN

/* Float Pi variations */

/* Division */
#ifndef M_PI_F
#define M_PI_F    (3.1415926535897932f)  /* pi */
#endif
#ifndef M_PI_2_F
#define M_PI_2_F  (1.5707963267948966f)  /* pi/2 */
#endif
#ifndef M_PI_4_F
#define M_PI_4_F  (0.7853981633974830f)  /* pi/4 */
#endif
#ifndef M_1_PI_F
#define M_1_PI_F  (0.3183098861837067f)  /* 1/pi */
#endif
#ifndef M_2_PI_F
#define M_2_PI_F  (0.6366197723675813f)  /* 2/pi */
#endif

/* Multiplication */
#ifndef M_2PI_F
#define M_2PI_F   (6.2831853071795864f)  /* 2*pi */
#endif
#ifndef M_4PI_F
#define M_4PI_F   (12.566370614359172f)  /* 4*pi */
#endif

/* Float sqrt variations */

#ifndef M_SQRT2_F
#define M_SQRT2_F (1.4142135623730950f)  /* sqrt(2) */
#endif

#ifndef M_LN2_F
#define M_LN2_F   (0.6931471805599453f)  /* ln(2) */
#endif

#ifndef M_LN10_F
#define M_LN10_F  (2.3025850929940457f)  /* ln(10) */
#endif

/* Scalar */

#ifdef _WIN32

#ifndef __KERNEL_OPENCL__

ccl_device_inline float fmaxf(float a, float b)
{
	return (a > b)? a: b;
}

ccl_device_inline float fminf(float a, float b)
{
	return (a < b)? a: b;
}

#endif

#endif

#ifndef __KERNEL_GPU__

using std::isfinite;
using std::isnan;

ccl_device_inline int abs(int x)
{
	return (x > 0)? x: -x;
}

ccl_device_inline int max(int a, int b)
{
	return (a > b)? a: b;
}

ccl_device_inline int min(int a, int b)
{
	return (a < b)? a: b;
}

ccl_device_inline float max(float a, float b)
{
	return (a > b)? a: b;
}

ccl_device_inline float min(float a, float b)
{
	return (a < b)? a: b;
}

ccl_device_inline double max(double a, double b)
{
	return (a > b)? a: b;
}

ccl_device_inline double min(double a, double b)
{
	return (a < b)? a: b;
}

/* These 2 guys are templated for usage with registers data.
 *
 * NOTE: Since this is CPU-only functions it is ok to use references here.
 * But for other devices we'll need to be careful about this.
 */

template<typename T>
ccl_device_inline T min4(const T& a, const T& b, const T& c, const T& d)
{
	return min(min(a,b),min(c,d));
}

template<typename T>
ccl_device_inline T max4(const T& a, const T& b, const T& c, const T& d)
{
	return max(max(a,b),max(c,d));
}

#endif

ccl_device_inline float min4(float a, float b, float c, float d)
{
	return min(min(a, b), min(c, d));
}

ccl_device_inline float max4(float a, float b, float c, float d)
{
	return max(max(a, b), max(c, d));
}

ccl_device_inline float max3(float3 a)
{
	return max(max(a.x, a.y), a.z);
}

#ifndef __KERNEL_OPENCL__

ccl_device_inline int clamp(int a, int mn, int mx)
{
	return min(max(a, mn), mx);
}

ccl_device_inline float clamp(float a, float mn, float mx)
{
	return min(max(a, mn), mx);
}

ccl_device_inline float mix(float a, float b, float t)
{
    return a + t*(b - a);
}

#endif

#ifndef __KERNEL_CUDA__

ccl_device_inline float saturate(float a)
{
	return clamp(a, 0.0f, 1.0f);
}

#endif

ccl_device_inline int float_to_int(float f)
{
	return (int)f;
}

ccl_device_inline int floor_to_int(float f)
{
	return float_to_int(floorf(f));
}

ccl_device_inline int ceil_to_int(float f)
{
	return float_to_int(ceilf(f));
}

ccl_device_inline float signf(float f)
{
	return (f < 0.0f)? -1.0f: 1.0f;
}

ccl_device_inline float nonzerof(float f, float eps)
{
	if(fabsf(f) < eps)
		return signf(f)*eps;
	else
		return f;
}

ccl_device_inline float smoothstepf(float f)
{
	float ff = f*f;
	return (3.0f*ff - 2.0f*ff*f);
}

ccl_device_inline int mod(int x, int m)
{
	return (x % m + m) % m;
}

/* Float2 Vector */

#ifndef __KERNEL_OPENCL__

ccl_device_inline bool is_zero(const float2& a)
{
	return (a.x == 0.0f && a.y == 0.0f);
}

#endif

#ifndef __KERNEL_OPENCL__

ccl_device_inline float average(const float2& a)
{
	return (a.x + a.y)*(1.0f/2.0f);
}

#endif

#ifndef __KERNEL_OPENCL__

ccl_device_inline float2 operator-(const float2& a)
{
	return make_float2(-a.x, -a.y);
}

ccl_device_inline float2 operator*(const float2& a, const float2& b)
{
	return make_float2(a.x*b.x, a.y*b.y);
}

ccl_device_inline float2 operator*(const float2& a, float f)
{
	return make_float2(a.x*f, a.y*f);
}

ccl_device_inline float2 operator*(float f, const float2& a)
{
	return make_float2(a.x*f, a.y*f);
}

ccl_device_inline float2 operator/(float f, const float2& a)
{
	return make_float2(f/a.x, f/a.y);
}

ccl_device_inline float2 operator/(const float2& a, float f)
{
	float invf = 1.0f/f;
	return make_float2(a.x*invf, a.y*invf);
}

ccl_device_inline float2 operator/(const float2& a, const float2& b)
{
	return make_float2(a.x/b.x, a.y/b.y);
}

ccl_device_inline float2 operator+(const float2& a, const float2& b)
{
	return make_float2(a.x+b.x, a.y+b.y);
}

ccl_device_inline float2 operator-(const float2& a, const float2& b)
{
	return make_float2(a.x-b.x, a.y-b.y);
}

ccl_device_inline float2 operator+=(float2& a, const float2& b)
{
	return a = a + b;
}

ccl_device_inline float2 operator*=(float2& a, const float2& b)
{
	return a = a * b;
}

ccl_device_inline float2 operator*=(float2& a, float f)
{
	return a = a * f;
}

ccl_device_inline float2 operator/=(float2& a, const float2& b)
{
	return a = a / b;
}

ccl_device_inline float2 operator/=(float2& a, float f)
{
	float invf = 1.0f/f;
	return a = a * invf;
}


ccl_device_inline float dot(const float2& a, const float2& b)
{
	return a.x*b.x + a.y*b.y;
}

ccl_device_inline float cross(const float2& a, const float2& b)
{
	return (a.x*b.y - a.y*b.x);
}

#endif

#ifndef __KERNEL_OPENCL__

ccl_device_inline bool operator==(const int2 a, const int2 b)
{
	return (a.x == b.x && a.y == b.y);
}

ccl_device_inline float len(const float2& a)
{
	return sqrtf(dot(a, a));
}

ccl_device_inline float2 normalize(const float2& a)
{
	return a/len(a);
}

ccl_device_inline float2 normalize_len(const float2& a, float *t)
{
	*t = len(a);
	return a/(*t);
}

ccl_device_inline float2 safe_normalize(const float2& a)
{
	float t = len(a);
	return (t != 0.0f)? a/t: a;
}

ccl_device_inline bool operator==(const float2& a, const float2& b)
{
	return (a.x == b.x && a.y == b.y);
}

ccl_device_inline bool operator!=(const float2& a, const float2& b)
{
	return !(a == b);
}

ccl_device_inline float2 min(const float2& a, const float2& b)
{
	return make_float2(min(a.x, b.x), min(a.y, b.y));
}

ccl_device_inline float2 max(const float2& a, const float2& b)
{
	return make_float2(max(a.x, b.x), max(a.y, b.y));
}

ccl_device_inline float2 clamp(const float2& a, const float2& mn, const float2& mx)
{
	return min(max(a, mn), mx);
}

ccl_device_inline float2 fabs(const float2& a)
{
	return make_float2(fabsf(a.x), fabsf(a.y));
}

ccl_device_inline float2 as_float2(const float4& a)
{
	return make_float2(a.x, a.y);
}

#endif

#ifndef __KERNEL_GPU__

ccl_device_inline void print_float2(const char *label, const float2& a)
{
	printf("%s: %.8f %.8f\n", label, (double)a.x, (double)a.y);
}

#endif

#ifndef __KERNEL_OPENCL__

ccl_device_inline float2 interp(const float2& a, const float2& b, float t)
{
	return a + t*(b - a);
}

#endif

/* Float3 Vector */

#ifndef __KERNEL_OPENCL__

ccl_device_inline float3 operator-(const float3& a)
{
#ifdef __KERNEL_SSE__
	return float3(_mm_xor_ps(a.m128, _mm_castsi128_ps(_mm_set1_epi32(0x80000000))));
#else
	return make_float3(-a.x, -a.y, -a.z);
#endif
}

ccl_device_inline float3 operator*(const float3& a, const float3& b)
{
#ifdef __KERNEL_SSE__
	return float3(_mm_mul_ps(a.m128,b.m128));
#else
	return make_float3(a.x*b.x, a.y*b.y, a.z*b.z);
#endif
}

ccl_device_inline float3 operator*(const float3& a, const float f)
{
#ifdef __KERNEL_SSE__
	return float3(_mm_mul_ps(a.m128,_mm_set1_ps(f)));
#else
	return make_float3(a.x*f, a.y*f, a.z*f);
#endif
}

ccl_device_inline float3 operator*(const float f, const float3& a)
{
	/* TODO(sergey): Currently disabled, gives speedup but causes precision issues. */
#if defined(__KERNEL_SSE__) && 0
	return float3(_mm_mul_ps(_mm_set1_ps(f), a.m128));
#else
	return make_float3(a.x*f, a.y*f, a.z*f);
#endif
}

ccl_device_inline float3 operator/(const float f, const float3& a)
{
	/* TODO(sergey): Currently disabled, gives speedup but causes precision issues. */
#if defined(__KERNEL_SSE__) && 0
	__m128 rc = _mm_rcp_ps(a.m128);
	return float3(_mm_mul_ps(_mm_set1_ps(f),rc));
#else
	return make_float3(f / a.x, f / a.y, f / a.z);
#endif
}

ccl_device_inline float3 operator/(const float3& a, const float f)
{
	float invf = 1.0f/f;
	return a * invf;
}

ccl_device_inline float3 operator/(const float3& a, const float3& b)
{
	/* TODO(sergey): Currently disabled, gives speedup but causes precision issues. */
#if defined(__KERNEL_SSE__) && 0
	__m128 rc = _mm_rcp_ps(b.m128);
	return float3(_mm_mul_ps(a, rc));
#else
	return make_float3(a.x / b.x, a.y / b.y, a.z / b.z);
#endif
}

ccl_device_inline float3 operator+(const float3& a, const float3& b)
{
#ifdef __KERNEL_SSE__
	return float3(_mm_add_ps(a.m128, b.m128));
#else
	return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
#endif
}

ccl_device_inline float3 operator-(const float3& a, const float3& b)
{
#ifdef __KERNEL_SSE__
	return float3(_mm_sub_ps(a.m128, b.m128));
#else
	return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
#endif
}

ccl_device_inline float3 operator+=(float3& a, const float3& b)
{
	return a = a + b;
}

ccl_device_inline float3 operator*=(float3& a, const float3& b)
{
	return a = a * b;
}

ccl_device_inline float3 operator*=(float3& a, float f)
{
	return a = a * f;
}

ccl_device_inline float3 operator/=(float3& a, const float3& b)
{
	return a = a / b;
}

ccl_device_inline float3 operator/=(float3& a, float f)
{
	float invf = 1.0f/f;
	return a = a * invf;
}

ccl_device_inline float dot(const float3& a, const float3& b)
{
#if defined(__KERNEL_SSE41__) && defined(__KERNEL_SSE__)
	return _mm_cvtss_f32(_mm_dp_ps(a, b, 0x7F));
#else	
	return a.x*b.x + a.y*b.y + a.z*b.z;
#endif
}

ccl_device_inline float dot_xy(const float3& a, const float3& b)
{
#if defined(__KERNEL_SSE41__) && defined(__KERNEL_SSE__)
	return _mm_cvtss_f32(_mm_hadd_ps(_mm_mul_ps(a,b),b));
#else
	return a.x*b.x + a.y*b.y;
#endif
}

ccl_device_inline float dot(const float4& a, const float4& b)
{
#if defined(__KERNEL_SSE41__) && defined(__KERNEL_SSE__)
	return _mm_cvtss_f32(_mm_dp_ps(a, b, 0xFF));
#else	
	return (a.x*b.x + a.y*b.y) + (a.z*b.z + a.w*b.w);
#endif
}

ccl_device_inline float3 cross(const float3& a, const float3& b)
{
	float3 r = make_float3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	return r;
}

#endif

ccl_device_inline float len(const float3 a)
{
#if defined(__KERNEL_SSE41__) && defined(__KERNEL_SSE__)
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(a.m128, a.m128, 0x7F)));
#else
	return sqrtf(dot(a, a));
#endif
}

ccl_device_inline float len_squared(const float3 a)
{
	return dot(a, a);
}

#ifndef __KERNEL_OPENCL__

ccl_device_inline float len_squared(const float4& a)
{
	return dot(a, a);
}

ccl_device_inline float3 normalize(const float3& a)
{
#if defined(__KERNEL_SSE41__) && defined(__KERNEL_SSE__)
	__m128 norm = _mm_sqrt_ps(_mm_dp_ps(a.m128, a.m128, 0x7F));
	return _mm_div_ps(a.m128, norm);
#else
	return a/len(a);
#endif
}

#endif

ccl_device_inline float3 saturate3(float3 a)
{
	return make_float3(saturate(a.x), saturate(a.y), saturate(a.z));
}

ccl_device_inline float3 normalize_len(const float3 a, float *t)
{
	*t = len(a);
	float x = 1.0f / *t;
	return a*x;
}

ccl_device_inline float3 safe_normalize(const float3 a)
{
	float t = len(a);
	return (t != 0.0f)? a * (1.0f/t) : a;
}

ccl_device_inline float3 safe_normalize_len(const float3 a, float *t)
{
	*t = len(a);
	return (*t != 0.0f)? a/(*t): a;
}

#ifndef __KERNEL_OPENCL__

ccl_device_inline bool operator==(const float3& a, const float3& b)
{
#ifdef __KERNEL_SSE__
	return (_mm_movemask_ps(_mm_cmpeq_ps(a.m128, b.m128)) & 7) == 7;
#else
	return (a.x == b.x && a.y == b.y && a.z == b.z);
#endif
}

ccl_device_inline bool operator!=(const float3& a, const float3& b)
{
	return !(a == b);
}

ccl_device_inline float3 min(const float3& a, const float3& b)
{
#ifdef __KERNEL_SSE__
	return _mm_min_ps(a.m128, b.m128);
#else
	return make_float3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
#endif
}

ccl_device_inline float3 max(const float3& a, const float3& b)
{
#ifdef __KERNEL_SSE__
	return _mm_max_ps(a.m128, b.m128);
#else
	return make_float3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
#endif
}

ccl_device_inline float3 clamp(const float3& a, const float3& mn, const float3& mx)
{
	return min(max(a, mn), mx);
}

ccl_device_inline float3 fabs(const float3& a)
{
#ifdef __KERNEL_SSE__
	__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x7fffffff));
	return _mm_and_ps(a.m128, mask);
#else
	return make_float3(fabsf(a.x), fabsf(a.y), fabsf(a.z));
#endif
}

#endif

ccl_device_inline float3 float2_to_float3(const float2 a)
{
	return make_float3(a.x, a.y, 0.0f);
}

ccl_device_inline float3 float4_to_float3(const float4 a)
{
	return make_float3(a.x, a.y, a.z);
}

ccl_device_inline float4 float3_to_float4(const float3 a)
{
	return make_float4(a.x, a.y, a.z, 1.0f);
}

#ifndef __KERNEL_GPU__

ccl_device_inline void print_float3(const char *label, const float3& a)
{
	printf("%s: %.8f %.8f %.8f\n", label, (double)a.x, (double)a.y, (double)a.z);
}

ccl_device_inline float3 rcp(const float3& a)
{
#ifdef __KERNEL_SSE__
	float4 r = _mm_rcp_ps(a.m128);
	return _mm_sub_ps(_mm_add_ps(r, r), _mm_mul_ps(_mm_mul_ps(r, r), a));
#else
	return make_float3(1.0f/a.x, 1.0f/a.y, 1.0f/a.z);
#endif
}

#endif

ccl_device_inline float3 interp(float3 a, float3 b, float t)
{
	return a + t*(b - a);
}

#ifndef __KERNEL_OPENCL__

ccl_device_inline float3 mix(const float3& a, const float3& b, float t)
{
	return a + t*(b - a);
}

#endif

ccl_device_inline bool is_zero(const float3 a)
{
#ifdef __KERNEL_SSE__
	return a == make_float3(0.0f);
#else
	return (a.x == 0.0f && a.y == 0.0f && a.z == 0.0f);
#endif
}

ccl_device_inline float reduce_add(const float3 a)
{
	return (a.x + a.y + a.z);
}

ccl_device_inline float average(const float3 a)
{
	return reduce_add(a)*(1.0f/3.0f);
}

ccl_device_inline bool isequal_float3(const float3 a, const float3 b)
{
#ifdef __KERNEL_OPENCL__
	return all(a == b);
#else
	return a == b;
#endif
}

/* Float4 Vector */

#ifdef __KERNEL_SSE__

template<size_t index_0, size_t index_1, size_t index_2, size_t index_3> __forceinline const float4 shuffle(const float4& b)
{
	return _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(b), _MM_SHUFFLE(index_3, index_2, index_1, index_0)));
}

#if defined(__KERNEL_SSE3__)
template<> __forceinline const float4 shuffle<0, 0, 2, 2>(const float4& b)
{
	return _mm_moveldup_ps(b);
}

template<> __forceinline const float4 shuffle<1, 1, 3, 3>(const float4& b)
{
	return _mm_movehdup_ps(b);
}
#endif

template<> __forceinline const float4 shuffle<0, 1, 0, 1>(const float4& b)
{
	return _mm_castpd_ps(_mm_movedup_pd(_mm_castps_pd(b)));
}

#endif

#ifndef __KERNEL_OPENCL__

ccl_device_inline float4 operator-(const float4& a)
{
#ifdef __KERNEL_SSE__
	__m128 mask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	return _mm_xor_ps(a.m128, mask);
#else
	return make_float4(-a.x, -a.y, -a.z, -a.w);
#endif
}

ccl_device_inline float4 operator*(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_mul_ps(a.m128, b.m128);
#else
	return make_float4(a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w);
#endif
}

ccl_device_inline float4 operator*(const float4& a, float f)
{
#if defined(__KERNEL_SSE__)
	return a * make_float4(f);
#else
	return make_float4(a.x*f, a.y*f, a.z*f, a.w*f);
#endif
}

ccl_device_inline float4 operator*(float f, const float4& a)
{
	return a * f;
}

ccl_device_inline float4 rcp(const float4& a)
{
#ifdef __KERNEL_SSE__
	float4 r = _mm_rcp_ps(a.m128);
	return _mm_sub_ps(_mm_add_ps(r, r), _mm_mul_ps(_mm_mul_ps(r, r), a));
#else
	return make_float4(1.0f/a.x, 1.0f/a.y, 1.0f/a.z, 1.0f/a.w);
#endif
}

ccl_device_inline float4 operator/(const float4& a, float f)
{
	return a * (1.0f/f);
}

ccl_device_inline float4 operator/(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return a * rcp(b);
#else
	return make_float4(a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w);
#endif

}

ccl_device_inline float4 operator+(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_add_ps(a.m128, b.m128);
#else
	return make_float4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
#endif
}

ccl_device_inline float4 operator-(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_sub_ps(a.m128, b.m128);
#else
	return make_float4(a.x-b.x, a.y-b.y, a.z-b.z, a.w-b.w);
#endif
}

ccl_device_inline float4 operator+=(float4& a, const float4& b)
{
	return a = a + b;
}

ccl_device_inline float4 operator*=(float4& a, const float4& b)
{
	return a = a * b;
}

ccl_device_inline float4 operator/=(float4& a, float f)
{
	return a = a / f;
}

ccl_device_inline int4 operator<(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_cvtps_epi32(_mm_cmplt_ps(a.m128, b.m128)); /* todo: avoid cvt */
#else
	return make_int4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
#endif
}

ccl_device_inline int4 operator>=(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_cvtps_epi32(_mm_cmpge_ps(a.m128, b.m128)); /* todo: avoid cvt */
#else
	return make_int4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
#endif
}

ccl_device_inline int4 operator<=(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_cvtps_epi32(_mm_cmple_ps(a.m128, b.m128)); /* todo: avoid cvt */
#else
	return make_int4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
#endif
}

ccl_device_inline bool operator==(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return (_mm_movemask_ps(_mm_cmpeq_ps(a.m128, b.m128)) & 15) == 15;
#else
	return (a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
#endif
}

ccl_device_inline float4 cross(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return (shuffle<1,2,0,0>(a)*shuffle<2,0,1,0>(b)) - (shuffle<2,0,1,0>(a)*shuffle<1,2,0,0>(b));
#else
	return make_float4(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x, 0.0f);
#endif
}

ccl_device_inline bool is_zero(const float4& a)
{
#ifdef __KERNEL_SSE__
	return a == make_float4(0.0f);
#else
	return (a.x == 0.0f && a.y == 0.0f && a.z == 0.0f && a.w == 0.0f);
#endif
}

ccl_device_inline float reduce_add(const float4& a)
{
#ifdef __KERNEL_SSE__
	float4 h = shuffle<1,0,3,2>(a) + a;
	return _mm_cvtss_f32(shuffle<2,3,0,1>(h) + h); /* todo: efficiency? */
#else
	return ((a.x + a.y) + (a.z + a.w));
#endif
}

ccl_device_inline float average(const float4& a)
{
	return reduce_add(a) * 0.25f;
}

ccl_device_inline float len(const float4& a)
{
	return sqrtf(dot(a, a));
}

ccl_device_inline float4 normalize(const float4& a)
{
	return a/len(a);
}

ccl_device_inline float4 safe_normalize(const float4& a)
{
	float t = len(a);
	return (t != 0.0f)? a/t: a;
}

ccl_device_inline float4 min(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_min_ps(a.m128, b.m128);
#else
	return make_float4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
#endif
}

ccl_device_inline float4 max(const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_max_ps(a.m128, b.m128);
#else
	return make_float4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w));
#endif
}

#endif

#ifndef __KERNEL_GPU__

ccl_device_inline float4 select(const int4& mask, const float4& a, const float4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_or_ps(_mm_and_ps(_mm_cvtepi32_ps(mask), a), _mm_andnot_ps(_mm_cvtepi32_ps(mask), b)); /* todo: avoid cvt */
#else
	return make_float4((mask.x)? a.x: b.x, (mask.y)? a.y: b.y, (mask.z)? a.z: b.z, (mask.w)? a.w: b.w);
#endif
}

ccl_device_inline float4 reduce_min(const float4& a)
{
#ifdef __KERNEL_SSE__
	float4 h = min(shuffle<1,0,3,2>(a), a);
	return min(shuffle<2,3,0,1>(h), h);
#else
	return make_float4(min(min(a.x, a.y), min(a.z, a.w)));
#endif
}

ccl_device_inline float4 reduce_max(const float4& a)
{
#ifdef __KERNEL_SSE__
	float4 h = max(shuffle<1,0,3,2>(a), a);
	return max(shuffle<2,3,0,1>(h), h);
#else
	return make_float4(max(max(a.x, a.y), max(a.z, a.w)));
#endif
}

#if 0
ccl_device_inline float4 reduce_add(const float4& a)
{
#ifdef __KERNEL_SSE__
	float4 h = shuffle<1,0,3,2>(a) + a;
	return shuffle<2,3,0,1>(h) + h;
#else
	return make_float4((a.x + a.y) + (a.z + a.w));
#endif
}
#endif

ccl_device_inline void print_float4(const char *label, const float4& a)
{
	printf("%s: %.8f %.8f %.8f %.8f\n", label, (double)a.x, (double)a.y, (double)a.z, (double)a.w);
}

#endif

/* Int2 */

#ifndef __KERNEL_OPENCL__

ccl_device_inline int2 operator+(const int2 &a, const int2 &b)
{
	return make_int2(a.x + b.x, a.y + b.y);
}

ccl_device_inline int2 operator+=(int2 &a, const int2 &b)
{
	return a = a + b;
}

ccl_device_inline int2 operator-(const int2 &a, const int2 &b)
{
	return make_int2(a.x - b.x, a.y - b.y);
}

ccl_device_inline int2 operator*(const int2 &a, const int2 &b)
{
	return make_int2(a.x * b.x, a.y * b.y);
}

ccl_device_inline int2 operator/(const int2 &a, const int2 &b)
{
	return make_int2(a.x / b.x, a.y / b.y);
}

#endif

/* Int3 */

#ifndef __KERNEL_OPENCL__

ccl_device_inline int3 min(int3 a, int3 b)
{
#if defined(__KERNEL_SSE__) && defined(__KERNEL_SSE41__)
	return _mm_min_epi32(a.m128, b.m128);
#else
	return make_int3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
#endif
}

ccl_device_inline int3 max(int3 a, int3 b)
{
#if defined(__KERNEL_SSE__) && defined(__KERNEL_SSE41__)
	return _mm_max_epi32(a.m128, b.m128);
#else
	return make_int3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
#endif
}

ccl_device_inline int3 clamp(const int3& a, int mn, int mx)
{
#ifdef __KERNEL_SSE__
	return min(max(a, make_int3(mn)), make_int3(mx));
#else
	return make_int3(clamp(a.x, mn, mx), clamp(a.y, mn, mx), clamp(a.z, mn, mx));
#endif
}

ccl_device_inline int3 clamp(const int3& a, int3& mn, int mx)
{
#ifdef __KERNEL_SSE__
	return min(max(a, mn), make_int3(mx));
#else
	return make_int3(clamp(a.x, mn.x, mx), clamp(a.y, mn.y, mx), clamp(a.z, mn.z, mx));
#endif
}

#endif

#ifndef __KERNEL_GPU__

ccl_device_inline void print_int3(const char *label, const int3& a)
{
	printf("%s: %d %d %d\n", label, a.x, a.y, a.z);
}

#endif

/* Int4 */

#ifndef __KERNEL_GPU__

ccl_device_inline int4 operator+(const int4& a, const int4& b)
{
#ifdef __KERNEL_SSE__
	return _mm_add_epi32(a.m128, b.m128);
#else
	return make_int4(a.x+b.x, a.y+b.y, a.z+b.z, a.w+b.w);
#endif
}

ccl_device_inline int4 operator+=(int4& a, const int4& b)
{
	return a = a + b;
}

ccl_device_inline int4 operator>>(const int4& a, int i)
{
#ifdef __KERNEL_SSE__
	return _mm_srai_epi32(a.m128, i);
#else
	return make_int4(a.x >> i, a.y >> i, a.z >> i, a.w >> i);
#endif
}

ccl_device_inline int4 min(int4 a, int4 b)
{
#if defined(__KERNEL_SSE__) && defined(__KERNEL_SSE41__)
	return _mm_min_epi32(a.m128, b.m128);
#else
	return make_int4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w));
#endif
}

ccl_device_inline int4 max(int4 a, int4 b)
{
#if defined(__KERNEL_SSE__) && defined(__KERNEL_SSE41__)
	return _mm_max_epi32(a.m128, b.m128);
#else
	return make_int4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w));
#endif
}

ccl_device_inline int4 clamp(const int4& a, const int4& mn, const int4& mx)
{
	return min(max(a, mn), mx);
}

ccl_device_inline int4 select(const int4& mask, const int4& a, const int4& b)
{
#ifdef __KERNEL_SSE__
	__m128 m = _mm_cvtepi32_ps(mask);
	return _mm_castps_si128(_mm_or_ps(_mm_and_ps(m, _mm_castsi128_ps(a)), _mm_andnot_ps(m, _mm_castsi128_ps(b)))); /* todo: avoid cvt */
#else
	return make_int4((mask.x)? a.x: b.x, (mask.y)? a.y: b.y, (mask.z)? a.z: b.z, (mask.w)? a.w: b.w);
#endif
}

ccl_device_inline void print_int4(const char *label, const int4& a)
{
	printf("%s: %d %d %d %d\n", label, a.x, a.y, a.z, a.w);
}

#endif

/* Int/Float conversion */

#ifndef __KERNEL_OPENCL__

ccl_device_inline int as_int(uint i)
{
	union { uint ui; int i; } u;
	u.ui = i;
	return u.i;
}

ccl_device_inline uint as_uint(int i)
{
	union { uint ui; int i; } u;
	u.i = i;
	return u.ui;
}

ccl_device_inline uint as_uint(float f)
{
	union { uint i; float f; } u;
	u.f = f;
	return u.i;
}

ccl_device_inline int __float_as_int(float f)
{
	union { int i; float f; } u;
	u.f = f;
	return u.i;
}

ccl_device_inline float __int_as_float(int i)
{
	union { int i; float f; } u;
	u.i = i;
	return u.f;
}

ccl_device_inline uint __float_as_uint(float f)
{
	union { uint i; float f; } u;
	u.f = f;
	return u.i;
}

ccl_device_inline float __uint_as_float(uint i)
{
	union { uint i; float f; } u;
	u.i = i;
	return u.f;
}


/* Interpolation */

template<class A, class B> A lerp(const A& a, const A& b, const B& t)
{
	return (A)(a * ((B)1 - t) + b * t);
}

/* Triangle */

ccl_device_inline float triangle_area(const float3& v1, const float3& v2, const float3& v3)
{
	return len(cross(v3 - v2, v1 - v2))*0.5f;
}

#endif

/* Versions of functions which are safe for fast math. */
ccl_device_inline bool isnan_safe(float f)
{
	unsigned int x = __float_as_uint(f);
	return (x << 1) > 0xff000000u;
}

ccl_device_inline bool isfinite_safe(float f)
{
	/* By IEEE 754 rule, 2*Inf equals Inf */
	unsigned int x = __float_as_uint(f);
	return (f == f) && (x == 0 || (f != 2.0f*f)) && !((x << 1) > 0xff000000u);
}

/* Orthonormal vectors */

ccl_device_inline void make_orthonormals(const float3 N, float3 *a, float3 *b)
{
#if 0
	if(fabsf(N.y) >= 0.999f) {
		*a = make_float3(1, 0, 0);
		*b = make_float3(0, 0, 1);
		return;
	}
	if(fabsf(N.z) >= 0.999f) {
		*a = make_float3(1, 0, 0);
		*b = make_float3(0, 1, 0);
		return;
	}
#endif

	if(N.x != N.y || N.x != N.z)
		*a = make_float3(N.z-N.y, N.x-N.z, N.y-N.x);  //(1,1,1)x N
	else
		*a = make_float3(N.z-N.y, N.x+N.z, -N.y-N.x);  //(-1,1,1)x N

	*a = normalize(*a);
	*b = cross(N, *a);
}

/* Color division */

ccl_device_inline float3 safe_invert_color(float3 a)
{
	float x, y, z;

	x = (a.x != 0.0f)? 1.0f/a.x: 0.0f;
	y = (a.y != 0.0f)? 1.0f/a.y: 0.0f;
	z = (a.z != 0.0f)? 1.0f/a.z: 0.0f;

	return make_float3(x, y, z);
}

ccl_device_inline float3 safe_divide_color(float3 a, float3 b)
{
	float x, y, z;

	x = (b.x != 0.0f)? a.x/b.x: 0.0f;
	y = (b.y != 0.0f)? a.y/b.y: 0.0f;
	z = (b.z != 0.0f)? a.z/b.z: 0.0f;

	return make_float3(x, y, z);
}

ccl_device_inline float3 safe_divide_even_color(float3 a, float3 b)
{
	float x, y, z;

	x = (b.x != 0.0f)? a.x/b.x: 0.0f;
	y = (b.y != 0.0f)? a.y/b.y: 0.0f;
	z = (b.z != 0.0f)? a.z/b.z: 0.0f;

	/* try to get gray even if b is zero */
	if(b.x == 0.0f) {
		if(b.y == 0.0f) {
			x = z;
			y = z;
		}
		else if(b.z == 0.0f) {
			x = y;
			z = y;
		}
		else
			x = 0.5f*(y + z);
	}
	else if(b.y == 0.0f) {
		if(b.z == 0.0f) {
			y = x;
			z = x;
		}
		else
			y = 0.5f*(x + z);
	}
	else if(b.z == 0.0f) {
		z = 0.5f*(x + y);
	}

	return make_float3(x, y, z);
}

/* Rotation of point around axis and angle */

ccl_device_inline float3 rotate_around_axis(float3 p, float3 axis, float angle)
{
	float costheta = cosf(angle);
	float sintheta = sinf(angle);
	float3 r;

	r.x = ((costheta + (1 - costheta) * axis.x * axis.x) * p.x) +
		(((1 - costheta) * axis.x * axis.y - axis.z * sintheta) * p.y) +
		(((1 - costheta) * axis.x * axis.z + axis.y * sintheta) * p.z);

	r.y = (((1 - costheta) * axis.x * axis.y + axis.z * sintheta) * p.x) +
		((costheta + (1 - costheta) * axis.y * axis.y) * p.y) +
		(((1 - costheta) * axis.y * axis.z - axis.x * sintheta) * p.z);

	r.z = (((1 - costheta) * axis.x * axis.z - axis.y * sintheta) * p.x) +
		(((1 - costheta) * axis.y * axis.z + axis.x * sintheta) * p.y) +
		((costheta + (1 - costheta) * axis.z * axis.z) * p.z);

	return r;
}

/* NaN-safe math ops */

ccl_device_inline float safe_sqrtf(float f)
{
	return sqrtf(max(f, 0.0f));
}

ccl_device float safe_asinf(float a)
{
	return asinf(clamp(a, -1.0f, 1.0f));
}

ccl_device float safe_acosf(float a)
{
	return acosf(clamp(a, -1.0f, 1.0f));
}

ccl_device float compatible_powf(float x, float y)
{
#ifdef __KERNEL_GPU__
	if(y == 0.0f) /* x^0 -> 1, including 0^0 */
		return 1.0f;

	/* GPU pow doesn't accept negative x, do manual checks here */
	if(x < 0.0f) {
		if(fmodf(-y, 2.0f) == 0.0f)
			return powf(-x, y);
		else
			return -powf(-x, y);
	}
	else if(x == 0.0f)
		return 0.0f;
#endif
	return powf(x, y);
}

ccl_device float safe_powf(float a, float b)
{
	if(UNLIKELY(a < 0.0f && b != float_to_int(b)))
		return 0.0f;

	return compatible_powf(a, b);
}

ccl_device float safe_logf(float a, float b)
{
	if(UNLIKELY(a < 0.0f || b < 0.0f))
		return 0.0f;

	return logf(a)/logf(b);
}

ccl_device float safe_divide(float a, float b)
{
	return (b != 0.0f)? a/b: 0.0f;
}

ccl_device float safe_modulo(float a, float b)
{
	return (b != 0.0f)? fmodf(a, b): 0.0f;
}

ccl_device_inline float beta(float x, float y)
{
#ifndef __KERNEL_OPENCL__
	return expf(lgammaf(x) + lgammaf(y) - lgammaf(x+y));
#else
	return expf(lgamma(x) + lgamma(y) - lgamma(x+y));
#endif
}

ccl_device_inline float xor_signmask(float x, int y)
{
	return __int_as_float(__float_as_int(x) ^ y);
}

/* projections */
ccl_device_inline float2 map_to_tube(const float3 co)
{
	float len, u, v;
	len = sqrtf(co.x * co.x + co.y * co.y);
	if(len > 0.0f) {
		u = (1.0f - (atan2f(co.x / len, co.y / len) / M_PI_F)) * 0.5f;
		v = (co.z + 1.0f) * 0.5f;
	}
	else {
		u = v = 0.0f;
	}
	return make_float2(u, v);
}

ccl_device_inline float2 map_to_sphere(const float3 co)
{
	float l = len(co);
	float u, v;
	if(l > 0.0f) {
		if(UNLIKELY(co.x == 0.0f && co.y == 0.0f)) {
			u = 0.0f;  /* othwise domain error */
		}
		else {
			u = (1.0f - atan2f(co.x, co.y) / M_PI_F) / 2.0f;
		}
		v = 1.0f - safe_acosf(co.z / l) / M_PI_F;
	}
	else {
		u = v = 0.0f;
	}
	return make_float2(u, v);
}

ccl_device_inline int util_max_axis(float3 vec)
{
#ifdef __KERNEL_SSE__
	__m128 a = shuffle<0,0,1,1>(vec.m128);
	__m128 b = shuffle<1,2,2,1>(vec.m128);
	__m128 c = _mm_cmpgt_ps(a, b);
	int mask = _mm_movemask_ps(c) & 0x7;
	static const char tab[8] = {2, 2, 2, 0, 1, 2, 1, 0};
	return tab[mask];
#else
	if(vec.x > vec.y) {
		if(vec.x > vec.z)
			return 0;
		else
			return 2;
	}
	else {
		if(vec.y > vec.z)
			return 1;
		else
			return 2;
	}
#endif
}

CCL_NAMESPACE_END

#endif /* __UTIL_MATH_H__ */
