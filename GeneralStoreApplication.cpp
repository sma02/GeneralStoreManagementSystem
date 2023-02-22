#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
using namespace std;

// prototypes
void init();
void Login();
void addUser();
void removeUser();
void printLogo();
void printMenuItems(int offset, string items[], int arraySize);
void printCurrentMenuAndUserType(string menuName);
void printBill(int productsInOrderCount);
void printStringColumn(int x, int y, string title, string items[], int arraySize, int padding);
void printIntColumn(int x, int y, string title, int items[], int arraySize, int padding);
void printFloatColumn(int x, int y, string title, float items[], int arraySize, string extraInfo, int padding);
double calculateTotalPayable(int productsInOrderCount);
void productAdd();
void productRemove();
void processProductManagement();
void productList();
void productUpdateHandle(int choice, int productLocation);
void processNewOrder();
void halt();
void viewNetProfit();
void gotoxy(int x, int y);
void logout();
void handleAdmin();
void handleCashier();
void processAdmin(int choice);
void processCashier(int choice);
void errorEmptyString(string item);
void errorLessThanZero(string item);
void errorDisplay(string error);
// file related functions
void storeProducts();
void loadProducts();
// utilities
void printTitle(string text, int paddng, short color);
void printPadding(int x, int y, int length, int width, short color);
void setColor(short color);
void setFontSize();
int getConsoleHeight();
int getConsoleWidth();
void consoleCursor(bool visibility);
string getStringAtxy(short int x, short int y);
string takeStringInput(string message);
int takeIntInput(string message);
bool isValidIntInput(int input);
bool isValidFloatInput(float input);
float takeFloatInput(string message);
bool takeYesNoQuestion(string message);
bool isPresent(string data, string array[], int arraySize);
int searchIndex(string data, string array[], int arraySize);
int takeChoice(int offset, int size, short color);
void movePointer(int previousPos, int pointerPos, int offset, short color);

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
    "View list of products and their quantities",
    "New order",
    "logout..."};

string productEditMenu[] = {
    "Change Product name",
    "update cost price",
    "update profit percentage needed",
    "update quantity in inventory",
    "back..."};
// Products
#define NoOfProducts 100
int currentNumberOfProducts = 0;
string productNames[NoOfProducts];
float productCostPrice[NoOfProducts];
float productProfitPercentage[NoOfProducts];
float productRetailPrice[NoOfProducts];
int productQuantity[NoOfProducts];

// order details
string productsInOrderNames[NoOfProducts];
int productInOrderQuantities[NoOfProducts];

// login info
#define NoOfUsers 20
string usernames[NoOfUsers] = {"admin"};
string passwords[NoOfUsers] = {"pass123"};
int roles[NoOfUsers] = {0};
int usersRegistered = 1;

