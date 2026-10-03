#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include "item.h"

void sell(std::map <std::string, itemParameters> &item, std::ofstream &file);