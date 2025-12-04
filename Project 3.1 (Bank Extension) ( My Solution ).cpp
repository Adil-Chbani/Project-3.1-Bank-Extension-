
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
const string NomFile = "Clients.txt";        

enum EnNumberBank 
{
	Show         = 1 ,
	Add          = 2 ,
	Delete       = 3 ,
	Update       = 4 ,
	Find         = 5 ,
	Transactions = 6 ,
	Exit         = 7
};
enum EnTransactions 
{
	Deposit       = 1,
	Withdraw      = 2,
	TotalBalances = 3,
	MainMenue     = 4,
};
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkDelete = false;
};

sClient ReadInformationClient(vector<sClient>& Clients)
{
	sClient info;
	
	
	cout << "Enter Account Number ? ";
	getline(cin >> ws, info.AccountNumber);

		for (sClient& v : Clients)
		{
			while (v.AccountNumber == info.AccountNumber)
			{
				cout << "Client With [A150] alreat , exists , Enter another Account Number ? ";
				getline(cin, info.AccountNumber);
			}
		}

	cout << "Enter PinCode ? ";
	getline(cin, info.PinCode);

	cout << "Enter Name ? ";
	getline(cin, info.Name);

	cout << "Enter Phone ? ";
	getline(cin, info.Phone);

	cout << "Enter AccountBalance ? ";
	cin >> info.AccountBalance;
	return info;
}

string Space(string esp)
{
	return esp;
}
void PrintTracerTable()
{
	cout << "==============================================================\n";
	cout << Space("\t\t\t")<<"Main Menue Screen\n";
	cout << "==============================================================\n";
	cout << Space("\t") << "[1] Show Client List.\n";
	cout << Space("\t") << "[2] Add New Client.\n";
	cout << Space("\t") << "[3] Delete Client.\n";
	cout << Space("\t") << "[4] Update Client Info.\n";
	cout << Space("\t") << "[5] Find Client.\n";
	cout << Space("\t") << "[6] Transactions.\n";
	cout << Space("\t") << "[7] Exit.\n";
	cout << "==============================================================\n";


}
 
vector<string> SplitPhrase(string S1,string Delimiter="#//#")
{
	vector<string>vString;
	int pos = 0;
	string word = "";
	while ((pos = S1.find(Delimiter)) != S1.npos)
	{
		word = S1.substr(0, pos);
		if (word != "")
		{
			vString.push_back(word);
		}
		S1.erase(0, (pos + Delimiter.length()));
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}

sClient FillingStruct(string S1)
{
	sClient client;
	vector<string>vString = SplitPhrase(S1);

	client.AccountNumber = vString[0];
	client.PinCode = vString[1];
	client.Name = vString[2];
	client.Phone = vString[3];
	client.AccountBalance = stod(vString[4]);
	return client;
}

string ConcatString(sClient words,string Delimiter= "#//#")
{
	string Concat = "";
	Concat = words.AccountNumber + Delimiter
		+ words.PinCode + Delimiter
		+ words.Name + Delimiter
		+ words.Phone+ Delimiter
		+ to_string(words.AccountBalance);
	return Concat;
}

vector<sClient> ReadContentFile()
{
	fstream file;
	vector<sClient>vString;
	file.open(NomFile, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			vString.push_back(FillingStruct(line));
		}
	}
	return vString;
}

