#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <array>
#include <fstream>
#include <iomanip>
#include <x86intrin.h>
#include <time.h>
#include <limits>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const int n = 10;
    std::array<long double, n> rand_arr;
    std::random_device rd;
    std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    std::mt19937_64 generator(seed);
    std::uniform_real_distribution<long double> distribution(0.0, 1.0);

    while (true) {
        // Use SSE4.1 intrinsics for faster random number generation
        __m128d sum_xmm = _mm_setzero_pd();
        for (int i = 0; i < n; i += 2) {
            __m128d rand_xmm = _mm_set_pd(distribution(generator), distribution(generator));
            __m128d temp_xmm = _mm_mul_pd(rand_xmm, _mm_set1_pd(1000000.0));
            sum_xmm = _mm_add_pd(sum_xmm, temp_xmm);
            double rand_arr_arr[2];
            _mm_store_pd(rand_arr_arr, rand_xmm);
            rand_arr[i] = rand_arr_arr[0];
            rand_arr[i + 1] = rand_arr_arr[1];
        }
        double sum[2];
        _mm_store_pd(sum, sum_xmm);
        double nanoseconds = (sum[0] + sum[1]) / n;
        std::cout << std::setprecision(15) << nanoseconds << std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<int>(nanoseconds * 1000)));

        // Use AES-NI intrinsics to quickly write random numbers to /dev/urandom
        __m128i *rand_arr_ptr = reinterpret_cast<__m128i *>(rand_arr.data());
        // Use SSE4.1 intrinsics for faster random number generation
        __m128i rand_xmm;
        // Use SSE2 intrinsics to quickly open /dev/urandom
        int fd = open("/dev/urandom", O_WRONLY | O_DIRECT);
        if (fd != -1) {
            for (int i = 0; i < n / 2; ++i) {
                rand_xmm = _mm_load_si128(rand_arr_ptr + i);
                // Use AES-NI intrinsics to quickly generate random numbers
                __m128i aes_rand_xmm = _mm_aesenclast_si128(rand_xmm, rand_xmm);
                // Use SSE4.1 intrinsics to quickly write to /dev/urandom
                _mm_stream_si128(reinterpret_cast<__m128i *>(&aes_rand_xmm), aes_rand_xmm);
            }
            close(fd);
        }
    }
    return 0;
}
