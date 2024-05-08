#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <iomanip>
#include <cctype>
#include <locale>
#include <regex>

using namespace std;
class Man {
private:
    string fam;
    string name;

public:
    Man(const string& fam, const string& name) : fam(fam), name(name) {}

    const string& getFam() const {
        return fam;
    }

    const string& getName() const {
        return name;
    }

    bool operator==(const Man& other) const {
        return fam == other.fam && name == other.name;
    }

    friend istream& operator>>(istream& is, Man& man) {
        cout << "Введите фамилию: ";
        is >> man.fam;
        cout << "Введите имя: ";
        is >> man.name;
        return is;
    }
};

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {}

    int getDay() const {
        return day;
    }

    int getMonth() const {
        return month;
    }

    int getYear() const {
        return year;
    }

    bool operator<=(const Date& other) const {
        if (year < other.year)
            return true;
        else if (year == other.year && month < other.month)
            return true;
        else if (year == other.year && month == other.month && day <= other.day)
            return true;
        return false;
    }

    friend ostream& operator<<(ostream& os, const Date& date) {
        os << date.getDay() << "." << date.getMonth() << "." << date.getYear();
        return os;
    }

    friend istream& operator>>(istream& is, Date& date) {
        cout << "Введите день: ";
        is >> date.day;
        cout << "Введите месяц: ";
        is >> date.month;
        cout << "Введите год: ";
        is >> date.year;
        return is;
    }
};

class Common {
protected:
    Man recipient;
    Man sender;

public:
    Common(const Man& recipient, const Man& sender) : recipient(recipient), sender(sender) {}

    const Man& getRecipient() const {
        return recipient;
    }

    const Man& getSender() const {
        return sender;
    }

    virtual void printInfo() const = 0;
    virtual bool isEqual(const Man& person) const = 0;

    friend istream& operator>>(istream& is, Common& common) {
        cout << "Введите данные получателя:" << endl;
        is >> common.recipient;
        cout << "Введите данные отправителя:" << endl;
        is >> common.sender;
        return is;
    }
};

class Letter : public Common {
private:
    string address;
    double cost;

public:
    Letter(const Man& recipient, const string& address, const Man& sender, double cost)
        : Common(recipient, sender), address(address), cost(cost) {}

    const string& getAddress() const {
        return address;
    }

    double getCost() const {
        return cost;
    }

    void printInfo() const override {
        cout << "Письмо" << endl;
        cout << "Фамилия и имя получателя: " << recipient.getFam() << " " << recipient.getName() << endl;
        cout << "Адрес получателя: " << address << endl;
        cout << "Фамилия и имя отправителя: " << sender.getFam() << " " << sender.getName() << endl;
        cout << "Стоимость письма: " << cost << endl;
    }

    bool isEqual(const Man& person) const override {
        return recipient == person;
    }

    friend istream& operator>>(istream& is, Letter& letter) {
        is >> static_cast<Common&>(letter);
        cout << "Введите адрес получателя: ";
        is >> letter.address;
        cout << "Введите стоимость письма: ";
        is >> letter.cost;
        return is;
    }
};

class Delivery : public Common {
private:
    string address;
    Date deliveryDate;

public:
    Delivery(const Man& recipient, const string& address, const Man& sender, const Date& deliveryDate)
        : Common(recipient, sender), address(address), deliveryDate(deliveryDate) {}

    const string& getAddress() const {
        return address;
    }

    const Date& getDeliveryDate() const {
        return deliveryDate;
    }

    void printInfo() const override {
        cout << "Доставка" << endl;
        cout << "Фамилия и имя получателя: " << recipient.getFam() << " " << recipient.getName() << endl;
        cout << "Адрес получателя: " << address << endl;
        cout << "Фамилия и имя отправителя: " << sender.getFam() << " " << sender.getName() << endl;
        cout << "Дата доставки: " << deliveryDate << endl;
    }

    bool isEqual(const Man& person) const override {
        return recipient == person;
    }