void FeeHeadTable(vector<sClient>Clients)
{
	cout << Space("\t\t\t\t\t\t") << "Client List ("<< Clients.size()<<") Client(s).";
	cout << "\n______________________________________________________________________________________________________________\n\n";
	cout <<"| "<<left<< setw(20) << "Account Number"
		<< "| " <<left<< setw(15) << "Pin code "
		<< "| " <<left<< setw(40) << "Client Name"
		<< "| " <<left<< setw(15) << "Phone "
		<< "| " <<left<< setw(15) << "Balance" << endl;
	cout << "______________________________________________________________________________________________________________\n\n";
	for (sClient& C : Clients)
	{
		cout <<"| "<<left<<setw(20) << C.AccountNumber
			<< "| " <<left<<setw(15) << C.PinCode
			<< "| " <<left<<setw(40) << C.Name
			<< "| " <<left<<setw(15) << C.Phone
			<< "| " <<left<<setw(15) << C.AccountBalance<<endl;
	}
	cout << "______________________________________________________________________________________________________________\n";

}
void FeeTableTransactionsAndSumTotalBalance(vector<sClient>Clients)
{
	long int Balance = 0;
	cout << Space("\t\t\t\t\t\t") << "Client List (" << Clients.size() << ") Client(s).";
	cout << "\n______________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(20) << "Account Number"
		<< "| " << left << setw(40) << "Client Name"
		<< "| " << left << setw(15) << "Balance" << endl;
	cout << "______________________________________________________________________________________________________________\n\n";
	for (sClient& C : Clients)
	{
		cout << "| " << left << setw(20) << C.AccountNumber
			<< "| " << left << setw(40) << C.Name
			<< "| " << left << setw(15) << C.AccountBalance << endl;
		Balance += C.AccountBalance;
	}
	cout << "______________________________________________________________________________________________________________\n";
	cout << Space("\t\t\t\t\t\t") << "Total Balances = " << Balance << " \n";

}
void UpadatOnFileAtCaseAdd(vector<sClient> Clients)
{
	fstream file;
	file.open(NomFile, ios::out);
	if (file.is_open())
	{
		
		for (sClient& C : Clients)
		{
			if (C.MarkDelete == false)
			{
			file << ConcatString(C)<<endl;
			}
	    }
	}
}

void FunctionSpecialAddNewClients(vector<sClient>& Clients)
{
	sClient Client = ReadInformationClient(Clients);
	string Phrase = ConcatString(Client);
	sClient Result=FillingStruct(Phrase);
	Clients.push_back(Result);
	UpadatOnFileAtCaseAdd(Clients);
}     
string SearchOnClientByNumberAccount(vector<sClient>Clients)
{
	string NumAccount="";
	cout << "Enter Account Number ? ";
	getline(cin>>ws, NumAccount);

	return NumAccount;
}


void PrintInformationOneClient(vector<sClient>& Clients,string NumAccount)
{

		for (sClient& C : Clients)
		{
	if (C.AccountNumber == NumAccount)
	{
	cout << "\nThe following are the client details : \n";
			cout << "\n----------------------------------------------\n";
			cout << "Account Number : " << C.AccountNumber << endl;
			cout << "Pin code      : " << C.PinCode << endl;
			cout << "Client Name   : " << C.Name << endl;
			cout << "Phone         : " << C.Phone << endl;
			cout << "Balance       : " << C.AccountBalance << endl;
			cout << "\n----------------------------------------------\n";
		}
	}
}
bool MarkOnClientYourWantDelete(vector<sClient> &Clients, string NumAccount)
{
	char charvaluer = ' ';
	cout << "\nAre you sure you want delete this client? y/n ? ";
	cin >> charvaluer;
	if (charvaluer == 'Y' || charvaluer == 'y')
	{
	  for (sClient& C : Clients)
	  {
		if (C.AccountNumber == NumAccount)
		{
			C.MarkDelete = true;
			return true;
		}
	  }
	}
	return false;
}
void DeleteClientIsMark(vector<sClient>& Clients, string NumAccount)
{

	bool found = false;
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == NumAccount)
		{

			PrintInformationOneClient(Clients, NumAccount);
			if (MarkOnClientYourWantDelete(Clients, NumAccount))
			{
				found = true;
				UpadatOnFileAtCaseAdd(Clients);
				Clients = ReadContentFile();
				cout << "\nClient Delete Successfully.\n\n";
			}
			else
			{
				cout << "\nnot delete \n\n";
			}
		}
	}
	if (!found)
	{
	cout << "Client with Account Number (" << NumAccount << ") is Not found ! \n";
	}
	
}

