// Copyright 2021 Alexsand Guchkov <firer.a45@gmail.com>

#include <Cache_tester.hpp>

Cache_tester::Cache_tester(int min, int max)
{
  min_size = min;
  max_size = max;
  set_massive_size();
}

void Cache_tester::set_massive_size()
{
  const float for_min_size = 0.5;
  const float for_max_size = 1.5;
  const int creat_mass = 2;
  int a;
  a = min_size * for_min_size;
  massive_size.push_back(a);
  n = 0;
  n += 1;
  while (a <= max_size/creat_mass)
  {
    a = a * creat_mass;
    n += 1;
    massive_size.push_back(a);
  }
  a = a * for_max_size;
  n += 1;
  massive_size.push_back(a);
  all_experiments();
}

void Cache_tester::all_experiments()
{
  direct.type = "direct";
  reverse.type = "reverse";
  random.type = "random";
  const unsigned int in_new_size = 256;
  const unsigned int in_rand_size = 16;
  const int element_mass_null = 1;
  const int element_max_value = 100;
  for ( int i = 0; i < n; ++i )
  {
    int size = massive_size[i] * in_new_size;
    int mass_rand_size = massive_size[i] * in_rand_size;
    int* array = new int[size];
    int k = 0; int shag = 0;
    int *array_rand = new int[mass_rand_size];
    int *mass_shag = new int[mass_rand_size];
    for (int j = 0; j < mass_rand_size; j++)
    {
      mass_shag[j] = shag;
      shag = shag + shag_in_mass;
    }
    unsigned int b = time(NULL);
    while (k < mass_rand_size)
    {
      int a = rand_r(&b)%mass_rand_size;
      if (mass_shag[a] != element_mass_null)
      {
        array_rand[k] = mass_shag[a];
        k += 1;
        mass_shag[a] = element_mass_null;
      }
    }
    unsigned int a = time(NULL);
    for (int j = 0; j < size; j+=1)
    {
      array[j] = rand_r(&a)%element_max_value;
    }
    experiment_direct(array, size, i);
    experiment_reverse(array, size, i);
    experiment_random(array, mass_rand_size, i, array_rand);
    delete[] array;
    delete[] array_rand;
    delete[] mass_shag;
  }
  out_info();
}

void Cache_tester::experiment_direct(int* array, int size, int i)
{
  int b;
  for (int j = size-1; j > 0; j -= shag_in_mass)
  {
    b = array[j];
  }
  auto start = std::chrono::high_resolution_clock::now();
  for (int k = 0; k < number_of_runs; ++k) {
    for (int j = size-1; j > 0; j -= shag_in_mass)
    {
      b = array[j];
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  b += b;
  float r_time = std::chrono::duration_cast<std::chrono::microseconds>
      (finish - start).count();
  r_time = r_time / number_of_runs;
  direct.time.push_back(r_time);
  direct.number.push_back(i);
}

void Cache_tester::experiment_reverse(int* array, int size, int i)
{
  int b;
  auto start = std::chrono::high_resolution_clock::now();
  for (int k = 0; k < number_of_runs; ++k) {
    for (int j = 0; j < size; j += shag_in_mass)
    {
      b = array[j];
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  b += b;
  float r_time =
      std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
      .count();
  r_time = r_time / number_of_runs;
  reverse.time.push_back(r_time);
  reverse.number.push_back(i);
}

void Cache_tester::experiment_random(int* array, int size, int i, int *shag)
{
  const int shag_in_rand_mass = 1;
  int b;
  auto start = std::chrono::high_resolution_clock::now();
  for (int k = 0; k < number_of_runs; ++k) {
    for (int j = 0; j < size; j += shag_in_rand_mass)
    {
      b = array[shag[j]];
    }
  }
  auto finish = std::chrono::high_resolution_clock::now();
  b += b;
  float r_time =
      std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
      .count();
  r_time = r_time / number_of_runs;
  random.time.push_back(r_time);
  random.number.push_back(i);
}

void Cache_tester::out_info()
{
  std::vector<struct Out_put> mass_out;
  mass_out.push_back(direct);
  mass_out.push_back(reverse);
  mass_out.push_back(random);
  const int number_of_structures = 3;
  for (int j = 0; j < number_of_structures; j++) {
    std::cout << "investigation:" << std::endl;
    std::cout << "  travel_order: "
              << mass_out[j].type << std::endl;
    std::cout << "  experiments:" << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cout << "  - experiment:" << std::endl;
      std::cout << "     number: " << mass_out[j].number[i] + 1 << std::endl;
      std::cout << "     input_data:" << std::endl;
      std::cout << "       buffer_size: " << massive_size[i] << " Kb"
                << std::endl;
      std::cout << "     result:" << std::endl;
      std::cout << "       duration: " << mass_out[j].time[i]
                << " mcs" << std::endl;
    }
    std::cout << std::endl;
  }
}

Cache_tester::~Cache_tester(){}
