#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для хранения информации о ячейке на складе
struct CellInfo {
    string name; // Название товара
    int amount; // Количество товара
};

// Класс для управления складом
class Warehouse {
private:
    map<string, CellInfo> cells; // Карта ячеек склада
    int totalCapacity; // Общая вместимость склада
    int totalFilled; // Общее количество заполненных ячеек

public:
    Warehouse(int totalCapacity) : totalCapacity(totalCapacity), totalFilled(0) {}

    // Добавление товара в ячейку
    void addItem(const string& itemName, int amount, const string& cellAddress) {
        int totalAmountInCell = 0;
        for (const auto& [address, item] : cells) {
            if (address == cellAddress) {
                totalAmountInCell += item.amount;
            }
        }

        if (totalAmountInCell + amount <= 10) {
            if (cells.count(cellAddress) == 0) {
                // Если ячейка пустая, создаем новую запись
                cells[cellAddress] = {itemName, amount};
                totalFilled++;
                cout << "Добавлено " << amount << " " << itemName << " в ячейку " << cellAddress << endl;
            } else {
                // Если ячейка не пустая, добавляем товар
                cells[cellAddress].name = itemName;
                cells[cellAddress].amount += amount;
                cout << "Добавлено " << amount << " " << itemName << " в ячейку " << cellAddress << endl;
            }
        } else {
            cout << "Невозможно добавить товар, превышен лимит ячейки!" << endl;
        }
    }

    // Удаление товара из ячейки
    void removeItem(const string& itemName, int amount, const string& cellAddress) {
        if (cells.count(cellAddress) > 0 && cells[cellAddress].name == itemName) {
            if (cells[cellAddress].amount >= amount) {
                cells[cellAddress].amount -= amount;
                if (cells[cellAddress].amount == 0) {
                    cells.erase(cellAddress);
                    totalFilled--;
                }
                cout << "Удалено " << amount << " " << itemName << " из ячейки " << cellAddress << endl;
            } else {
                cout << "Недостаточно товара в ячейке для списания!" << endl;
            }
        } else {
            cout << "Товар не найден в указанной ячейке!" << endl;
        }
    }

    // Получение информации о состоянии склада
    void printInfo() {
        double totalFillRatio = static_cast<double>(totalFilled) / totalCapacity * 100;
        cout << "Общая загруженность склада: " << fixed << setprecision(2) << totalFillRatio << "%" << endl;

        map<char, int> zoneStats;
        for (const auto& [address, item] : cells) {
            zoneStats[address[0]]++;
        }

        for (const auto& [zone, count] : zoneStats) {
            double zoneRatio = static_cast<double>(count) / (totalFilled / 3) * 100;
            cout << "Зона " << zone << ": " << fixed << setprecision(2) << zoneRatio << "%" << endl;
        }

        cout << "Заполненные ячейки:" << endl;
        for (const auto& [address, item] : cells) {
            cout << address << ": " << item.name << " (" << item.amount << ")" << endl;
        }

        cout << "Пустые ячейки:" << endl;
        for (int i = 1; i <= 20; i++) {
            for (char zone = 'A'; zone <= 'C'; zone++) {
                string address = string(1, zone) + to_string(i);
                if (cells.count(address) == 0) {
                    cout << address << " ";
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Warehouse warehouse(6000); // Создаем склад с общей вместимостью 6000 единиц

    string command;
    while (true) {
        cout << "Введите команду (ADD, REMOVE, INFO, EXIT): ";
        getline(cin, command);

        if (command == "EXIT") {
            break;
        } else if (command == "ADD") {
            string itemName;
            int amount;
            string cellAddress;
            cout << "Введите название товара, количество и адрес ячейки: ";
            cin >> itemName >> amount >> cellAddress;
            cin.ignore(); // Игнорируем символ перевода строки
            warehouse.addItem(itemName, amount, cellAddress);
        } else if (command == "REMOVE") {
            string itemName;
            int amount;
            string cellAddress;
            cout << "Введите название товара, количество и адрес ячейки: ";
            cin >> itemName >> amount >> cellAddress;
            cin.ignore(); // Игнорируем символ перевода строки
            warehouse.removeItem(itemName, amount, cellAddress);
        } else if (command == "INFO") {
            warehouse.printInfo();
        } else {
            cout << "Неизвестная команда. Попробуйте еще раз." << endl;
        }
    }

    return 0;
}
