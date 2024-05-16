#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

struct Ticket {
    int number;
    int duration;
    int endTime;
};

int main() {
    system("chcp 65001");
    int numWindows;
    cout << ">>> Введите количество окон" << endl;
    cin >> numWindows;

    vector<queue<Ticket>> windows(numWindows);
    int ticketNumber = 1;
    int currentTime = 0;

    cout << "Введите команду ENQUEUE, чтобы добавить талон, или DISTRIBUTE, чтобы прекратить ввод: " << endl;

    while (true) {
        string command;
        cout << "<<< ";
        cin >> command;

        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            Ticket ticket = {ticketNumber, duration, currentTime + duration};
            int minEndTime = windows[0].empty() ? 0 : windows[0].back().endTime;
            int minWindow = 0;
            for (int i = 1; i < numWindows; i++) {
                if (windows[i].empty() || windows[i].back().endTime < minEndTime) {
                    minEndTime = windows[i].empty() ? 0 : windows[i].back().endTime;
                    minWindow = i;
                }
            }
            windows[minWindow].push(ticket);
            cout << ">>> T" << setw(3) << setfill('0') << ticket.number << endl;
            ticketNumber++;
            currentTime = max(currentTime, ticket.endTime);
        } else if (command == "DISTRIBUTE") {
            for (int i = 0; i < numWindows; i++) {
                int totalTime = 0;
                cout << ">>> Окно " << i + 1 << " (";
                while (!windows[i].empty()) {
                    Ticket ticket = windows[i].front();
                    totalTime += ticket.duration;
                    cout << "T" << setw(3) << setfill('0') << ticket.number << " (" << ticket.duration << " мин)";
                    if (!windows[i].empty()) {
                        cout << " + ";
                    }
                    windows[i].pop();
                }
                cout << "= " << totalTime << " минут): " << endl;
            }
            break;
        } else {
            cout << "Некорректная команда. Попробуйте еще раз." << endl;
        }
    }

    return 0;
}
