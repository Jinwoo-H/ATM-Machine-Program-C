//Created by Jinwoo Hong

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STANDARD DEFINITIONS TO PROVIDE CROSS PLATFORM clear screen and pause commands
#if defined(_WIN32) || defined(_WIN64)
    #define clrscr() system("cls")
    #define pause() system("pause")
#else
    #define clrscr() printf("\x1B[1;1H\x1B[2J")
    #define pause() fflush(stdout); system("read -r -p \"Press any key to continue...\" key")
#endif

typedef struct //Profile Struct
{
    char userName[50];
    char pin[30];
    char firstName[30];
    char lastName[30];
    float balance;
} Profile;

//##################################################### MENU FUNCTION #######################################################

int menu()
{
    char option[50];
    int validChoice = 0;

    do
    {
        printf("Thank you for visiting Jinwoo's ATM\n");
        printf("-------------------------------------\n\n\n");
        printf("What would you like to do today?\n\n");
        printf("1) Login to account\n");
        printf("2) Create Account\n");
        printf("3) Exit\n");

        scanf("%s", option);

        if (!strcmp(option, "1")) //User chooses to manage their account
        {
            clrscr();
            return 1;
        }
        else if (!strcmp(option, "2")) //User chooses to create an account
        {
            clrscr();
            return 2;
        }
        else if (!strcmp(option, "3")) //User chooses to exit program
        {
            exit(1);
        }
        else
        {
            printf("Please enter an appropriate response\n");
            pause();
            clrscr();
        }

    } while (validChoice == 0); //Loops if user inputs invalid response

    return 0; //Just so there is not warning of control reaching end of non-void function
}

//##################################################### MAIN FUNCTION #####################################################

