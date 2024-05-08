#include <iostream>
#include <string>
using namespace std;

struct PriceTag { //информация о продукте
    string product;
    float price;
    string expirationDate;
};

void validDate(string date) { //функция проверки даты на правильный формат
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        cout << "Неправильная дата" << endl;
        return;
    }
    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        cout << "Неправильная дата" << endl;
        return;
    }
}

void addPriceTag(PriceTag*& tags, int& size) {
    setlocale(LC_ALL, "rus");
    PriceTag* newPTags = new PriceTag[size + 1];
    for (int i = 0; i < size; i++) {
        newPTags[i] = tags[i];
    }
    cout << "Введите имя продукта: "; //ввод ценника
    cin >> newPTags[size].product;
    cout << "Введите цену: ";
    cin >> newPTags[size].price;
    cout << "Введите дату окончания срока годности (дд/мм/гггг): ";
    cin >> newPTags[size].expirationDate;
    validDate(newPTags[size].expirationDate);
    size++;
    delete[] tags;
    tags = newPTags;
}

void findExpiredProducts(PriceTag* tags, int size) {
    string currentDate;
    cout << "Введите дату (дд/мм/гггг): ";
    cin >> currentDate;
    if (currentDate.length() != 10 || currentDate[2] != '/' || currentDate[5] != '/') {
        cout << "Неправильная дата" << endl;
        return;
    }
    int day = stoi(currentDate.substr(0, 2)); //дата продукта, разбитая на д., м., г.
    int month = stoi(currentDate.substr(3, 2));
    int year = stoi(currentDate.substr(6, 4));
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        cout << "Неправильная дата" << endl;
        return;
    }
    PriceTag* expiredTags = nullptr;
    int expiredSize = 0;
    for (int i = 0; i < size; i++) {
        // Check if expiration date is valid
        if (tags[i].expirationDate.length() != 10 || tags[i].expirationDate[2] != '/' || tags[i].expirationDate[5] != '/') {
            cout << "Неправильная дата " << tags[i].product << endl;
            continue;
        }

        int expDay = stoi(tags[i].expirationDate.substr(0, 2)); //текущая дата, разбитая на д., м., г.
        int expMonth = stoi(tags[i].expirationDate.substr(3, 2));
        int expYear = stoi(tags[i].expirationDate.substr(6, 4));
        if (expDay < 1 || expDay > 31 || expMonth < 1 || expMonth > 12) {
            cout << "Введите текущую дату " << tags[i].product << endl;
            continue;
        }
        // проверка на срок годности
        if (expYear < year || (expYear == year && expMonth < month) || (expYear == year && expMonth == month && expDay < day)) {
            PriceTag* newExpiredTags = new PriceTag[expiredSize + 1];
            for (int j = 0; j < expiredSize; j++) {
                newExpiredTags[j] = expiredTags[j];
            }
            newExpiredTags[expiredSize] = tags[i];
            expiredSize++;
            delete[] expiredTags;
            expiredTags = newExpiredTags;
        }
    }
    cout << "Просроченные продукты:" << endl;
    for (int i = 0; i < expiredSize; i++) {
        cout << expiredTags[i].product << ": " << expiredTags[i].price << ", " << expiredTags[i].expirationDate << endl;

    }
    delete[] expiredTags;
}

void deletePriceTags(PriceTag*& tags) {
    delete[] tags;
    tags = nullptr;
}

int main() {
    setlocale(LC_ALL, "rus");
    PriceTag* tags = nullptr;
    int size = 0;
    string command;
    while (true) {
        cout << "Введите команду (add, find, exit): ";
        cin >> command;
        if (cin.fail()) {
            cout << "Неправильный ввод" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (command == "add") {
            addPriceTag(tags, size);
        }
        else if (command == "find") {
            findExpiredProducts(tags, size);
        }
        else if (command == "exit") {
            deletePriceTags(tags);
            break;
        }
        else {
            cout << "Неправильная команда" << endl;
        }
    }
    return 0;
}