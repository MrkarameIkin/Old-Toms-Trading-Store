#include "buy.h"

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

void buy(std::map <std::string, itemParameters> &item, std::string name, std::ofstream &file) {
    std::string input;

    std::cout << "\nВведите название того, что хотите купить\n\n> ";
    std::getline(std::cin, name);

    auto it = item.find(name);

    if(it == item.end()) std::cout << "\nУ нас такого нету!\n\n";
    else {  
        std::cout << "\nВведите количество товара\n\n> ";
        std::getline(std::cin, input);

        if(std::stoi(input) > it->second.count) std::cout << "\nУ нас столько нету!\n\n";
        else {
            time_t timeLogs = time(nullptr);
            struct tm *local = localtime(&timeLogs);
            
            std::cout << "\nБыл приобретен товар '" << name << "' в количестве " << input << " шт.\n\n";

            it->second.count -= stoi(input);
            file << std::put_time(local, "[%d.%m.%Y %H:%M:%S]") << " Игрок купил: " << name << " (" << input << " шт.)\n";

            if(it->second.count == 0) item.erase(it);
        }
    }
}