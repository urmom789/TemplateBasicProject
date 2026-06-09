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
  int n = static_cast<int>(regions.size());
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
    mergeSortRec(regions, 0, static_cast<int>(regions.size() - 1));
  }
}

Region binaryFind(const vector<Region>& regions, int id)
{
  int left = 0;
  int right = static_cast<int>(regions.size()) - 1;

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
  for (int i = 0; i < 5 && i < static_cast<int>(regions.size()); i++) {
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

  cout << "First 5 regions after sorting by ID:" << endl;

  for (int i = 0; i < 5 && i < static_cast<int>(regions.size()); i++) {
    cout << regions[i].id << " | " << regions[i].city << " | "
         << regions[i].state << endl;
  }

  cout << "-----------------------------Part 3----------------------------\n";
  vector<Region> regionsByName = regions;

  start = clock();
  mergeSort(regionsByName);
  end = clock();

  cout << "Took " << static_cast<double>(end - start) / CLOCKS_PER_SEC
       << " seconds to merge sort.\n";
  cout << "First 5 regions after sorting by city:" << endl;
  for (int i = 0; i < 5 && i < regionsByName.size(); i++) {
    cout << regionsByName[i].id << " | " << regionsByName[i].city << " | "
         << regionsByName[i].state << endl;
  }

  cout << "-----------------------------Part 4----------------------------\n";

  Region foundRegion = binaryFind(regions, 36768);
  if (foundRegion.id != -1) {
    cout << "Found region 36768: " << foundRegion.id << " | "
         << foundRegion.city << " | " << foundRegion.state << endl;

  } else {
    cout << "Region 36768 not found" << endl;
  }

  cout << "-----------------------------Part 5----------------------------\n";

  vector<PriceRecord> prices;
  ifstream pricesFile("ZILLOW_DATA.csv");

  if (!pricesFile.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  while (getline(pricesFile, line)) {
    if (!line.empty()) {
      try {
        prices.push_back(parsePriceRecord(line));
      } catch (...) {
      }
    }
  }
  pricesFile.close();

  cout << "First 5 price records:" << endl;
  for (int i = 0; i < 5 && i < prices.size(); i++) {
    cout << prices[i].regionId << " | " << prices[i].date << " | $" << fixed
         << setprecision(2) << prices[i].price << endl;
  }

  cout << "-----------------------------Part 5----------------------------\n";
  string targetCity;
  getline(cin, targetCity);

  start = clock();
  int martchCount = 0;

  for (const PriceRecord& p : prices) {
    Region r = binaryFind(regions, p.regionId);
    if (r.id != -1 && r.city == targetCity) {
      cout << r.city << ", " << r.state << " | " << p.date << " | $" << fixed
           << setprecision(2) << p.price << endl;
      martchCount++;
    }
  }
  end = clock();

  cout << "\nFound " << martchCount << " records for " << targetCity << endl;
  cout << "Took " << static_cast<double>(end - start) / CLOCKS_PER_SEC
       << " seconds to complete the search loop." << endl;
}
