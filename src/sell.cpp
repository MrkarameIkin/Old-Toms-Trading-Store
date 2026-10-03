#include "sell.h"

void sell(std::map <std::string, itemParameters> &item, std::ofstream &file) {
    std::string name, cost, count;

    while(true) {
        std::cout << "\nВведите название товара (или 0, чтобы выйти)\n\n> ";

        std::getline(std::cin, name);

        if(name == "0") break;
        else {
            std::cout << "\nВведите стоимость товара\n\n> ";

            std::getline(std::cin, cost);

            if(item.count(name)) {
                if(std::stoi(cost) > item[name].cost) {
                    std::cout << "\nСлишком дорого!\n";
                    continue;
                }

                time_t timeLogs = time(nullptr);
                struct tm *local = localtime(&timeLogs);

                std::cout << "\nВведите количество товара\n\n> ";

                std::getline(std::cin, count);

                if(std::stoi(count) > 0) {
                    item[name].count += stoi(count);
                    
                    file << std::put_time(local, "[%d.%m.%Y %H:%M:%S]") << " Игрок продал: ";
                    file << name << " (" << count << " шт.) за " << cost << " зол.\n";
                }
                else std::cout << "\nОшибка ввода!\n";
            }
            else {
                time_t timeLogs = time(nullptr);
                struct tm *local = localtime(&timeLogs);

                std::cout << "\nВведите количество товара\n\n> ";

                std::getline(std::cin, count);

                if(std::stoi(count) > 0) {
                    item.insert({name, {stoi(count), stoi(cost) - stoi(cost)%5 + 15}});

                    file << std::put_time(local, "[%d.%m.%Y %H:%M:%S]") << " Игрок продал: ";
                    file << name << " (" << count << " шт.) за " << cost << " зол.\n";
                }
                else std::cout << "\nОшибка ввода!\n";
            }
        }
    }
}