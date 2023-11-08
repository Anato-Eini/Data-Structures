#include <iostream>
#include <vector>
using namespace std;
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int peek(vector<int>(&ht)){
    if(ht.empty()){
        return -1;
    }else{
        return ht[0];
    }
}
// Hey there, implement the min heap operations here...
void heapify(vector<int>(&ht), int n){
    int size = (int)ht.size(), smallest = n;
    if(n * 2 + 1 < size && ht[smallest] > ht[n * 2 + 1])
        smallest = n * 2 + 1;
    if(n * 2 + 2 < size && ht[smallest] > ht[n * 2 + 2])
        smallest = n * 2 + 2;
    if(n != smallest){
        swap(&ht[n], &ht[smallest]);
        heapify(ht, smallest);
    }
}
void deleteNode(vector<int>(&ht), int num){
    for(int i = (int)ht.size() - 1; i >= 0; i--){
        if(ht[i] == num){
            swap(ht[i], ht[ht.size() - 1]);
            ht.pop_back();
            for(;i >= 0; i--){
                heapify(ht, i);
            }
        }
    }
}

void insert(vector<int> &hT, int new_num) {
    int size = hT.size();
    if (size == 0) {
        hT.push_back(new_num);
    } else {
        hT.push_back(new_num);
        for (int ctr = size / 2 - 1; ctr >= 0; ctr--) {
            heapify(hT, ctr);
        }
    }
}

void printHeapTree(vector<int> &hT) {
    for (int ctr : hT) {
        cout << ctr << " ";
    }
    cout << endl;
}
int removeMin(vector<int>(&ht)){
    if(ht.empty()){
        return -1;
    }
    int z = ht[0];
    swap(&ht[0], &ht[ht.size() - 1]);
    ht.pop_back();
    heapify(ht, 0);
    return z;
}

int main () {
    vector<int> heapTree;
    int operation,input, elementPeeked;

    do {
        cout << "Enter operation: ";
        cin >> operation;

        switch (operation) {
            case 1:
                cout << "Enter element to add: ";
                cin >> input;
                insert(heapTree, input);
                break;
            case 2:
                elementPeeked = peek(heapTree);
                if (elementPeeked != -1) {
                    cout << "Minimum element is: " << elementPeeked << endl;
                }else {
                    cout << endl << "Heap is empty" << endl;
                }
                break;
            case 3:
                cout << "Enter element to delete: ";
                cin >> input;
                deleteNode(heapTree, input);
                cout << endl;
                printHeapTree(heapTree);
                break;
            case 4:
                cout << "Minimum element removed is: " << removeMin(heapTree) << endl << endl;
                printHeapTree(heapTree);
                break;
            default:
                break;
        }
        cout << endl;
    }while(operation != 0);
    printHeapTree(heapTree);
}