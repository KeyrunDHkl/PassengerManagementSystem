
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

struct userdetails
{
    char username[30];
    char password[30];
};
class authentication
{
    string authfilename = "authentication.dat";

    string username;
    string password;

public:
    bool login()
    {
        int choice;

        cout << "***ENTER YOUR DESIRED OPTION***" << endl;

        cout << "1.Register as a new user: " << endl;
        cout << "2.LOGIN to the system: " << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            Register();
            break;
        case 2:
            return validate();
            break;
        default:
            break;
        }
        return false;
    }
    void Register()
    {
        fstream fin;
        userdetails user;

        fin.open(authfilename, ios::app | ios::binary);

        cout << "\t***PLEASE CAREFULLY ENTER YOUR CREDINTIALS IN ORDER TO REMEMBER IT WHILE LOGGING TO THE SYSTEM NEXT TIME***\n";
        cout << "\t____________________________________________________________________________________________________________\n";

        cout << "Enter your username: ";
        cin >> user.username;
        cout << "Enter your Password: ";
        cin >> user.password;

        fin.write((char *)&user, sizeof(userdetails));
    }
    bool validate()
    {
        fstream fin;
        fin.open(authfilename, ios::in | ios::binary);
        userdetails user, tempuser;

        cout << "Enter Username: ";
        cin >> user.username;
        cout << "Enter Password: ";
        cin >> user.password;

        while (fin.read((char *)&tempuser, sizeof(userdetails)))
        {
            bool userNameMatched = strcmp(user.username, tempuser.username) == 0;
            bool passwordMatched = strcmp(user.password, tempuser.password) == 0;
            if (userNameMatched && passwordMatched)
            {
                return true;
            }
        }
        return false;
    }
};
struct database
{
    char name[500];
    char destination[500];
    char shift[500];
    int ticketno;
};
class menu
{
    string PassengerDetails = "passenger.txt";

public:
    void insert_record();
    void display_record();
    void search_record();
    void delete_record();
    void update_record();
    void sort_record();
    int choice;
    void selection(menu m)
    {
        do
        {
            cout << "Enter your choice: [1-7]" << endl;
            cout << "1: Insert Passenger Record: " << endl;
            cout << "2: Display passenger Record: " << endl;
            cout << "3: Search passenger Record: " << endl;
            cout << "4: Delete Passenger Record: " << endl;
            cout << "5: Update passenger Record: " << endl;
            cout << "6: Sort passenger Record: " << endl;
            cout << "7: Exit: " << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                m.insert_record();
                break;
            case 2:
                m.display_record();
                break;
            case 3:
                m.search_record();
                break;
            case 4:
                m.delete_record();
                break;
            case 5:
                m.update_record();
                break;
            case 6:
                m.sort_record();
                break;
            case 7:
                exit(0);
            default:
                cout << "Invalid option entered please enter form 1 to 7: ";
                exit(0);
            }
        } while (choice <= 7 && choice > 0);
    }
};
void menu::insert_record()
{
    ofstream file;
    database data;
    file.open(PassengerDetails, ios::binary | ios::app);

    if (!file.is_open())
    {
        cout << "\n\n\tError! Cannot open the file..." << endl;
        return;
    }

    cout << "Enter the ticket Number of the passenger: ";
    cin >> data.ticketno;
    cout << "Enter the name of the passenger: ";
    cin.ignore();
    cin.getline(data.name, 500);
    cout << "Enter the Destination of the passenger: ";
    cin.getline(data.destination, 500);
    cout << "Enter the travelling shift of the passenger: ";
    cin.getline(data.shift, 500);

    file.write((char *)&data, sizeof(data));
    cout << "\t\t***Record Updated Successfully***\n\n";
    file.close();
    display_record();
}
void menu::display_record()
{
    ifstream file;
    database data, temp;
    file.open(PassengerDetails, ios::in | ios::binary);

      if (!file.is_open())
    {
        cout << "\n\n\tError! Cannot open the file..." << endl;
        return;
    }

    cout<<"Ticket NO.\tName\t\tDestination\t\tShift\n";
    while(file.read((char *)&temp, sizeof(temp)))
    {
        cout<<temp.ticketno<<"\t"<<temp.name<<"\t\t"<<temp.destination<<"\t\t"<<temp.shift<<endl;
    }
    file.close();
}
void menu::search_record()
{
    int search, flag = 0;
    database data;
    ifstream file;
    file.open(PassengerDetails, ios::binary | ios::in);
    cout << "\n\tEnter the ticket number of the passenger you want to search: ";
    cin >> search;
    while (file.read((char *)&data, sizeof(data)) && flag == 0)
    {
        if (search == data.ticketno)
        {
            flag = 1;
            cout << "\n\t\tSearch successful, Passenger record found..." << endl;
            cout << "\n\tNAME\tDESTINATION\tTICKET NO\tTRAVELLING SHIFT\n";
            cout << "\n\t" << data.name << "\t" << data.destination << "\t" << data.ticketno << "\t" << data.shift << endl;
        }
    }
    if (flag == 0)
    {
        cout << "\n\n\nNo Record found\n";
    }
    file.close();
}
void menu::delete_record()
{
    int ticketno;
    database data,temp;
    int count = 0, n = 0;

    fstream file(PassengerDetails, ios::in | ios::binary);
    if (!file.is_open())
    {
        cout << "\n\n\tError! Cannot open the file..." << endl;
        return;
    }
    cout << "\n\n\t\tPreviously stored record\n\n";
    display_record();

    cout << "\n\n\tEnter Passenger ticket number which you want to delete: ";
    cin >> ticketno;

    fstream tempfile("newrecord.txt", ios::out | ios::binary | ios::app);
    if (!tempfile.is_open())
    {
        cout << "\n\n\tError! Unable to open the file\n\n";
        return;
    }

    while (file.read((char *) &temp, sizeof(temp)))
    {
        n++;
        if (ticketno != temp.ticketno)
        {
            tempfile.write((char *) &temp, sizeof(temp));
            count++;
        }
    }

    if (count < n)
    {
        cout << "\n\t\tRECORD DELETED SUCCESSFULLY\n";
    }
    else
    {
        cout << "\n\t\tRECORD NOT FOUND\n";
    }
    file.close();
    tempfile.close();
    remove("passenger.txt");
    rename("newrecord.txt", "Passenger.txt");
    display_record();
}
void menu::update_record()
{
    display_record();
    database data;
    int ticketno;
    int flag = 0;
    fstream file;
    fstream tempfile;
    file.open(PassengerDetails, ios::in | ios::out | ios::binary);
    if(!file.is_open())
    {
        cout << "\n\n\tError! Cannot open the file..." << endl;
        return;
    }
    cout << "\n\tEnter the ticketno of the passenger you want to update:";
    cin >> ticketno;
    tempfile.open("newfile.txt", ios::in | ios::out | ios::binary | ios::app);
    if(!tempfile.is_open())
    {
        cout << "\n\n\tError! Cannot open the file..." << endl;
        return;
    }
    while (file.read((char *) &data, sizeof(data))) {
    if (ticketno!=data.ticketno) {
    tempfile.write((char *) &data, sizeof(data));
    } else {
    flag = 1;
    cout << "\n\tNAME\tDESTINATION\tTICKET NO\tTRAVELLING SHIFT\n";
    cout << "\t" << data.name << "\t" << data.destination << "\t" << data.ticketno << "\t" << data.shift << endl;
    cout << "\n\t\tNow Enter the new record\n\n";
    cout << "\n\nUpdated Passenger Name:\n";
    cin.ignore();
    cin.getline(data.name,500);
    cout << "\n\nUpdated Passenger Destination:\n";
    cin.getline(data.destination,500);
    cout << "\n\nUpdated Passenger Travelling Shift:\n";
    cin.getline(data.shift,500);    
    cout << "\n\nUpdated Passenger Ticket NO:\n";
    cin >> data.ticketno;
    tempfile.write((char *) &data, sizeof(data));
    cout << "\n\n\tRecord Updted Successfully*\n";
    }
    }
    if (flag == 0) {
    cout << "\n\t\tError: Record not found...!!!\n\n";
    }
    file.close();
    tempfile.close();
    remove("Passenger.txt");
    rename("newfile.txt", "Passenger.txt");
    display_record();
}
void menu::sort_record()
{
    database temp;
    database arr[50];
    int i, j, k = 0;
    ifstream file;
    file.open("passenger.txt", ios::binary);
    if (!file.is_open())
    {
        cout << "\n\nError! Unable to open the file..." << endl;
        return;
    }
    i = 0;
    while (file.read((char *)&arr[i], sizeof(arr[i])))
    {
        i++, k++;
    }
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k - i - 1; j++)
        {
            if (arr[j].ticketno > arr[j + 1].ticketno)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    cout << "\n\t\tAfter sorting passenger Details!! \n\n";
    for (i = 0; i < k; i++)
    {
        cout << arr[i].ticketno << "\t" << arr[i].name << "\t" << arr[i].destination << "\t" << arr[i].shift << endl;
    }
    file.close();
}
int main()
{
    authentication auth;
    bool loginsuccess = auth.login();
    if (!loginsuccess)
    {
        exit(0);
    }
    cout << "\t\t__________________________________________________\n";
    cout << "\t\t|*****WELCOME TO PASSSENGER MANAGEMENT SYSTEM*****|\n";
    cout << "\t\t--------------------------------------------------\n\n\n";
    menu m1, m2;
    m1.selection(m2);
    return 0;
}