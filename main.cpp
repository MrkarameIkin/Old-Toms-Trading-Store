#include <iostream>
#include <map>
#include <fstream>
#include <ctime>
#include <iomanip>

#define LOG_SAVING 1 // 1 - дописывать логи, 0 - перезаписывать логи

struct itemParameters {
    int count;
    int cost;
};

void buy(std::map <std::string, itemParameters> &item, std::string name, std::ofstream &file) {
    std::string input;

    time_t timeLogs = time(nullptr);
    struct tm *local = localtime(&timeLogs);

    std::cout << "\nВведите название того, что хотите купить\n\n> ";
    std::getline(std::cin, name);

    auto it = item.find(name);

    if(it == item.end()) std::cout << "\nУ нас такого нету!\n\n";
    else {
        std::cout << "\nВведите количество товара\n\n> ";
        std::getline(std::cin, input);

        if(std::stoi(input) > it->second.count) std::cout << "\nУ нас столько нету!\n\n";
        else {
            std::cout << "\nБыл приобретен товар '" << name << "' в количестве " << input << " шт.\n\n";

            it->second.count -= stoi(input);
            file << std::put_time(local, "[%d.%m.%Y %H:%M:%S]") << " Игрок купил: " << name << " (" << input << " шт.)\n";

            if(it->second.count == 0) item.erase(it);
        }
    }
}

void priceList(std::map <std::string, itemParameters> &item, std::ofstream &file) {
    std::string name, input;

    std::cout << std::endl;

    for(const auto &it : item) {
        std::cout << it.first << "\t: ";
        std::cout << it.second.count << " шт. ( ";
        std::cout << it.second.cost << " зол. )\n";
    }

    std::cout << "\nХотите что-то прикупить? (Да/Нет)\n\n> ";
    
    while(true) {
        std::getline(std::cin, input);

        if(input == "Да" || input == "да") buy(item,name,file);
        else if(input == "Нет" || input == "нет") break;
        else std::cout << "\nПовторите ввод!\n";

        std::cout << "Хотите еще что-то прикупить? (Да/Нет)\n\n> ";
    }
}

void sell(std::map <std::string, itemParameters> &item, std::ofstream &file) {
    std::string name, cost, count;

    time_t timeLogs = time(nullptr);
    struct tm *local = localtime(&timeLogs);

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

int main() {
    std::map <std::string, itemParameters> item; // Название, количество и стоимость предмета
    std::string input;

    #if LOG_SAVING == 1
        std::ofstream file("shop_log.txt", std::ios::app);
    #endif

    #if LOG_SAVING == 0
        std::ofstream file("shop_log.txt", std::ios::binary);
        file << "// purchase and sale logs in the Old Tom's Trading Store\n\n";
    #endif

    item.insert({"Меч", {5,100}});
    item.insert({"Щит", {8,110}});
    item.insert({"Лук", {11,75}});
    item.insert({"Стрела", {117,5}});
    item.insert({"Зелье", {21,25}});

    std::cout << "Добро пожаловать к Старому Тому!\n";

    while(true) {
        std::cout << "\n1. Прайс-лист\n";
        std::cout << "2. Продать товар\n";
        std::cout << "3. Выход\n";

        std::cout << "\n> ";

        std::getline(std::cin, input);

        if(input == "1") priceList(item, file);
        else if(input == "2") sell(item, file);
        else if(input == "3") {
            std::cout << "\nДо свидания!\n\n";
            break;
        }
        else std::cout << "\nНеправильный ввод!\n";
    }
    
    file.close();
}