bool CheckYourWantUpdate(vector<sClient>& Clients, string NumAccount)
{
	char charvaluer = ' ';
	cout << "\nAre you sure you want Update this client? y/n ? ";
	cin >> charvaluer;
	if (charvaluer == 'Y' || charvaluer == 'y')
	{
		for (sClient& C : Clients)
		{
			if (C.AccountNumber == NumAccount)
			{
				C.AccountNumber = NumAccount;
				cout << "Pin code      : ";
                getline(cin>>ws,C.PinCode);
				cout << "Client Name   : ";
				getline(cin, C.Name);
				cout << "Phone         : ";
				getline(cin, C.Phone);
				cout << "Account Balance: ";
				cin >> C.AccountBalance;
				return true;
			}
		}

	}
	return false;
}

void UpdateInformationOneClient(vector<sClient>& Clients, string NumAccount)
{
	bool found = false;
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == NumAccount)
		{
			PrintInformationOneClient(Clients, NumAccount);
			if (CheckYourWantUpdate(Clients, NumAccount))
			{
				found = true;
				UpadatOnFileAtCaseAdd(Clients);
				Clients = ReadContentFile();
				cout << "\nClient Update Successfully.\n\n";

			}
		}
	}
	if (!found)
	{
		cout << "Client with Account Number (" << NumAccount << ") is Not found ! \n";
	}
}

bool SearchOnClient(vector<sClient> Clients,string NumAccount)
{
	for (sClient& info : Clients)
	{
		if (info.AccountNumber == NumAccount)
		{
			PrintInformationOneClient(Clients, NumAccount);
			return true;
		}

	}
	return false;
}

void LastFunctionSearchClient(vector<sClient> Clients, string NumAccount)
{
	if (!SearchOnClient(Clients, NumAccount))
	{
		cout << "\nthis Client Not Found ! \n";
	}
}

void FunctionFinishProject(string Message)
{
	system("cls");
	cout << "=====================================================\n\n";
	cout <<Space("\t")<< " "<< Message <<" \n\n";
	cout << "=====================================================" << endl;

}

EnNumberBank ChoiceNumberYourlike()
{
	int Number = 0;
	do
	{
		cout << "choose what do you want to do ? [1 to 7] ? ";
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			cout << "Please Enter Number (Ex:1 to 7) : ";
			cin >> Number;
		}
	} while (Number < 1 || Number>7);
	return EnNumberBank(Number);
}
EnTransactions ChoiceNumberTransactions()
{
	int Number = 0;
	do
	{
		cout << "choose what do you want to do ? [1 to 4] ? ";
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Please Enter Number (Ex:1 to 4) : ";
			cin >> Number;
		}
	} while (Number < 1 || Number>4);
	return EnTransactions(Number);
}

bool FunctionDeposit(vector<sClient>& Clients, string& NumAccount, long int& NewBalance, EnTransactions EnInfo)
{
	string value;
	bool repose = true;
	long int BalanceDeposit = 0;
	char character = ' ';
	long int valueFinal = 0;
	for (sClient& C : Clients)
	{
		for (sClient& Cl : Clients)
		{
			if (Cl.AccountNumber == NumAccount)
			{
				repose = false;
				break;
			}
		}
		while (repose)
		{
			    cout << "Client with [" << NumAccount << "] does not exist .\n";
			     value  = SearchOnClientByNumberAccount(Clients);
			for (sClient& A : Clients)
			{
				if (A.AccountNumber == value)
				{
				   repose = false;
					break; 
				}
			}
		}
		if (value == C.AccountNumber || NumAccount == C.AccountNumber)
		{
			(value == C.AccountNumber) ? PrintInformationOneClient(Clients, value) : PrintInformationOneClient(Clients, NumAccount);
			cout << "Please enter deposit amount ? ";
			cin >> BalanceDeposit;
			cout << "\nAre you sure you want delete this client? y/n ? ";
			cin >> character;
			if (character == 'Y' || character == 'y')
			{
				if (EnTransactions::Deposit == EnInfo)
				{
				  C.AccountBalance += BalanceDeposit;
				}
				else
				{
					C.AccountBalance -= BalanceDeposit;
				}
				NewBalance = C.AccountBalance;
				UpadatOnFileAtCaseAdd(Clients);
				return true;
		        break;
			}
		}
	}
	
	return false;
}
void FeeTableSpeailTransaction()
{
	cout << Space("\t") << "[1] Deposit .\n";
	cout << Space("\t") << "[2] Withdraw .\n";
	cout << Space("\t") << "[3] Total Balances .\n";
	cout << Space("\t") << "[4] Main Menue .\n";
	cout << "============================================\n";
	
}



