#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h> 

using namespace std;

struct Bill {
    string payerAccount;
    string recipientAccount;
    double amount;
};

void Menu();
void Print(Bill* bills, int N);
void AddBill(Bill*& bills, int& N);
void SortBillsByPayerAccount(Bill* bills, int N);
void FindAmountByPayer(Bill* bills, int N);
void ReadFromFile(Bill*& bills, int& N);
void WriteToFile(Bill* bills, int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Bill* bills = nullptr;
    int N = 0;
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        Menu();
        cout << "Виберіть опцію: ";
        cin >> choice;

        switch (choice) {
        case 1:
            Print(bills, N);
            break;
        case 2:
            AddBill(bills, N);
            break;
        case 3:
            SortBillsByPayerAccount(bills, N);
            cout << "Рахунки відсортовано за рахунками платників.\n";
            break;
        case 4:
            FindAmountByPayer(bills, N);
            break;
        case 5:
            ReadFromFile(bills, N);
            break;
        case 6:
            WriteToFile(bills, N);
            break;
        case 7:
            exitProgram = true;
            break;
        default:
            cout << "Неправильний вибір. Спробуйте ще раз.\n";
        }
    }

    delete[] bills;
    return 0;
}

void Menu() {
    cout << "\n=== МЕНЮ ===\n";
    cout << "1. Вивести список рахунків\n";
    cout << "2. Додати новий рахунок\n";
    cout << "3. Сортувати рахунки за рахунком платника\n";
    cout << "4. Показати суму за введеним рахунком платника\n";
    cout << "5. Зчитати дані з файлу\n";
    cout << "6. Записати дані у файл\n";
    cout << "7. Вихід\n";
}

void Print(Bill* bills, int N) {
    if (N == 0) {
        cout << "Список рахунків порожній.\n";
        return;
    }
    cout << "\n=== Список рахунків ===\n";
    for (int i = 0; i < N; i++) {
        cout << "Рахунок платника: " << bills[i].payerAccount
            << ", Рахунок одержувача: " << bills[i].recipientAccount
            << ", Сума: " << bills[i].amount << " грн\n";
    }
}

void AddBill(Bill*& bills, int& N) {
    Bill* temp = new Bill[N + 1];
    for (int i = 0; i < N; i++) {
        temp[i] = bills[i];
    }

    cout << "\n=== Додавання нового рахунку ===\n";
    cout << "Рахунок платника: ";
    cin >> temp[N].payerAccount;
    cout << "Рахунок одержувача: ";
    cin >> temp[N].recipientAccount;
    cout << "Сума: ";
    cin >> temp[N].amount;

    delete[] bills;
    bills = temp;
    N++;
}

void SortBillsByPayerAccount(Bill* bills, int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (bills[j].payerAccount > bills[j + 1].payerAccount) {
                swap(bills[j], bills[j + 1]);
            }
        }
    }
}

void FindAmountByPayer(Bill* bills, int N) {
    string payerAccount;
    cout << "Введіть рахунок платника: ";
    cin >> payerAccount;

    bool found = false;
    for (int i = 0; i < N; i++) {
        if (bills[i].payerAccount == payerAccount) {
            cout << "Сума, знята з рахунку " << payerAccount << ": " << bills[i].amount << " грн\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Рахунок платника не знайдено.\n";
    }
}

void ReadFromFile(Bill*& bills, int& N) {
    string filename;
    cout << "Введіть ім'я файлу для читання: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не вдалося відкрити файл.\n";
        return;
    }

    file >> N;
    delete[] bills;
    bills = new Bill[N];

    for (int i = 0; i < N; i++) {
        file >> bills[i].payerAccount >> bills[i].recipientAccount >> bills[i].amount;
    }

    file.close();
    cout << "Дані успішно завантажені з файлу.\n";
}

void WriteToFile(Bill* bills, int N) {
    string filename;
    cout << "Введіть ім'я файлу для запису: ";
    cin >> filename;

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Не вдалося відкрити файл для запису.\n";
        return;
    }

    file << N << endl;
    for (int i = 0; i < N; i++) {
        file << bills[i].payerAccount << " " << bills[i].recipientAccount << " " << bills[i].amount << endl;
    }

    file.close();
    cout << "Дані успішно записані у файл.\n";
}
