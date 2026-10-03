#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include "item.h"

void priceList(std::map <std::string, itemParameters> &item, std::ofstream &file);

void buy(std::map <std::string, itemParameters> &item, std::ofstream &file);