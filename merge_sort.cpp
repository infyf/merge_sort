#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

int n; 


int control() {
    while (true) {
        cout << "Enter the number of elements of the array: ";
        cin >> n;
        if (cin.good() && n > 0) {
            break;
        }
        else {
            cout << "An integer is expected!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return n;
}


void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


void genRandom(int* arr) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 2001 - 1000;
    }
}


void genSpad(int* arr) {
    for (int i = 0; i < n; i++) {
        arr[i] = 1000 - i;
    }
}


void duplicateValue(int* arr, int value) {
    for (int i = 0; i < n; i++) {
        arr[i] = value;
    }
}

void genTheSameValue(int* arr) {
    duplicateValue(arr, rand() % 2001 - 1000);
    int index1 = rand() % n;
    int index2;
    do {
        index2 = rand() % n;
    } while (index2 == index1);

    arr[index2] = arr[index1];
}

int main() {
    n = control();

    int* randomArr = new int[n];
    genRandom(randomArr);

    int* descendArr = new int[n];
    genSpad(descendArr);

    int uniformValue = rand() % 2001 - 1000;
    int* uniformArr = new int[n];
    duplicateValue(uniformArr, uniformValue);

    int* duplicateArr = new int[n + 2];
    genTheSameValue(duplicateArr);

    clock_t start_time1 = clock();
    mergeSort(randomArr, 0, n - 1);
    clock_t end_time1 = clock();

    clock_t start_time2 = clock();
    mergeSort(descendArr, 0, n - 1);
    clock_t end_time2 = clock();

    clock_t start_time3 = clock();
    mergeSort(uniformArr, 0, n - 1);
    clock_t end_time3 = clock();

    clock_t start_time4 = clock();
    mergeSort(duplicateArr, 0, n - 1);
    clock_t end_time4 = clock();

    cout << "Merge sort for random array: " << (end_time1 - start_time1) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
    cout << "Merge sort for spad: " << (end_time2 - start_time2) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
    cout << "Merge sort for uniform array: " << (end_time3 - start_time3) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
    cout << "Merge sort for array with two equal values: " << (end_time4 - start_time4) * 1000 / CLOCKS_PER_SEC << "ms" << endl;

    delete[] randomArr;
    delete[] descendArr;
    delete[] uniformArr;
    delete[] duplicateArr;

    system("pause");
    return 0;
}
