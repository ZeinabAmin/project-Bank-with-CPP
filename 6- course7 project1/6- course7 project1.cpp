// 6- course7 project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";

void ShowMainMenue();

struct sClient 
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete;
};

vector <string> SplitString(string S1, string Delim) {
    vector <string> vString;
    short Pos = 0;
    string sWord;
    while ((Pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, Pos);
        if(sWord != ""){
        vString.push_back(sWord);
        }
        S1.erase(0, Pos + Delim.length());
    }
    if (S1 != "") {
        vString.push_back(S1);
    }
    return vString;

}
sClient ConvertLineToRecord(string Line, string Separator = "#//#") 
{
    sClient Client;
    vector <string> vClientData;

    vClientData = SplitString(Line, Separator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance =stod(vClientData[4]);

    return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.Phone + Separator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName) 
{
    vector <sClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line)) 
        
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);

        }

        MyFile.close();
     
    }
    return false;
}

sClient ReadNewClient() {
    sClient Client;
    cout << "Enter AccountNumber? ";

    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\n client with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);

    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}


vector <sClient> LoadClientsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))

        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);

        }

        MyFile.close();
    }
    return vClients;

}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{
        vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

        cout << "\n\t\t\t\t\t\t clients list (" << vClients.size() << ") client(s).";
        cout << "\n----------------------------------------------";
        cout << "----------------------------------------------\n" << endl;


        cout << "| " << setw(15) << left << "AccountNumber";
        cout << "| " << setw(10) << left << "PinCode";
        cout << "| " << setw(40) << left << "Name";
        cout << "| " << setw(12) << left << "Phone";
        cout << "| " << setw(12) << left << "AccountBalance";

        cout << "\n----------------------------------------------";
        cout << "----------------------------------------------\n" << endl;

        if(vClients.size() == 0 )
            cout << "\n\t\t\t\t\t\t no clients available in the system !";
        else
            for (sClient Client : vClients)
            {
                PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n----------------------------------------------";
        cout << "----------------------------------------------\n" << endl;

}

void PrintClientCard(sClient Client)
{
    cout << "\n the following are the client details: \n";

    cout << "----------------------------------------------";

    cout << "\n AccountNumber: " << Client.AccountNumber;
    cout << "\n PinCode: " << Client.PinCode;
    cout << "\n Name: " << Client.Name;
    cout << "\n Phone: " << Client.Phone;
    cout << "\n AccountBalance: " << Client.AccountBalance;

    cout << "\n----------------------------------------------\n";
    
}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;


cout << "\n\nEnter PinCode? ";
getline(cin >> ws, Client.PinCode);

cout << "Enter Name? ";
getline(cin, Client.Name);

cout << "Enter Phone? ";
getline(cin, Client.Phone);

cout << "Enter AccountBalance? ";
cin >> Client.AccountBalance;

return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient & C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); //overwrite

    string DataLine;


    if (MyFile.is_open())
    {
            for (sClient C : vClients)
            {
                if (C.MarkForDelete == false)
                {

                    DataLine = ConvertRecordToLine(C);
                    MyFile << DataLine << endl;
                }
            }

        MyFile.close();
    }
    return vClients;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app); 

    if (MyFile.is_open()){
                MyFile << stDataLine << endl;
                MyFile.close();
            }
}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddNewClients()
{
    char AddMore = 'Y';
    do {
        //system("cls");
        cout << "\n\n Adding new client: \n\n";
        AddNewClient();
        cout << "\n\n client added successfully , do you want to add more clients ? Y/N ? \n\n";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber( AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\n are you sure you want to delete this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber( AccountNumber,vClients);
            SaveClientsDataToFile(ClientsFileName,vClients);
            //refresh clients
            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "client deleted successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\n client with AccountNumber (" << AccountNumber << ") is not found!";
        return false;

    }
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\n are you sure you want to update this client? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients) {

                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;

                }
            }
            SaveClientsDataToFile(ClientsFileName, vClients);
        
            cout << "client updated successfully.\n";
            return true;
        }
    }
    else
    {
        cout << "\n client with AccountNumber (" << AccountNumber << ") is not found!";
        return false;

    }
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\n please enter AccountNumber? ";
    cin >> AccountNumber;

    return AccountNumber;


}
void ShowDeleteClientScreen()
{
    cout << "\n---------------------------------------------------------\n";
    cout << "\t Delete Client Screen";
    cout << "\n---------------------------------------------------------\n";

    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber,vClients);
}
void ShowUpdateClientScreen()
{
    cout << "\n---------------------------------------------------------\n";
    cout << "\t Update Client Screen";
    cout << "\n---------------------------------------------------------\n";

    vector <sClient>  vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    cout << "\n---------------------------------------------------------\n";
    cout << "\t Add New Clients Screen";
    cout << "\n---------------------------------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n---------------------------------------------------------\n";
    cout << "\t Find Client Screen";
    cout << "\n---------------------------------------------------------\n";

    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else {
        cout << "\n client with AccountNumber (" << AccountNumber << ") is not found!";
    }

}
void ShowEndScreen()
{
    cout << "\n---------------------------------------------------------\n";
    cout << "\t Program Ends :-) ";
    cout << "\n---------------------------------------------------------\n";
}
enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient=2,
    eDeleteClient=3, eUpdateClient=4,
    eFindClient=5, eExit=6

};
void GoBackToMainMenue()
{
    cout << "\n\n press any key to go back to main menue...";
    system("pause>0");
    ShowMainMenue();
}
short ReadMainMenueOption()
{
    cout << " choose what do you want to do ? [1 to 6] ?";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        GoBackToMainMenue();
        break;

    }
}
void ShowMainMenue()
{
    system("cls");
    cout << "====================================================================\n";
    cout << "\t Main Mainue Screen \n";
    cout << "====================================================================\n";
    cout << "\t [1] Show Client List. \n"; 
    cout << "\t [2] Add New Client. \n";
    cout << "\t [3] Delete Client. \n";
    cout << "\t [4] Update Client Info. \n";
    cout << "\t [5] Find Client. \n";
    cout << "\t [6] Exit. \n";
    cout << "====================================================================\n";

    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
int main()
{
    ShowMainMenue();
    system("pause>0");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
