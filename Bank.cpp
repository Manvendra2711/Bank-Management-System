#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <cstring>
using namespace std;

class temp
{
    // Class members
    int accNo;      // Account Number
    char name[25];  // User's Name
    char CVV[5];    // CVV Number
    char P_no[25];  // Phone Number
    char email[25]; // Email Address
    float amount;   // Account Balance
    int newAmount;  // Amount to be deposited or withdrawn
    fstream file, file1;

public:
    int search; // Account Number to search for
    // Member functions
    void createAccount(void);                      // Function to create a new account
    void depositAmount(void);                      // Function to deposit money into account
    void withdrawAmount(void);                     // Function to withdraw money from account
    void checkInfo(void);                          // Function to check account information
    bool authenticate(int accNo, const char *CVV); // Function to authenticate account
};

// Main function
int main()
{
    temp obj;    // Creating an object of class temp
    char choice; // Variable to store user's choice

    // Display menu options
    cout << "\n\n\n\t\t......::: Citi Bank :::........";
    cout << "\n\t\t:: Press 1 to Login  Account :: ";
    cout << "\n\t\t:: Press 2 to Create Account ::";
    cout << "\n\t\t:: Press 0 to Exit           ::";
    cout << "\n\t\t:: ......................... ::\n\t\t\t\t";
    cout << endl;
    cin >> choice;

    switch (choice)
    {
    case '1':
        cout << "Enter your account no :: ";
        cin >> obj.search;

        char enteredCVV[5];
        cout << "Enter your CVV :: ";
        cin >> enteredCVV;

        // Authenticating user
        if (obj.authenticate(obj.search, enteredCVV))
        {
            while (1)
            {
                // Display account operation options
                cout << "\n\n\n\t\t........::: Citi Bank :::........";
                cout << "\n\t\t:: Press 1 to Deposit Amount   ::";
                cout << "\n\t\t:: Press 2 to Withdraw Amount  ::";
                cout << "\n\t\t:: Press 3 to Check Info       ::";
                cout << "\n\t\t:: Press 0 to Exit             ::";
                cout << "\n\t\t:: ........................... ::\n\t\t\t\t";
                cout << endl;
                cin >> choice;

                // Perform chosen operation
                switch (choice)
                {
                case '1':
                    obj.depositAmount();
                    break;
                case '2':
                    obj.withdrawAmount();
                    break;
                case '3':
                    obj.checkInfo();
                    break;
                case '0':
                    return 0;
                    break;
                default:
                    cout << "Invalid Choice...!";
                    break;
                }
                system("pause");
                system("cls");
            }
        }
        else
        {
            cout << "Invalid Account Number or CVV." << endl;
        }
        break;
    case '2':
        obj.createAccount(); // Create a new account
        break;
    case '0':
        system("exit");
        break;
    default:
        cout << "\n Invalid choice...! ";
        break;
    }
    return 0;
}

// Function to create a new account
void temp::createAccount()
{
    // Generating a random account number
    srand(time(0));
    accNo = rand() * rand() + rand() * rand();

    // Getting user input for account details
    cout << "Enter Your Name :: ";
    cin >> name;

    cout << "Enter Your CVV (4 digits) :: ";
    cin >> CVV;
    CVV[4] = '\0'; // Ensuring null termination of CVV string

    cout << "Enter Your phone No. :: ";
    cin >> P_no;

    cout << "Enter Your Email :: ";
    cin >> email;

    cout << "Enter Your Amount :: ";
    cin >> amount;

    // Displaying account number
    cout << endl
         << "This is your Account Number:  " << accNo;
    cout << "\n Please save it for future use! \n\n";

    // Writing account details to file
    file.open("data.txt", ios::out | ios::app);
    file << accNo << "\t" << name << "\t" << CVV << "\t" << P_no << "\t" << email << "\t" << amount << endl;
    file.close();
}

// Function to authenticate account
bool temp::authenticate(int accNo, const char *enteredCVV)
{
    // Opening file to read account details
    file.open("data.txt", ios::in);
    if (!file)
    {
        cout << "File opening error !" << endl;
        return false;
    }

    // Reading account details and authenticating
    while (file >> this->accNo >> name >> this->CVV >> P_no >> email >> amount)
    {
        if (this->accNo == accNo && strcmp(this->CVV, enteredCVV) == 0)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Function to deposit money into account
void temp ::depositAmount()
{
    cout << "Enter Amount to Deposit :: ";
    cin >> newAmount;

    // Opening files for reading and writing
    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);
    file >> accNo >> name >> CVV >> P_no >> email >> amount;

    // Processing account transactions
    while (!file.eof())
    {
        if (accNo == search)
        {
            cout << "\nCurrent Amount :: " << amount;
            amount = amount + newAmount;
            cout << "\nUpdated Amount :: " << amount << endl;
            file1 << accNo << "\t" << name << "\t" << CVV << "\t" << P_no << "\t" << email << "\t" << amount << endl;
        }
        else
        {
            file1 << accNo << "\t" << name << "\t" << CVV << "\t" << P_no << "\t" << email << "\t" << amount << endl;
        }
        file >> accNo >> name >> CVV >> P_no >> email >> amount;
    }

    // Closing files and performing file operations
    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

// Function to withdraw money from account
void temp ::withdrawAmount()
{
    cout << "Enter Amount to Withdraw :: ";
    cin >> newAmount;

    // Opening files for reading and writing
    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);
    file >> accNo >> name >> CVV >> P_no >> email >> amount;

    // Processing account transactions
    while (!file.eof())
    {
        if (accNo == search)
        {
            cout << "\nCurrent Amount :: " << amount;
            amount = amount - newAmount;
            cout << "\nUpdated Amount :: " << amount << endl;
            file1 << accNo << "\t" << name << "\t" << CVV << "\t" << P_no << "\t" << email << "\t" << amount << endl;
        }
        else
        {
            file1 << accNo << "\t" << name << "\t" << CVV << "\t" << P_no << "\t" << email << "\t" << amount << endl;
        }
        file >> accNo >> name >> CVV >> P_no >> email >> amount;
    }

    // Closing files and performing file operations
    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

// Function to check account information
void temp ::checkInfo()
{
    // Opening file to read account details
    fstream file;
    file.open("data.txt", ios::in);
    if (!file)
    {
        cout << "File opening error !";
    }
    file >> accNo >> name >> CVV >> P_no >> email >> amount;
    while (!file.eof())
    {
        if (accNo == search)
        {
            // Displaying account information
            cout << "\n---------------------------------------------------------------------------------------------------------------------------------------\n";
            cout << endl
                 << "\t::: Account Number ::: ";
            cout << "\t   " << accNo << endl;
            cout << "\t::: User Name      ::: ";
            cout << "\t   " << name << "\n";
            cout << "\t::: CVV Number     ::: ";
            cout << "\t   " << CVV << "\n";
            cout << "\t::: Phone Number   ::: ";
            cout << "\t   " << P_no << "\n";
            cout << "\t::: Email          ::: ";
            cout << "\t   " << email << "\n";
            cout << "\t::: Current Amount ::: ";
            cout << "\t   " << amount << endl;
            cout << "\n---------------------------------------------------------------------------------------------------------------------------------------\n\n";
        }
        file >> accNo >> name >> CVV >> P_no >> email >> amount;
    }

    file.close();
}
