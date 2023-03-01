#include <iostream>
#include <iosfwd>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <wincon.h>
#include <time.h>
#include <thread>
using namespace std;

// prototypes
void init();
void Login();
void addUser();
void removeUser();
void changePassword();
void printLogo();
void printMenuItems(int offset, string items[], int arraySize);
void printCurrentMenuAndUserType(string menuName);
void printBill(int productsInOrderCount);
void printSalesRecord();
void printPricePayable(double pricePayable);
void drawCashiersPerformanceGraph();
void printStringColumn(int x, int y, string title, string items[], int arraySize, int padding);
void printIntColumn(int x, int y, string title, int items[], int arraySize, int padding);
void printFloatColumn(int x, int y, string title, float items[], int arraySize, string extraInfo, int padding);
double calculateTotalPayable(int productsInOrderCount);
double calculateTotalCostPrice(int productsInOrderCount);
void swapProduct(int firstProductIndex, int secondProductIndex);
void productAdd();
void productRemove();
void processProductManagement();
void printProductList();
int processProductQuantity(int productLocation);
void productUpdateHandle(int choice, int productLocation);
void processNewOrder();
void halt();
void viewNetProfit();
void gotoxy(int x, int y);
void logout();
void handleAdmin();
void handleCashier();
void handleUserManagement();
void handleStats();
void processAdmin(int choice);
void processCashier(int choice);
void processUserManagement(int choice);
void processStats(int choice);
bool errorDisplay(string error);
// file related functions
void storeUsers();
void storeProducts();
void storeBasicStats();
void storeSalesRecord();
void loadProducts();
void loadUsers();
void loadBasicStats();
void loadSalesRecord();
// utilities
void printTitle(string text, int paddng, short color);
void printPadding(int x, int y, int length, int width, short color);
void setColor(short color);
int getCursorX();
int getCursorY();
int getConsoleHeight();
int getConsoleWidth();
void consoleCursor(bool visibility);
void ProductSort(string arr[], int arraysize);
string getStringAtxy(short int x, short int y);
bool takeStringInput(string message, string &str);
string parseData(string line, int fieldNumber);
bool takeIntInput(string message, int &data);
bool takeFloatInput(string message, float &data);
bool takeYesNoQuestion(string message);
int searchIndex(string data, string array[], int arraySize);
int takeChoice(int offset, int size, short color);
void movePointer(int previousPos, int pointerPos, int offset, short color);
void eraseInput();
void printDateAndTime();
void addToRecord(double totalCostPrice, double totalSellPrice);
void handleTimeUpdate(bool flag);
string getCurrentDate();
string getCurrentTime();
string getCurrentDateAndTime();
bool takeLine(string &str);
int getCurrentMinute();
char takech();
// string menus
string adminMenu[] = {
    "View list of products and their quantites",
    "Add a product",
    "remove a product",
    "update quantity of a product",
    "User Management",
    "Statistics",
    "logout..."};

string cashierMenu[] = {
    "View list of products and their quantities",
    "New order",
    "change password",
    "logout..."};

string productEditMenu[] = {
    "Change Product name",
    "update cost price",
    "update profit percentage needed",
    "update quantity in inventory",
    "back..."};

string userManageMenu[] = {
    "View All users",
    "Add a user",
    "remove a user",
    "change password for your account",
    "back..."};

