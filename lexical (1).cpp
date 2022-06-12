#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

//**************************************************************************************************** 
string line, without_comment;

void remove_comments()
{
	without_comment = "";
	ofstream wcmnt;

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '~')
		{
			int j = i;
			do
			{
				i++;
				j++;

			} while (line[j] != '~');
		}
		else
			without_comment += line[i];
	}

	line = without_comment;

	wcmnt.open("without_cmnt.txt");

	if (wcmnt.is_open())
	{
		wcmnt << without_comment;
	}

	else
	{
		cout << "\n Error With Opening File \n";
		exit(0);
	}
	wcmnt.close();
}

//**********************************************************************************************************
void print_code()
{
	string a = ""; 					// used to read from file only
	fstream program;

	line = "";

	program.open("program.txt");

	if (program.is_open())
	{
		cout << "\n\n***** Your Entered Program *****\n";
		int i = 1;

		while (!program.eof())
		{
			getline(program, a);  		// reading line by line code from txt file

			line += a;  				// append code in line variable
			line += '\n';  			// add '/n' at the end of every line of code

			cout << "Line " << i << " >> " << a << endl;
			i += 1;
		}
	}
	else
	{
		cout << "Error In Opening The File!\n";
	}
	program.close();
}

//**********************************************************************************************************
void print_code_without_cmnt()
{
	string a = ""; 					// used to read from file only
	fstream program;

	line = "";

	program.open("without_cmnt.txt");

	if (program.is_open())
	{
		cout << "\n\n***** Program Without Comment *****\n";
		int i = 1;

		while (!program.eof())
		{
			getline(program, a);  		// reading line by line code from txt file

			line += a;  				// append code in line variable
			line += '\n';  			// add '/n' at the end of every line of code

			cout << "Line " << i << " >> " << a << endl;
			i += 1;
		}
	}
	else
	{
		cout << "Error In Opening The File!\n";
	}
	program.close();
}

//****************************************************************************************************
bool is_punctuator(char word)
{
	bool flag = false;
	char punctuators[13] = { '{','}','[',']','(',')',':',',','?','\\','#','.',';' };
	for (int i = 0; i < 13; i++)
	{
		if (word == punctuators[i])
		{
			return true;
			break;
		}
	}
	return flag;
}

//**************************************************************************************************
bool is_letter(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}

//**************************************************************************************************
bool is_digit(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return true;
	else
		return false;
}

//***************************************************************************
bool is_delimeter(char ch)
{
	if ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r'))
		return true;
	else
		return false;
}

//****************************************************************************************************
int is_keyword(string str)
{
	string keyword[18] = { "however","else","begin","common","personal","secured","output","input","move","sample","if","loop","elif"
							,"break","continue","do-loop","return","end" };

	string data_type[6] = { "num",    "decimal",    "alpha",    "alphanumeric"   ,"void",    "bool" };
	string boole[2] = { "false",    "true" };

	for (int i = 0; i < 18; i++)
	{
		if (keyword[i] == str)
			return 1;
	}
	for (int i = 0; i < 6; i++)
	{
		if (data_type[i] == str)
			return 2;
	}
	for (int i = 0; i < 2; i++)
	{
		if (boole[i] == str)
			return 3;
	}
	return 0;
}

//******************************************************************************************************
bool is_divmul(char word)
{
	bool flag = false;
	char punctuators[3] = { '*','/','%' };
	for (int i = 0; i < 3; i++)
	{
		if (word == punctuators[i])
		{
			return true;
			break;
		}
	}
	return flag;
}

//******************************************************************************************************
bool is_add_sub(char word)
{
	bool flag = false;
	char punctuators[3] = { '+','-' };
	for (int i = 0; i < 12; i++)
	{
		if (word == punctuators[i])
		{
			return true;
			break;
		}
	}
	return flag;
}

