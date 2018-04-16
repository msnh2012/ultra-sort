//#include <cassert>
//#include "metrics/cycletimer.h"
//#include <random>
//#include "common.h"
//#include "avx256/simd_sort.h"
//
//template <typename T>
//void rand_gen(T* &arr, int N, int lo, int hi) {
//  aligned_init<T>(arr, N);
//  std::random_device rd;  //Will be used to obtain a seed for the random number engine
//  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
//  std::uniform_int_distribution<> dis(lo, hi);
//  for(size_t i = 0; i < N; i++) {
//    arr[i] = dis(gen);
//  }
//}
//
////void rand_pairgen(std::pair<int,int>** &arr, int N, int lo_key, int hi_key, int lo_value, int hi_value) {
////  aligned_init<std::pair<int,int>*>(arr, N);
////  std::random_device rd;  //Will be used to obtain a seed for the random number engine
////  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
////  std::uniform_int_distribution<> dis_key(lo_key, hi_key);
////  std::uniform_int_distribution<> dis_value(lo_value, hi_value);
////  for(size_t i = 0; i < N; i++) {
////    arr[i] = new std::pair<int, int>(dis_key(gen), dis_value(gen));
////  }
////}
//
//void check_correctness(int* cand, int N) {
//  for(int i = 1; i < N; i++) {
//    assert(cand[i] >= cand[i - 1]);
//  }
//}
//
//void check_correctness(int64_t * cand, int N) {
//  for(int i = 1; i < N; i++) {
//    assert(cand[i] >= cand[i - 1]);
//  }
//}
//
//
//int main() {
//  // Initialization
//  // Need to resolve pass buffer problem for all multiples of 2
//  int N = 64;
//  int lo = -10;
//  int hi = 10;
//  int64_t *rand_arr;
//  int64_t *soln_arr;
//  double start, end;
//
//  // Initialization
//  rand_gen<int64_t>(rand_arr, N, lo, hi);
//
//  // C++11 std::stable_sort
//  aligned_init<int64_t>(soln_arr, N);
//  std::copy(rand_arr, rand_arr + N, soln_arr);
//  start = currentSeconds();
//  std::stable_sort(soln_arr, soln_arr + N);
//  end = currentSeconds();
//  check_correctness(soln_arr, N);
//  printf("[std::stable_sort] %d elements: %.8f seconds\n", N, end - start);
//  delete soln_arr;
//
//  // C++11 std::sort
//  aligned_init<int64_t>(soln_arr, N);
//  std::copy(rand_arr, rand_arr + N, soln_arr);
//  start = currentSeconds();
//  std::sort(soln_arr, soln_arr + N);
//  end = currentSeconds();
//  check_correctness(soln_arr, N);
//  printf("[std::sort] %d elements: %.8f seconds\n", N, end - start);
//  delete soln_arr;
//
//#ifdef AVX2
//  aligned_init<int64_t>(soln_arr, N);
//  std::copy(rand_arr, rand_arr + N, soln_arr);
//  print_arr(rand_arr, 0, N);
//  print_arr(soln_arr, 0, N);
//  start = currentSeconds();
//  SIMDSorter::SIMDSort64(N, soln_arr);
//  end = currentSeconds();
//  print_arr(soln_arr, 0, N);
//  check_correctness(soln_arr, N);
//  printf("[avx256::sort] %d elements: %.8f seconds\n", N, end - start);
//#endif
//
//#ifdef AVX512
//
//  sort_block_avx512(rand_arr, 0);
//#endif
//  return 0;
//}
