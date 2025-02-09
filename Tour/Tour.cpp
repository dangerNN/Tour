#include <iostream>
#include <cstring>
#include <Windows.h>
#include <string>
using namespace std;

class Tour {
private:
    string name, country, city;
    double price_per_day, transport_cost;
    int days;
    bool food_included;

public:
    Tour(string n = "", string c = "", string ct = "", double ppd = 0, int d = 0, bool fi = false, double tc = 0)
        : name(n), country(c), city(ct), price_per_day(ppd), days(d), food_included(fi), transport_cost(tc) {}

    void print() const {
        cout << "Тур: " << name << ", Напрямок: " << country << ", " << city
            << ", Ціна за день: " << price_per_day << " грн, Днів: " << days
            << ", Харчування: " << (food_included ? "Так" : "Ні")
            << ", Вартість проїзду: " << transport_cost << " грн" << endl;
    }

    string getName() const { return name; }
    string getCountry() const { return country; }
    string getCity() const { return city; }
    double getTransportCost() const { return transport_cost; }
};

class TouristAgency {
private:
    Tour tours[100];
    int tourCount = 0;

public:
    void addTour(const Tour& tour) { if (tourCount < 100) tours[tourCount++] = tour; }
    void printTours() const { for (int i = 0; i < tourCount; i++) tours[i].print(); }
    void deleteTour(const string& name) {
        for (int i = 0; i < tourCount; i++) {
            if (tours[i].getName() == name) {
                for (int j = i; j < tourCount - 1; j++) {
                    tours[j] = tours[j + 1];
                }
                tourCount--;
                break;
            }
        }
    }
    void searchByDestination(const string& destination) const {
        for (int i = 0; i < tourCount; i++) {
            if (tours[i].getCountry() == destination || tours[i].getCity() == destination)
                tours[i].print();
        }
    }
    void sortByDestination() {
        for (int i = 0; i < tourCount - 1; i++) {
            for (int j = i + 1; j < tourCount; j++) {
                if (tours[i].getCountry() > tours[j].getCountry()) {
                    swap(tours[i], tours[j]);
                }
            }
        }
    }
    void sortByTransportCost() {
        for (int i = 0; i < tourCount - 1; i++) {
            for (int j = i + 1; j < tourCount; j++) {
                if (tours[i].getTransportCost() > tours[j].getTransportCost()) {
                    swap(tours[i], tours[j]);
                }
            }
        }
    }
    void addTourFromInput() {
        string name, country, city;
        double price_per_day, transport_cost;
        int days;
        bool food_included;

        cout << "\nВведіть найменування туру через пробіл: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введіть країну через пробіл: ";
        cin.ignore();
        getline(cin, country);
        cout << "Введіть місто через пробіл: ";
        cin.ignore();
        getline(cin, city);
        cout << "Введіть ціну за день: ";
        cin >> price_per_day;
        cout << "Введіть кількість днів: ";
        cin >> days;
        cout << "Чи включене харчування? (1 - Так, 0 - Ні): ";
        cin >> food_included;
        cout << "Введіть вартість проїзду: ";
        cin >> transport_cost;

        addTour(Tour(name, country, city, price_per_day, days, food_included, transport_cost));
    }
};

int main() {
    setlocale(0, "");
    srand(static_cast<unsigned int>(time(0)));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TouristAgency agency;
    agency.addTour({ "Морський відпочинок", "Греція", "Афіни", 1500, 7, true, 3000 });
    agency.addTour({ "Гірськолижний курорт", "Швейцарія", "Цюріх", 2000, 5, true, 5000 });
    agency.addTour({ "Екскурсійний тур", "Італія", "Рим", 1700, 6, false, 4000 });

    cout << "\n=== Всі тури ===\n";
    agency.printTours();

    cout << "\n=== Додавання нового туру ===\n";
    agency.addTourFromInput();
    agency.printTours();

    cout << "\n=== Пошук туру по напрямку (Італія) ===\n";
    agency.searchByDestination("Італія");

    cout << "\n=== Видалення туру \"Гірськолижний курорт\" ===\n";
    agency.deleteTour("Гірськолижний курорт");
    agency.printTours();

    cout << "\n=== Сортування за напрямком ===\n";
    agency.sortByDestination();
    agency.printTours();

    cout << "\n=== Сортування за вартістю проїзду ===\n";
    agency.sortByTransportCost();
    agency.printTours();

    return 0;
}
