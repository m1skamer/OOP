#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

class Storage {
private:
    string name;
    double price;
    int quant;
public:
    Storage(const string& name = "", double price = 0.0, int quant = 0)
        : name(name), price(price), quant(quant) {}

    const string& getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quant;
    }

    // Поиск товара по названию
    bool searchByName(const string& itemName) const {
        return (name == itemName);
    }

    // Найти все товары с ценой больше заданного значения
    bool searchByPrice(double minPrice) const {
        return (price > minPrice);
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    vector<Storage> storageItems; // Вектор для хранения товаров

    while (true) {
        cout << "\nВыберите действие:\n";
        cout << "1. Добавить товар\n";
        cout << "2. Распечатать товары\n";
        cout << "3. Поиск товара по названию\n";
        cout << "4. Найти все товары с ценой больше заданной\n";
        cout << "5. Показать количество созданных объектов\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
        {
            string name;
            cout << "Введите название товара: ";
            cin.ignore(); // Очищаем буфер ввода
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
            cout << "Название\t\tЦена\t\tКоличество" << endl;
            for (const Storage& item : storageItems) {
                cout << item.getName() << "\t\t\t" << item.getPrice() << "\t\t" << item.getQuantity() << endl;
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
                    cout << "Название: " << item.getName() << endl;
                    cout << "Цена: " << item.getPrice() << endl;
                    cout << "Количество: " << item.getQuantity() << endl;
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
                    cout << item.getName() << "\t\t" << item.getPrice() << "\t\t" << item.getQuantity() << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "Нет товаров с ценой больше " << minPrice << endl;
            }
        }
        break;
        case 5:
            cout << "Количество созданных объектов: " << storageItems.size() << endl;
            break;
        case 6:
            cout << "Выход\n";
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}

// 1. Класс представляет собой шаблон для создания объектов, который описывает свойства и методы объектов данного типа.
//2. Элементы класса включают данные-члены (переменные), функции-члены (методы), конструкторы и деструкторы, а также спецификаторы доступа.
//3. Спецификаторы доступа включают public, private и protected. Public позволяет доступ к элементам класса из любой части программы,private ограничивает доступ только к элементам класса изнутри самого класса, a protected позволяет доступ к элементам класса из его наследников.
//4. Доступ к элементам класса осуществляется через оператор точки (.), который указывает на член класса, или через указатель this, который ссылается на текущий объект класса.
//5. Конструктор используется для инициализации объектов класса при их создании. Например, можно создать конструктор для класса Person, который будет принимать имя и возраст объекта и инициализировать соответствующие переменные.
//6. Деструктор используется для освобождения ресурсов, занятых объектом класса при его уничтожении.Например, можно создать деструктор для класса File, который будет закрывать файловый поток при уничтожении объекта.
//7. Область видимости в классе определяет, где доступны данные - члены класса.Например, если переменная объявлена внутри функции - члена класса, то она будет видна только внутри этой функции.
//8. Область видимости можно изменить с помощью ключевых слов public, private и protected.
//9. Друзья класса - это другие классы или функции, которые имеют доступ к приватным и защищенным членам данного класса.
//10. Ключевое слово public позволяет доступ к элементам класса из любой части программы, в то время как дружественные функции могут иметь доступ только к конкретным элементам класса.
//11. Статические поля класса - это поля, которые принадлежат самому классу, а не его объектам.Они могут использоваться для хранения общей информации для всех объектов данного класса и доступны без создания экземпляров класса.Отличие от обычных полей заключается в том, что они не связаны с конкретным объектом класса, а с самим классом.