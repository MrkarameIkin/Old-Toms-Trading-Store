#include <iostream>
#include <map>

struct itemParameters {
    int count;
    int cost;
};

void buy(std::map <std::string, itemParameters> &item, std::string name) {
    std::string input;

    std::cout << "\nВведите название того, что хотите купить\n\n> ";
    std::getline(std::cin, name);

    if(!item.count(name)) std::cout << "\nУ нас такого нету!\n\n";
    else {
        std::cout << "\nВведите количество товара\n\n> ";
        std::getline(std::cin, input);

        if(std::stoi(input) > item[name].count) std::cout << "\nУ нас столько нету!\n\n";
        else {
            std::cout << "\nБыл приобретен товар '" << name << "' в количестве " << input << " шт.\n\n";
            item[name].count -= stoi(input);

            if(item[name].count == 0) item.erase(name);
        }
    }
}

void priceList(std::map <std::string, itemParameters> &item) {
    std::string name, input;

    std::cout << std::endl;

    for(auto it = item.begin(); it != item.end(); it++) {
        std::cout << it->first << "\t: ";
        std::cout << it->second.count << " шт. ( ";
        std::cout << it->second.cost << " зол. )\n";
    }

    std::cout << "\nХотите что-то прикупить? (Да/Нет)\n\n> ";
    
    while(true) {
        std::getline(std::cin, input);

        if(input == "Да" || input == "да") {
            buy(item,name);
        }
        else if(input == "Нет" || input == "нет") break;
        else std::cout << "\nПовторите ввод!\n";

        std::cout << "Хотите еще что-то прикупить? (Да/Нет)\n\n> ";
    }
}

void sell(std::map <std::string, itemParameters> &item) {
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
                    break;
                }

                std::cout << "\nВведите количество товара\n\n> ";

                std::getline(std::cin, count);

                if(std::stoi(count) > 0) item[name].count += stoi(count);
                else std::cout << "\nОшибка ввода!\n";
            }
            else {
                std::cout << "\nВведите количество товара\n\n> ";

                std::getline(std::cin, count);

                if(std::stoi(count) > 0) item.insert({name, {stoi(count), stoi(cost) - stoi(cost)%5 + 15}});
                else std::cout << "\nОшибка ввода!\n";
            }
        }
    }
}

int main() {
    std::map <std::string, itemParameters> item; // Название, количество и стоимость предмета
    std::string input;

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

        if(input == "1") priceList(item);
        else if(input == "2") sell(item);
        else if(input == "3") {
            std::cout << "\nДо свидания!\n\n";
            break;
        }
        else std::cout << "\nНеправильный ввод!\n";
    }
}