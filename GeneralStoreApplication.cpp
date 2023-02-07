#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

// prototypes
void Login();
void addUser();
void printAdminMenu();
void printLogo();
void printCashierMenu();
int choiceEntered();
int takeChoice(string arr[], int size);
void gotoxy(int x, int y);
void logout();
void processAdmin(int choice);
void processCashier(int choice);
void movePointer(int pointerPos, int previousPos);

// string menus
string adminMenu[] = {
    "View list of products and their quantites",
    "Add a product",
    "remove a product",
    "update quantity of a product",
    "add a user",
    "remove a user",
    "view net profit",
    "logout..."};

string cashierMenu[] = {
    "New order",
    "logout"};

// Products
#define NoOfProducts 100
int currentNumberOfProducts = 0;
string productNames[NoOfProducts];
float productCostPrice[NoOfProducts];
float productProfitPercentage[NoOfProducts];
int productQuantity[NoOfProducts];

// login info
#define NoOfUsers 20
string usernames[NoOfUsers] = {"admin"};
string passwords[NoOfUsers] = {"pass123"};
int roles[NoOfUsers] = {0};
int usersRegistered = 1;

// Globals
bool someoneLoggedIn = false;
string currentUser = "";
int role = -1;

void productList()
{
    system("cls");
    printLogo();
    int count = 0;
    gotoxy(2, 5);
    cout << "Product";
    while (count != currentNumberOfProducts)
    {
        if (productNames[count] != "")
        {
            gotoxy(2, count + 1+5);
            cout << productNames[count];
            count++;
        }
    }
    count = 0;
    gotoxy(20, 5);
    cout << "cost Price";
    while (count != currentNumberOfProducts)
    {
        if (productNames[count] != "")
        {
            gotoxy(20, count + 1+5);
            cout << productCostPrice[count];
            count++;
        }
    }
     count = 0;
    gotoxy(40, 5);
    cout << "Profit";
    while (count != currentNumberOfProducts)
    {
        if (productNames[count] != "")
        {
            gotoxy(40, count + 1+5);
            cout << productProfitPercentage[count]<<"%";
            count++;
        }
    }
        count = 0;
    gotoxy(50, 5);
    cout << "Quantity Present";
    while (count != currentNumberOfProducts)
    {
        if (productNames[count] != "")
        {
            gotoxy(50, count + 1+5);
            cout << productQuantity[count];
            count++;
        }
    }
    cin.get();
    cin.sync();
}

void testingRemoveUser()
{
    cout << "Enter the username to remove a user: ";
    cin.get();
}
void productAdd()
{
    string productName;
    float costPrice, profitPercentage;
    int quantity;
    int count=0;
    printLogo();
    cout << "Enter the name of product: ";
    getline(cin, productName);
    cout << "Enter the unit cost price of product: ";
    cin.sync();
    cin >> costPrice;
    cout << "Enter the percentage of profit desired on product: ";
    cin >> profitPercentage;
    cout << "Enter the current quantity of product in inventory: ";
    cin >> quantity;
    cin.sync();
  for(int i=0;i<NoOfProducts;i++)
  {
    if(productNames[i]=="")
    {
        productNames[i]=productName;
        productCostPrice[i]=costPrice;
        productProfitPercentage[i]=profitPercentage;
        productQuantity[i]=quantity;
        currentNumberOfProducts++;
        return;
    }
  }
}
void testingProductRemove()
{
    cout << "Enter the name of product to remove it: ";
    cin.get();
}
void testingUpdateQuantity()
{
    string blah;
    cout << "Enter the name of product to update: ";
    cin >> blah;
    cout << "Enter the unit cost price of product: ";
    cin >> blah;
    cout << "Enter the percentage of profit desired on product: ";
    cin >> blah;
    cout << "Enter the current quantity of product in inventory: ";
    cin >> blah;
}
void testingNetProfit()
{
    cout << "Net Profit: 1500Rs" << endl;
}
void testingNewOrder()
{
    cout << "Enter the name of product: Bread" << endl;
    cout << "Enter the quantity: 15" << endl;
    cout << "Another item?[press y or n]:y" << endl;
    cout << "Enter the name of product: water bottle" << endl;
    cout << "Enter the quantity: 3" << endl;
    cout << "Another item?[press y or n]:n" << endl;
    cout << "Amount payable: 3000Rs" << endl;
}
void init()
{
    for (int i = NoOfUsers - 1; i >= usersRegistered; i--)
    {
        usernames[i] = "";
        passwords[i] = "";
        roles[i] = -1;
    }
    for (int i = NoOfProducts - 1; i >= currentNumberOfProducts; i--)
    {
        productNames[i] = "";
        productCostPrice[i] = 0;
        productProfitPercentage[i] = 0;
        productQuantity[0] = 0;
    }
}
int main()
{
    init();
    while (1)
    {
        while (!someoneLoggedIn)
        {
            Login();
        }
        while (role == 0)
        {
            processAdmin(takeChoice(adminMenu, 8));
        }
        while (role == 1)
        {
            processCashier(takeChoice(cashierMenu, 2));
        }
    }
    // printAdminMenu();
    // printCashierMenu();
    // choiceEntered();
    // testingProductList();
    // testingProductAdd();
    // testingProductRemove();
    // testingAddUser();
    // testingRemoveUser();
    // testingNetProfit();
    // testingUpdateQuantity();
    // testingNewOrder();
}
void printLogo()
{
    system("cls");
    cout << "*******************************************************************************" << endl;
    cout << "**********************General Store Management Applcation**********************" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}
