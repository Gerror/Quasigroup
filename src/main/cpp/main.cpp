#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <fstream>
#include "Quasigroup.h"
#include "IncidenceCube.h"

using namespace std;

void Test(int min_order, int max_order, int numOfAttempts) {
    if (min_order <= 0 || max_order <= 0 || min_order > max_order || numOfAttempts <= 0)
        return;

    time_t seed = std::time(NULL);

    std::ofstream out_generation_worst;
    std::ofstream out_generation_average;

    std::ofstream out_affine_worst;
    std::ofstream out_affine_average;

    std::ofstream out_simple_worst;
    std::ofstream out_simple_average;

    std::ofstream out_seed;

    double worst_time_generation = 0.0;
    double worst_time_affine = 0.0;
    double worst_time_simple = 0.0;

    double average_time_generation = 0.0;
    double average_time_affine = 0.0;
    double average_time_simple = 0.0;

    out_generation_worst.open("generation_worst.txt", std::ios::app);
    out_generation_average.open("generation_average.txt", std::ios::app);

    out_affine_worst.open("affine_worst.txt", std::ios::app);
    out_affine_average.open("affine_average.txt", std::ios::app);

    out_simple_worst.open("simple_worst.txt", std::ios::app);
    out_simple_average.open("simple_average.txt", std::ios::app);

    out_seed.open("seed.txt", std::ios::app);

    std::srand(seed);

    for (int i = min_order; i <= max_order; i++) {
        worst_time_generation = 0.0;
        worst_time_affine = 0.0;
        worst_time_simple = 0.0;

        average_time_generation = 0.0;
        average_time_affine = 0.0;
        average_time_simple = 0.0;

        for (int j = 0; j < numOfAttempts; j++) {
            auto begin = chrono::steady_clock::now();
            Quasigroup::Quasigroup quasigroup(i);
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            double time = elapsed.count() / ((double) 1000000);

            average_time_generation += time;
            if (time > worst_time_generation)
                worst_time_generation = time;

            begin = chrono::steady_clock::now();
            quasigroup.IsAffine();
            end = chrono::steady_clock::now();
            elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            time = elapsed.count() / ((double) 1000000);

            average_time_affine += time;
            if (time > worst_time_affine)
                worst_time_affine = time;

            begin = chrono::steady_clock::now();
            quasigroup.IsSimple();
            end = chrono::steady_clock::now();
            elapsed = chrono::duration_cast<chrono::microseconds>(end - begin);
            time = elapsed.count() / ((double) 1000000);

            average_time_simple += time;
            if (time > worst_time_simple)
                worst_time_simple = time;

        }

        average_time_generation /= double(numOfAttempts);
        average_time_affine /= double(numOfAttempts);
        average_time_simple /= double(numOfAttempts);

        out_generation_average << i << " " << average_time_generation << "\n";
        out_generation_worst << i << " " << worst_time_generation << "\n";

        out_affine_average << i << " " << average_time_affine << "\n";
        out_affine_worst << i << " " << worst_time_affine << "\n";

        out_simple_average << i << " " << average_time_simple << "\n";
        out_simple_worst << i << " " << worst_time_simple << "\n";

        std::cout << i << "\n";
    }

    out_seed << "Seed: " << seed << "\n";
}

int main() {
    return 0;
}
