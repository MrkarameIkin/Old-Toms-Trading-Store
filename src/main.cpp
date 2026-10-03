#include <iostream>
#include <map>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "buy.h"
#include "sell.h"

#define LOG_SAVING 1 // 1 - дописывать логи, 0 - перезаписывать логи

int main() {
    std::map <std::string, itemParameters> item; // Название, количество и стоимость предмета
    std::string input;

    #if LOG_SAVING == 1
        std::ofstream file("logs/shop_log.txt", std::ios::app);
    #endif

    #if LOG_SAVING == 0
        std::ofstream file("logs/shop_log.txt");
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