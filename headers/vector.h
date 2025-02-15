/* #if BONSAI_EMCC */
/* #include <wasm_simd128.h> */
/* typedef v128_t __m128; */
/* #else */
#include <immintrin.h>
#include <xmmintrin.h>
/* #endif */

union v2i
{
  s32 E[2];
  struct { s32 x; s32 y; };
};

union v2
{
  r32 E[2];
  struct { r32 x; r32 y; };
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
union v3i
{
  s32 E[3];

  struct { s32 x; s32 y; s32 z; };
  struct { s32 r; s32 g; s32 b; };

  struct {
    v2i xy;
    s32 Ignored0_;
  };

  struct {
    s32 Ignored1_;
    v2i yz;
  };
};

union v3
{
  r32 E[3];

  struct { r32 x; r32 y; r32 z; };
  struct { r32 r; r32 g; r32 b; };

  struct {
    v2 xy;
    r32 Ignored0_;
  };

  struct {
    r32 Ignored1_;
    v2 yz;
  };
};


// Note: OpenGL matrices have x first
union v4
{
  r32 E[4];

  struct { r32 x; r32 y; r32 z; r32 w; };
  struct { r32 r; r32 g; r32 b; r32 a; };
  struct { r32 Left; r32 Top; r32 Right; r32 Bottom; };

  struct {
    v2 xy;
    r32 Ignored0_;
    r32 Ignored01_;
  };

  struct {
    v2 Ignored1_;
    v2 zw;
  };


  struct {
    v3 xyz;
    r32 Ignored03_;
  };

  struct {
    v3 rgb;
    r32 Ignored04_;
  };

