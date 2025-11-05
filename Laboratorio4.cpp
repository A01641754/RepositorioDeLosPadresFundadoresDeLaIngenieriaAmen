#include <iostream>
#include <cstdlib>   // Para numeros pseudoaleatorios
#include <chrono>    // For measuring execution time
#include <vector>    // Para std::vector

// ------------------------------  Starter Code  ------------------------

void fill_random(std::vector<int> &values, int max_value)
{
    std::srand(0);
    for (int i = 0; i < values.size(); ++i)
    {
        values.at(i) = std::rand() % max_value;
    }
}

void fill_incremental(std::vector<int> &values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = 0; i < values.size(); ++i)
    {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

void fill_decremental(std::vector<int> &values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = values.size() - 1; i >= 0; --i)
    {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

//------------------------- Sorting Algorithms -----------------------






int main () {

    // Ejemplo de uso del cronómetro

// auto start = std::chrono::high_resolution_clock::now();

// Codigo pa





// auto stop = std::chrono::high_resolution_clock::now();
// auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
// double total_time = duration.count() / 1'000'000.0;
// std::cout << "Tiempo: " << total_time << "s\n";



    return 0;
}


