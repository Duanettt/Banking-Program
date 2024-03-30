#include <iostream>
#include <cctype>

void showBalance();
double withdrawMoney();
double depositMoney();
void bankMenu();
void menuChoice();
bool userCreateAccount();
bool logIn();
void logOut();
void bankSystem();


double money;
int choice;
std::string username;
std::string password;
std::string enteredUsername;
std::string enteredPassword;

int main()
{
    bankSystem();
}

void bankSystem()
{
/* If our user has created there account then it will move onto the logIn and if they've successfully logged in
    the function will return true and move onto the bankMenu */
    if (userCreateAccount())
    {
        if (logIn())
        {
            bankMenu();
        }
    }
}

void bankMenu()
{
    std::cout << "// -- Welcome to our Banking System -- //\n";
    std::cout << "Please pick from our three options: \n";
    std::cout << "1. Deposit money\n";
    std::cout << "2. Withdraw money\n";
    std::cout << "3. Show Balance\n";
    std::cout << "4. Log Out\n";
    std::cin >> choice;
    std::cin.ignore();
//  In our bank system user has to input a number between 1-4 to choose between what the user wants to do.
    switch(choice)
    {
        case 1:
            depositMoney();
            break;
        case 2:
            withdrawMoney();
            break;
        case 3:
            showBalance();
            break;
        case 4:
            logOut();
            break;
        default:
            std::cout << "Invalid option, please try again. \n" << std::endl;
            menuChoice();
            break;
    }

}
// Method for choosing a menu once completion of a task is done from the bankMenu.
void menuChoice()
{
    int menuChoice;

    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Return to the menu\n";
    std::cout << "2. Exit banking system\n";
    std::cin >> menuChoice;
    switch(menuChoice)
    {
        case 1:
            bankMenu();
            break;
        case 2:
            std::exit(0);
            break;
    }

}

double withdrawMoney()
{
    double withdrawal;
    char yesOrNo;
    do
    {
        std::cout << "Please input the amount of money you would like to withdraw: ";
        std::cin >> withdrawal;
        std::cout << "Confirmation that you are withdrawing: $" << withdrawal << "\nYes(y)\nNo(n)" << std::endl;
        std::cin >> yesOrNo;
    }
    while(yesOrNo == 'N' || yesOrNo == 'n');

    if(yesOrNo == 'y' || yesOrNo == 'Y')
    {
        if(money > withdrawal)
        {
            money = money - withdrawal;
            std::cout << "You have withdrew: $" << withdrawal << "\n" << std::endl;
            menuChoice();
        }
        else
        {
            std::cout << "Declined withdrawal request. Insufficient funds." << std::endl;
            bankMenu();
        }

    }

    menuChoice();

}


double depositMoney()
{
    double deposit;
    char yesOrNo;
    do
    {
        std::cout << "Please input the amount of money you would like to deposit: ";
        std::cin >> deposit;
        std::cout << "Confirmation that you are depositing: $" << deposit << "\nYes(y)\nNo(n)" << std::endl;
        std::cin >> yesOrNo;
    }
    while(yesOrNo == 'N' || yesOrNo == 'n');

    if(yesOrNo == 'y' || yesOrNo == 'Y')
    {
        std::cout << "You have deposited: $" << deposit << "\n" << std::endl;
        money = money + deposit;
    }

    menuChoice();

}

void showBalance()
{
    std::cout << "Here is your balance: $" << money << "\n" << std::endl;
    bankMenu();
}

bool userCreateUsername()
{
    do
    {
        std::cout << "Enter your username: \n";
        std::getline(std::cin, username);
        if(username.length() < 4)
        {
            std::cout << "Username needs to be longer. Above 4 characters long." << std::endl;
        }
    }while(username.length() < 4);
    return true;
}

bool passwordDigitChecker(const std::string& password)
{
    int digitCount = 2;
    for(char ch : password)
    {
        if(std::isdigit(ch))
        {
            digitCount++;
            if(digitCount >= 2)
            {
                return true;
            }
        }
    }
    return false;
}

bool userCreatePassword()
{
    std::string confirmPassword;
    do {
        std::cout << "Enter your password: \n";
        std::getline(std::cin, password);
        confirmPassword = password;
        if(!passwordDigitChecker(password))
        {
            std::cout << "Password must contain at least two digits." << std::endl;
            continue;
        }
        if(password.length() < 8)
        {
            std::cout << "Incorrect length(greater than 8 characters long), please try again!" << std::endl;
        }
        else
        {
            std::cout << "Confirm your password: \n";
            std::getline(std::cin, confirmPassword);
            if(confirmPassword != password)
            {
                std::cout << "Incorrect, please try again!" << std::endl;
            }
        }
    } while(password.length() < 8 || confirmPassword != password);
    return true;
}

bool userCreateAccount()
{
//    Create account system incorporates a confirmPassword string to always update upon call.
    std::string confirmPassword;
    std::cout << "Welcome to the Create an Account System, Please fill in the following details below: \n";
    bool userCreatedPasswordAndUsername = userCreateUsername() && userCreatePassword();
//  If both of these statements are true then we return
    if(userCreatedPasswordAndUsername)
    {
       return true;
    }
}

bool confirmAccountCredentials(std::string usersEnteredName,std::string usersEnteredPassword)
{
    if(usersEnteredName == username && usersEnteredPassword == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool logIn()
{
//   User enters their personal username and password then information is sent to confirm account function.
    bool credentialsAreCorrect;

    std::cout << "Welcome to the Log In System" << std::endl;
    do
    {
        std::cout << "Enter your username: \n";
        std::getline(std::cin, enteredUsername);
//        std::cout << enteredUsername << "  " << username << std::endl;
        std::cout << "Enter your password: \n";
        std::getline(std::cin, enteredPassword);
//        std::cout << enteredPassword << "  " << password << std::endl;

        credentialsAreCorrect = confirmAccountCredentials(enteredUsername,enteredPassword);
        bool credentialsAreNotCorrect = credentialsAreCorrect == false;

        if(credentialsAreNotCorrect)
        {
            std::cout << "Login failed. Incorrect username or password. Please try again" << std::endl;
        }
    }  while (!credentialsAreCorrect);
    return true;
}

void logOut()
{
    money = 0.0;
    username = "";
    password = "";

    bankSystem();

}
