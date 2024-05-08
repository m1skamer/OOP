#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day = 0, int month = 0, int year = 0)
        : day(day), month(month), year(year) {
    }

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }
};

class Storage {
private:
    string name; // Changed char* name to string name
    double price;
    int quant;
    Date delivery_date;
    static int count;

public:
    Storage(const string& name = "", double price = 0.0, int quant = 0, const Date& delivery_date = Date())
        : name(name), price(price), quant(quant), delivery_date(delivery_date) {
        count++;
    }

    ~Storage() {
        count--;
    }

    const string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quant;
    }

    const Date& getDeliveryDate() const {
        return delivery_date;
    }

    static int getCount() {
        return count;
    }

    bool searchByName(const string& itemName) const {
        return (name == itemName);
    }

    bool searchByPrice(double minPrice) const {
        return (price > minPrice);
    }

    friend ostream& operator<<(ostream& os, const Storage& item) {
        os << item.getName() << "\t\t" << item.getPrice() << "\t\t" << item.getQuantity() << "\t\t" << item.getDeliveryDate().getDay() << "/" << item.getDeliveryDate().getMonth() << "/" << item.getDeliveryDate().getYear();
        return os;
    }
};

int Storage::count = 0;

int main() {
    setlocale(LC_ALL, "RU");
    vector<Storage> storageItems;

    const string filename = "database.txt";
    ifstream file(filename);
    if (file.is_open()) {
        string name;
        double price;
        int quant;
        int day, month, year;
        while (file >> name >> price >> quant >> day >> month >> year) {
            storageItems.push_back(Storage(name, price, quant, Date(day, month, year)));
        }
    }
    file.close();

    while (true) {
        cout << "\nВыберите действие:\n";
        cout << "1. Добавить товар\n";
        cout << "2. Распечатать товары\n";
        cout << "3. Поиск товара по названию\n";
        cout << "4. Найти все товары с ценой больше заданной\n";
        cout << "5. Показать количество созданных объектов\n";
        cout << "6. Выход и сохранение базы данных\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            cout << "Введите название товара: ";
            cin.ignore();
            getline(cin, name);

            double price;
            cout << "Введите цену товара: ";
            cin >> price;

            int quant;
            cout << "Введите количество товара: ";
            cin >> quant;

            int day, month, year;
            cout << "Введите дату поступления (день, месяц, год): ";
            cin >> day >> month >> year;

            storageItems.push_back(Storage(name, price, quant, Date(day, month, year)));
        }
              break;
        case 2:
            cout << "Товары в хранилище:\n";
            cout << "Название\tЦена\t\tКоличество\tДата поступления" << endl;
            for (const Storage& item : storageItems) {
                cout << item << endl;
            }
            break;
        case 3: {
            string name;
            cout << "Введите название товара для поиска: ";
            cin.ignore();
            getline(cin, name);

            bool found = false;
            for (const Storage& item : storageItems) {
                if (item.searchByName(name)) {
                    cout << "Товар найден:\n";
                    cout << item << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Товар не найден.\n";
            }
        }
              break;
        case 4: {
            double minPrice;
            cout << "Введите минимальную цену для поиска: ";
            cin >> minPrice;

            cout << "Товары с ценой больше " << minPrice << ":\n";
            cout << "Название\t\tЦена\t\tКоличество\tДата поступления" << endl;

            bool found = false;
            for (const Storage& item : storageItems) {
                if (item.searchByPrice(minPrice)) {
                    cout << item << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Нет товаров с ценой больше " << minPrice << endl;
            }
        }
              break;
        case 5:
            cout << "Количество созданных объектов: " << Storage::getCount() << endl;
            break;
        case 6: {
            // Сохранение базы данных в файл перед выходом
            ofstream outFile(filename);
            if (outFile.is_open()) {
                for (const Storage& item : storageItems) {
                    Date deliveryDate = item.getDeliveryDate();
                    outFile << item.getName() << " " << item.getPrice() << " " << item.getQuantity() << " "
                        << deliveryDate.getDay() << " " << deliveryDate.getMonth() << " " << deliveryDate.getYear() << endl;
                }
                outFile.close();
                cout << "База данных сохранена в файл: " << filename << endl;
            }
            else {
                cout << "Ошибка при сохранении базы данных в файле: " << filename << endl;
            }
            return 0;
        }
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }

    return 0;
}