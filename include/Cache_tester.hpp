// Copyright 2021 Alexsand Guchkov <firer.a45@gmail.com>

#ifndef INCLUDE_CACHE_TESTER_HPP_
#define INCLUDE_CACHE_TESTER_HPP_

#include <vector>
#include <iostream>
#include <time.h>
#include <chrono>
#include <string>

struct Out_put
{
  std::string type;
  std::vector<float> time;
  std::vector<uint32_t> number;
};

class Cache_tester
{
 public:
  explicit Cache_tester(int min, int max);
  void set_massive_size();
  void all_experiments();
  void experiment_direct(int* array, int size, int i);
  void experiment_reverse(int* array, int size, int i);
  void experiment_random(int* array, int size, int i, int *shag);
  void out_info();
  ~Cache_tester();
 private:
  const int number_of_runs = 1000;
  const int shag_in_mass = 16;
  std::vector<int> massive_size;
  struct Out_put direct;
  struct Out_put reverse;
  struct Out_put random;
  int n;
  int min_size;
  int max_size;
};
#endif // INCLUDE_CACHE_TESTER_HPP_
