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
    const int ZONE_COUNT = 3; // Количество зон
    const int SHELF_COUNT = 20; // Количество стеллажей
    const int SECTION_COUNT = 5; // Количество вертикальных секций в стеллаже
    const int SHELF_LEVEL_COUNT = 2; // Количество полок в вертикальной секции

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
        double totalFillRatio = static_cast<double>(totalFilled) / (totalCapacity / 10) * 100;
        cout << "Общая загруженность склада: " << fixed << setprecision(2) << totalFillRatio << "%" << endl;

        vector<int> zoneCount(ZONE_COUNT, 0);
        for (const auto& [address, item] : cells) {
            int zoneIndex = address[0] - 'A';
            if (zoneIndex >= 0 && zoneIndex < ZONE_COUNT) {
                zoneCount[zoneIndex]++;
            }
        }

        double zoneARatio = static_cast<double>(zoneCount[0]) / totalFilled * 100;
        double zoneBRatio = static_cast<double>(zoneCount[1]) / totalFilled * 100;
        double zoneCRatio = static_cast<double>(zoneCount[2]) / totalFilled * 100;

        cout << "Зона A: " << fixed << setprecision(2) << zoneARatio << "%" << endl;
        cout << "Зона Б: " << fixed << setprecision(2) << zoneBRatio << "%" << endl;
        cout << "Зона В: " << fixed << setprecision(2) << zoneCRatio << "%" << endl;

        cout << "Заполненные ячейки:" << endl;
        for (const auto& [address, item] : cells) {
            cout << address << ": " << item.name << " (" << item.amount << ")" << endl;
        }

        cout << "Пустые ячейки:" << endl;
        for (int zone = 0; zone < ZONE_COUNT; zone++) {
            for (int shelf = 1; shelf <= SHELF_COUNT; shelf++) {
                for (int section = 1; section <= SECTION_COUNT; section++) {
                    for (int shelfLevel = 1; shelfLevel <= SHELF_LEVEL_COUNT; shelfLevel++) {
                        string address = string(1, static_cast<char>('A' + zone)) + to_string(shelf) + to_string(section) + to_string(shelfLevel);
                        if (cells.count(address) == 0) {
                            cout << address << " ";
                        }
                    }
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
