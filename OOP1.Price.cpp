#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

class Item {
public:
    Item(const char* name = "", double price = 0.0, int quant = 0)
        : price(price), quant(quant) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Item() {
        delete[] name;
    }

    // Геттеры и сеттеры для полей
    const char* getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quant;
    }

private:
    char* name;
    double price;
    int quant;
};

class ItemDatabase {
public:
    ItemDatabase() : count(0) {}

    ~ItemDatabase() {
        for (Item* item : items) {
            delete item;
        }
    }

    void addNewItem(const Item& newItem) {
        items.push_back(new Item(newItem));
        count++;
    }

    void printItems() const {
        cout << "Имя товара\t\tЦена\t\tКоличество" << endl;
        for (const Item* item : items) {
            cout << item->getName() << "\t\t" << item->getPrice() << "\t\t" << item->getQuantity() << endl;
        }
    }

    void searchByName(const char* itemName) const {
        cout << "Имя товара\t\tЦена\t\tКоличество" << endl;
        bool found = false;
        for (const Item* item : items) {
            if (strcmp(item->getName(), itemName) == 0) {
                cout << item->getName() << "\t\t" << item->getPrice() << "\t\t" << item->getQuantity() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Предмет не найден!" << endl;
        }
    }

    void searchByQuantity(int quantity) const {
        cout << "Имя\t\tЦена\t\tКоличество" << endl;
        bool found = false;
        for (const Item* item : items) {
            if (item->getQuantity() < quantity) {
                cout << item->getName() << "\t\t" << item->getPrice() << "\t\t" << item->getQuantity() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << " Нет товаров с количеством меньше заданного " << quantity << endl;
        }
    }

    void saveItemsToFile(const char* filename) const {
        ofstream fout(filename);
        fout << count << endl;
        for (const Item* item : items) {
            fout << item->getName() << endl;
            fout << item->getPrice() << endl;
            fout << item->getQuantity() << endl;
        }
        fout.close();
    }

    void loadItemsFromFile(const char* filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << "Сохраненные данные не найдены" << endl;
            return;
        }

        fin >> count;
        fin.ignore();
        char buffer[100];
        double price;
        int quant;

        for (int i = 0; i < count; i++) {
            fin.getline(buffer, 100);
            fin >> price;
            fin >> quant;
            fin.ignore();
            addNewItem(Item(buffer, price, quant));
        }
        fin.close();
    }

private:
    vector<Item*> items;
    int count;
};

int main() {
    setlocale(LC_ALL, "RU");
    ItemDatabase database;
    database.loadItemsFromFile("items.txt");

    while (true) {
        cout << "Введите номер функции:" << endl;
        cout << "1. Добавить новый предмет" << endl;
        cout << "2. Распечатать базу товаров" << endl;
        cout << "3. Поиск товара по названию" << endl;
        cout << "4. Фильтр по цене" << endl;
        cout << "5. Выход из программы" << endl;

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
        {
            char buffer[100];
            cout << "Введите имя товара: ";
            cin.getline(buffer, 100);
            double price;
            cout << "Введите цену товара: ";
            cin >> price;
            int quant;
            cout << "Введите количество товара: ";
            cin >> quant;
            cin.ignore();
            database.addNewItem(Item(buffer, price, quant));
        }
        break;
        case 2:
            database.printItems();
            break;
        case 3:
        {
            char buffer[100];
            cout << "Введите название товара для поиска: ";
            cin.getline(buffer, 100);
            database.searchByName(buffer);
        }
        break;
        case 4:
        {
            int quantity;
            cout << "Введите максимальное количество для поиска: ";
            cin >> quantity;
            cin.ignore();
            database.searchByQuantity(quantity);
        }
        break;
        case 5:
            database.saveItemsToFile("items.txt");
            return 0;
        default:
            cout << "Неверный выбор! Введите снова." << endl;
        }
    }
}