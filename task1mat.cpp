#include <iostream> 
#include <vector> 
#include <random> 
#include <algorithm>
#include <string>

void printSeparator(const std::string& title) {
    std::cout << "\n--- " << title << " ---\n";
}

// 1. Сортировка пузырьком
// Добавляем счетчик сравнений (comparisons) по ссылке
std::vector<int> bubbleSort(std::vector<int> arr, int& comparisons)
{
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i)
    {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            comparisons++; // Считаем каждое сравнение
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return arr;
}

// 2. Сортировка вставками
std::vector<int> insertionSort(std::vector<int> arr, int& comparisons)
{
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = static_cast<int>(i) - 1;

        // Сдвигаем элементы, которые больше key, на одну позицию вправо
        while (j >= 0) {
            comparisons++; // Считаем сравнение
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    return arr;
}

// 3. Быстрая сортировка (Хоара)
std::vector<int> quickSort(const std::vector<int>& arr, int& comparisons) {
    if (arr.size() <= 1) {
        return arr;
    }

    int pivot = arr[arr.size() / 2];

    std::vector<int> left;
    std::vector<int> middle;
    std::vector<int> right;

    for (int val : arr) {
        comparisons++; // Считаем сравнение с опорным элементом
        if (val < pivot) {
            left.push_back(val);
        }
        else if (val > pivot) {
            right.push_back(val);
        }
        else {
            middle.push_back(val);
        }
    }

    std::vector<int> sorted_left = quickSort(left, comparisons);
    std::vector<int> sorted_right = quickSort(right, comparisons);

    std::vector<int> result;
    result.reserve(arr.size());

    result.insert(result.end(), sorted_left.begin(), sorted_left.end());
    result.insert(result.end(), middle.begin(), middle.end());
    result.insert(result.end(), sorted_right.begin(), sorted_right.end());

    return result;
}

int main() {
    setlocale(LONG_MAX, "Russian");

    const size_t N = 10000;
    std::vector<int> original_arr(N);

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(-100, 100);

    for (size_t i = 0; i < N; ++i) {
        original_arr[i] = dist(gen);
    }

    // Создаем отдельные копии массива для каждого алгоритма
    std::vector<int> bubble_arr = original_arr;
    std::vector<int> insertion_arr = original_arr;
    std::vector<int> quick_arr = original_arr;

    // Счетчики операций сравнения
    int bubble_comps = 0;
    int insertion_comps = 0;
    int quick_comps = 0;

    // Вызываем функции, передавая наши копии и счетчики
    std::vector<int> sorted_bubble = bubbleSort(bubble_arr, bubble_comps);
    std::vector<int> sorted_insertion = insertionSort(insertion_arr, insertion_comps);
    std::vector<int> sorted_quick = quickSort(quick_arr, quick_comps);

    // Вывод результатов
    printSeparator("РЕЗУЛЬТАТЫ СОРТИРОВКИ (N = 10000)");
    std::cout << "Алгоритм             | Число сравнений\n";
    std::cout << "---------------------|------------------\n";
    std::cout << "Пузырьком            | " << bubble_comps << "\n";
    std::cout << "Вставками            | " << insertion_comps << "\n";
    std::cout << "Хоара (Быстрая)      | " << quick_comps << "\n";

    printSeparator("ВЫВОД");
    std::cout << "1. Пузырек делает больше всего сравнений (O(N^2)).\n";
    std::cout << "2. Вставки с бинарным поиском в твоем изначальном коде работали бы медленно из-за erase/insert.\n";
    std::cout << "   Классические вставки (со сдвигами) работают быстрее пузырька на почти отсортированных данных.\n";
    std::cout << "3. Быстрая сортировка (Хоара) делает меньше всего сравнений (O(N log N)).\n";

    return 0;
}