// Globals
int consoleWidth;
int consoleHeight;
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
            handleAdmin();
        }
        while (role == 1)
        {
            handleCashier();
        }
    }
}
void init()
{
    consoleCursor(false);
    consoleWidth = getConsoleWidth();
    consoleHeight = getConsoleHeight();
    loadProducts();
}
void printTitle(string text, int paddng, short color)
{
    setColor((color / 16 % 16) + color);
    for (int i = 0; i < paddng; i++)
    {
        cout << "*";
    }
    setColor(color);
    cout << text;
    setColor((color / 16 % 16) + color);
    for (int i = 0; i < paddng; i++)
    {
        cout << "*";
    }
}
void printPadding(int x, int y, int length, int width, short color)
{
    setColor((color / 16 % 16) + color);
    for (int j = 0; j < width; j++)
    {
        gotoxy(x, y + j);
        for (int i = 0; i < length; i++)
        {
            cout << "*";
        }
    }
}
void printLogo()
{
    system("cls");
    printPadding(0, 0, consoleWidth, 3, 0x50);
    gotoxy((consoleWidth - 32) / 2, 1);
    printTitle("General Store Management system", 1, 0x50);
    setColor(0x7);
    gotoxy(0, 4);
}
void printMenuItems(int offset, string items[], int arraySize)
{
    setColor(0x3);
    gotoxy(0, offset);
    for (int i = 1; i <= arraySize; i++)
    {
        cout << "  " << i << ".\t" << items[i - 1] << endl;
    }
    setColor(0x7);
}
void printBill(int productsInOrderCount)
{
    int productIndex = -1;
    double price = 0;
    float productInOrderPrices[productsInOrderCount];
    for (int i = 0; i < productsInOrderCount; i++)
    {
        productIndex = searchIndex(productsInOrderNames[i], productNames, currentNumberOfProducts);
        productInOrderPrices[i] = productInOrderQuantities[i] * productCostPrice[productIndex] * (100 + productProfitPercentage[productIndex]) / 100;
    }
    printLogo();
    printStringColumn(2, 5, "Product", productsInOrderNames, productsInOrderCount, 20);
    printIntColumn(30, 5, "Quantity", productInOrderQuantities, productsInOrderCount, 20);
    printFloatColumn(45, 5, "Price", productInOrderPrices, productsInOrderCount, "Rs", 20);

    // gotoxy(0, 22);
    cout << endl;
    if (takeYesNoQuestion("Order confirmed"))
    {
        setColor(0xa);
        cout << "Price payable: " << calculateTotalPayable(productsInOrderCount) << "Rs" << endl;
        getch();
        setColor(0x7);
    }
}
double calculateTotalPayable(int productsInOrderCount)
{
    int productIndex;
    double pricePayable;
    for (int i = 0; i < productsInOrderCount; i++)
    {
        productIndex = searchIndex(productsInOrderNames[i], productNames, currentNumberOfProducts);
        pricePayable += productInOrderQuantities[i] * productCostPrice[productIndex] * (100 + productProfitPercentage[productIndex]) / 100;
        netProfit += (productProfitPercentage[productIndex] * productCostPrice[productIndex] * productInOrderQuantities[i]) / 100;
        productQuantity[productIndex] -= productInOrderQuantities[i];
    }
    return pricePayable;
}
void printStringColumn(int x, int y, string title, string items[], int arraySize, int padding)
{
    int count = 0;
    gotoxy(x, y);
    printTitle(title, padding, 0x30);
    setColor(0x6);
    for (int i = 0; i < arraySize; i++)
    {
        gotoxy(x + (title.length() + (padding * 2) - items[i].length()) / 2, i + y + 2);
        cout << items[i];
        count++;
    }
    setColor(0x7);
}
void printIntColumn(int x, int y, string title, int items[], int arraySize, int padding)
{
    int count = 0;
    gotoxy(x, y);
    printTitle(title, padding, 0x30);
    setColor(0x6);
    for (int i = 0; i < arraySize; i++)
    {
        gotoxy(x + (title.length() + padding) / 2, i + y + 2);
        cout << items[i];
        count++;
    }
    setColor(0x7);
}
void printFloatColumn(int x, int y, string title, float items[], int arraySize, string extraInfo, int padding)
{
    int count = 0;
    gotoxy(x, y);
    printTitle(title, padding, 0x30);
    setColor(0x6);
    for (int i = 0; i < arraySize; i++)
    {
        gotoxy(x + (title.length() + padding) / 2, i + y + 2);
        cout << items[i] << extraInfo;
        count++;
    }
    setColor(0x7);
}
void printCurrentMenuAndUserType(string menuName)
{
    gotoxy(0, 3);
    cout << "  " << menuName;
    gotoxy(80 - 20, 3);
    cout << "User Type: ";
    if (role == 0)
    {
        setColor(0x4);
        cout << "Admin";
    }
    else
    {
        setColor(0x2);
        cout << "Cashier";
    }
    gotoxy(0, 4);
    setColor(0x02);
    for (int i = 0; i < 80; i++)
    {
        cout << "_";
    }
    gotoxy(0, 5);
}
string takeStringInput(string message)
{
    string input;
    setColor(0x2);
    consoleCursor(true);
    cout << "Enter the " << message << ": ";
    setColor(0x6);
    cin.sync();
    getline(cin, input);
    cin.sync();
    setColor(0x7);
    consoleCursor(false);
    return input;
}
int takeIntInput(string message)
{
    int input;
    setColor(0x2);
    consoleCursor(true);
    cout << "Enter the " << message << ": ";
    setColor(0x6);
    if (!(cin >> input))
    {
        cin.ignore();
        input = -1;
    }
    setColor(0x7);
    consoleCursor(false);
    return input;
}
float takeFloatInput(string message)
{
    float input;
    setColor(0x2);
    consoleCursor(true);
    cout << "Enter the " << message << ": ";
    setColor(0x6);
    if (!(cin >> input))
    {
        cin.ignore();
        input = -1;
    }
    setColor(0x7);
    consoleCursor(false);
    return input;
}
bool takeYesNoQuestion(string message)
{
    int option;
    setColor(0x3);
    cout << message << "?[press Y or N]: " << endl;
    setColor(0x7);
    while (1)
    {
        int option = getch();
        if (option == 'y' || option == 'Y')
        {
            return true;
        }
        else if (option == 'n' || option == 'N')
        {
            return false;
        }
    }
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
    setColor(0xc);
    cout << "Error:";
    setColor(0xe);
    cout << error << endl;
    setColor(0x7);
    cout << "Press any key to continue..." << endl;
    getch();
    cin.clear();
    cin.sync();
}
void errorLessThanZero(string item)
{
    string actualError = "Invalid input for " + item;
    errorDisplay(actualError);
}
void errorEmptyString(string item)
{
    string actualError = item + " cannot be empty!";
    errorDisplay(actualError);
}
void halt()
{
    cout << "Press any key to continue..." << endl;
    getch();
    cin.sync();
}
void viewNetProfit()
{
    int x = 40, y = 10;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Net Profit");
    gotoxy(x - 12, y);
    printTitle("Net Profit", 1, 0x20);
    printPadding(x, y, 8, 1, 0x60);
    gotoxy(x + 1, y);
    setColor(0x60);
    cout << netProfit << " Rs";
    setColor(0x7);
    getch();
}
// file related function
void storeProducts()
{
    fstream file;
    file.open("products.txt", ios::out);
    for (int i = 0; i < currentNumberOfProducts; i++)
    {
        file << productNames[i] <<'\0';
        file << productCostPrice[i] << endl;
        file << productQuantity[i] << endl;
        file << productProfitPercentage[i] << endl;
    }
    file.close();
}
void loadProducts()
{
    fstream file;
    file.open("products.txt", ios::in);
    int i = 0;
    while (!file.eof())
    {
          getline(file,productNames[i],'\0');
         
        file >> productCostPrice[i];
        file >> productQuantity[i];
        file >> productProfitPercentage[i];
        i++;
    }
    file.close();
    i--;
    currentNumberOfProducts = i;
}
void productList()
{
    printLogo();
    printStringColumn(consoleWidth / 32, consoleHeight / 5, "product", productNames, currentNumberOfProducts, consoleWidth / 32);
    printIntColumn(9 * consoleWidth / 32, consoleHeight / 5, "Quantity Present", productQuantity, currentNumberOfProducts, consoleWidth / 32);
    if (role == 0)
    {
        printFloatColumn(19 * consoleWidth / 32, consoleHeight / 5, "cost Price", productCostPrice, currentNumberOfProducts, "Rs", consoleWidth / 32);
        printFloatColumn(27 * consoleWidth / 32, consoleHeight / 5, "Profit", productProfitPercentage, currentNumberOfProducts, "%", consoleWidth / 32);
    }
    else
    {
        printFloatColumn(19 * consoleWidth / 32, consoleHeight / 5, "Retail price", productRetailPrice, currentNumberOfProducts, "Rs", consoleWidth / 32);
    }
    cin.sync();
}
void productAdd()
{

    int count = 0;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Product Add");
    string productName = takeStringInput("name of product");
    if (productName == "")
    {
        errorEmptyString("product name");
        return;
    }
    else if (searchIndex(productName, productNames, currentNumberOfProducts) != -1)
    {
        errorDisplay("product already exists!");
        return;
    }
    float costPrice = takeFloatInput("unit cost price");
    if (costPrice < 0)
    {
        errorLessThanZero("cost price");
        return;
    }
    float profitPercentage = takeFloatInput("percentage of profit desired on product");
    if (profitPercentage < 0)
    {
        errorLessThanZero("profit percentage");
        return;
    }
    int quantity = takeIntInput("current quantity of product in inventory");
    if (quantity < 0)
    {
        errorLessThanZero("quantity");
        return;
    }
    productNames[currentNumberOfProducts] = productName;
    productCostPrice[currentNumberOfProducts] = costPrice;
    productProfitPercentage[currentNumberOfProducts] = profitPercentage;
    productRetailPrice[currentNumberOfProducts] = costPrice * (100 + profitPercentage) / 100;
    productQuantity[currentNumberOfProducts] = quantity;
    currentNumberOfProducts++;
}
void productRemove()
{
    int productLocation = -1;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Product Remove");
    string product = takeStringInput("name of product to remove");
    if (product == "")
    {
        errorEmptyString("name of product");
    }
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
            productRetailPrice[i] = productRetailPrice[i + 1];
        }
        currentNumberOfProducts--;
    }
}
void processNewOrder()
{
    string product;
    int productsInOrderCount = 0;
    int quantity;
    int productIndex = -1;
    int productInOrderIndex = -1;
    bool running = true;
    double pricePayable = 0;
    int option;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>New Order");
    while (running)
    {
        product = takeStringInput("name of product");
        productIndex = searchIndex(product, productNames, currentNumberOfProducts);
        if (productIndex == -1)
        {
            running = takeYesNoQuestion("Another item");
            continue;
        }
        quantity = takeIntInput("quantity");
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
        productInOrderIndex = searchIndex(product, productsInOrderNames, productsInOrderCount);
        if (productInOrderIndex == -1)
        {
            productsInOrderNames[productsInOrderCount] = product;
            productInOrderQuantities[productsInOrderCount] = quantity;
            productsInOrderCount++;
        }
        else if (productQuantity[productIndex] < (productInOrderQuantities[productInOrderIndex] + quantity))
        {
            errorDisplay("not enough quantity present in inventory!");
            continue;
        }
        else
        {
            productInOrderQuantities[productInOrderIndex] += quantity;
        }
        running = takeYesNoQuestion("Another item");
    }
    printBill(productsInOrderCount);
}
void productUpdateHandle(int choice, int productLocation)
{
    printLogo();
    if (choice == 0)
    {
        string productName = takeStringInput("new product name");
        if (productName == "")
        {
            errorDisplay("product name cannot be empty");
            return;
        }
        productNames[productLocation] = productName;
    }
    else if (choice == 1)
    {
        float costPrice = takeFloatInput("new cost price");
        if (costPrice <= 0)
        {
            errorDisplay("invalid cost price");
            return;
        }
        productCostPrice[productLocation] = costPrice;
        productRetailPrice[productLocation] = costPrice * (100 + productProfitPercentage[productLocation]) / 100;
    }
    else if (choice == 2)
    {
        float profitPercentage = takeFloatInput("new profit percentage");
        if (profitPercentage < 0)
        {
            errorDisplay("invalid profit percentage");
            return;
        }
        productProfitPercentage[productLocation] = profitPercentage;
        productRetailPrice[productLocation] = productCostPrice[productLocation] * (100 + profitPercentage) / 100;
    }
    else if (choice == 3)
    {
        int quantity = takeIntInput("new product quantity");
        if (quantity < 0)
        {
            errorDisplay("quantity of product cannot be negetive");
            return;
        }
        productQuantity[productLocation] = quantity;
    }
}
void handleCashier()
{
    printLogo();
    printCurrentMenuAndUserType("Main Menu");
    printMenuItems(5, cashierMenu, 3);
    int choice = takeChoice(5, 3, 0x3);
    processCashier(choice);
}
void processCashier(int choice)
{
    if (choice == 0)
    {
        productList();
        getch();
    }
    else if (choice == 1)
    {
        processNewOrder();
    }
    else if (choice == 2)
    {
        logout();
    }
}
void handleAdmin()
{
    printLogo();
    printCurrentMenuAndUserType("Main Menu");
    printMenuItems(5, adminMenu, 8);
    int choice = takeChoice(5, 8, 0x3);
    processAdmin(choice);
}
void processAdmin(int choice)
{
    if (choice == 0)
    {
        productList();
        getch();
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
        processProductManagement();
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
        storeProducts();
        logout();
    }
}
void processProductManagement()
{
    productList();
    int productLocation = takeChoice(7, currentNumberOfProducts, 0x06);
    if (productLocation != -1)
    {
        printLogo();
        printMenuItems(5, productEditMenu, 5);
        int choice = takeChoice(5, 5, 0x03);
        productUpdateHandle(choice, productLocation);
    }
}
void Login()
{
    string username, password;
    printLogo();
    cin.sync();
    int x = consoleWidth / 4;
    int y = consoleHeight / 2;
    gotoxy(x, y);
    printTitle("username", 1, 0x20);
    gotoxy(x, y + 1);
    printTitle("password", 1, 0x20);
    printPadding(x + 10, y, consoleWidth / 3, 2, 0x60);
    gotoxy(x + 11, y);
    setColor(0x60);
    getline(cin, username);
    gotoxy(x + 11, y + 1);
    getline(cin, password);
    setColor(0x7);
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
    printCurrentMenuAndUserType("Main Menu>Add User");
    username = takeStringInput("username for new user");
    if (username == "")
    {
        errorEmptyString("username");
        return;
    }
    else if (isPresent(username, usernames, usersRegistered))
    {
        errorDisplay("Username already registered!");
        return;
    }
    password = takeStringInput("password for user");
    if (password == "")
    {
        errorEmptyString("password");
        return;
    }
    else if (password.length() < 8)
    {
        errorDisplay("length of password cannot be less than 8!");
        return;
    }
    role = takeStringInput("role for user[admin or cashier]");
    if ((role != "admin") && (role != "cashier"))
    {
        errorDisplay("role not found!");
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
    printCurrentMenuAndUserType("Main Menu>Remove User");
    username = takeStringInput("username of the user to remove");
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
int takeChoice(int offset, int size, short color)
{
    int pointerPos = 0;
    int previousPos = 0;
    int key = -1;
    if (size != 0)
    {
        movePointer(previousPos, pointerPos, offset, color);
    }
    else
    {
        getch();
        return key;
    }
    while (1)
    {
        key = getch();
        if (GetAsyncKeyState(VK_UP) && pointerPos > 0)
        {
            previousPos = pointerPos;
            pointerPos--;
            movePointer(previousPos, pointerPos, offset, color);
        }
        else if (GetAsyncKeyState(VK_DOWN) && pointerPos < size - 1)
        {
            previousPos = pointerPos;
            pointerPos++;
            movePointer(previousPos, pointerPos, offset, color);
        }
        if (key > '0' && key <= '9')
        {
            key -= '0';
            if (key <= size)
            {
                key = key - 1;
                break;
            }
        }
        if (key == VK_ESCAPE)
        {
            key = -1;
            break;
        }
        else if (key == VK_RETURN)
        {
            key = pointerPos;
            break;
        }
        Sleep(100);
    }
    setColor(0x7);
    return key;
}
void movePointer(int previousPos, int pointerPos, int offset, short color)
{
    previousPos += offset;
    pointerPos += offset;
    string temp = getStringAtxy(0, previousPos);
    setColor(color);
    gotoxy(0, previousPos);
    cout << temp;
    temp = getStringAtxy(0, pointerPos);
    setColor(0x30);
    gotoxy(0, pointerPos);
    cout << temp;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
string getStringAtxy(short int x, short int y)
{
    char buffer[80];
    COORD position{x, y};
    DWORD dwChars;
    ReadConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, 80, position, &dwChars);
    buffer[dwChars] = '\0';
    string temp = buffer;
    return temp;
}
void consoleCursor(bool visibility)
{
    CONSOLE_CURSOR_INFO ci;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = visibility;
    SetConsoleCursorInfo(stdHandle, &ci);
}
int getConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
void setColor(short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void logout()
{
    someoneLoggedIn = false;
    role = -1;
    currentUser = "";
}