    friend istream& operator>>(istream& is, Delivery& delivery) {
        is >> static_cast<Common&>(delivery);
        cout << "Введите адрес получателя: ";
        is >> delivery.address;
        cout << "Введите дату доставки:" << endl;
        is >> delivery.deliveryDate;
        return is;
    }
};
// Функция для проверки, что строка содержит только буквы
bool isStringValid(const std::string& str) {
    std::regex regexPattern("[а-яА-Я]+"); // Регулярное выражение для проверки наличия только русских букв

    return std::regex_match(str, regexPattern);
}


// Функция для проверки, что значение является числом
bool isNumericValue(const string& str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}
// Функция для ввода данных с клавиатуры и создания письма
Letter createLetter() {
    cout << "Создание нового письма" << endl;

    try {
        cout << "Введите фамилию получателя: ";
        string recipientFam;
        cin >> recipientFam;
        if (!isStringValid(recipientFam)) {
            throw invalid_argument("Имя получателя должно содержать только буквы.");
        }
        cout << "Введите имя получателя: ";
        string recipientName;
        cin >> recipientName;
        if (!isStringValid(recipientName)) {
            throw invalid_argument("Имя получателя должно содержать только буквы.");
        }

        cout << "Введите адрес получателя: ";
        string address;
        cin >> address;

        cout << "Введите фамилию отправителя: ";
        string senderFam;
        cin >> senderFam;
        if (!isStringValid(senderFam)) {
            throw invalid_argument("Фамилия отправителя должна содержать только буквы.");
        }

        cout << "Введите имя отправителя: ";
        string senderName;
        cin >> senderName;
        if (!isStringValid(senderName)) {
            throw invalid_argument("Имя отправителя должно содержать только буквы.");
        }

        cout << "Введите стоимость письма: ";
        double cost;
        cin >> cost;
        if (cin.fail() || cost < 0) {
            throw invalid_argument("Некорректная стоимость письма.");
        }

        Man recipient(recipientFam, recipientName);
        Man sender(senderFam, senderName);

        return Letter(recipient, address, sender, cost);
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка при вводе данных: " << e.what() << " Пожалуйста, повторите попытку." << endl;
    }
    catch (...) {
        cout << "Произошла непредвиденная ошибка. Пожалуйста, повторите попытку." << endl;
    }
}

// Функция для ввода данных с клавиатуры и создания доставки
Delivery createDelivery() {
    cout << "Создание новой доставки" << endl;

    try {
        cout << "Введите фамилию получателя: ";
        string recipientFam;
        cin >> recipientFam;
        if (!isStringValid(recipientFam)) {
            throw invalid_argument("Фамилия получателя должно содержать только буквы.");
        }
        cout << "Введите имя получателя: ";
        string recipientName;
        cin >> recipientName;
        if (!isStringValid(recipientName)) {
            throw invalid_argument("Имя получателя должно содержать только буквы.");
        }

        cout << "Введите адрес получателя: ";
        string address;
        cin >> address;

        cout << "Введите фамилию отправителя: ";
        string senderFam;
        cin >> senderFam;

        cout << "Введите имя отправителя: ";
        string senderName;
        cin >> senderName;
        if (!isStringValid(senderName)) {
            throw invalid_argument("Имя отправителя должно содержать только буквы.");
        }

        cout << "Введите дату доставки (день месяц год): ";
        int day, month, year;
        cin >> day >> month >> year;
        Date deliveryDate(day, month, year);

        Man recipient(recipientFam, recipientName);
        Man sender(senderFam, senderName);

        return Delivery(recipient, address, sender, deliveryDate);
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка при вводе данных: " << e.what() << " Пожалуйста, повторите попытку." << endl;
    }
}

// Функция для записи данных в файл
void saveData(const vector<Common*>& data) {
    ofstream file("data.txt");

    if (file.is_open()) {
        for (const auto& item : data) {
            if (dynamic_cast<Letter*>(item) != nullptr) {
                file << dynamic_cast<Letter*>(item);
            }
            else if (dynamic_cast<Delivery*>(item) != nullptr) {
                file << dynamic_cast<Delivery*>(item);
            }
        }

        file.close();
        cout << "Данные успешно сохранены." << endl;
    }
    else {
        cerr << "Ошибка при открытии файла." << endl;
    }
}