  r32&
  operator[](s32 index)
  {
    r32& Result = this->E[index];
    return Result;
  }
};


link_internal v4
V4(v3 v, f32 w)
{
  v4 Result = {
    .x = v.x,
    .y = v.y,
    .z = v.z,
    .w = w,
  };
  return Result;
}

link_internal v4
V4(r32 Fill)
{
  v4 Result = {
    .x = Fill,
    .y = Fill,
    .z = Fill,
    .w = Fill,
  };
  return Result;
}

link_internal v4
V4( f32 x, f32 y, f32 z, f32 w)
{
  v4 Result = {
    .x = x,
    .y = y,
    .z = z,
    .w = w,
  };
  return Result;
}


#pragma GCC diagnostic pop


typedef v3i voxel_position;
typedef v3i chunk_dimension;
typedef v3i world_position;

inline voxel_position
Voxel_Position(v3 Offset)
{
  voxel_position Result;

  Result.x = (s32)Offset.x;
  Result.y = (s32)Offset.y;
  Result.z = (s32)Offset.z;

  return Result;
}


poof(gen_vector_operators(v2))
#include <generated/gen_vector_operators_v2.h>

poof(gen_vector_operators(v2i))
#include <generated/gen_vector_operators_v2i.h>

poof(gen_vector_operators(v3))
#include <generated/gen_vector_operators_v3.h>

poof(gen_vector_operators(v3i))
#include <generated/gen_vector_operators_v3i.h>

poof(gen_vector_operators(v4))
#include <generated/gen_vector_operators_v4.h>

poof(gen_hetero_vector_operators(v2, v2i))
#include <generated/gen_hetero_vector_operators_v2_v2i.h>

poof(gen_hetero_vector_operators(v2i, v2))
#include <generated/gen_hetero_vector_operators_v2i_v2.h>

poof(gen_hetero_vector_operators(v3, v3i))
#include <generated/gen_hetero_vector_operators_v3_v3i.h>

poof(gen_hetero_vector_operators(v3i, v3))
#include <generated/gen_hetero_vector_operators_v3i_v3.h>



inline v3i
operator~(v3i P)
{
  v3i Result = {
    .x = ~P.x,
    .y = ~P.y,
    .z = ~P.z
  };
  return Result;
}

inline v3
operator*(voxel_position P1, f32 f)
{
  v3 Result;
  Result.x = (r32)P1.x * f;
  Result.y = (r32)P1.y * f;
  Result.z = (r32)P1.z * f;
  return Result;
}


inline v3i
V3i(v3 V)
{
  v3i Result = {{ (s32)V.x, (s32)V.y, (s32)V.z }};
  return Result;
}

inline v3i
V3i(v2i XY, s32 Z)
{
  v3i Result = {{ XY.x, XY.y, Z}};
  return Result;
}

inline v3i
V3i(f32 Flood)
{
  v3i Result = {{ s32(Flood), s32(Flood), s32(Flood) }};
  return Result;
}

inline v3i
V3i(s32 Flood)
{
  v3i Result = {{ Flood, Flood, Flood }};
  return Result;
}

inline v3i
V3i(s32 X, s32 Y, s32 Z)
{
  v3i Result = {{ X, Y, Z }};
  return Result;
}

inline v3
V3(r32 I)
{
  v3 Result;
  Result.x = I;
  Result.y = I;
  Result.z = I;
  return Result;
}

inline v3
V3(s32 I)
{
  v3 Result;
  Result.x = (r32)I;
  Result.y = (r32)I;
  Result.z = (r32)I;
  return Result;
}

inline v3
V3(v3i wp)
{
  v3 Result;
  Result.x = (f32)wp.x;
  Result.y = (f32)wp.y;
  Result.z = (f32)wp.z;
  return Result;
}

inline v3
V3(s32 x, s32 y, s32 z)
{
  v3 Result = {};
  Result.x = (f32)x;
  Result.y = (f32)y;
  Result.z = (f32)z;
  return Result;
}

inline v3
V3(v2 XY, f32 z)
{
  v3 Result = {{ XY.x, XY.y, z }};
  return Result;
}

inline v3
V3(f32 x, f32 y, f32 z)
{
  v3 Result = {};
  Result.x = x;
  Result.y = y;
  Result.z = z;
  return Result;
}

inline world_position
World_Position(v3 V)
{
  voxel_position Result;
  Result.x = (s32)V.x;
  Result.y = (s32)V.y;
  Result.z = (s32)V.z;
  return Result;
}

inline voxel_position
Voxel_Position(s32 P)
{
  voxel_position Result;
  Result.x = P;
  Result.y = P;
  Result.z = P;
  return Result;
}

inline voxel_position
Voxel_Position(s32 x, s32 y, s32 z)
{
  voxel_position Result;
  Result.x = x;
  Result.y = y;
  Result.z = z;
  return Result;
}

inline world_position
World_Position(s32 P)
{
  chunk_dimension Result = Voxel_Position(P);
  return Result;
}

inline world_position
World_Position(s32 x, s32 y, s32 z)
{
  chunk_dimension Result = Voxel_Position(x,y,z);
  return Result;
}


inline chunk_dimension
Chunk_Dimension(s32 flood)
{
  chunk_dimension Result = Voxel_Position(flood,flood,flood);
  return Result;
}

inline chunk_dimension
Chunk_Dimension(s32 x, s32 y, s32 z)
{
  chunk_dimension Result = Voxel_Position(x,y,z);
  return Result;
}

v3
Truncate(v3 Input)
{
  v3 Result = V3(Voxel_Position(Input));
  return Result;
}

r32
Truncate(r32 Input)
{
  s32 Truncated = (s32)Input;
  r32 Result = (r32)Truncated;
  return Result;
}

inline s32
Volume(v3 Dim)
{
  Dim.x = Max(Dim.x, 0.f);
  Dim.y = Max(Dim.y, 0.f);
  Dim.z = Max(Dim.z, 0.f);
  s32 Result = (s32)(Dim.x*Dim.y*Dim.z);
  Assert(Result > 0);
  return Result;
}

inline s32
Volume(chunk_dimension Dim)
{
  Dim.x = Max(Dim.x, 0);
  Dim.y = Max(Dim.y, 0);
  Dim.z = Max(Dim.z, 0);
  return (Dim.x*Dim.y*Dim.z);
}

inline v2
V2(v2i V)
{
  v2 Result;
  Result.x = (r32)V.x;
  Result.y = (r32)V.y;
  return Result;
}

inline v2
V2(s32 F)
{
  v2 Result = {{(r32)F, (r32)F}};
  return Result;
}

inline v2
V2(r32 F)
{
  v2 Result = {{F, F}};
  return Result;
}

v2
V2(f32 x,f32 y)
{
  v2 Result = {{x,y}};
  return Result;
}

v2i
V2i(v2 V)
{
  v2i Result;
  Result.x = (s32)V.x;
  Result.y = (s32)V.y;
  return Result;
}

v2i
V2i(s32 P)
{
  v2i Result = {{P,P}};
  return Result;
}

v2i
V2i(s32 x, s32 y)
{
  v2i Result = {{x,y}};
  return Result;
}

v2i
V2i(u32 x, u32 y)
{
  v2i Result = V2i((s32)x, (s32)y);
  return Result;
}

inline v3i
operator%(v3i A, v3i B)
{
  v3i Result;
  Result.x = A.x % B.x;
  Result.y = A.y % B.y;
  Result.z = A.z % B.z;
  return Result;
}

inline v3
operator/(v3 A, s32 B)
{
  v3 Result;
  Result.x = A.x / (f32)B;
  Result.y = A.y / (f32)B;
  Result.z = A.z / (f32)B;
  return Result;
}

inline v3
operator/(voxel_position A, r32 f)
{
  v3 Result;
  Result.x = (r32)A.x / f;
  Result.y = (r32)A.y / f;
  Result.z = (r32)A.z / f;
  return Result;
}


union f32_reg {
  r32 F[4];
  __m128 Sse;
};



// TODO(Jesse): Now that we're generating operators, it's pretty easy for us to
// do performance experiments by converting all operators to SIMD in one fell
// swoop..
#if 0
#define SIMD_OPERATORS 1
#define SANITY_CHECK_SIMD_OPERATORS 1
inline v3
operator*(v3 A, v3 B)
{

#if SIMD_OPERATORS
  __m128 Vec1 = _mm_set_ps(0, A.z, A.y, A.x);
  __m128 Vec2 = _mm_set_ps(0, B.z, B.y, B.x);

  f32_reg Res;
  Res.Sse = _mm_mul_ps(Vec1, Vec2);

  v3 Result = {{ Res.F[0], Res.F[1], Res.F[2] }};

#if SANITY_CHECK_SIMD_OPERATORS
  v3 Sanity;
  Sanity.x = A.x * B.x;
  Sanity.y = A.y * B.y;
  Sanity.z = A.z * B.z;
  Assert(Sanity.x == Result.x);
  Assert(Sanity.y == Result.y);
  Assert(Sanity.z == Result.z);
#endif

  return Result;

#else
  v3 Result;

  Result.x = A.x * B.x;
  Result.y = A.y * B.y;
  Result.z = A.z * B.z;

  return Result;
#endif

}
#endif

v3 operator+(v3 A, v2 B)
{
  v3 Result = {
    .x = A.x + B.x,
    .y = A.y + B.y,
    .z = A.z,
  };
  return Result;
}

v3 &
operator+=(v3 &A, v2 B)
{
  A = A + B;
  return A;
}


v4
operator*(v4 A, s32 B)
{
  v4 Result = {};
  Result.x = A.x * (f32)B;
  Result.y = A.y * (f32)B;
  Result.z = A.z * (f32)B;
  Result.w = A.w * (f32)B;
  return Result;
}

inline v4
operator*=(v4 A, s32 B)
{
  A = A * B;
  return A;
}

inline v3
operator^(v3 P1, v3 P2)
{
  v3 Result;
  Result.x = (r32)((s32)P1.x ^ (s32)P2.x);
  Result.y = (r32)((s32)P1.y ^ (s32)P2.y);
  Result.z = (r32)((s32)P1.z ^ (s32)P2.z);
  return Result;
}

inline v3
operator%(v3 A, s32 i)
{
  v3 Result;
  Result.x = (f32)((s32)A.x % i);
  Result.y = (f32)((s32)A.y % i);
  Result.z = (f32)((s32)A.z % i);
  return Result;
}

poof(gen_vector_infix_operator(v3i, {^}))
#include <generated/gen_vector_infix_operator_v3i_688856449.h>

poof(gen_vector_infix_operator(v3i, {&}))
#include <generated/gen_vector_infix_operator_v3i_688856393.h>

poof(gen_vector_lerp(f32))
#include <generated/gen_lerp_f32.h>

poof(gen_vector_lerp(v2))
#include <generated/gen_lerp_v2.h>

poof(gen_vector_lerp(v3))
#include <generated/gen_lerp_v3.h>

// TODO(Jesse): The heck do we use this for?
// UPDATE(Jesse): Apparently nothing..
/* poof(gen_vector_lerp(v4)) */
/* #include <generated/gen_lerp_v4.h> */

poof(gen_vector_area(v2))
#include <generated/gen_vector_area_v2.h>

poof(gen_vector_area(v2i))
#include <generated/gen_vector_area_v2i.h>

poof(gen_common_vector(v2))
#include <generated/gen_common_vector_v2.h>

poof(gen_common_vector(v3))
#include <generated/gen_common_vector_v3.h>

poof(gen_common_vector(v3i))
#include <generated/gen_common_vector_v3i.h>

poof(gen_vector_normalize(v2))
#include <generated/gen_vector_normalize_funcs_v2.h>

poof(gen_vector_normalize(v3))
#include <generated/gen_vector_normalize_funcs_v3.h>


inline v3
Ceil(v3 Vec)
{
  v3 Result = {{ Ceilf(Vec.x), Ceilf(Vec.y), Ceilf(Vec.z) }};
  return Result;
}

inline r32
Distance( v3 P1, v3 P2 )
{
  r32 Result = Length(P1-P2);
  return Result;
}

inline r32
DistanceSq( v3 P1, v3 P2 )
{
  r32 Result = LengthSq(P1-P2);
  return Result;
}


inline r32
Dot( v3 A, v3 B)
{
  r32 Result;
  Result = (A.x*B.x) + (A.y*B.y) + (A.z*B.z);
  return Result;
}

inline v3
Cross( voxel_position A, voxel_position B )
{
  v3 Result = {{
    (r32)(A.y*B.z)-(r32)(A.z*B.y),
    (r32)(A.z*B.x)-(r32)(A.x*B.z),
    (r32)(A.x*B.y)-(r32)(A.y*B.x)
  }};

  return Result;
}

inline v3
Cross( v3 A, v3 B )
{
  v3 Result = {{
    (A.y*B.z)-(A.z*B.y),
    (A.z*B.x)-(A.x*B.z),
    (A.x*B.y)-(A.y*B.x)
  }};

  return Result;
}

inline v3
SafeDivide0(v3 Dividend, r32 Divisor)
{
  v3 Result = {};

  if (Divisor != 0.0f)
    Result = Dividend/Divisor;

  return Result;
}

b32
PointsAreWithinDistance(v3 P1, v3 P2, f32 Thresh)
{
  v3 P1toP2 = P2-P1;
  f32 LenSq = LengthSq(P1toP2);

  b32 Result = LenSq < Square(Thresh);
  return Result;
}

inline v3
SafeDivide(v3 Dividend, r32 Divisor)
{
  v3 Result = Dividend;

  if (Divisor != 0.0f)
    Result = Dividend/Divisor;

  return Result;
}

inline voxel_position
ClampMinus1toInfinity( voxel_position V )
{
  voxel_position Result = V;

  if ( V.x < 0 )
    Result.x = -1;

  if ( V.y < 0 )
    Result.y = -1;

  if ( V.z < 0 )
    Result.z = -1;

  return Result;
}

inline v3i
GetSigni(v3 P)
{
  v3i Result = V3i( GetSign(P.x), GetSign(P.y), GetSign(P.z));
  return Result;
}
