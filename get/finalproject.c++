#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 100; // الحد الأقصى للحسابات
string usernames[MAX_USERS];
string passwords[MAX_USERS];
double balances[MAX_USERS];
int loginAttempts[MAX_USERS];
bool accountLocked[MAX_USERS];
int userCount = 0; // عدد الحسابات الحالية

// البحث عن اسم المستخدم وإرجاع الفهرس
int findUserIndex(const string &name) {
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == name) return i;
    }
    return -1; // لم يتم العثور على المستخدم
}

// التحقق من أن اسم المستخدم يحتوي على حروف فقط
bool isValidUsername(const string &name) {
    for (char c : name) {
        if (!isalpha(c)) return false;
    }
    return true;
}

// عرض شعار البنك
void displayLogo() {
    cout << "************************************\n";
    cout << "*         Bank The Winners         *\n";
    cout << "************************************\n";
}

// عرض القائمة الرئيسية
void showMenu() {
    cout << "\n<<< WELCOME TO OUR BANK >>>\n\n";
    cout << "[1] Create New Account\n";
    cout << "[2] Log In\n";
    cout << "[3] Exit\n";
    cout << "Enter your choice: ";
}

// إنشاء حساب جديد
void createAccount() {
    if (userCount >= MAX_USERS) {
        cout << "Sorry, the bank has reached the maximum number of accounts.\n";
        return;
    }

    string name, password, confirmPassword;
    double initialBalance;

    do {
        cout << "Enter Your Name (English letters only): ";
        cin.ignore();
        getline(cin, name);

        if (!isValidUsername(name)) {
            cout << "Invalid name! Please use English letters only.\n";
            continue;
        }

        if (findUserIndex(name) != -1) {
            cout << "Username already taken, please choose another one.\n";
            continue;
        }

        break;
    } while (true);

    do {
        cout << "Enter a 4-digit password: ";
        cin >> password;

        if (password.length() > 4) {
            cout << "Password must not exceed 4 digits.\n";
            continue;
        }

        cout << "Confirm your password: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << "Passwords do not match. Try again.\n";
        }
    } while (password != confirmPassword);

    cout << "Enter initial deposit amount: ";
    cin >> initialBalance;

    usernames[userCount] = name;
    passwords[userCount] = password;
    balances[userCount] = initialBalance;
    loginAttempts[userCount] = 0;
    accountLocked[userCount] = false;
    userCount++;

    cout << "Account Created Successfully!\n";
}

// تغيير كلمة المرور
void changePassword(int userIndex) {
    string oldPassword, newPassword, confirmNewPassword;
    cout << "Enter your current password: ";
    cin >> oldPassword;

    if (oldPassword != passwords[userIndex]) {
        cout << "Incorrect password. Password change failed.\n";
        return;
    }

    do {
        cout << "Enter a new 4-digit password: ";
        cin >> newPassword;

        if (newPassword.length() > 4) {
            cout << "Password must not exceed 4 digits.\n";
            continue;
        }

        cout << "Confirm your new password: ";
        cin >> confirmNewPassword;

        if (newPassword != confirmNewPassword) {
            cout << "Passwords do not match. Try again.\n";
        }
    } while (newPassword != confirmNewPassword);

    passwords[userIndex] = newPassword;
    cout << "Password changed successfully!\n";
}

// تحويل الأموال
void transferMoney(int userIndex) {
    string recipient;
    double amount;

    cout << "Enter recipient name: ";
    cin.ignore();
    getline(cin, recipient);

    int recipientIndex = findUserIndex(recipient);
    if (recipientIndex == -1) {
        cout << "Recipient account not found!\n";
        return;
    }

    cout << "Enter amount to transfer: ";
    cin >> amount;

    if (amount > balances[userIndex]) {
        cout << "Insufficient balance!\n";
        return;
    }

    balances[userIndex] -= amount;
    balances[recipientIndex] += amount;
    cout << "Transfer successful!\n";
}

// إغلاق الحساب
void closeAccount(int userIndex) {
    if (balances[userIndex] > 0) {
        cout << "You must withdraw all your money before closing the account.\n";
        return;
    }

    for (int i = userIndex; i < userCount - 1; i++) {
        usernames[i] = usernames[i + 1];
        passwords[i] = passwords[i + 1];
        balances[i] = balances[i + 1];
        loginAttempts[i] = loginAttempts[i + 1];
        accountLocked[i] = accountLocked[i + 1];
    }
    userCount--;

    cout << "Account closed successfully!\n";
}

// قائمة الخدمات البنكية بعد تسجيل الدخول
void bankingServices(int userIndex) {
    int choice;
    do {
        cout << "\n[1] Deposit Money\n";
        cout << "[2] Withdraw Money\n";
        cout << "[3] Check Balance\n";
        cout << "[4] Transfer Money\n";
        cout << "[5] Close Account\n";
        cout << "[6] Change Password\n";
        cout << "[7] Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter deposit amount: ";
                double depositAmount;
                cin >> depositAmount;
                balances[userIndex] += depositAmount;
                cout << "Deposit successful!\n";
                break;
            case 2:
                cout << "Enter withdrawal amount: ";
                double withdrawAmount;
                cin >> withdrawAmount;
                if (withdrawAmount > balances[userIndex]) {
                    cout << "Insufficient balance!\n";
                } else {
                    balances[userIndex] -= withdrawAmount;
                    cout << "Withdrawal successful!\n";
                }
                break;
            case 3:
                cout << "Your current balance: " << balances[userIndex] << "\n";
                break;
            case 4:
                transferMoney(userIndex);
                break;
            case 5:
                closeAccount(userIndex);
                return;
            case 6:
                changePassword(userIndex);
                break;
            case 7:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (true);
}

// تسجيل الدخول
void login() {
    string name, password;

    cout << "Enter Your Name: ";
    cin.ignore();
    getline(cin, name);

    int userIndex = findUserIndex(name);
    if (userIndex == -1) {
        cout << "Account not found!\n";
        return;
    }

    if (accountLocked[userIndex]) {
        cout << "Your account is locked. Please contact customer service.\n";
        return;
    }

    for (int attempts = 0; attempts < 3; attempts++) {
        cout << "Enter Your Password: ";
        cin >> password;

        if (passwords[userIndex] == password) {
            cout << "Login Successful!\n";
            bankingServices(userIndex);
            return;
        } else {
            cout << "Incorrect password. Try again.\n";
        }
    }

    cout << "Account locked. Please contact customer service.\n";
    accountLocked[userIndex] = true;
}

// البرنامج الرئيسي
int main() {
    displayLogo();
    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Exiting the system. Thank you!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (true);
}