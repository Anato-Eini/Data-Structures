#include <iostream>
#include "Heap.h"
using namespace std;

int main() {
    Heap* heap = new Heap();
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int array[size];
    for(int a = 0; a < size; a++){
        cout << "Enter element " << a + 1 << ": ";
        cin >> array[a];
    }
    heap->heapSort(array, size);
    for(int a = 0; a < size; a++){
        cout << array[a] << " ";
    }
    return 0;
}