string statsMenu[] = {
    "View net profit",
    "Sales record",
    "Cashiers performance graph",
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
string usernames[NoOfUsers];
string passwords[NoOfUsers];
string roles[NoOfUsers];
int orderTakenByCashier[NoOfUsers];
int usersRegistered = 0;

// Record Variables
string orderDate[100];
string orderTime[100];
string orderCashierUserName[100];
float orderTotalCostPrice[100];
float orderTotalSellPrice[100];
int currentRecordCount = 0;
// Globals
int consoleWidth;
int consoleHeight;
bool someoneLoggedIn = false;
string currentUser = "";
string currentUserPassword = "";
string role = "";
int currentMinute = 0;
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
        while (role == "admin")
        {
            handleAdmin();
        }
        while (role == "cashier")
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
    loadUsers();
    if (usersRegistered == 0)
    {
        usernames[0] = "default";
        passwords[0] = "something";
        roles[0] = "admin";
        orderTakenByCashier[0] = -1;
        usersRegistered++;
    }
    loadProducts();
    loadBasicStats();
    loadSalesRecord();
}
void printDateAndTime()
{
    int x = getCursorX();
    int y = getCursorY();
    setColor(0x3);
    gotoxy(1, 0);
    cout << getCurrentDate();
    gotoxy(consoleWidth - 9, 0);
    cout << getCurrentTime();
    setColor(0x7);
    gotoxy(x, y);
}
void printTitle(string text, int paddng, short color)
{
    setColor((color / 16 % 16) * 17);
    for (int i = 0; i < paddng; i++)
    {
        cout << "*";
    }
    setColor(color);
    cout << text;
    setColor((color / 16 % 16) * 17);
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
    printDateAndTime();
    printPadding(0, 1, consoleWidth, 3, 0x50);
    gotoxy((consoleWidth - 32) / 2, 2);
    printTitle("General Store Management system", 2, 0x50);
    setColor(0x7);
    gotoxy(0, 5);
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
    printStringColumn(consoleWidth / 32, 5, "Product", productsInOrderNames, productsInOrderCount, 5 * consoleWidth / 32);
    printIntColumn(17 * consoleWidth / 32, 5, "Quantity", productInOrderQuantities, productsInOrderCount, consoleWidth / 32);
    printFloatColumn(27 * consoleWidth / 32, 5, "Price", productInOrderPrices, productsInOrderCount, " Rs", consoleWidth / 32);
    cout << endl;
}
double calculateTotalPayable(int productsInOrderCount)
{
    int productIndex;
    double pricePayable = 0;
    for (int i = 0; i < productsInOrderCount; i++)
    {
        productIndex = searchIndex(productsInOrderNames[i], productNames, currentNumberOfProducts);
        pricePayable += productInOrderQuantities[i] * productCostPrice[productIndex] * (100 + productProfitPercentage[productIndex]) / 100;
        netProfit += (productProfitPercentage[productIndex] * productCostPrice[productIndex] * productInOrderQuantities[i]) / 100;
        productQuantity[productIndex] -= productInOrderQuantities[i];
    }
    return pricePayable;
}
double calculateTotalCostPrice(int productsInOrderCount)
{
    int productIndex;
    double totalCostPrice = 0;
    for (int i = 0; i < productsInOrderCount; i++)
    {
        productIndex = searchIndex(productsInOrderNames[i], productNames, currentNumberOfProducts);
        totalCostPrice += productInOrderQuantities[i] * productCostPrice[productIndex];
    }
    return totalCostPrice;
}
void printStringColumn(int x, int y, string title, string items[], int arraySize, int padding)
{
    int count = 0;
    gotoxy(x, y);
    printTitle(title, padding, 0x30);
    setColor(0x6);
    for (int i = 0; i < arraySize; i++)
    {
        gotoxy(x, i + y + 2);
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
        gotoxy(x - 1 + (title.length() + 2 * padding) / 2, i + y + 2);
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
        gotoxy(x - 1 + (title.length() + 2 * padding) / 2, i + y + 2);
        cout << items[i] << extraInfo;
        count++;
    }
    setColor(0x7);
}
void printCurrentMenuAndUserType(string menuName)
{
    gotoxy(0, 4);
    cout << "  " << menuName;
    gotoxy(24 * consoleWidth / 32, 4);
    cout << "User Type: ";
    if (role == "admin")
    {
        setColor(0x4);
        cout << "Admin";
    }
    else
    {
        setColor(0x2);
        cout << "Cashier";
    }
    gotoxy(0, 5);
    setColor(0x02);
    for (int i = 0; i < consoleWidth; i++)
    {
        cout << "_";
    }
    gotoxy(0, 6);
}
void swapProduct(int firstProductIndex, int secondProductIndex)
{
    string tempProductName = productNames[firstProductIndex];
    int tempProductQuantity = productQuantity[firstProductIndex];
    float tempProductCostPrice = productCostPrice[firstProductIndex];
    float tempProductRetailPrice = productRetailPrice[firstProductIndex];
    float tempProductProfitPercentage = productProfitPercentage[firstProductIndex];
    productNames[firstProductIndex] = productNames[secondProductIndex];
    productQuantity[firstProductIndex] = productQuantity[secondProductIndex];
    productCostPrice[firstProductIndex] = productCostPrice[secondProductIndex];
    productRetailPrice[firstProductIndex] = productRetailPrice[secondProductIndex];
    productProfitPercentage[firstProductIndex] = productProfitPercentage[secondProductIndex];
    productNames[secondProductIndex] = tempProductName;
    productQuantity[secondProductIndex] = tempProductQuantity;
    productCostPrice[secondProductIndex] = tempProductCostPrice;
    productRetailPrice[secondProductIndex] = tempProductRetailPrice;
    productProfitPercentage[secondProductIndex] = tempProductProfitPercentage;
}
void ProductSort(string arr[], int arraysize)
{
    for (int i = 0; i < arraysize; i++)
    {
        for (int j = 0; j < arraysize ; j++)
        {
            if (arr[j] > arr[i])
            {
                swapProduct(i, j);
            }
        }
    }
}
void eraseInput()
{
    int position=getCursorY();
    setColor(0);
    gotoxy(0, position-3);
    for (int i = position-3; i < position; i++)
    {
        cout << getStringAtxy(0, i);
    }
    gotoxy(0, position-3);
}
bool isFloat(string str)
{
    char *ptr;
    strtof(str.c_str(), &ptr);
    return *ptr == '\0';
}
bool isInt(string str)
{
    if (!(isdigit(str[0]) || str[0] == '+' || str[0] == '-'))
    {
        return false;
    }
    for (int i = 1; i < str.length() - 1; i++)
    {

        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
bool takeStringInput(string message, string &str)
{
    bool status;
    str = "";
    while (1)
    {
        setColor(0x2);
        consoleCursor(true);
        cout << "Enter the " << message << ": ";
        setColor(0x6);
        status = takeLine(str);
        setColor(0x7);
        consoleCursor(false);
        if (str == "" && status)
        {
            if (errorDisplay(message + " can't be empty!"))
            {
                return false;
            }
            eraseInput();
        }
        else if (!status)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
bool takeIntInput(string message, int &data)
{
    while (1)
    {
        string tempInput;
        if (!takeStringInput(message, tempInput))
        {
            return false;
        }
        if (isInt(tempInput))
        {
            data = stoi(tempInput);
            if (data < 0)
            {
                if (errorDisplay(message + " can't be less than zero!"))
                {
                    return false;
                }
                eraseInput();
            }
            else
            {
                return true;
            }
        }
        else
        {
            if (errorDisplay("invalid value for " + message))
            {
                return false;
            }
            eraseInput();
        }
    }
    return true;
}
bool takeFloatInput(string message, float &data)
{
    while (1)
    {
        string tempInput;
        if (!takeStringInput(message, tempInput))
        {
            return false;
        }
        if (isFloat(tempInput))
        {
            data = stof(tempInput);
            if (data < 0)
            {
                if (errorDisplay(message + " can't be less than zero!"))
                {
                    return false;
                }
                eraseInput();
            }
            else
            {
                return true;
            }
        }
        else
        {
            if (errorDisplay("invalid value for " + message))
            {
                return false;
            }
            eraseInput();
        }
    }
    return true;
}
bool takeYesNoQuestion(string message)
{
    int option;
    setColor(0x3);
    cout << message << "?[press Y or N]: " << endl;
    setColor(0x7);
    while (1)
    {
        int option = takech();
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
bool errorDisplay(string error)
{
    int key = 0;
    int x = getCursorX();
    int y = getCursorY();
    setColor(0xc);
    cout << "Error:";
    setColor(0xe);
    cout << error << endl;
    setColor(0x7);
    cin.clear();
    cin.sync();
    cout << "Press Enter to continue or Escape to abort operation..." << endl;
    while (1)
    {
        key = takech();
        if (key == VK_RETURN)
        {
            return false;
        }
        if (key == VK_ESCAPE)
        {
            return true;
        }
    }
}
void halt()
{
    cout << "Press any key to continue..." << endl;
    takech();
    cin.sync();
}
void viewNetProfit()
{
    int x = consoleWidth/2, y = consoleHeight/2;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Statistics>Net Profit");
    gotoxy(x - 12, y);
    printTitle("Net Profit", 1, 0x20);
    printPadding(x, y, 8, 1, 0x60);
    gotoxy(x + 1, y);
    setColor(0x60);
    cout << netProfit << " Rs";
    setColor(0x7);
}
// file related function
void storeUsers()
{
    fstream file;
    file.open("users.txt", ios::out);
    if (file)
    {
        for (int i = 0; i < usersRegistered; i++)
        {
            file << usernames[i] << ',';
            file << passwords[i] << ',';
            file << roles[i] << ',';
            file << orderTakenByCashier[i];
            file << endl;
        }
    }
    file.close();
}
void storeProducts()
{
    fstream file;
    file.open("products.txt", ios::out);
    if (file)
    {
        for (int i = 0; i < currentNumberOfProducts; i++)
        {
            file << productNames[i] << ',';
            file << productCostPrice[i] << ',';
            file << productQuantity[i] << ',';
            file << productProfitPercentage[i] << endl;
        }
    }
    file.close();
}
void storeBasicStats()
{
    fstream file;
    file.open("basicStats.txt", ios::out);
    if (file)
    {
        file << netProfit << endl;
    }
    file.close();
}
void storeSalesRecord()
{
    fstream file;
    file.open("purchaseRecord.txt", ios::app);
    if (file)
    {
        file << orderDate[currentRecordCount] << ',';
        file << orderTime[currentRecordCount] << ',';
        file << orderCashierUserName[currentRecordCount] << ',';
        file << orderTotalCostPrice[currentRecordCount] << ',';
        file << orderTotalSellPrice[currentRecordCount] << endl;
    }
    file.close();
}
void loadUsers()
{
    fstream file;
    string temp;
    file.open("users.txt", ios::in);
    while (getline(file, temp))
    {
        usernames[usersRegistered] = parseData(temp, 1);
        passwords[usersRegistered] = parseData(temp, 2);
        roles[usersRegistered] = parseData(temp, 3);
        if (roles[usersRegistered] == "cashier")
        {
            orderTakenByCashier[usersRegistered] = stoi(parseData(temp, 4));
        }
        else
        {
            orderTakenByCashier[usersRegistered] = -1;
        }
        usersRegistered++;
    }
}
void loadProducts()
{
    fstream file;
    string temp;
    file.open("products.txt", ios::in);
    while (getline(file, temp))
    {
        productNames[currentNumberOfProducts] = parseData(temp, 1);
        productCostPrice[currentNumberOfProducts] = stof(parseData(temp, 2));
        productQuantity[currentNumberOfProducts] = stoi(parseData(temp, 3));
        productProfitPercentage[currentNumberOfProducts] = stof(parseData(temp, 4));
        productRetailPrice[currentNumberOfProducts] = productCostPrice[currentNumberOfProducts] * (100 + productProfitPercentage[currentNumberOfProducts]) / 100;
        currentNumberOfProducts++;
    }
    file.close();
}
void loadBasicStats()
{
    fstream file;
    string temp;
    file.open("BasicStats.txt", ios::in);
    if (file)
    {
        getline(file, temp);
        netProfit = stod(temp);
    }
    file.close();
}
void loadSalesRecord()
{
    fstream file;
    string temp;
    file.open("purchaseRecord.txt", ios::in);
    if (file)
    {
        while (getline(file, temp))
        {
            orderDate[currentRecordCount] = parseData(temp, 1);
            orderTime[currentRecordCount] = parseData(temp, 2);
            orderCashierUserName[currentRecordCount] = parseData(temp, 3);
            orderTotalCostPrice[currentRecordCount] = stof(parseData(temp, 4));
            orderTotalSellPrice[currentRecordCount] = stof(parseData(temp, 5));
            currentRecordCount++;
        }
    }
    file.close();
}
string parseData(string line, int fieldNumber)
{
    int initialPos = 0;
    int finalPos = 0;
    int fieldCount = 0;
    string result = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            fieldCount++;
            if (fieldNumber != fieldCount)
            {
                initialPos = i + 1;
            }
            else
            {
                finalPos = i;
            }
        }
        else if (i == line.length() - 1)
        {
            fieldCount++;
            finalPos = i + 1;
        }
        if (fieldNumber == fieldCount)
        {
            for (int j = initialPos; j < finalPos; j++)
            {
                result += line[j];
            }
            return result;
        }
    }
}
void printProductList()
{
    printLogo();
    printStringColumn(consoleWidth / 32, 5, "product", productNames, currentNumberOfProducts, 2 * consoleWidth / 32);
    printIntColumn(9 * consoleWidth / 32, 5, "Quantity Present", productQuantity, currentNumberOfProducts, consoleWidth / 32);
    if (role == "admin")
    {
        printFloatColumn(19 * consoleWidth / 32, 5, "cost Price", productCostPrice, currentNumberOfProducts, " Rs", consoleWidth / 32);
        printFloatColumn(27 * consoleWidth / 32, 5, "Profit", productProfitPercentage, currentNumberOfProducts, "%", consoleWidth / 32);
    }
    else
    {
        printFloatColumn(19 * consoleWidth / 32, 5, "Retail price", productRetailPrice, currentNumberOfProducts, " Rs", consoleWidth / 32);
    }
}
void usersList()
{
    printLogo();
    printStringColumn(consoleWidth / 32, 5, "Username", usernames, usersRegistered, 5 * consoleWidth / 32);
    printStringColumn(16 * consoleWidth / 32, 5, "Role", roles, usersRegistered, 1 * consoleWidth / 32);
}
void productAdd()
{
    string productName;
    float costPrice, profitPercentage;
    int quantity;
    int count = 0;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Product Add");
    while (1)
    {
        if (!takeStringInput("name of product", productName))
        {
            return;
        }
        else if (searchIndex(productName, productNames, currentNumberOfProducts) != -1)
        {
            if (errorDisplay("product already exists!"))
            {
                return;
            }
            eraseInput();
        }
        else
        {
            break;
        }
    }
    if (!takeFloatInput("unit cost price", costPrice))
    {
        return;
    }
    if (!takeFloatInput("profit percentage on product", profitPercentage))
    {
        return;
    }
    if (!takeIntInput("quantity of product in inventory", quantity))
    {
        return;
    }
    productNames[currentNumberOfProducts] = productName;
    productCostPrice[currentNumberOfProducts] = costPrice;
    productProfitPercentage[currentNumberOfProducts] = profitPercentage;
    productRetailPrice[currentNumberOfProducts] = costPrice * (100 + profitPercentage) / 100;
    productQuantity[currentNumberOfProducts] = quantity;
    currentNumberOfProducts++;
    ProductSort(productNames, currentNumberOfProducts);
    storeProducts();
}
void productRemove()
{
    string product;
    int productLocation = -1;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Product Remove");
    while (1)
    {

        if (!takeStringInput("name of product", product))
        {
            return;
        }
        else
        {
            productLocation = searchIndex(product, productNames, currentNumberOfProducts);
            if (productLocation == -1)
            {
                if (errorDisplay("product does not exist!"))
                {
                    return;
                }
                eraseInput();
            }
            else
            {
                break;
            }
        }
    }
    for (int i = productLocation; i < currentNumberOfProducts; i++)
    {
        productNames[i] = productNames[i + 1];
        productCostPrice[i] = productCostPrice[i + 1];
        productQuantity[i] = productQuantity[i + 1];
        productProfitPercentage[i] = productProfitPercentage[i + 1];
        productRetailPrice[i] = productRetailPrice[i + 1];
    }
    currentNumberOfProducts--;
    storeProducts();
}
void processNewOrder()
{
    int productsInOrderCount = 0;
    int quantity;
    int productInOrderIndex = -1;
    bool running = true;
    double pricePayable = 0;
    int option;
    while (running)
    {
        printProductList();
        int productLocation = takeChoice(7, currentNumberOfProducts, 0x06);

        quantity = processProductQuantity(productLocation);
        if (quantity == -1)
        {
            return;
        }
        productInOrderIndex = searchIndex(productNames[productLocation], productsInOrderNames, productsInOrderCount);
        if (productInOrderIndex == -1)
        {
            productsInOrderNames[productsInOrderCount] = productNames[productLocation];
            productInOrderQuantities[productsInOrderCount] = quantity;
            productsInOrderCount++;
        }
        else if (productQuantity[productLocation] < (productInOrderQuantities[productInOrderIndex] + quantity))
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
    if (takeYesNoQuestion("Order confirmed"))
    {
        double pricePayable = calculateTotalPayable(productsInOrderCount);
        double totalCostPrice = calculateTotalCostPrice(productsInOrderCount);
        addToRecord(totalCostPrice, pricePayable);
        printPricePayable(pricePayable);
        storeProducts();
        storeBasicStats();
    }
}
void addToRecord(double totalCostPrice, double totalSellPrice)
{
    int i = searchIndex(currentUser, usernames, usersRegistered);
    orderTakenByCashier[i]++;
    orderDate[currentRecordCount] = getCurrentDate();
    orderTime[currentRecordCount] = getCurrentTime();
    orderCashierUserName[currentRecordCount] = currentUser;
    orderTotalCostPrice[currentRecordCount] = totalCostPrice;
    orderTotalSellPrice[currentRecordCount] = totalSellPrice;
    storeSalesRecord();
    storeUsers();
    currentRecordCount++;
}
void printPricePayable(double pricePayable)
{
    setColor(0xa);
    cout << "Price payable: " << pricePayable << " Rs" << endl;
    setColor(0x7);
    takech();
}
int processProductQuantity(int productLocation)
{
    int quantity;
    printLogo();
    printCurrentMenuAndUserType("new Order>" + productNames[productLocation] + ">Quantity");
    while (1)
    {
        if (!takeIntInput("Quantity of product", quantity))
        {
            return -1;
        }
        else if (quantity > productQuantity[productLocation])
        {
            if (errorDisplay("not enough quantity present in inventory!"))
            {
                return -1;
            }
            eraseInput();
        }
        else
        {
            return quantity;
        }
    }
    return -1;
}
void productUpdateHandle(int choice, int productLocation)
{
    printLogo();
    if (choice == 0)
    {
        string productName;
        if (!takeStringInput("product name", productName))
        {
            return;
        }
        productNames[productLocation] = productName;
        ProductSort(productNames, currentNumberOfProducts);
    }
    else if (choice == 1)
    {
        float costPrice;
        if (!takeFloatInput("cost price", costPrice))
        {
            return;
        }
        productCostPrice[productLocation] = costPrice;
        productRetailPrice[productLocation] = costPrice * (100 + productProfitPercentage[productLocation]) / 100;
    }
    else if (choice == 2)
    {
        float profitPercentage;
        if (!takeFloatInput("profit percentage", profitPercentage))
        {
            return;
        }
        productProfitPercentage[productLocation] = profitPercentage;
        productRetailPrice[productLocation] = productCostPrice[productLocation] * (100 + profitPercentage) / 100;
    }
    else if (choice == 3)
    {
        int quantity;
        if (!takeIntInput("product quantity", quantity))
        {
            return;
        }
        productQuantity[productLocation] = quantity;
    }
    storeProducts();
}
void handleUserManagement()
{
    int choice = 0;
    while (choice != -1)
    {
        printLogo();
        printCurrentMenuAndUserType("Main Menu>Users Management");
        printMenuItems(6, userManageMenu, 5);

        choice = takeChoice(6, 5, 0x3);
        if (choice > 3)
        {
            choice = -1;
        }
        processUserManagement(choice);
    }
}
void processUserManagement(int choice)
{
    if (choice == 0)
    {
        usersList();
        takech();
    }
    else if (choice == 1)
    {
        addUser();
    }
    else if (choice == 2)
    {
        removeUser();
    }
    else if (choice == 3)
    {
        changePassword();
    }
}
void handleCashier()
{
    printLogo();
    printCurrentMenuAndUserType("Main Menu");
    printMenuItems(6, cashierMenu, 4);
    int choice = takeChoice(6, 4, 0x3);
    processCashier(choice);
}
void processCashier(int choice)
{
    if (choice == 0)
    {
        printProductList();
        takech();
    }
    else if (choice == 1)
    {
        processNewOrder();
    }
    else if (choice == 2)
    {
        changePassword();
    }
    else if (choice == 3)
    {
        logout();
    }
}
void handleAdmin()
{
    printLogo();
    printCurrentMenuAndUserType("Main Menu");
    printMenuItems(6, adminMenu, 7);
    int choice = takeChoice(6, 7, 0x3);
    processAdmin(choice);
}
void handleStats()
{
    int choice = 0;
    while (choice != -1)
    {
        printLogo();
        printCurrentMenuAndUserType("Main Menu>Statistics");
        printMenuItems(6, statsMenu, 3);
        choice = takeChoice(6, 4, 0x3);
        if (choice > 5)
        {
            choice = -1;
        }
        processStats(choice);
    }
}
void processStats(int choice)
{
    if (choice == 0)
    {
        viewNetProfit();
        takech();
    }
    else if (choice == 1)
    {
        printSalesRecord();
        takech();
    }

    else if (choice == 2)
    {
        drawCashiersPerformanceGraph();
        takech();
    }
}
void printSalesRecord()
{
    printLogo();
    printStringColumn(consoleWidth / 32, 5, "Date", orderDate, currentRecordCount, consoleWidth / 32);
    printStringColumn(4 * consoleWidth / 32, 5, "Time", orderTime, currentRecordCount, consoleWidth / 32);
    printStringColumn(15 * consoleWidth / 64, 5, "Cashier Name", orderCashierUserName, currentRecordCount, 3 * consoleWidth / 32);
    printFloatColumn(18 * consoleWidth / 32, 5, "Total Cost Price", orderTotalCostPrice, currentRecordCount, " Rs", consoleWidth / 32);
    printFloatColumn(25 * consoleWidth / 32, 5, "Total Sell Price", orderTotalSellPrice, currentRecordCount, " Rs", consoleWidth / 32);
}
void drawCashiersPerformanceGraph()
{
    int offset = 10;
    int cashierCount = 0;
    int scaleX = 16 * consoleWidth / 32;
    int scaleY = 16 * consoleHeight / 32;
    int totalProcessedOrdersCount = 0;
    string cashiers[100];
    int cashiersOrderCount[100];
    char c254 = 254;
    char c245 = 245;
    char c196 = 196;
    printLogo();
    int maxNameLength = 0;
    for (int i = 0; i < usersRegistered; i++)
    {

        if (roles[i] == "cashier")
        {
            if (usernames[i].length() > maxNameLength)
            {
                maxNameLength = usernames[i].length();
            }
            cashiers[cashierCount] = usernames[i];
            cashiersOrderCount[cashierCount] = orderTakenByCashier[i];
            totalProcessedOrdersCount += orderTakenByCashier[i];
            cashierCount++;
        }
    }
    for (int i = offset; i < scaleY + offset; i++)
    {
        gotoxy(offset + maxNameLength, i);
        cout << c245;
    }
    for (int i = offset; i < scaleX + offset; i++)
    {
        cout << c196;
    }
    setColor(0x3);
    for (int i = 0; i < cashierCount; i++)
    {
        gotoxy(offset + maxNameLength - cashiers[i].length() - 1, (i * scaleY / cashierCount) + offset);
        cout << cashiers[i];
        gotoxy(offset + maxNameLength + 1, (i * scaleY / cashierCount) + offset);
        for (int j = 0; j < scaleX * cashiersOrderCount[i] / totalProcessedOrdersCount; j++)
        {
            cout << c254;
        }
        cout << ' ' << (cashiersOrderCount[i] * 100) / totalProcessedOrdersCount << '%';
    }
}
void processAdmin(int choice)
{
    if (choice == 0)
    {
        printProductList();
        takech();
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
        handleUserManagement();
    }
    else if (choice == 5)
    {
        handleStats();
    }
    else if (choice == 6)
    {
        storeProducts();
        logout();
    }
}
void processProductManagement()
{
    while (1)
    {
        printProductList();
        int productLocation = takeChoice(7, currentNumberOfProducts, 0x06);
        if (productLocation != -1)
        {

            printLogo();
            printCurrentMenuAndUserType("Main Menu>Update product>" + productNames[productLocation]);
            printMenuItems(6, productEditMenu, 5);
            int choice = takeChoice(6, 5, 0x03);
            productUpdateHandle(choice, productLocation);
        }
        else
        {
            return;
        }
    }
}
void Login()
{
    string username, password;
    printLogo();
    cin.sync();
    int x = 10 * consoleWidth / 32;
    int y = 16 * consoleHeight / 32;
    printPadding(7 * consoleWidth / 32, 9 * consoleHeight / 32, 19 * consoleWidth / 32, 16 * consoleHeight / 32, 0x30);
    gotoxy(x, y);
    printTitle("username", 1, 0x27);
    gotoxy(x, y + 1);
    printTitle("password", 1, 0x27);
    printPadding(x + 10, y, 11 * consoleWidth / 32, 2, 0x70);
    gotoxy(x + 11, y);
    setColor(0x70);
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
                currentUserPassword = passwords[i];
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
    printCurrentMenuAndUserType("Main Menu>Users Management>Add User");
    while (1)
    {
        if (!takeStringInput("username", username))
        {
            return;
        }
        else if (searchIndex(username, usernames, usersRegistered)!=-1)
        {
            if (errorDisplay("Username already registered!"))
            {
                return;
            }
            eraseInput();
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if (!takeStringInput("password", password))
        {
            return;
        }
        else if (password.length() < 8)
        {
            if (errorDisplay("length of password cannot be less than 8!"))
            {
                return;
            }
            eraseInput();
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        if (!takeStringInput("role for user", role))
        {
            return;
        }
        else if ((role != "admin") && (role != "cashier"))
        {
            if (errorDisplay("role not found[role must be admin or cashier]!"))
            {
                return;
            }
            eraseInput();
        }
        else
        {
            break;
        }
    }
    usernames[usersRegistered] = username;
    passwords[usersRegistered] = password;
    roles[usersRegistered] = role;
    usersRegistered++;
    storeUsers();
}
void removeUser()
{
    string username;
    int userLocation = 0;
    printLogo();
    printCurrentMenuAndUserType("Main Menu>Users Management>Remove User");
    while (1)
    {
        if (!takeStringInput("username", username))
        {
            return;
        }
        userLocation = searchIndex(username, usernames, usersRegistered);
        if (username == currentUser)
        {
            if (errorDisplay("you cannot delete your own account!"))
            {
                return;
            }
            eraseInput();
        }
        else if (userLocation == -1)
        {
            if (errorDisplay("user does not exist!"))
            {
                return;
            }
            eraseInput();
        }
        else
        {
            break;
        }
    }

    for (int i = userLocation; i < usersRegistered; i++)
    {
        usernames[i] = usernames[i + 1];
        passwords[i] = passwords[i + 1];
        roles[i] = roles[i + 1];
    }
    usersRegistered--;
    storeUsers();
}
void changePassword()
{
    string password;
    printLogo();
    if (role == "admin")
    {
        printCurrentMenuAndUserType("Main Menu>User Management>Change Password");
    }
    else
    {
        printCurrentMenuAndUserType("Main Menu>Change Password");
    }
    while (1)
    {
        if (!takeStringInput("password", password))
        {
            return;
        }
        else if (password.length() < 8)
        {
            if (errorDisplay("length of assword cannot be less than 8!"))
            {
                return;
            }
            eraseInput();
        }
        else if (password == currentUserPassword)
        {
            if (errorDisplay("your previous password cannot be your new password"))
            {
                return;
            }
            eraseInput();
        }
        else
        {
            break;
        }
    }
    currentUserPassword = password;
    int i = searchIndex(currentUser, usernames, usersRegistered);
    passwords[i] = password;
    storeUsers();
    return;
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
        takech();
        return key;
    }
    while (1)
    {
        handleTimeUpdate(false);
        if (kbhit())
        {
            key = getch();
            if (key == 224) // getch() function two values for arrow keys,so discarding first one
            {
                key = getch();
            }
            if (key == 72 && pointerPos == 0)
            {
                previousPos = pointerPos;
                pointerPos = size - 1;
                movePointer(previousPos, pointerPos, offset, color);
            }
            else if (key == 80 && pointerPos == size - 1)
            {
                previousPos = pointerPos;
                pointerPos = 0;
                movePointer(previousPos, pointerPos, offset, color);
            }
            else if (key == 72 && pointerPos > 0)
            {
                previousPos = pointerPos;
                pointerPos--;
                movePointer(previousPos, pointerPos, offset, color);
            }
            else if (key == 80 && pointerPos < size - 1)
            {
                previousPos = pointerPos;
                pointerPos++;
                movePointer(previousPos, pointerPos, offset, color);
            }
            else if (key > '0' && key <= '9')
            {
                key -= '0';
                if (key <= size)
                {
                    key = key - 1;
                    break;
                }
            }
            else if (key == VK_ESCAPE)
            {
                key = -1;
                break;
            }
            else if (key == VK_RETURN)
            {
                key = pointerPos;
                break;
            }
        }
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
bool takeLine(string &str)
{
    char c = 0;
    while (1)
    {
        handleTimeUpdate(true);
        setColor(0x6);
        if (kbhit())
        {
            c = getch();
            if (c == VK_ESCAPE)
            {
                return false;
            }
            else if (c == '\b')
            {
                if (str.length())
                {
                    cout << '\b';
                    cout << ' ';
                    cout << '\b';
                    str.erase(str.size() - 1);
                }
            }
            else if (c == -32)
            {
                getch();
            }
            else if (c == VK_RETURN)
            {
                cout << endl;
                break;
            }
            else
            {
                cout << c;
                str += c;
            }
        }
    }
    return true;
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
int getCursorX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}
int getCursorY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}
string getStringAtxy(short int x, short int y)
{
    char buffer[consoleWidth + 1];
    COORD position{x, y};
    DWORD dwChars;
    ReadConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), buffer, consoleWidth, position, &dwChars);
    buffer[consoleWidth] = '\0';
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
string getCurrentDate()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y", &tstruct);
    return buf;
}
string getCurrentTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%I:%M%p", &tstruct);
    return buf;
}
int getCurrentMinute()
{
    time_t now = time(0);
    return localtime(&now)->tm_min;
}
string getCurrentDateAndTime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}
void logout()
{
    someoneLoggedIn = false;
    role = -1;
    currentUser = "";
}
void handleTimeUpdate(bool flag)
{

    if (currentMinute != getCurrentMinute())
    {
        if (flag)
        {
            consoleCursor(false);
        }
        currentMinute = getCurrentMinute();
        printDateAndTime();
        if (flag)
        {
            consoleCursor(true);
        }
    }
}
char takech()
{
    cin.clear();
    while (1)
    {
        handleTimeUpdate(false);
        if (kbhit())
        {
            return getch();
        }
    }
}