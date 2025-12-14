#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

////////////////////////////////////////////////////////////////
//
// Function Declarations    
//
////////////////////////////////////////////////////////////////
void SelectOption();
void EmiFormulaImplementation();
void SipFormulaImplementation();
void FormatAmount(double value, char *output);

///////////////////////////////////////////////////////////////
//
// Structure : Emi
// Use : Holds information about EMI calculation
//
///////////////////////////////////////////////////////////////
struct Emi
{
    double Principle;
    double AnnualInterestRate;
    int LoanTenure; // in years 
};

///////////////////////////////////////////////////////////////
//
// Structure : Sip
// Use : Holds information about SIP calculation
//
///////////////////////////////////////////////////////////////
struct Sip
{
    double MonthlyInvestment;
    double AnnualInterestRate;
    int InvestmentTenure; // in years 
};

///////////////////////////////////////////////////////////////
//
// Structure : LoginPage
// Use : Holds information about client login credentials.
//
///////////////////////////////////////////////////////////////
struct LoginPage
{
    char UserName[20];
    char Password[16];
    char FileName[20];
};

///////////////////////////////////////////////////////////////
//
// Function : CustomerAccount
// Use : Customer login with username and password
//
///////////////////////////////////////////////////////////////
void CustomerAccount(struct LoginPage* LoginPage)
{
    FILE *fp;
    char Line[100], FileUser[20], FilePass[16], ch;
    int i = 0, Found = 0;

    fp = fopen("CustomerLogin.txt", "r");

    if (!fp)
    {
        printf("Error opening file..!\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter your UserName: ");
    scanf("%s", LoginPage->UserName);

    printf("Enter your Password: ");

    while (1)
    {
        ch = getch();
        if (ch == 13)  // Enter key
            break;
        else if (ch == 8) // Backspace
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (i < 15)
        {
            LoginPage->Password[i++] = ch;
            printf("*");
        }
    }
    LoginPage->Password[i] = '\0';
    printf("\n");

    // Read file line by line
    while (fgets(Line, sizeof(Line), fp))
    {
        if (sscanf(Line, "%[^,],%s", FileUser, FilePass) == 2)
        {
            if (strcmp(FileUser, LoginPage->UserName) == 0 &&
                strcmp(FilePass, LoginPage->Password) == 0)
            {
                Found = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (Found)
    {
        printf("\nLogin Successful!\n\n");
    }
    else
    {
        printf("\nInvalid Username or Password!\n");
        exit(EXIT_FAILURE);
    }
}

///////////////////////////////////////////////////////////////
//
// Function : FormatAmount
// Use : Format the amount with commas
//
///////////////////////////////////////////////////////////////
void FormatAmount(double value, char *output)
{
    char temp[60];
    int i, j = 0, count = 0, len;

    sprintf(temp, "%.2lf", value);
    len = strlen(temp);

    for (i = len - 1; i >= 0; i--)
    {
        output[j++] = temp[i];

        if (temp[i] == '.')
        {
            count = 0;
            continue;
        }

        count++;

        if ((count == 3 || (count > 3 && (count - 3) % 2 == 0)) &&
            i > 0 && temp[i - 1] != '.')
        {
            output[j++] = ',';
        }
    }

    output[j] = '\0';

    for (i = 0; i < j / 2; i++)
    {
        char ch = output[i];
        output[i] = output[j - i - 1];
        output[j - i - 1] = ch;
    }
}

///////////////////////////////////////////////////////////////
//
// Function : EmiFormulaImplementation
// Use : Calculates EMI and displays details
//
///////////////////////////////////////////////////////////////
void EmiFormulaImplementation()
{
    struct Emi eobj;

    double CalculateEmi, MonthlyInterestRate, CalculatePower, TotalAmount, TotalInterest;
    int N, iOption;

    char EmiStr[60], PrincipleStr[60], InterestStr[60], TotalStr[60];

    printf("Enter the Principle Loan Amount: \n");
    scanf("%lf",&eobj.Principle);

    printf("Enter the Annual Interest Rate: \n");
    scanf("%lf",&eobj.AnnualInterestRate);

    printf("Enter the Loan Tenure(Years): \n");
    scanf("%d",&eobj.LoanTenure);

    // Input validation
    if (eobj.Principle <= 0 || 
        eobj.AnnualInterestRate < 0 || 
        eobj.LoanTenure <= 0)
    {
        printf("\nInvalid input! Please enter valid loan details.\n");
        return;
    }

    // Monthly interest rate
    MonthlyInterestRate = eobj.AnnualInterestRate / 
                          (12.0 * 100.0); 

    // Total number of monthly payments
    N = eobj.LoanTenure * 12;   

    // (1 + R) ^ N using pow()
    CalculatePower = pow(1 + MonthlyInterestRate, N); 

    CalculateEmi = (eobj.Principle * MonthlyInterestRate * CalculatePower) / 
                   (CalculatePower - 1);

    TotalAmount = CalculateEmi * N;
    TotalInterest = TotalAmount - eobj.Principle;

    // Formatted Amount
    FormatAmount(CalculateEmi, EmiStr);
    FormatAmount(eobj.Principle, PrincipleStr);
    FormatAmount(TotalInterest, InterestStr);
    FormatAmount(TotalAmount, TotalStr);

    // Output
    printf("\n================ EMI DETAILS ================\n");
    printf("Monthly EMI         : %s rs\n", EmiStr);
    printf("Principal Amount    : %s rs\n", PrincipleStr);
    printf("Total Interest      : %s rs\n", InterestStr);
    printf("Total Amount Payable: %s rs\n", TotalStr);
    printf("==============================================\n");

    printf("\n\n1. Back to Banking Facilities Calculator\n");
    printf("0. Exit\n");
    printf("Enter your Option\n");
    scanf("%d",&iOption);

    if (iOption == 1)
    {
        system("cls");
        SelectOption();
    }
    else if (iOption == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Invalid Choice");
    }
    
}

///////////////////////////////////////////////////////////////
//
// Function : SipFormulaImplementation
// Use : Calculates SIP returns and displays details
//
///////////////////////////////////////////////////////////////
void SipFormulaImplementation()
{
    struct Sip sobj;

    double InterestRate, PowerValue, FutureValue, InvestedAmount, Returns;
    int Tenure, iOption;

    char MonthlyStr[60], InvestedStr[60], ReturnsStr[60], FutureStr[60];

    printf("Enter the Monthly Investment Amount: \n");
    scanf("%lf",&sobj.MonthlyInvestment);

    printf("Enter the Expected Return Rate: \n");
    scanf("%lf",&sobj.AnnualInterestRate);

    printf("Enter the Time Period (Years): \n");
    scanf("%d",&sobj.InvestmentTenure);

    // Monthly interest rate
    InterestRate = sobj.AnnualInterestRate / (12.0* 100.0);     

    // Total Months
    Tenure = sobj.InvestmentTenure * 12;        

    PowerValue = pow(1 + InterestRate, Tenure);

    FutureValue = sobj.MonthlyInvestment * 
                  ((PowerValue - 1) / InterestRate) * 
                  (1 + InterestRate);

    InvestedAmount = sobj.MonthlyInvestment * Tenure;
    Returns = FutureValue - InvestedAmount;

    // Formatted Amount
    FormatAmount(sobj.MonthlyInvestment, MonthlyStr);
    FormatAmount(InvestedAmount, InvestedStr);
    FormatAmount(Returns, ReturnsStr);
    FormatAmount(FutureValue, FutureStr);

    // Output
    printf("\n=========== SIP CALCULATION RESULT ===========\n");
    printf("Monthly SIP Amount   : %s rs\n", MonthlyStr);
    printf("Total Months         : %d \n", Tenure);
    printf("Invested Amount      : %s rs\n", InvestedStr);
    printf("Total Returns        : %s rs\n", ReturnsStr);
    printf("Final Maturity Value : %s rs\n", FutureStr);
    printf("===============================================\n");

    printf("\n\n1. Back to Banking Facilities Calculator\n");
    printf("0. Exit\n");
    printf("Enter your Option\n");
    scanf("%d",&iOption);

    if (iOption == 1)
    {
        system("cls");
        SelectOption();
    }
    else if (iOption == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Invalid Choice");
    }
}

///////////////////////////////////////////////////////////////
//
// Function : HomePage
// Use : Displays home page and handles login
//
///////////////////////////////////////////////////////////////
void HomePage()
{
    struct LoginPage login;
    int iOption = 0;

    printf("\n=========== Banking Facilities Calculator ===========\n");
    printf("1. Login\n");
    printf("2. Login as Guest\n");
    printf("0. Exit\n");
    printf("Enter the Option: \n");
    scanf("%d",&iOption);
    printf("=====================================================\n");

    if (iOption == 1)
    {
        CustomerAccount(&login);

        printf("\n=========== Banking Facilities Calculator ===========\n");
        printf("1. Calculate EMI\n");
        printf("2. Calculate SIP\n");
        printf("0. Exit\n");
        printf("Enter the Option: \n");
        scanf("%d",&iOption);
        printf("=====================================================\n");

        if (iOption == 1)
        {
            EmiFormulaImplementation();
        }
        else if (iOption == 2)
        {
            SipFormulaImplementation();
        }
        else if (iOption == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Invalid Choice");
        }
    }
    else if (iOption == 2)
    {
        printf("\n=========== Banking Facilities Calculator ===========\n");
        printf("1. Calculate EMI\n");
        printf("2. Calculate SIP\n");
        printf("0. Exit\n");
        printf("Enter the Option: \n");
        scanf("%d",&iOption);
        printf("=====================================================\n");

        if (iOption == 1)
        {
            EmiFormulaImplementation();
        }
        else if (iOption == 2)
        {
            SipFormulaImplementation();
        }
        else if (iOption == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Invalid Choice");
        }
    }
    else if (iOption == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Invalid Choice");
    }
}

///////////////////////////////////////////////////////////////
//
// Function : SelectOption
// Use : Displays menu and navigates to selected option
//
///////////////////////////////////////////////////////////////
void SelectOption()
{
    int iOption = 0;

    printf("\n=========== Banking Facilities Calculator ===========\n");
    printf("1. Calculate EMI\n");
    printf("2. Calculate SIP\n");
    printf("0. Exit\n");
    printf("Enter the Option: \n");
    scanf("%d",&iOption);
    printf("=====================================================\n");

    if (iOption == 1)
    {
        EmiFormulaImplementation();
    }
    else if (iOption == 2)
    {
        SipFormulaImplementation();
    }
    else if (iOption == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Invalid Choice");
    }
}

/////////////////////////////////////////////////////////////////
//
// Function : main
// Use : Entry point of the program
//
/////////////////////////////////////////////////////////////////
int main()
{
    HomePage();
    SelectOption();
   

    return 0;
}