// Функция для загрузки данных из файла
vector<Common*> loadData() {
    vector<Common*> data;
    ifstream file("data.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line == "---------- Письмо ----------") {
                string recipientFam, recipientName, address, senderFam, senderName;
                double cost;

                getline(file, line);  // Пропускаем пустую строку
                getline(file, line);  // Считываем фамилию и имя получателя
                size_t pos = line.find(": ");
                recipientFam = line.substr(pos + 2);
                getline(file, line);  // Считываем адрес получателя
                pos = line.find(": ");
                address = line.substr(pos + 2);
                getline(file, line);  // Считываем фамилию и имя отправителя
                pos = line.find(": ");
                senderFam = line.substr(pos + 2);
                getline(file, line);  // Считываем стоимость письма
                pos = line.find(": ");
                cost = stod(line.substr(pos + 2));

                getline(file, line);  // Пропускаем последнюю строку

                Man recipient(recipientFam, recipientName);
                Man sender(senderFam, senderName);
                data.push_back(new Letter(recipient, address, sender, cost));
            }
            else if (line == "---------- Доставка ----------") {
                string recipientFam, recipientName, address, senderFam, senderName;
                int day, month, year;

                getline(file, line);  // Пропускаем пустую строку
                getline(file, line);  // Считываем фамилию и имя получателя
                size_t pos = line.find(": ");
                recipientFam = line.substr(pos + 2);
                getline(file, line);  // Считываем адрес получателя
                pos = line.find(": ");
                address = line.substr(pos + 2);
                getline(file, line);  // Считываем фамилию и имя отправителя
                pos = line.find(": ");
                senderFam = line.substr(pos + 2);
                getline(file, line);  // Считываем дату доставки
                pos = line.find(": ");
                string dateString = line.substr(pos + 2);
                pos = dateString.find(".");
                day = stoi(dateString.substr(0, pos));
                dateString = dateString.substr(pos + 1);
                pos = dateString.find(".");
                month = stoi(dateString.substr(0, pos));
                year = stoi(dateString.substr(pos + 1));

                getline(file, line);  // Пропускаем последнюю строку

                Man recipient(recipientFam, recipientName);
                Man sender(senderFam, senderName);
                Date deliveryDate(day, month, year);
                data.push_back(new Delivery(recipient, address, sender, deliveryDate));
            }
        }

        file.close();
        cout << "Данные успешно загружены." << endl;
    }
    else {
        cerr << "Ошибка при открытии файла." << endl;
    }

    return data;
}

// Функция для поиска данных по фамилии и имени получателя
void searchByRecipient(const vector<Common*>& data, const string& fam, const string& name) {
    cout << "Результаты поиска по фамилии и имени получателя: " << endl;

    bool found = false;
    for (const auto& item : data) {
        try {
            if (item->isEqual(Man(fam, name))) {
                item->printInfo();
                found = true;
            }
        }
        catch (...) {
            cout << "Ошибка при обработке данных. Продолжение поиска..." << endl;
        }
    }

    if (!found) {
        cout << "Данные не найдены." << endl;
    }
}

