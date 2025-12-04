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

struct LoginPage
{
    char UserName[20];
    char Password[16];
    char FileName[20];
};

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
// Function : EmiFormulaImplementation
// Use : Calculates EMI and displays details
//
///////////////////////////////////////////////////////////////
void EmiFormulaImplementation()
{
    struct Emi eobj;

    double CalculateEmi, MonthlyInterestRate, CalculatePower, TotalAmount, TotalInterest;
    int N, iOption;

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

    // Output
    printf("\n================ EMI DETAILS ================\n");
    printf("Monthly EMI         : %.2lf rs\n", CalculateEmi);
    printf("Principal Amount    : %.2lf rs\n", eobj.Principle);
    printf("Total Interest      : %.2lf rs\n", TotalInterest);
    printf("Total Amount Payable: %.2lf rs\n", TotalAmount);
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


    printf("\n=========== SIP CALCULATION RESULT ===========\n");
    printf("Monthly SIP Amount   : %.2lf rs\n", sobj.MonthlyInvestment);
    printf("Total Months         : %d \n", Tenure);
    printf("Invested Amount      : %.2lf rs\n", InvestedAmount);
    printf("Total Returns        : %.2lf rs\n", Returns);
    printf("Final Maturity Value : %.2lf rs\n", FutureValue);
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
