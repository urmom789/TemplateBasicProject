//----------------------------------------------------------
// CS162 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may be republished without approval.
//----------------------------------------------------------

#include "Region.h"

using namespace std;

Region parseRegion(const string &line) {
  Region r;

  size_t firstComma = line.find(',');
  size_t secondComma = line.find(',', firstComma + 1);

  r.id = stoi(line.substr(0, firstComma));
  r.city = line.substr(firstComma + 1, secondComma - firstComma - 1);
  r.state = line.substr(secondComma + 1);

  return r;
}

PriceRecord parsePriceRecord(const string &line) {
  PriceRecord sp;

  size_t firstComma = line.find(',');
  size_t secondComma = line.find(',', firstComma + 1);

  sp.regionId = stoi(line.substr(0, firstComma));
  sp.date = line.substr(firstComma + 1, secondComma - firstComma - 1);
  sp.price = stod(line.substr(secondComma + 1));

  return sp;
}