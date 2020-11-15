#include <fstream>
#include <iostream>

using namespace std;

#define ARRAY_SIZE 100000
#define BUFFER_SIZE ARRAY_SIZE - 1
int gBuffer[ARRAY_SIZE]; // Buffer has a size of 99999
int pBufferWrite = 0;

int getMax(int arr[], int n) {
  int mx = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > mx)
      mx = arr[i];
  return mx;
}

void countSort(int arr[], int n, int exp) {
  int output[n]; // output array
  int i, count[10] = {0};

  for (i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  for (i = 0; i < n; i++)
    arr[i] = output[i];
}

void radixsort(int arr[], int n) {
  int m = getMax(arr, n);
  for (int exp = 1; m / exp > 0; exp *= 10)
    countSort(arr, n, exp);
}

int main() {
  int arr[ARRAY_SIZE];
  int n = 0;

  ifstream f1;
  ofstream f2;

  f1.open("input.txt");
  f2.open("output.txt");

  if (!f1) {
    cout << "Can not open this file!" << endl;
    return 0;
  } else
    cout << "File is opened" << endl;

  while (true) {
    f1 >> arr[pBufferWrite];
    if (f1.eof())
      break;
    n++;
    if (pBufferWrite < BUFFER_SIZE) {
      pBufferWrite++;
    } else {
      pBufferWrite = 0;
    }
  }

  radixsort(arr, n);
  for (int i = 0; i < n; i++) {
    f2 << arr[i] << endl;
  }
  f1.close();
  f2.close();

  return 0;
}
