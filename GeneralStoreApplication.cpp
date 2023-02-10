#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

// prototypes
void init();
void Login();
void addUser();
void removeUser();
void printLogo();
void productAdd();
void productRemove();
void productUpdate();
bool isPresent(string data, string array[], int arraySize);
int searchIndex(string data, string array[], int arraySize);
int takeChoice(string arr[], int size);
void processNewOrder();
void halt();
void viewNetProfit();
void errorDisplay(string error);
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
    "View list of products and their quantities",
    "logout..."};

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
double netProfit = 0;


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
            processCashier(takeChoice(cashierMenu, 3));
        }
    }
}
void printLogo()
{
    system("cls");
    cout << "*******************************************************************************" << endl;
    cout << "**********************General Store Management Applcation**********************" << endl;
    cout << "*******************************************************************************" << endl;
    cout << endl;
}
bool isPresent(string data, string array[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (data == array[i])
        {
            return true;
        }
    }
    return false;
}
int searchIndex(string data, string array[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (data == array[i])
        {
            return i;
        }
    }
    return -1;
}
void errorDisplay(string error)
{
    cout << "Error:" << error << endl;
    cout << "Press any key to continue..." << endl;
    getch();
    cin.sync();
}
void halt()
{
    cout << "Press any key to continue..." << endl;
    getch();
    cin.sync();
}
void viewNetProfit()
{
    printLogo();
    cout << "Net Profit: " << netProfit << "Rs" << endl;
    halt();
}
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
            gotoxy(2, count + 1 + 5);
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
            gotoxy(20, count + 1 + 5);
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
            gotoxy(40, count + 1 + 5);
            cout << productProfitPercentage[count] << "%";
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
            gotoxy(50, count + 1 + 5);
            cout << productQuantity[count];
            count++;
        }
    }
    cin.get();
    cin.sync();
}
void productAdd()
{
    string productName;
    float costPrice, profitPercentage;
    int quantity;
    int count = 0;
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
    productNames[currentNumberOfProducts] = productName;
    productCostPrice[currentNumberOfProducts] = costPrice;
    productProfitPercentage[currentNumberOfProducts] = profitPercentage;
    productQuantity[currentNumberOfProducts] = quantity;
    currentNumberOfProducts++;
}
void productRemove()
{
    string product;
    int productLocation = -1;
    printLogo();
    cout << "Enter the name of product to remove it: ";
    cin.sync();
    getline(cin, product);
    cin.sync();
    productLocation = searchIndex(product, productNames, currentNumberOfProducts);
    if (productLocation == -1)
    {
        errorDisplay("product does not exist!");
    }
    else
    {
        for (int i = productLocation; i < currentNumberOfProducts; i++)
        {
            productNames[i] = productNames[i + 1];
            productCostPrice[i] = productCostPrice[i + 1];
            productQuantity[i] = productQuantity[i + 1];
            productProfitPercentage[i] = productProfitPercentage[i + 1];
        }
        currentNumberOfProducts--;
    }
}
void productUpdate()
{
    string productName;
    float costPrice, profitPercentage;
    int quantity;
    int productLocation = -1;
    int count = 0;
    printLogo();
    cout << "Enter the name of product to update: ";
    getline(cin, productName);
    productLocation = searchIndex(productName, productNames, currentNumberOfProducts);
    if (productLocation == -1)
    {
        errorDisplay("product not found!");
        return;
    }
    cout << "Enter the unit cost price of product: ";
    cin.sync();
    cin >> costPrice;
    cout << "Enter the percentage of profit desired on product: ";
    cin >> profitPercentage;
    cout << "Enter the current quantity of product in inventory: ";
    cin >> quantity;
    cin.sync();
    productNames[productLocation] = productName;
    productCostPrice[productLocation] = costPrice;
    productProfitPercentage[productLocation] = profitPercentage;
    productQuantity[productLocation] = quantity;
}
void processNewOrder()
{
    string product;
    int quantity;
    int productIndex = -1;
    bool running = true;
    double pricePayable = 0;
    int option;
    printLogo();
    while (running)
    {
        cin.sync();
        cout << "Enter the name of product: ";
        getline(cin, product);
        productIndex = searchIndex(product, productNames, currentNumberOfProducts);
        if (productIndex == -1)
        {
            errorDisplay("product not present!");
            continue;
        }
        cin.sync();
        cout << "Enter the quantity: ";
        cin >> quantity;
        if (quantity < 0)
        {
            errorDisplay("quantity cannot be negetive!");
            continue;
        }
        else if (quantity > productQuantity[productIndex])
        {
            errorDisplay("not enough quantity present in inventory!");
            continue;
        }
        pricePayable += quantity * productCostPrice[productIndex] * (100 + productProfitPercentage[productIndex]) / 100;
        netProfit += (productProfitPercentage[productIndex] * productCostPrice[productIndex] * quantity) / 100;
        productQuantity[productIndex] -= quantity;
        cout << "Another item?[press Y or N]: " << endl;
        option = getch();
        if (option == 'n' || option == 'N')
        {
            running = false;
        }
    }
    cout << "Price payable: " << pricePayable << "Rs" << endl;
    halt();
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
void processCashier(int choice)
{
    if (choice == 0)
    {
        processNewOrder();
    }
    else if (choice == 1)
    {
        productList();
    }
    else if (choice == 2)
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
    else if (choice == 2)
    {
        productRemove();
    }
    else if (choice == 3)
    {
        productUpdate();
    }
    else if (choice == 4)
    {
        addUser();
    }
    else if (choice == 5)
    {
        removeUser();
    }
    else if (choice == 6)
    {
        viewNetProfit();
    }
    else if (choice == 7)
    {
        logout();
    }
}
void Login()
{
    string username, password;
    printLogo();
    cout << "Your username: ";
    getline(cin, username);
    cout << "Your password: ";
    getline(cin, password);
    for (int i = 0; i < usersRegistered; i++)
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
    if (isPresent(username, usernames, usersRegistered))
    {
        errorDisplay("Username already registered!");
        return;
    }
    if ((role != "admin") && (role != "cashier"))
    {
        cout << endl;
        cout << "Error:Role not found!" << endl;
        cout << "Press Any key to continue...";
        getch();
        return;
    }
    if (role == "admin")
    {
        roles[usersRegistered] = 0;
    }
    else if (role == "cashier")
    {
        roles[usersRegistered] = 1;
    }
    usernames[usersRegistered] = username;
    passwords[usersRegistered] = password;
    usersRegistered++;
}
void removeUser()
{
    string username;
    int userLocation = 0;
    printLogo();
    cout << "Enter the username of the user to remove: ";
    getline(cin, username);
    userLocation = searchIndex(username, usernames, usersRegistered);
    if (username == currentUser)
    {
        errorDisplay("you cannont  delete your own account!");
    }
    else if (userLocation == -1)
    {
        errorDisplay("user does not exist!");
    }
    else
    {
        for (int i = userLocation; i < usersRegistered; i++)
        {
            usernames[i] = usernames[i + 1];
            passwords[i] = passwords[i + 1];
            roles[i] = roles[i + 1];
        }
        usersRegistered--;
    }
}
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