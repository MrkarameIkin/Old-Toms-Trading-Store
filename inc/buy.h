#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include "item.h"

void priceList(std::map <std::string, itemParameters> &item, std::ofstream &file);

void buy(std::map <std::string, itemParameters> &item, std::string name, std::ofstream &file);