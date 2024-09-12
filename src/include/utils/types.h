#ifndef TYPES_H
#define TYPES_H

// fixed width numeric types
#include <stdint.h>
#include <inttypes.h>
#include "optional.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

typedef opt_bt(u8) opt_u8;
typedef opt_bt(u16) opt_u16;
typedef opt_bt(u32) opt_u32;
typedef opt_bt(u64) opt_u64;

typedef opt_bt(s8) opt_s8;
typedef opt_bt(s16) opt_s16;
typedef opt_bt(s32) opt_s32;
typedef opt_bt(s64) opt_s64;

typedef opt_bt(f32) opt_f32;
typedef opt_bt(f64) opt_f64;

#endif