void processCashier(int choice)
{
    if (choice == 0)
    {
    }
    else if (choice == 1)
    {
        logout();
    }
}
void processAdmin(int choice)
{
    if (choice == 0)
    {
        productList();
    }
    else if (choice == 1)
    {
        productAdd();
    }
    else if (choice == 4)
    {
        addUser();
    }
    else if (choice == 7)
    {
        logout();
    }
}
void printAdminMenu()
{
    cout << "1.\t\tView list of products and their quantites" << endl;
    cout << "2.\t\tAdd a product" << endl;
    cout << "3.\t\tremove a product" << endl;
    cout << "4.\t\tupdate quantity of a product" << endl;
    cout << "5.\t\tadd a user" << endl;
    cout << "6.\t\tremove a user" << endl;
    cout << "7.\t\tview net profit" << endl;
    cout << "8.\t\tlogout..." << endl;
}
void printCashierMenu()
{
    cout << "1.\tNew order" << endl;
    cout << "2.\tlogout" << endl;
}
void Login()
{
    string username, password;
    printLogo();
    cout << "Your username: ";
    getline(cin, username);
    cout << "Your password: ";
    getline(cin, password);
    for (int i = 0; i < NoOfUsers; i++)
    {
        if (username == usernames[i])
        {
            if (password == passwords[i])
            {
                currentUser = usernames[i];
                role = roles[i];
                someoneLoggedIn = true;
            }
        }
    }
}
void addUser()
{
    string username, password, role;
    int freeLocation = 0;
    printLogo();
    cout << "Enter the username for new user: ";
    getline(cin, username);
    cout << "Enter the password for user: ";
    getline(cin, password);
    cout << "Enter the role of user[admin or cashier]: ";
    getline(cin, role);
    for (int i = 0; i < NoOfUsers; i++)
    {
        if (username == usernames[i])
        {
            cout << endl;
            cout << "Error:Username already registered!" << endl;
            cout << "Press Any key to continue...";
            getch();
            return;
        }
    }
    if ((role != "admin") && (role != "cashier"))
    {
        cout << endl;
        cout << "Error:Role not found!" << endl;
        cout << "Press Any key to continue...";
        getch();
        return;
    }
    for (int i = 0; i < NoOfUsers; i++)
    {
        if (roles[i] == -1)
        {
            freeLocation = i;
            break;
        }
    }
    if (role == "admin")
    {
        roles[freeLocation] = 0;
    }
    else if (role == "cashier")
    {
        roles[freeLocation] = 1;
    }
    usernames[freeLocation] = username;
    passwords[freeLocation] = password;
    usersRegistered++;
}
/*int choiceEntered()
{
    int choice=1;
    cout<<endl<<"Enter your choice: ";
    cin>>choice;
    return choice;
}*/
int takeChoice(string arr[], int size)
{
    int pointerPos = 0;
    int previousPos = 0;
    printLogo();
    for (int i = 1; i <= size; i++)
    {
        cout << "  " << i << ".\t" << arr[i - 1] << endl;
    }
    movePointer(previousPos, pointerPos);
    while (1)
    {
        int key = getch();
        if (GetAsyncKeyState(VK_UP) && pointerPos > 0)
        {
            previousPos = pointerPos;
            pointerPos--;
            movePointer(previousPos, pointerPos);
        }
        else if (GetAsyncKeyState(VK_DOWN) && pointerPos < size - 1)
        {
            previousPos = pointerPos;
            pointerPos++;
            movePointer(previousPos, pointerPos);
        }
        if (key > '0' && key <= '9')
        {
            key -= '0';
            if (key <= size)
            {
                return key - 1;
            }
        }
        if (key == VK_ESCAPE)
        {
            return -1;
        }
        else if (key == VK_RETURN)
        {
            return pointerPos;
        }
        Sleep(100);
    }
}
void movePointer(int previousPos, int pointerPos)
{
    previousPos += 4;
    pointerPos += 4;
    gotoxy(0, previousPos);
    cout << "  ";
    gotoxy(0, pointerPos);
    cout << "->";
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void logout()
{
    someoneLoggedIn = false;
    role = -1;
    currentUser = "";
}