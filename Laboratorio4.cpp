#include <iostream>
#include <cstdlib>   // Para numeros pseudoaleatorios
#include <chrono>    // For measuring execution time
#include <vector>    // Para std::vector

// ------------------------------  Starter Code  --------------------------

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

void Insertionsort(std::vector<int> &values)
{
    // Recorremos todos los elementos del arreglo
    for (int i = 0; i < values.size(); i++)
    {
        // Guardamos el valor que queremos insertar en la parte ordenada
        int temp = values[i];

        // Buscamos la posición j donde meteremos key
        int j = i - 1;

        // Mientras estemos dentro del arreglo y encontremos valores mayores a key,
        // los movemos hacia la derecha
        while (j >= 0 && values[j] > temp)
        {
            values[j + 1] = values[j];
            j--;
        }

        // Insertamos key en la posición j+1 (que es su lugar correcto)
        values[j + 1] = temp;
    }
}

void Selectionsort(std::vector<int> &values)
{
    // Recorremos cada posición del arreglo
    for (int i = 0; i < values.size(); i++)
    {
        // Suponemos que el más pequeño está en i
        int min_index = i;

        // Buscamos el menor a partir de i
        for (int j = i + 1; j < values.size(); j++)
        {
            if (values[j] < values[min_index])
            {
                min_index = j;  // Encontramos un valor más pequeño
            }
        }

        // Intercambiamos values[i] con values[min_index]
        if (min_index != i)
        {
            int temp = values[i];
            values[i] = values[min_index];
            values[min_index] = temp;
        }
    }
}

void Bubblesort(std::vector<int> &values)
{
    bool not_sorted = true; // Para repetir mientras falte ordenar

    while (not_sorted)
    {
        not_sorted = false; // Asumimos que ya está ordenado

        // Recorremos el vector buscando elementos desordenados
        for (int i = 1; i < values.size(); i++)
        {
            // Si están al revés (valores[i] < valores[i-1]), los intercambiamos
            if (values[i] < values[i - 1])
            {
                int temp = values[i];
                values[i] = values[i - 1];
                values[i - 1] = temp;

                not_sorted = true; // Como hubo swap, aún no estaba ordenado
            }
        }
    }
}

int Partition(std::vector<int> &values, int start, int end)
{
    int divider = values[start];   // Tomamos el primer elemento como pivote
    int left = start + 1;
    int right = end;

    while (true)
    {
        // Mueve left hacia adelante mientras sea menor que el pivote
        while (left <= right && values[left] < divider)
        {
            left++;
        }

        // Mueve right hacia atrás mientras sea mayor o igual que el pivote
        while (left <= right && values[right] >= divider)
        {
            right--;
        }

        // Si se cruzan, terminamos la partición
        if (left > right)
        {
            break;
        }

        // Intercambiamos
        int temp = values[left];
        values[left] = values[right];
        values[right] = temp;
    }

    // Ponemos el pivote en su lugar final
    values[start] = values[right];
    values[right] = divider;

    return right; // índice donde quedó el pivote (middle)
}

void Quicksort(std::vector<int> &values, int start, int end)
{
    // Caso base: si start >= end ya está ordenado
    if (start >= end)
    {
        return;
    }

    // Particionamos, obtenemos la posición final del pivote (middle)
    int middle = Partition(values, start, end);

    // Recursivamente ordenamos las dos mitades
    Quicksort(values, start, middle - 1);
    Quicksort(values, middle + 1, end);
}

void Mergesort(std::vector<int> &values, std::vector<int> &scratch, int start, int end)
{
    // Caso base: un solo elemento está ordenado
    if (start == end)
    {
        return;
    }

    // Encontrar el punto medio
    int midpoint = (start + end) / 2;

    // Ordenar primera mitad
    Mergesort(values, scratch, start, midpoint);

    // Ordenar segunda mitad
    Mergesort(values, scratch, midpoint + 1, end);

    // Mezclar las dos mitades ordenadas
    int left_index = start;
    int right_index = midpoint + 1;
    int scratch_index = start;

    // Mientras haya elementos en ambas mitades
    while (left_index <= midpoint && right_index <= end)
    {
        if (values[left_index] <= values[right_index])
        {
            scratch[scratch_index] = values[left_index];
            left_index++;
        }
        else
        {
            scratch[scratch_index] = values[right_index];
            right_index++;
        }
        scratch_index++;
    }

    // Copiar lo que quedó en la mitad izquierda
    for (int i = left_index; i <= midpoint; i++)
    {
        scratch[scratch_index] = values[i];
        scratch_index++;
    }

    // Copiar lo que quedó en la mitad derecha
    for (int i = right_index; i <= end; i++)
    {
        scratch[scratch_index] = values[i];
        scratch_index++;
    }

    // Copiar de scratch de vuelta a values
    for (int i = start; i <= end; i++)
    {
        values[i] = scratch[i];
    }
}


void Countingsort(std::vector<int> &values, int max_value)
{
    // Crear arreglo counts para guardar frecuencias
    std::vector<int> counts(max_value + 1);

    // Inicializar counts en 0
    for (int i = 0; i <= max_value; i++)
    {
        counts[i] = 0;
    }

    // Contar cuántas veces aparece cada valor
    for (int i = 0; i < values.size(); i++)
    {
        counts[values[i]] = counts[values[i]] + 1;
    }

    // Copiar los valores ordenados de regreso a values
    int index = 0;

    for (int i = 0; i <= max_value; i++)
    {
        // Repetimos el valor i tantas veces como indique counts[i]
        for (int j = 1; j <= counts[i]; j++)
        {
            values[index] = i;
            index = index + 1;
        }
    }
}




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


