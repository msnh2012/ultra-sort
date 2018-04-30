#include "gtest/gtest.h"
#include "test_util.h"
#include "avx512/utils.h"
#include "avx512/sort_util.h"
#include "avx512/merge_util.h"
#include <algorithm>
#include <iterator>

#ifdef AVX512

TEST(UtilsTest, AVX512LoadStore32BitTest) {
  int *a;
  int *b;
  aligned_init(a, 16);
  aligned_init(b, 16);
  TestUtil::PopulateSeqArray(a, 0, 16);
  TestUtil::PopulateSeqArray(b, 16, 32);
  __m512i ra, rb;
  AVX512Util::LoadReg(ra, a);
  AVX512Util::LoadReg(rb, b);
  AVX512Util::StoreReg(ra, b);
  AVX512Util::StoreReg(rb, a);
  for(int i = 0; i < 16; i++) {
    EXPECT_EQ(b[i], i);
    EXPECT_EQ(a[i], i + 16);
  }
  delete[](a);
  delete[](b);
}

TEST(UtilsTest, AVX512LoadStore64BitTest) {
  int64_t *a;
  int64_t *b;
  aligned_init<int64_t>(a, 8);
  aligned_init<int64_t>(b, 8);
  TestUtil::PopulateSeqArray<int64_t>(a, 0, 8);
  TestUtil::PopulateSeqArray<int64_t>(b, 8, 16);
  __m512i ra, rb;
  AVX512Util::LoadReg(ra, a);
  AVX512Util::LoadReg(rb, b);
  AVX512Util::StoreReg(ra, b);
  AVX512Util::StoreReg(rb, a);
  for(int i = 0; i < 8; i++) {
    EXPECT_EQ(b[i], i);
    EXPECT_EQ(a[i], i + 8);
  }
  delete[](a);
  delete[](b);
}

TEST(UtilsTest, AVX512MinMax16Int32BitTest) {
  int *a;
  int *b;
  aligned_init(a, 16);
  aligned_init(b, 16);
  TestUtil::RandGenInt(a, 16, -10, 10);
  TestUtil::RandGenInt(b, 16, -10, 10);
  __m512i ra, rb;
  AVX512Util::LoadReg(ra, a);
  AVX512Util::LoadReg(rb, b);
  AVX512Util::MinMax16(ra, rb);
  AVX512Util::StoreReg(ra, a);
  AVX512Util::StoreReg(rb, b);
  for(int i = 0; i < 16; i++) {
    EXPECT_LE(a[i], b[i]);
  }
  delete[](a);
  delete[](b);
}

TEST(UtilsTest, AVX512MinMax16Float32BitTest) {
  float *a;
  float *b;
  aligned_init(a, 16);
  aligned_init(b, 16);
  float lo = -10;
  float hi = 10;
  TestUtil::RandGenFloat(a, 16, lo, hi);
  TestUtil::RandGenFloat(b, 16, lo, hi);
  __m512 ra, rb;
  AVX512Util::LoadReg(ra, a);
  AVX512Util::LoadReg(rb, b);
  AVX512Util::MinMax16(ra, rb);
  AVX512Util::StoreReg(ra, a);
  AVX512Util::StoreReg(rb, b);
  for(int i = 0; i < 16; i++) {
    EXPECT_LE(a[i], b[i]);
  }
  delete[](a);
  delete[](b);
}

TEST(UtilsTest, AVX512MinMax8Int64BitTest) {
  int64_t *a;
  int64_t *b;
  aligned_init<int64_t>(a, 8);
  aligned_init<int64_t>(b, 8);
  TestUtil::RandGenInt<int64_t>(a, 8, -10, 10);
  TestUtil::RandGenInt<int64_t>(b, 8, -10, 10);
  __m512i ra, rb;
  AVX512Util::LoadReg(ra, a);
  AVX512Util::LoadReg(rb, b);
  AVX512Util::MinMax8(ra, rb);
  AVX512Util::StoreReg(ra, a);
  AVX512Util::StoreReg(rb, b);
  for(int i = 0; i < 8; i++) {
    EXPECT_LE(a[i], b[i]);
  }
  delete[](a);
  delete[](b);
}

TEST(UtilsTest, AVX512MinMax8Float64BitTest) {
  double *a;
  double *b;
  aligned_init<double>(a, 8);
  aligned_init<double>(b, 8);
  TestUtil::RandGenFloat<double>(a, 8, -10, 10);
  TestUtil::RandGenFloat<double>(b, 8, -10, 10);
  __m512d ra, rb;
  AVX512Util::LoadReg(ra, a);
  AVX512Util::LoadReg(rb, b);
  AVX512Util::MinMax8(ra, rb);
  AVX512Util::StoreReg(ra, a);
  AVX512Util::StoreReg(rb, b);
  for(int i = 0; i < 8; i++) {
    EXPECT_LE(a[i], b[i]);
  }
  delete[](a);
  delete[](b);
}

TEST(UtilsTest, AVX512Reverse16Int32BitTest) {
  int *a;
  aligned_init<int>(a, 16);

  TestUtil::RandGenInt(a, 16, -10, 10);
  std::sort(a, a + 16);

  int check_arr[16];
  for (int i = 15; i >= 0; --i) {
    check_arr[15 - i] = a[i];
  }

  __m512i ra;
  AVX512Util::LoadReg(ra, a);
  ra = AVX512Util::Reverse16(ra);
  AVX512Util::StoreReg(ra, a);

  for (int j = 0; j < 16; ++j) {
    EXPECT_EQ(check_arr[j], a[j]);
  }

  delete[](a);
}

#endif