void DepositBalanceOnOldPrice(vector<sClient>& Clients, string NumAccount,EnTransactions EnInfo)
{
	long int NewBalance;
	if (FunctionDeposit(Clients, NumAccount,NewBalance,EnInfo))
	{
		cout << " Successfully , New Balance is : " << NewBalance << "\n";
	}
	else
	{
		cout << "Not Successfully";
	}
}
void ResultFinalProject();
void ResultTransactions()
{
	bool Result = true;
	while (Result)
	{
		system("cls");
		FunctionFinishProject("Transactions Menue Screen");
		FeeTableSpeailTransaction();
		EnTransactions EnInfo = ChoiceNumberTransactions();

		string NumberAccount;

		vector<sClient> values = ReadContentFile();
		switch (EnInfo)
		{
			// Deposit Balance
		case(EnTransactions::Deposit):
		{
			system("cls");
			FunctionFinishProject("Deposit Screen ");
			DepositBalanceOnOldPrice(values, NumberAccount = SearchOnClientByNumberAccount(values),EnInfo);
			system("pause");
			break;
		}
		// Withdrew Balance
		case (EnTransactions::Withdraw):
		{
			system("cls");
			FunctionFinishProject("Withdraw Screen ");
			DepositBalanceOnOldPrice(values, NumberAccount = SearchOnClientByNumberAccount(values), EnInfo);
			system("pause");
			break;
		}
			//Total Balances
		case (EnTransactions::TotalBalances):
		{
			system("cls");
			FeeTableTransactionsAndSumTotalBalance(values);
			system("pause");
			break;
		}
		// Return Menue
		case (EnTransactions::MainMenue):
		{
			Result = false;
			ResultFinalProject();
			break;
		}
		default:
			cout << "not found !";
		}
	}
}

void ResultFinalProject()
{
	bool Result = true;
	while (Result)
	{

		system("cls");
		PrintTracerTable();
		EnNumberBank 	EnInfo = ChoiceNumberYourlike();

		string NumberAccount;
		vector<sClient> values = ReadContentFile();

		switch (EnInfo)
		{
		case(EnNumberBank::Show):
		{
			system("cls");
			FeeHeadTable(values);
			system("pause");
			break;
		}
		case(EnNumberBank::Add):
		{
			FunctionFinishProject("Add New Clients Screen ");
			FunctionSpecialAddNewClients(values);
			system("pause");
			break;

			//2
		}
		case(EnNumberBank::Delete):
		{
			FunctionFinishProject("Delete Client Screen ");
			DeleteClientIsMark(values, NumberAccount = SearchOnClientByNumberAccount(values));
			system("pause");
			break;


		}
		case(EnNumberBank::Update):
		{
			FunctionFinishProject("Update Client Info Screen ");
			UpdateInformationOneClient(values, NumberAccount = SearchOnClientByNumberAccount(values));
			system("pause");
			break;

			//4
		}
		case(EnNumberBank::Find):
		{
			FunctionFinishProject("Find Client Screen ");
			LastFunctionSearchClient(values, NumberAccount = SearchOnClientByNumberAccount(values));
			system("pause");
			break;

			//5
		}
		case(EnNumberBank::Transactions):
		{
			ResultTransactions();
			system("pause");
			break;
			//6
		}
			
		
		case(EnNumberBank::Exit):
		{
			Result = false;
			FunctionFinishProject("Program Ends : -)");
			system("pause");
			break;

			//7
		}
		default:
			cout << "verifie your Number {1 to 6 } (-_-)\n";
			break;

		}

	}
}

int main()
{
	ResultFinalProject();
	return 0;
}