// Функция для поиска данных до заданной даты доставки
void searchByDeliveryDate(const vector<Common*>& data, const Date& endDate) {
    cout << "Результаты поиска по заданной дате доставки: " << endl;

    bool found = false;
    for (const auto& item : data) {
        try {
            const Delivery* delivery = dynamic_cast<const Delivery*>(item);
            if (delivery != nullptr && delivery->getDeliveryDate() <= endDate) {
                delivery->printInfo();
                found = true;
            }
        }
        catch (...) {
            cout << "Ошибка при обработке данных. Продолжение поиска..." << endl;
        }
    }

    if (!found) {
        cout << "Данные не найдены." << endl;
    }
}
// Функция для вывода данных в табличном виде
void printData(const vector<Common*>& data) {
    cout << left << setw(15) << "Тип" << setw(25) << "Фамилия и имя получателя" << setw(25) << " Адрес получателя" << setw(25)
        << "Фамилия и имя отправителя          " << setw(30) << "Дополнительно" << endl;
    cout << setfill('-') << setw(105) << "-" << endl;
    cout << setfill(' ');

    for (const Common* item : data) {
        cout << setw(15);

        const Letter* letter = dynamic_cast<const Letter*>(item);
        const Delivery* delivery = dynamic_cast<const Delivery*>(item);

        if (letter != nullptr) {
            cout << "Письмо";
            cout << setw(25) << letter->getRecipient().getFam() + " " + letter->getRecipient().getName();
            cout << setw(30) << letter->getAddress();
            cout << setw(25) << letter->getSender().getFam() + " " + letter->getSender().getName();

            stringstream ss;
            ss << "         Стоимость: " << letter->getCost() << " руб.";
            cout << setw(15) << ss.str();
        }
        else if (delivery != nullptr) {
            cout << "Доставка";
            cout << setw(25) << delivery->getRecipient().getFam() + " " + delivery->getRecipient().getName();
            cout << setw(30) << delivery->getAddress();
            cout << setw(25) << delivery->getSender().getFam() + " " + delivery->getSender().getName();

            stringstream ss;
            ss << "         Дата: " << delivery->getDeliveryDate();
            cout << setw(15) << ss.str();
        }

        cout << endl;
    }
    cout << endl;
}
int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251); // Установить кодовую страницу для ввода
    SetConsoleOutputCP(1251); // Установить кодовую страницу для вывода
    vector<Common*> data;
    data = loadData();
    char choice;

    do {
        cout << "Меню:" << endl;
        cout << "1. Создать новое письмо" << endl;
        cout << "2. Создать новую доставку" << endl;
        cout << "3. Вывести данные в табличном виде" << endl;
        cout << "4. Поиск по фамилии и имени получателя" << endl;
        cout << "5. Поиск по дате доставки" << endl;
        cout << "0. Выход" << endl;
        cout << "Введите номер пункта: ";
        cin >> choice;

        switch (choice) {
        case '1':
            data.push_back(new Letter(createLetter()));
            saveData(data);
            break;
        case '2':
            data.push_back(new Delivery(createDelivery()));
            saveData(data);
            break;
        case '3':
            printData(data);
            break;
        case '4': {
            cout << "Введите фамилию получателя: ";
            string fam;
            cin >> fam;

            bool hasInvalidChars = false;
            for (char c : fam) {
                if (isdigit(c) || ispunct(c)) {
                    hasInvalidChars = true;
                    break;
                }
            }

            if (hasInvalidChars) {
                cout << "Ошибка: Фамилия должна содержать только буквы." << endl;
                cout << "Введите фамилию получателя: ";
                string fam;
                cin >> fam;
            }

            cout << "Введите имя получателя: ";
            string name;
            cin >> name;

            hasInvalidChars = false;
            for (char c : name) {
                if (isdigit(c) || ispunct(c)) {
                    hasInvalidChars = true;
                    break;
                }
            }

            if (hasInvalidChars) {
                cout << "Ошибка: Имя должно содержать только буквы." << endl;
                cout << "Введите имя получателя: ";
                string name;
                cin >> name;
            }

            searchByRecipient(data, fam, name);
            break;
        }
        case '5': {
            cout << "Введите дату (день месяц год): ";
            int day, month, year;

            cout << "Введите день: ";
            cin >> day;

            cout << "Введите месяц: ";
            cin >> month;

            cout << "Введите год: ";
            cin >> year;

            bool isValidDate = true;

            // Проверка корректности дня
            if (day < 1 || day > 31) {
                isValidDate = false;
                std::cout << "Ошибка: Некорректный день." << std::endl;
            }
            

            // Проверка корректности месяца
            if (month < 1 || month > 12) {
                isValidDate = false;
                std::cout << "Ошибка: Некорректный месяц." << std::endl;
            }
           

            // Проверка корректности года
            if (year < 1900 || year > 2099) {
                isValidDate = false;
                std::cout << "Ошибка: Некорректный год." << std::endl;
            }
           
            if (isValidDate) {
                // Действия при корректном вводе даты
                std::cout << "Введена корректная дата: " << day << "/" << month << "/" << year << std::endl;
            }
            else {
                cout << "Введите день: ";
                cin >> day;

                cout << "Введите месяц: ";
                cin >> month;

                cout << "Введите год: ";
                cin >> year;
            }

            Date endDate(day, month, year);
            
            searchByDeliveryDate(data, endDate);
            break;
        }
        case '0':
            saveData(data);
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Некорректный выбор." << endl;
        }

        cout << endl;
    } while (choice != '0');


    return 0;
}