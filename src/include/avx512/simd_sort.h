#pragma once

#include "avx512/sort_util.h"
#include "avx512/merge_util.h"
#include "avx512/utils.h"
#include "common.h"

#ifdef AVX512
class AVX512SIMDSorter{
 public:
  static void SIMDSort32(size_t N, int *&arr);
  static void SIMDSort64(size_t N, int64_t *&arr);
};
#endif
