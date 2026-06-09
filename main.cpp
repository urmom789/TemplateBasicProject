#include "Region.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void selectionSort(vector<Region>& regions)
{
  int n = regions.size();
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      if (regions[j].id < regions[minIndex].id) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      swap(regions[i], regions[minIndex]);
    }
  }
}

void merge(vector<Region>& regions, int left, int mid, int right)
{
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<Region> L(n1), R(n2);
  for (int i = 0; i < n1; i++) {
    L[i] = regions[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = regions[mid + 1 + j];
  }
}

int main()
{
  cout << "Hello world" << endl;
}
