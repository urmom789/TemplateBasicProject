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

  int i = 0;
  int j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i].city <= R[j].city) {
      regions[k] = L[i];
      i++;
    } else {
      regions[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    regions[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    regions[k] = R[j];
    j++;
    k++;
  }
}

void mergeSortRec(vector<Region>& regions, int left, int right)
{
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  mergeSortRec(regions, left, mid);
  mergeSortRec(regions, mid + 1, right);
  merge(regions, left, mid, right);
}

void mergeSort(vector<Region>& regions)
{
  if (!regions.empty()) {
    mergeSortRec(regions, 0, regions.size() - 1);
  }
}

Region binaryFind(const vector<Region>& regions, int id)
{
  int left = 0;
  int right = regions.size() - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (regions[mid].id == id) {
      return regions[mid];
    }
    if (regions[mid].id < id) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return {-1, "Invalid", "Invalid"};
}

int main()
{
  cout << "-----------------------------Part 1----------------------------\n";
  vector<Region> regions;
  ifstream regionFile("ZILLOW_REGIONS.csv");
  string line;

  if (!regionFile.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  while (getline(regionFile, line)) {
    if (!line.empty()) {
      try {
        regions.push_back(parseRegion(line));
      } catch (...) {
      }
    }
  }
  regionFile.close();

  cout << "First 5 regions:" << endl;
  for (int i = 0; i < 5 && i < regions.size(); i++) {
    cout << regions[i].id << " | " << regions[i].city << " | "
         << regions[i].state << endl;
  }

  cout << "-----------------------------Part 2----------------------------\n";
  clock_t start = clock();
  selectionSort(regions);
  clock_t end = clock();

  cout << "Took " << static_cast<double>(end - start) / CLOCKS_PER_SEC
       << " seconds to selection sort.\n"
       << endl;
}
