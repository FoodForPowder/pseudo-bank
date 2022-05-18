#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
using namespace std;
class account{
private:
   char accNumber[21];
   unsigned int balance; 
   char pin[5];
public:
    account() : accNumber(""), balance(0), pin("")
    {}
    account(const char* accNumber_n, unsigned int balance_n,const char* pin_n) {
        strcpy_s(accNumber, accNumber_n);
        balance = balance_n;
        strcpy_s(pin, pin_n);
    }
    void setpin() {
        cout << "\n������� ���-���: ";
        cin >> pin;
        cin.ignore(255, '\n');
    }
    void setAccNumber() {
        cout << "\n������� ����� ��������: ";
        cin.getline(accNumber, 21);
        cin.ignore(255,'\n');
    }
    void setBalance() {
        cout << "\n������� �����: ";
        cin >> balance;
        cin.ignore(255, '\n');
    }
    char* get_accNumb() {
        return accNumber;
    }
    void RepBalance() {
        cout << "\n������� �����: ";
        unsigned int temp;
        cin >> temp;
        balance += temp;
        cout << " \n�������!";
    }
    void Withdraw() {
        cout << "\n������� �����: ";
        unsigned int temp;
        cin >> temp;
        if (temp <= balance) {
            balance -= temp;
            cout << " \n�������!";
        }
        else cout << "\n������������ �������.";
    }
    void TransMoney(account rec_ac) {
        unsigned int amount;
        cout << "\n������� ����� �����";
        cin >> amount;
        cin.ignore(255, '\n');
        if (balance < amount) cout << "\n������������ �������. ";
        else {
            balance -= amount;
            rec_ac.balance += amount;
            cout << "\n�������! ";
        }
    }
    bool verificationOfNumber(account ac2) {
        if (strcmp(ac2.accNumber, accNumber) == 0) return true;
        else return false;

    }
    bool verificationOfPin(account ac2) {
        if (strcmp(ac2.pin, pin) == 0) return true;
        else return false;

    }
    void print() {
        cout << "����� �����" << accNumber << " "<<"������: " << balance << endl;
    }
   
};
vector<account>vAccount;
void readAllAccountInfo(vector<account>&vAccount);
void WriteAllAccountsInfo(vector<account>&vAccount);
void print_menu(void);
int get_variant(int);
void menu(void);
void create_account(void);
void login_account(void);
void acc_menu(int);
void print_accMenu(int);
int main()
{
    setlocale(LC_ALL, "ru");
    readAllAccountInfo(vAccount);
    menu();
    WriteAllAccountsInfo(vAccount);
    return 0;
}
int get_variant(int count) {
    int variant;
    while (!(cin >> variant) || variant < 1 || variant > count) {
        cout << "\n������������ �������.���������� ��� ���\n";
    }
    return variant;

}
void menu() {
    int variant;
    do {
        print_menu();
        variant = get_variant(3);
        switch (variant) {
        case 1: 
            create_account();
            break;
        case 2: 
            login_account();
            break;
        }
        if (variant != 3) system("pause");
    } while (variant != 3);


}
void print_menu() {
    system("cls");
    cout << "����:\n";
    cout << "1.������� ����:\n";
    cout << "2.������ � �������:\n";
    cout << "3.�����\n";
}
void create_account() {
    account new_acc;
    new_acc.setAccNumber();
    new_acc.setpin();
    vAccount.push_back(new_acc);
}
void login_account() {
    account temp_acc;
    temp_acc.setAccNumber();
    temp_acc.setpin();
    int i;
    for ( i = 0; i < vAccount.size(); i++) {
        if (temp_acc.verificationOfNumber(vAccount[i]) && temp_acc.verificationOfPin(vAccount[i])) {
            cout << "\n����� ������� ������\n";
            system("pause");
            system("cls");
            acc_menu(i);
        }
    }
    if (i >= vAccount.size()) { cout << "\n�������� � ������ ������� �� ����������!\n"; }
}
void print_accMenu(int i) {
        
        system("cls");
        vAccount[i].print();
        cout << "\n�������� ��������:\n";
        cout << "1.��������� ������\n";
        cout << "2.����� ������\n";
        cout << "3.��������� ������ �� ������ ����\n";
        cout << "4.�����\n";
}
void acc_menu(int i) {
    int variant;
    do {
        print_accMenu(i);
        variant = get_variant(4);
        switch (variant) {
        case 1:
            vAccount[i].RepBalance();
            break;
        case 2:
            vAccount[i].Withdraw();
            break;
        case 3:
            cin.ignore(255, '\n');
            char temp_number[21];
            cout << "\n������� ����� �����\n";
            cin.getline(temp_number, 21);
            int j;
            for (j = 0; j < vAccount.size(); j++) {
                 char accNumb[21];
                 strcpy_s(accNumb, vAccount[j].get_accNumb());
                if (strcmp(temp_number,accNumb ) == 0) {
                    vAccount[i].TransMoney(vAccount[j]);
                        break;
                    }
                }
            if (j >= vAccount.size()) {
                cout << "\n������ ������ ����� �� ����������";
            }
            break;
            
        }
          if (variant != 4) system("pause");
        } while (variant != 4);
}
void readAllAccountInfo(vector<account>&vAccount){
    ifstream f;
    f.open("data.txt");
    if (f.is_open()) {
        account temp;
        while (f.read((char*)&temp, sizeof(temp))) {
            vAccount.push_back(temp); 
        }
        f.close();
    }
    else cout << "\n������ �������� �����.";

}
void WriteAllAccountsInfo(vector<account>&vAccount) {
    ofstream f;
    f.open("data.txt");
    if (f.is_open()) {
        for (int i = 0; i < vAccount.size(); i++) {
            f.write((char*)&vAccount[i], sizeof(account));
        }
        f.close();
    }
    else cout << "\n������ �������� �����.";
}
