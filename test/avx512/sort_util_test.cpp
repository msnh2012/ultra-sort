#include "avx512/sort_util.h"
#include "gtest/gtest.h"
#include "test_util.h"
#include "avx512/utils.h"

#ifdef AVX512
namespace avx512 {
TEST(SortUtilTest, AVX512SortBlock256Int32BitTest) {
  int *arr;
  aligned_init<int>(arr, 256);
  TestUtil::RandGenInt<int>(arr, 256, -10, 10);

  int *check_arr = (int *) malloc(256 * sizeof(int));
  int *temp_arr = (int *) malloc(16 * sizeof(int));
  for (int k = 0; k < 16; k++) {
    for (int i = 0; i < 16; ++i) {
      temp_arr[i] = arr[i * 16 + k];
    }
    std::sort(temp_arr, temp_arr + 16);
    for (int j = 0; j < 16; ++j) {
      check_arr[k * 16 + j] = temp_arr[j];
    }
  }

  SortBlock256<int, __m512i>(arr, 0);

  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(check_arr[i], arr[i]);
  }

  delete[](arr);
  free(check_arr);
  free(temp_arr);
}

TEST(SortUtilTest, AVX512SortBlock256Float32BitTest) {
  float *arr;
  aligned_init<float>(arr, 256);
  TestUtil::RandGenFloat<float>(arr, 256, -10, 10);

  auto *check_arr = (float *) malloc(256 * sizeof(float));
  auto *temp_arr = (float *) malloc(16 * sizeof(float));
  for (int k = 0; k < 16; k++) {
    for (int i = 0; i < 16; ++i) {
      temp_arr[i] = arr[i * 16 + k];
    }
    std::sort(temp_arr, temp_arr + 16);
    for (int j = 0; j < 16; ++j) {
      check_arr[k * 16 + j] = temp_arr[j];
    }
  }

  SortBlock256<float, __m512>(arr, 0);

  for (int i = 0; i < 256; i++) {
    EXPECT_EQ(check_arr[i], arr[i]);
  }

  delete[](arr);
  free(check_arr);
  free(temp_arr);
}
}
#endif