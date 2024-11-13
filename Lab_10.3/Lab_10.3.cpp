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
        cout << "������� �����: ";
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
            cout << "������� ����������� �� ��������� ��������.\n";
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
            cout << "������������ ����. ��������� �� ���.\n";
        }
    }

    delete[] bills;
    return 0;
}

void Menu() {
    cout << "\n=== ���� ===\n";
    cout << "1. ������� ������ �������\n";
    cout << "2. ������ ����� �������\n";
    cout << "3. ��������� ������� �� �������� ��������\n";
    cout << "4. �������� ���� �� �������� �������� ��������\n";
    cout << "5. ������� ��� � �����\n";
    cout << "6. �������� ��� � ����\n";
    cout << "7. �����\n";
}

void Print(Bill* bills, int N) {
    if (N == 0) {
        cout << "������ ������� �������.\n";
        return;
    }
    cout << "\n=== ������ ������� ===\n";
    for (int i = 0; i < N; i++) {
        cout << "������� ��������: " << bills[i].payerAccount
            << ", ������� ����������: " << bills[i].recipientAccount
            << ", ����: " << bills[i].amount << " ���\n";
    }
}

void AddBill(Bill*& bills, int& N) {
    Bill* temp = new Bill[N + 1];
    for (int i = 0; i < N; i++) {
        temp[i] = bills[i];
    }

    cout << "\n=== ��������� ������ ������� ===\n";
    cout << "������� ��������: ";
    cin >> temp[N].payerAccount;
    cout << "������� ����������: ";
    cin >> temp[N].recipientAccount;
    cout << "����: ";
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
    cout << "������ ������� ��������: ";
    cin >> payerAccount;

    bool found = false;
    for (int i = 0; i < N; i++) {
        if (bills[i].payerAccount == payerAccount) {
            cout << "����, ����� � ������� " << payerAccount << ": " << bills[i].amount << " ���\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "������� �������� �� ��������.\n";
    }
}

void ReadFromFile(Bill*& bills, int& N) {
    string filename;
    cout << "������ ��'� ����� ��� �������: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ����.\n";
        return;
    }

    file >> N;
    delete[] bills;
    bills = new Bill[N];

    for (int i = 0; i < N; i++) {
        file >> bills[i].payerAccount >> bills[i].recipientAccount >> bills[i].amount;
    }

    file.close();
    cout << "��� ������ ���������� � �����.\n";
}

void WriteToFile(Bill* bills, int N) {
    string filename;
    cout << "������ ��'� ����� ��� ������: ";
    cin >> filename;

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ���� ��� ������.\n";
        return;
    }

    file << N << endl;
    for (int i = 0; i < N; i++) {
        file << bills[i].payerAccount << " " << bills[i].recipientAccount << " " << bills[i].amount << endl;
    }

    file.close();
    cout << "��� ������ ������� � ����.\n";
}