//*******************************************************************************************************
void lexical(string str, int line_no)
{
	int state = 0;
	int i = 0;
	string lexeme = "";
	int flag = 1;
	char c = '\0';

	string tok = ""; 					// used to read from file only
	ofstream token;

	token.open("token.txt");

	while (str[i] != '\0')
	{
		c = str[i];
		flag = 1;

		switch (state)
		{
		case 0:
		{
		go:
			if ((is_letter(c)) || (c == '_'))
			{
				state = 1;
			}

			else if (is_digit(c))
			{
				state = 2;
			}

			else if (is_punctuator(c))
			{
				state = 0;
				lexeme = c;
				cout  << lexeme << " , " << lexeme << " , " << line_no  << endl;
				token  << lexeme << " , " << lexeme << " , " << line_no << endl;
				lexeme = "";
				flag = 0;
			}

			else if (is_divmul(c))
			{
				state = 3;
			}

			else if (is_add_sub(c))
			{
				state = 4;
			}

			else if (c == '=')
			{
				state = 5;
			}

			else if ((c == '>') || (c == '<'))  //ascii for > and <
			{
				state = 6;
			}

			else if (is_delimeter(c))
			{
				flag = 0;
			}

			else if (c == 39) //ascii for " ' "
			{
				state = 8;
			}

			else if (c == 34) //ascii for " "  "
			{
				state = 11;
			}

			else
			{
				cout << lexeme << " Invalid Tokken " << endl;
				token << lexeme << " Invalid Tokken " << endl;
				break;
			}

			break;
		}

		case 1:
		{
			if (!(is_letter(c) || is_digit(c) || c == '_'))
			{

				if (is_keyword(lexeme))
				{
					if (is_keyword(lexeme) == 1)
					{
						cout <<  " KW , " << lexeme << " , " << line_no <<  endl;
						token <<  " KW , " << lexeme << " , " << line_no <<  endl;
					}

					else if (is_keyword(lexeme) == 2)
					{
						cout <<  " DT , " << lexeme << " , " << line_no <<  endl;
						token <<  " DT , " << lexeme << " , " << line_no <<  endl;
					}

					else if (is_keyword(lexeme) == 3)
					{
						cout <<  " Bool , " << lexeme << " , " << line_no <<  endl;
						token <<  " Bool , " << lexeme << " , " << line_no <<  endl;
					}
				}

				else
				{
					cout <<  " Iden , " << lexeme << " , " << line_no <<  endl;
					token <<  " Iden , " << lexeme << " , " << line_no <<  endl;
				}
				state = 0;
				flag = 0;
				lexeme = c;
				goto go;
			}
			break;
		}

		case 2:
		{
			if (!(is_digit(c)))
			{
				state = 0;
				lexeme += c;
				lexeme = lexeme.erase(lexeme.size() - 1);
				cout << "int_const , " << lexeme << " , " << line_no <<  endl;
				token << "int_const , " << lexeme << " , " << line_no <<  endl;
				lexeme = c;
				flag = 0;
				goto go;
			}

			else if (is_digit(c))
			{
				state = 2;
			}

			else if (c == '.')
			{
				state = 7;  //move to state 7 because its float
			}
			break;
		}

		case 3:
		{
			if (c == '=')
			{
				state = 0;
				lexeme += c;
				cout << " AO , " << lexeme << " , " << line_no << endl;
				token << " AO , " << lexeme << " , " << line_no <<  endl;
				lexeme = "";
				flag = 0;
			}
			else
			{
				state = 0;
				cout << "Divmul , " << lexeme << " , " << line_no <<  endl;
				token << "Divmul , " << lexeme << " , " << line_no <<  endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			break;
		}

		case 4:
		{
			if (c == '=')
			{
				state = 0;
				lexeme += c;
				cout << "AO , " << lexeme << " , " << line_no <<  endl;
				token << "AO , " << lexeme << " , " << line_no <<  endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			else
			{
				state = 0;
				cout << "Add_sub , " << lexeme << " , " << line_no <<  endl;
				token << "Add_sub , " << lexeme << " , " << line_no <<  endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			break;
		}

		case 5:
		{
			if (c == '=')
			{
				state = 0;
				lexeme += c;
				cout << " RO , " << lexeme << " , " << line_no << endl;
				token << " RO , " << lexeme << " , " << line_no << endl;
				lexeme = "";
				flag = 0;
			}
			else if (str[i - 1] == '=')
			{
				state = 0;
				lexeme = str[i - 1];
				cout <<  " AO , " << lexeme << " , " << line_no << " )" << endl;
				token <<  " AO , " << lexeme << " , " << line_no << " )" << endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			break;
		}

		case 6:
		{
			if (c == '=')
			{
				state = 0;
				lexeme += c;
				cout <<  " RO , " << lexeme << " , " << line_no << " )" << endl;
				token <<  " RO , " << lexeme << " , " << line_no << " )" << endl;
				lexeme = "";
				flag = 0;
			}

			else if (c != '=')
			{
				state = 0;
				lexeme = str[i - 1];
				cout <<  " RO , " << lexeme << " , " << line_no << " )" << endl;
				token <<  " RO , " << lexeme << " , " << line_no << " )" << endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			break;
		}

		case 7:
		{
			if (is_digit(c))
			{
				state = 7;
			}

			else if (!is_digit(c))
			{
				state = 0;
				lexeme += c;
				lexeme = lexeme.erase(lexeme.size() - 1);
				cout <<  " Float_Constant , " << lexeme << " , " << line_no << " )" << endl;
				token <<  " Float_constant , " << lexeme << " , " << line_no << " )" << endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			break;
		}

		case 8:
		{
			if (is_letter(c) || is_digit(c))
			{
				state = 9;
			}

			else if (c == 92) // ascii for '\'
			{
				state = 10;
			}
			break;
		}

		case 9:
		{
			if (c == 39) //ascii for ' ' ' 
			{
				state = 0;
				lexeme += c;
				cout <<  " char_Constant , " << lexeme << " , " << line_no << " )" << endl;
				token <<  " char_constant , " << lexeme << " , " << line_no << " )" << endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
			break;
		}

		case 10:
		{
			if ((c <= 9 && c >= 13) || (c == 27) || (c == 32) || (c == 127)) //ascii for special char and escape
			{
				state = 9;
			}
			break;
		}

		case 11:
		{
			if (c != 34) //ascii for " ' "
			{
				state = 11;
			}

			else if (c == 34) //ascii for " ' "
			{
				state = 0;
				lexeme += c;
				cout <<  " string_Constant , " << lexeme << " , " << line_no << " )" << endl;
				token <<  " string_constant , " << lexeme << " , " << line_no << " )" << endl;
				lexeme = c;
				flag = 0;
				goto go;
			}
		}
		}

		if (flag)
			lexeme += c;
		i++;
	}
	token.close();
}

//**************************************************************************************************
void token()
{
	string code = ""; 					// used to read from file only
	fstream wcmnt;

	wcmnt.open("without_cmnt.txt");
		cout << "\n\n***** Tokens *****\n";

	if (wcmnt.is_open())
	{
		int line_no = 1;

		while (!wcmnt.eof())
		{
			getline(wcmnt, code);  		// reading line by line code from txt file
			lexical(code, line_no);			//method to generate lexime
			line_no += 1;
		}
	}
	else
	{
		cout << "Error In Opening The File!\n";
	}
	wcmnt.close();
}

//*************************************************************************************
int main()
{
start:
	system("cls");
	int choice;


	cout << "\n 1. Print Code (with comments) ";
	cout << "\n 2. Print Code (with and Without Comments) ";
	cout << "\n 3. Create Tokens ";
	cout << "\n 4. Exit ";
	cout << "\n Enter Your Choice: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		print_code();
		getch();
		goto start;
	}

	case 2:
	{
		print_code();
		remove_comments();  		//function to remove comment
		print_code_without_cmnt();
		getch();
		goto start;
	}

	case 3:
	{
		remove_comments();
		token();
		getch();
		goto start;
	}

	case 4:
	{
		exit(0);
	}

	default:
	{
		cout << "Please Select Valid Option";
		goto start;
	}
	}
}

