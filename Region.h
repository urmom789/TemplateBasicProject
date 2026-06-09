//----------------------------------------------------------
// CS162 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may be republished without approval.
//----------------------------------------------------------

#ifndef REGION_H
#define REGION_H

#include <string>

struct Region
{
  int id;
  std::string city;
  std::string state;
};

/**
 * @brief Parse a CSV line into a Region struct
 * 
 * @param line A line of the form "id,city,state"
 * @return Region containing the data from the line
 */
Region parseRegion(const std::string &line);



struct PriceRecord
{
  int regionId;
  std::string date;
  double price;
};

/**
 * @brief Parse a CSV line into a PriceRecord struct
 * 
 * @param line A line of the form "id,date,price"
 * @return PriceRecord containing the data from the line
 */
PriceRecord parsePriceRecord(const std::string &line);

#endif
