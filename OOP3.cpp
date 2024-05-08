
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Storage {
private:
    string name;
    double price;
    int quant;
    static int count;
public:
    Storage(const string& name = "", double price = 0.0, int quant = 0)
        : name(name), price(price), quant(quant) {
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
        os << item.getName() << "\t\t" << item.getPrice() << "\t\t" << item.getQuantity();
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
        while (file >> name >> price >> quant) {
            storageItems.push_back(Storage(name, price, quant));
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

        switch (choice){
        case 1:
        {
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

            storageItems.push_back(Storage(name, price, quant));
        }
        break;
        case 2:
            cout << "Товары в хранилище:\n";
            cout << "Название\tЦена\t\tКоличество" << endl;
            for (const Storage& item : storageItems) {
                cout << item << endl;
            }
            break;
        case 3:
        {
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
        case 4:
        {
            double minPrice;
            cout << "Введите минимальную цену для поиска: ";
            cin >> minPrice;

            cout << "Товары с ценой больше " << minPrice << ":\n";
            cout << "Название\t\tЦена\t\tКоличество" << endl;

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
                    outFile << item.getName() << " " << item.getPrice() << " " << item.getQuantity() << endl;
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

//1. Дружественными называются классы или функции, которые имеют доступ к приватным и защищенным членам другого класса.В данном коде нет дружественных классов или функций.
//2. Перегрузка операций осуществляется путем определения функции с тем же именем, что и операция, и специальным синтаксисом.Например, для перегрузки операции сложения для пользовательского типа данных необходимо определить функцию с именем operator+(), которая принимает два аргумента типа этого пользовательского типа данных.
//3. Унарная операция требует один аргумент, бинарная операция требует два аргумента.
//4. При использовании операции ++ в префиксной форме значение переменной увеличивается на единицу перед использованием этого значения в выражении.При использовании в постфиксной форме значение переменной увеличивается на единицу после использования этого значения в выражении.
//5. Ограничения перегрузки операторов включают ограничения на изменение семантики стандартных операций, неизменяемость числа аргументов и порядка их следования, а также необходимость сохранения ассоциативности и приоритетности операций.
//6. Указатель this при перегрузке операторов используется для доступа к членам класса, на котором вызывается операция.
//7. Указатель this при вызове метода класса используется для доступа к членам класса, на котором вызывается метод.
//8. Примеры повторных объявлений функций включают определение функций с одинаковыми именами и типами аргументов, но разными возвращаемыми типами или количеством аргументов.Например:

//int add(int a, int b);
//double add(int a, int b);

//int multiply(int a, int b);
//int multiply(int a, int b, int c);