int main()
{
    //Variable Declaration
    int option;
    char amountUser[3];
    int intAmountUser;
    int j;
    int finalLoop;
    //^^^ Variable Declaration

    FILE *fp; //Checks if program can open file
    fp = fopen("profiles.txt", "r");

    if (fp == NULL){
        printf("Could not access file");
        exit(1);
    }

    fclose(fp);

    Profile profile[100];

    //fgets(amountUser,sizeof(amountUser), fp); //First line of file shows how many registered profiles
    //intAmountUser = atoi(amountUser); //Converts to integer for ease of use

    //for (j=0 ; j<intAmountUser; j++) //Scans the current data in the file and stores it into a struct
    //{
      //  fscanf(fp, "%s %s %s %s %f", profile[j].userName, profile[j].pin, profile[j].firstName, profile[j].lastName, &profile[j].balance);
    //}

    //fclose(fp); //Close file for now

    do //Menu and options are looped to allow for reuse withouth re-running code;
    {
        fp = fopen("profiles.txt", "r"); //Scans one more time to be provided with most recent information when the loop is repeated
        fgets(amountUser,sizeof(amountUser), fp); //First line of file shows how many registered profiles
        intAmountUser = atoi(amountUser); //Converts to integer for ease of use

        for (j=0 ; j<intAmountUser ; j++)
        {
            fscanf(fp, "%s %s %s %s %f", profile[j].userName, profile[j].pin, profile[j].firstName, profile[j].lastName, &profile[j].balance);
        }
        fclose(fp);

        option = menu(); //Menu function
        finalLoop = 0;
        //Account Creation Variable Declaration
        char newUsername[100];
        char newPin[30];
        char newFirstName[100];
        char newLastName[100];
        int invalidInput = 1;
        int i;
        int validPin = 0;
        //Account Creation Variable Declaration

        if (option == 2)
        {


    // ENTER USERNAME
            //printf("Account Creation\n");
            //printf("----------------\n\n\n");
            do
            {
                invalidInput = 0;
                printf("Account Creation\n");
                printf("----------------\n\n\n");
                printf("Enter your username (Maximum of 30 characters)\n"); //Even though there are many more spaces in the array, I put a cap to prevent errors
                memset(newUsername, 0, sizeof(newUsername));
                scanf("%s", newUsername);

                for (int t=0 ; t<intAmountUser ; t++)
                {
                    if(!strcmp(profile[t].userName, newUsername))
                    {
                        printf("Username is already taken\n");
                        pause();
                        clrscr();
                        invalidInput = 1;

                    }
                }

                if (newUsername[29] != '\0'){ //If the 30th character is not NULL, the username is too long
                    printf("\n\n--------------------\n");
                    printf("Username is too long\n\n");
                    //memset(newUsername, 0, sizeof(newUsername)); //Clears the array so next input is not clogged
                    invalidInput = 1;
                    pause();
                    clrscr();
                    //printf("Account Creation\n");
                    //printf("----------------\n\n\n");
                }
                else { //If the input is not invalid
                    strcpy(profile[intAmountUser].userName, newUsername); //Copies the string value into the struct
                    //invalidInput = 0; //Breaks condition for the loop
                    clrscr();
                }

            } while (invalidInput == 1);

    //ENTER USERNAME^^^

    //ENTER PIN

            invalidInput = 1;

            printf("Account Creation\n");
            printf("----------------\n\n\n");

            do
            {
                validPin = 0; //This is a counter that increases whenever the character of the input is a number
                printf("Enter your 4 digit pin\n");
                memset(newPin, 0, sizeof(newPin));
                scanf("%s", newPin);

                for (i=0 ; i<4 ; i++){
                    if (newPin[i] >= '0' && newPin[i] <= '9') //If the input is a number from 0 - 9
                    {
                        validPin++; //Increase counter +1
                    }
                    else //If input is not a number
                    {
                        validPin = 0; //Reset counter
                    }
                }

                if (newPin[4] != '\0') //If there is a fifth digit or character in the input
                {
                    validPin = 0; //Reset counter
                }

                if (validPin == 4) //If the counter is 4, it means that the input is a four digit number
                {
                    strcpy(profile[intAmountUser].pin, newPin);
                    invalidInput = 0; //Breaks condition for the loop
                    clrscr();
                }
                else
                {
                    printf("Your pin may only be a four digit number\n");
                    pause();
                    clrscr();
                    printf("Account Creation\n");
                    printf("----------------\n\n\n");

                }

            } while (invalidInput == 1);

    //ENTER PIN^^^

    //ENTER FIRST NAME

            invalidInput = 1;



            do
            {
                printf("Account Creation\n");
                printf("----------------\n\n\n");
                printf("Enter your first name (Maximum of 30 characters\n");
                memset(newFirstName, 0, sizeof(newFirstName));
                scanf("%s", newFirstName);

                if (newFirstName[29] != '\0'){ //If the 30th character is not NULL, the name is too long
                    printf("\n\n--------------------\n");
                    printf("First name is too long\n\n");
                    //memset(newFirstName, 0, sizeof(newFirstName)); //Clears the array so next input is not clogged
                    invalidInput = 1;
                    pause();
                    clrscr();
                    //printf("Account Creation\n");
                    //printf("----------------\n\n\n");
                }
                else { //If the input is not invalid
                    strcpy(profile[intAmountUser].firstName, newFirstName); //Copies the string value into the struct
                    invalidInput = 0; //Breaks condition for the loop
                    clrscr();
                }

            } while (invalidInput == 1);

    //ENTER FIRST NAME ^^^

    //ENTER LAST NAME

            invalidInput = 1;


            do
            {
                printf("Account Creation\n");
                printf("----------------\n\n\n");
                printf("Enter your last name (Maximum of 30 characters)\n");
                memset(newLastName, 0, sizeof(newLastName));
                scanf("%s", newLastName);

                if (newLastName[29] != '\0'){ //If the 30th character is not NULL, the name is too long
                    printf("\n\n--------------------\n");
                    printf("Last name is too long\n\n");
                    //memset(newLastName, 0, sizeof(newLastName)); //Clears the array so next input is not clogged
                    invalidInput = 1;
                    pause();
                    clrscr();
                    //printf("Account Creation\n");
                    //printf("----------------\n\n\n");
                }
                else { //If the input is not invalid
                    strcpy(profile[intAmountUser].lastName, newLastName); //Copies the string value into the struct
                    invalidInput = 0; //Breaks condition for the loop
                    clrscr();
                }

            } while (invalidInput == 1);

    //ACCOUNT CREATION COMPLETE

            float signUpBonus = 100.00; //$100 sign up bonus is added opon creating an account
            profile[intAmountUser].balance = signUpBonus;
            intAmountUser++; //Index value goes up one after account creation is complete
            printf("Thank you for creating an account!\n");
            printf("----------------------------------\n\n");
            printf("As a sign up reward, $100 has been added to your balance!\n\n\n");

            //Overwriting all of the data with new information
            fp = fopen("profiles.txt", "w+");
            //fprintf("%i\n", intAmountUser);
            int x;
            fprintf(fp, "%i\n", intAmountUser);

            for (x=0 ; x<intAmountUser; x++)
            {
                fprintf(fp, "%s %s %s %s %f\n", profile[x].userName, profile[x].pin, profile[x].firstName, profile[x].lastName, profile[x].balance);
            }

            fclose(fp);
            pause();
        }

        if (option == 1)
        {
            //Login Variables
            char loginUser[100];
            char loginPin[100];
            int accountFound;
            int z;
            int correctPin;
            //Login Variables ^^^

    //######################################################ACCOUNT LOGIN######################################################



            do
            {
                printf("Account Login\n");
                printf("-------------\n\n\n");
                accountFound = 0;
                printf("Enter your username\n");
                memset(loginUser, 0, sizeof(loginUser));
                scanf("%s", loginUser);
                for (z=0 ; z<intAmountUser ; z++) //for each profile
                {
                    if (!strcmp(profile[z].userName, loginUser)) //Checks if inputted username matches one in the file
                    {
                        accountFound = 1; //If the user input matches with one of the files, usernames, the while loop condition is broken and the loop is also broken
                        break;
                    }
                    else
                    {
                        accountFound = 0; //No account found

                    }
                }
                if (accountFound == 0)
                {
                    printf("Account not found\n");
                    pause();
                    clrscr();
                }

            } while (accountFound == 0);

            clrscr();


            do
            {
                printf("Account Login\n");
                printf("-------------\n\n\n");
                correctPin = 0;
                printf("Enter your four digit pin\n");
                memset(loginPin, 0, sizeof(loginPin));
                scanf("%s", loginPin);

                if (!strcmp(profile[z].pin, loginPin)) //If the inputted pin matches the one of the profile
                {
                    correctPin = 1; //Breaks condition of loop
                    break;
                }

                else
                {
                    correctPin = 0;
                    printf("Incorrect password\n");
                    pause();
                    clrscr();
                }

            } while (correctPin == 0);

    //ACCOUNT MENU

            //Variable Declaration
            char menuChoose[100];
            int validMenuOption;
            char withdraw[50];
            float floatWithdraw;
            int validWithdraw;
            char confirmWithdraw[100];
            int completeWithdraw;
            char deposit[50];
            int validDeposit;
            char confirmDeposit[100];
            int completeDeposit;
            float floatDep;
            //Variable Declaration ^^^


            clrscr();
            validMenuOption = 0;

            do
            {
                printf("Welcome back %s %s! What would you like to do today?\n\n", profile[z].firstName, profile[z].lastName);
                printf("Your Balance: %.2f\n", profile[z].balance);
                printf("--------------------\n\n");
                printf("1) Deposit Money\n");
                printf("2) Withdraw Money\n");

                scanf("%s", menuChoose);
                clrscr();

                if(!strcmp(menuChoose, "1")) //#################################### Deposit ####################################
                {
                    //printf("How much money would you like to deposit?\n");
                    validMenuOption = 1;
                    do
                    {
                        validDeposit = 0;
                        printf("How much money would you like to deposit? (Max $1000.00)\n");
                        memset(deposit, 0, sizeof(deposit));
                        scanf("%s", deposit);
                        floatDep = atof(deposit); //Turns string value into float
                        if (floatDep <= 0 || floatDep > 1000) //If deposit amount is less or equal to 0 or more than 1000
                        {
                            printf("Please enter a valid amount\n");
                            validDeposit = 0;
                            pause();
                            clrscr();
                        }
                        else
                        {
                            validDeposit = 1; //Valid deposit amount

                            do
                            {
                                printf("Are you sure you want to deposit %.2f? (Y/N)\n", floatDep);
                                memset(confirmDeposit, 0, sizeof(confirmDeposit));
                                scanf("%s", confirmDeposit);
                                if(!strcmp(confirmDeposit, "Y") || !strcmp(confirmDeposit, "y")) //If input is Y or y
                                {
                                    completeDeposit = 1;
                                    validDeposit = 1;
                                    profile[z].balance += floatDep; //Deposit amount is added to the profiles balance
                                }
                                else if (!strcmp(confirmDeposit, "N") || !strcmp(confirmDeposit, "n")) //If input is N or n
                                {
                                    completeDeposit = 0;
                                    validDeposit = 0;
                                    clrscr();
                                }
                                else
                                {
                                    printf("Please enter a valid response (Y/N)\n"); //If the response is nt Y, y, N, or n
                                    pause();
                                    clrscr();
                                }
                            } while (completeDeposit == 0);

                        }

                    } while (validDeposit == 0);
                }


                else if (!strcmp(menuChoose, "2")) //#################################### Withdraw ####################################
                {
                    validMenuOption = 1;
                    do
                    {
                        validWithdraw = 0;
                        printf("How much money would you like to withdraw?\n");
                        memset(withdraw, 0, sizeof(withdraw));
                        scanf("%s", withdraw);
                        floatWithdraw = atof(withdraw); //Turns string value into float
                        if (floatWithdraw > profile[z].balance)
                        {
                            printf("You have an unsufficient balance to withdraw this amount\n");
                            pause();
                            clrscr();
                        }
                        else
                        {
                            validWithdraw = 1;
                            do
                            {
                                completeWithdraw = 0;
                                printf("Are you sure you want to withdraw %.2f? (Y/N)\n", floatWithdraw);
                                memset(confirmWithdraw, 0, sizeof(confirmWithdraw));
                                scanf("%s", confirmWithdraw);
                                if(!strcmp(confirmWithdraw, "Y") || !strcmp(confirmWithdraw, "y"))
                                   {
                                       completeWithdraw = 1;
                                       validWithdraw = 1;
                                       profile[z].balance -= floatWithdraw; //Subtracts withdraw amount from profiles balance
                                   }
                                else if (!strcmp(confirmWithdraw, "N") || !strcmp(confirmWithdraw, "n"))
                                    {
                                        completeWithdraw = 0;
                                        validWithdraw = 0;
                                        clrscr();
                                    }
                                else
                                {
                                    printf("Please enter a valid response (Y/N)\n");
                                    pause();
                                    clrscr();
                                }
                            } while (completeWithdraw == 0);

                        }
                    } while (validWithdraw == 0);


                }
                else //If you didn't choose 1 to dep or 2 to withdraw
                {
                    printf("Please enter a valid response\n");
                    pause();
                    clrscr();
                }
            } while (validMenuOption == 0);

            fp = fopen("profiles.txt", "w+"); //Re-write information back into file
            fprintf(fp, "%i\n", intAmountUser);
            for (int g=0 ; g<intAmountUser ; g++)
            {
                fprintf(fp, "%s %s %s %s %f\n", profile[g].userName, profile[g].pin, profile[g].firstName, profile[g].lastName, profile[g].balance);
            }
            fclose(fp);
        }
        char lastOption[50];
        int choice;
        clrscr();

        do
        {
            choice = 0;
            printf("What would you like to do now?\n");
            printf("------------------------------\n\n\n");
            printf("1) Go to start menu\n");
            printf("2) Exit\n");
            memset(lastOption, 0, sizeof(lastOption));
            scanf("%s", lastOption);

            if(!strcmp(lastOption, "1")) //Input is 1
            {
                clrscr();
                choice = 1;
                finalLoop = 1; //Makes loop to the beginning condition is true
            }
            else if (!strcmp(lastOption, "2")) //Input is 2
            {
                exit(1);
            }
            else
            {
                printf("Please input a valid response\n"); //Input is not 1 or 2
                choice = 0;
                pause();
                clrscr();
            }
        } while (choice == 0);

    } while (finalLoop == 1);

    return 0;
}
