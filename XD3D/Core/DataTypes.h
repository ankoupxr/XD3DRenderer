#pragma once

#include <stdint.h>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

static_assert(sizeof(int8) == 1, "int8 size incorrect.");
static_assert(sizeof(int16) == 2, "int16 size incorrect.");
static_assert(sizeof(int32) == 4, "int32 size incorrect.");
static_assert(sizeof(int64) == 8, "int64 size incorrect.");
static_assert(sizeof(uint8) == 1, "uint8 size incorrect.");
static_assert(sizeof(uint16) == 2, "uint16 size incorrect.");
static_assert(sizeof(uint32) == 4, "uint32 size incorrect.");
static_assert(sizeof(uint64) == 8, "uint64 size incorrect.");