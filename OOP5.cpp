#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

class Man {
public:
    string fam;
    string name;

    Man(const string& fam, const string& name)
        : fam(fam), name(name) {}

    string getFullName() const {
        return fam + " " + name;
    }
};

class Date {
public:
    int day;
    int month;
    int year;

    Date(int day, int month, int year)
        : day(day), month(month), year(year) {}
};

class Post {
public:
    Man recipient;
    string address;

    Post(const Man& recipient, const string& address)
        : recipient(recipient), address(address) {}

    virtual void printData() const = 0;

    virtual ~Post() {} // Adding a virtual destructor for polymorphic behavior
};

class Letter : public Post {
private:
    double cost;

public:
    Letter(const Man& recipient, const string& address, double cost)
        : Post(recipient, address), cost(cost) {}

    void printData() const override {
        cout << "Письмо" << endl;
        cout << "Получатель: " << recipient.getFullName() << endl;
        cout << "Адрес: " << address << endl;
        cout << "Стоимость: " << cost << endl;
    }
};

class Delivery : public Post {
public:
    Date deliveryDate;

    Delivery(const Man& recipient, const string& address, const Date& deliveryDate)
        : Post(recipient, address), deliveryDate(deliveryDate) {}

    void printData() const override {
        cout << "Доставка" << endl;
        cout << "Получатель: " << recipient.getFullName() << endl;
        cout << "Адрес: " << address << endl;
        cout << "Дата доставки: " << deliveryDate.day << "." << deliveryDate.month << "." << deliveryDate.year << endl;
    }
};

void saveData(const vector<Post*>& data) {
    ofstream file("data.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    for (const auto& item : data) {
        item->printData();
        file << "------------------" << endl;
    }

    file.close();
}

vector<Post*> loadData() {
    vector<Post*> data;

    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return data;
    }

    string line;
    string type;
    Man recipient("", "");
    string address;
    double cost;
    Date deliveryDate(0, 0, 0);

    while (getline(file, line)) {
        if (line == "Письмо") {
            type = "Письмо";
        }
        else if (line == "Доставка") {
            type = "Доставка";
        }
        else if (line.find("Получатель: ") == 0) {
            string recipientStr = line.substr(12);
            size_t spacePos = recipientStr.find(' ');
            string fam = recipientStr.substr(0, spacePos);
            string name = recipientStr.substr(spacePos + 1);
            recipient = Man(fam, name);
        }
        else if (line.find("Адрес: ") == 0) {
            address = line.substr(8);
        }
        else if (line.find("Стоимость: ") == 0) {
            cost = stod(line.substr(11));
            if (type == "Письмо") {
                data.push_back(new Letter(recipient, address, cost));
            }
            else if (type == "Доставка") {
                data.push_back(new Delivery(recipient, address, deliveryDate));
            }
        }
        else if (line.find("Дата доставки: ") == 0) {
            string dateStr = line.substr(15);
            size_t dotPos1 = dateStr.find('.');
            size_t dotPos2 = dateStr.rfind('.');
            int day = stoi(dateStr.substr(0, dotPos1));
            int month = stoi(dateStr.substr(dotPos1 + 1, dotPos2 - dotPos1 - 1));
            int year = stoi(dateStr.substr(dotPos2 + 1));
            deliveryDate = Date(day, month, year);
        }
    }

    file.close();
    return data;
}

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector<Post*> data = loadData();

    int choice;
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Добавить новое письмо" << endl;
        cout << "2. Добавить новую доставку" << endl;
        cout << "3. Поиск по фамилии и имени" << endl;
        cout << "4. Поиск до даты" << endl;
        cout << "5. Вывести данные" << endl;
        cout << "6. Выйти из программы" << endl;

        cin >> choice;
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string fam, name, address;
            double cost;

            cout << "Введите фамилию получателя: ";
            getline(cin, fam);
            cout << "Введите имя получателя: ";
            getline(cin, name);
            cout << "Введите адрес получателя: ";
            getline(cin, address);
            cout << "Введите стоимость письма: ";
            cin >> cost;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');

            data.push_back(new Letter(Man(fam, name), address, cost));
        }
        else if (choice == 2) {
            string fam, name, address;
            int day, month, year;

            cout << "Введите фамилию получателя: ";
            getline(cin, fam);
            cout << "Введите имя получателя: ";
            getline(cin, name);
            cout << "Введите адрес получателя: ";
            getline(cin, address);
            cout << "Введите день доставки: ";
            cin >> day;
            cout << "Введите месяц доставки: ";
            cin >> month;
            cout << "Введите год доставки: ";
            cin >> year;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');

            data.push_back(new Delivery(Man(fam, name), address, Date(day, month, year)));
        }
        else if (choice == 3) {
            string fam, name;
            cout << "Введите фамилию получателя: ";
            getline(cin, fam);
            cout << "Введите имя получателя: ";
            getline(cin, name);

            for (const auto& item : data) {
                const Letter* letter = dynamic_cast<const Letter*>(item);
                if (letter && letter->recipient.getFullName() == fam + " " + name) {
                    letter->printData();
                }
            }
        }
        else if (choice == 4) {
            int day, month, year;
            cout << "Введите день: ";
            cin >> day;
            cout << "Введите месяц: ";
            cin >> month;
            cout << "Введите год: ";
            cin >> year;
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (const auto& item : data) {
                const Delivery* delivery = dynamic_cast<const Delivery*>(item);
                if (delivery && (
                    delivery->deliveryDate.year < year ||
                    (delivery->deliveryDate.year == year && delivery->deliveryDate.month < month) ||
                    (delivery->deliveryDate.year == year && delivery->deliveryDate.month == month && delivery->deliveryDate.day <= day)
                    )) {
                    delivery->printData();
                }
            }
        }
        else if (choice == 5) {
            for (const auto& item : data) {
                item->printData();
            }
        }
        else if (choice == 6) {
            saveData(data);
            break;
        }
        else {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }

    // Cleaning up memory
    for (const auto& item : data) {
        delete item;
    }

    return 0;
}