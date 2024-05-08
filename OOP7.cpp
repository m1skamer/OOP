#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>

using namespace std;

enum Specialty {
    THERAPIST = 1,
    CARDIOLOGIST,
    DENTIST
};

class FIO {
private:
    string surname;
    string name;
public:
    FIO() {}
    FIO(const string& s, const string& n) : surname(s), name(n) {}

    string getSurname() const {
        return surname;
    }

    string getName() const {
        return name;
    }
    bool operator==(const FIO& other) const {
        return surname == other.surname && name == other.name;
    }
};

class Clinic {
private:
    FIO doctor;
    Specialty specialty;
public:
    Clinic() {}
    Clinic(const FIO& f, const Specialty& s) : doctor(f), specialty(s) {}

    FIO getDoctor() const {
        return doctor;
    }

    Specialty getSpecialty() const {
        return specialty;
    }

    bool operator==(const Clinic& clinic) const {
        return doctor == clinic.doctor && specialty == clinic.specialty;
    }
    bool operator==(const FIO& fio) const {
        return doctor == fio;
    }
};

void addDoctorToFront(deque<Clinic>& clinics) {
    cout << "Введите фамилию и имя врача: ";
    string surname, name;
    cin >> surname >> name;

    cout << "Введите специальность врача (1-терапевт, 2-кардиолог, 3-стоматолог): ";
    int specialty;
    cin >> specialty;

    FIO fio(surname, name);
    clinics.push_front(Clinic(fio, static_cast<Specialty>(specialty)));

    cout << "Врач успешно добавлен в базу данных." << endl;
}

void addDoctorToBack(deque<Clinic>& clinics) {
    cout << "Введите фамилию и имя врача: ";
    string surname, name;
    cin >> surname >> name;

    cout << "Введите специальность врача (1-терапевт, 2-кардиолог, 3-стоматолог): ";
    int specialty;
    cin >> specialty;

    FIO fio(surname, name);
    clinics.push_back(Clinic(fio, static_cast<Specialty>(specialty)));

    cout << "Врач успешно добавлен в базу данных." << endl;
}

void removeDoctorFromFront(deque<Clinic>& clinics) {
    if (!clinics.empty()) {
        clinics.pop_front();
        cout << "Первый врач удален из базы данных." << endl;
    }
    else {
        cout << "База данных врачей пуста." << endl;
    }
}

void searchByFIO(const deque<Clinic>& clinics) {
    cout << "Введите фамилию и имя врача: ";
    string surname, name;
    cin >> surname >> name;

    FIO fio(surname, name);
    bool found = false;

    for (const Clinic& clinic : clinics) {
        if (clinic == fio) {
            cout << "Врач найден:" << endl;
            cout << "Фамилия: " << clinic.getDoctor().getSurname() << endl;
            cout << "Имя: " << clinic.getDoctor().getName() << endl;
            cout << "Специальность: ";

            switch (clinic.getSpecialty()) {
            case THERAPIST:
                cout << "Терапевт";
                break;
            case CARDIOLOGIST:
                cout << "Кардиолог";
                break;
            case DENTIST:
                cout << "Стоматолог";
                break;
            }

            cout << "\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Врач не найден." << endl;
    }
}

bool compareBySurname(const Clinic& clinic1, const Clinic& clinic2) {
    return clinic1.getDoctor().getSurname() < clinic2.getDoctor().getSurname();
}

void sortByAlphabet(deque<Clinic>& clinics) {
    sort(clinics.begin(), clinics.end(), compareBySurname);
    cout << "Список врачей отсортирован по алфавиту." << endl;
}

void displayTable(const deque<Clinic>& clinics) {
    if (clinics.empty()) {
        cout << "База данных врачей пуста." << endl;
        return;
    }

    const int width = 15;

    cout << left << setw(width) << "Фамилия";
    cout << left << setw(width) << "Имя";
    cout << left << setw(width) << "Специальность" << endl;

    for (const Clinic& clinic : clinics) {
        cout << left << setw(width) << clinic.getDoctor().getSurname();
        cout << left << setw(width) << clinic.getDoctor().getName();

        switch (clinic.getSpecialty()) {
        case THERAPIST:
            cout << left << setw(width) << "Терапевт";
            break;
        case CARDIOLOGIST:
            cout << left << setw(width) << "Кардиолог";
            break;
        case DENTIST:
            cout << left << setw(width) << "Стоматолог";
            break;
        }

        cout << endl;
    }
}
void saveDatabaseToFile(const deque<Clinic>& clinics) {
    ofstream file("database.txt");
    if (file.is_open()) {
        for (const auto& clinic : clinics) {
            file << clinic.getDoctor().getSurname() << " " << clinic.getDoctor().getName() << " " << clinic.getSpecialty() << endl;
        }

        file.close();
        cout << "База данных успешно сохранена в файл." << endl;
    }
    else {
        cout << "Ошибка при открытии файла." << endl;
    }
}
void loadDatabaseFromFile(deque<Clinic>& clinics) {
    ifstream file("database.txt");

    if (file) {
        clinics.clear();

        string surname, name;
        int specialty;

        while (file >> surname >> name >> specialty) {
            FIO fio(surname, name);
            clinics.push_back(Clinic(fio, static_cast<Specialty>(specialty)));
        }

        cout << "База данных успешно загружена из файла." << endl;
    }
    else {
        cout << "Ошибка при открытии файла." << endl;
    }

    file.close();
}
int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251); // Установить кодовую страницу для ввода
    SetConsoleOutputCP(1251); // Установить кодовую страницу для вывода
    deque<Clinic> clinics;
    loadDatabaseFromFile(clinics);
    int choice = 0;

    while (choice != 7) {
        cout << "\nБАЗА ДАННЫХ ПОЛИКЛИНИКА" << endl;
        cout << "1. Добавить врача в начало очереди" << endl;
        cout << "2. Добавить врача в конец очереди" << endl;
        cout << "3. Удалить первого врача из очереди" << endl;
        cout << "4. Поиск врача по фамилии и имени" << endl;
        cout << "5. Сортировка врачей по алфавиту (по фамилии)" << endl;
        cout << "6. Вывести информацию о врачах в табличном виде" << endl;
        cout << "7. Выйти из программы" << endl;
        cout << "Выберите действие: ";

        cin >> choice;

        switch (choice) {
        case 1:
            addDoctorToFront(clinics);
            break;
        case 2:
            addDoctorToBack(clinics);
            break;
        case 3:
            removeDoctorFromFront(clinics);
            break;
        case 4:
            searchByFIO(clinics);
            break;
        case 5:
            sortByAlphabet(clinics);
            break;
        case 6:
            displayTable(clinics);
            break;
        case 7:
            saveDatabaseToFile(clinics);
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неправильный выбор. Повторите попытку." << endl;
            break;
        }
    }

    return 0;
}