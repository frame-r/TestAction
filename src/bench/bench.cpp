#include "vmath.h"
#include "benchmark/benchmark.h"
#include <chrono>

using namespace math;

float _m[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
constexpr auto iters = 2'000'000;

static void mat4_mult(benchmark::State &state) {
  
  for (auto _ : state) {
	  
    auto start = std::chrono::high_resolution_clock::now();
	  
	for (auto i = 0; i < iters; ++i) {
		mat4 a(_m);
		mat4 b(_m);		
		benchmark::DoNotOptimize(a * b);
	}
	
	auto end = std::chrono::high_resolution_clock::now();
	
	auto elapsed_seconds =
      std::chrono::duration_cast<std::chrono::duration<double>>(
        end - start);
		
	state.SetIterationTime(elapsed_seconds.count());
  }
}

static void mat4_inv(benchmark::State &state) {
  for (auto _ : state) {	
	for (auto i = 0; i < iters; ++i) {
		mat4 a(_m);
		benchmark::DoNotOptimize(a.Inverse());
	}
  }
}

// Register the function as a benchmark
BENCHMARK(mat4_mult)->UseManualTime();
BENCHMARK(mat4_inv);

// Run the benchmark
BENCHMARK_MAIN();