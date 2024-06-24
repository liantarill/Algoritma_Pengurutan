#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Bubble Sort
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// Merge Sort
void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(vector<int> &arr)
{
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Quick Sort
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortHelper(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int> &arr)
{
    quickSortHelper(arr, 0, arr.size() - 1);
}

void printArray(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

void generateData(vector<int> &arr, int N, string type)
{
    arr.resize(N);
    if (type == "random")
    {
        for (int i = 0; i < N; i++)
            arr[i] = rand() % 10000;
    }
    else if (type == "sorted")
    {
        for (int i = 0; i < N; i++)
            arr[i] = i;
    }
    else if (type == "reversed")
    {
        for (int i = 0; i < N; i++)
            arr[i] = N - i;
    }
}

void measureTime(void (*sortFunction)(vector<int> &), vector<int> &arr, string sortName, int N)
{
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " (N=" << N << "): " << duration.count() << " microseconds" << endl;
}

int main()
{
    srand(time(0));
    vector<int> sizes = {10, 100, 500, 1000, 10000};
    vector<string> dataTypes = {"random", "sorted", "reversed"};
    string sortNames[] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort"};
    void (*sortFunctions[])(vector<int> &) = {bubbleSort, insertionSort, selectionSort, mergeSort, quickSort};

    for (int size : sizes)
    {
        for (string dataType : dataTypes)
        {
            cout << "Data Type: " << dataType << ", Size: " << size << endl;
            vector<int> data;
            generateData(data, size, dataType);
            for (int i = 0; i < 5; i++)
            {
                vector<int> tempData = data;
                measureTime(sortFunctions[i], tempData, sortNames[i], size);
            }
            cout << endl;
        }
    }

    return 0;
}
