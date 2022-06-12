#include<iostream>
#include <string.h>
#include <fstream>
#include<limits>
#include<string>
using namespace std;
int i = 0;
string class_part[500];
string lineNumber[500];
int decl();
int init();
int list();
int constants();
int Arithmaticdecl();
int cond();
int Arithm_Incr_Decr();
int body();
int INCDEC();
int Assignment();
int c();
int Idconst();
int begin();
int sample();
int move();
int m_st();
int s_st();
int else_st();
int elif();
//*****************************************************************************************************************
int begin() {
	if (class_part[i] == "DT") {
		cout << "num DT done\n";
		i++;
		if (class_part[i] == "Iden") {
			cout << "begin done\n";
			i++;
			if (class_part[i] == "(") {
				cout << "( done\n";
				i++;
				if (class_part[i] == ")") {
					cout << ") done\n";
					i++;
					if (class_part[i] == "{") {
						cout << "{ done\n";
						i++;
						if (class_part[i] == "KW") {
							i++;
							if (class_part[i] == ";") {
								return true;
							}
							if (class_part[i] == "}") {
								return true;
							}

						}
						else if (s_st() || m_st()) {
							cout << "begin multi-statement done \n";
							i++;
							cout << "Now Here " << class_part[i] << "  " << class_part[i + 1] << endl;
							cout << "Now Here " << class_part[i + 2] << "  " << class_part[i + 3] << endl;
							cout << "Now Here " << class_part[i + 4] << "  " << class_part[i + 5] << endl;
							if (class_part[i] == "KW") {
								cout << "end \n";
								i++;
								if (class_part[i] == ";") {
									return true;
								}
								if (class_part[i] == "}") {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}
//*****************************************************************************************************************
int decl()
{
	if (class_part[i] == "DT")
	{
		i++;
		cout << "DT done (Declaration)\n";
		if (class_part[i] == "ID")
		{
			i++;
			cout << "ID done (Declaration)\n";
			if (init())
			{
				i++;
				if (list())
				{
					return true;
				}

			}

		}

	}

	return false;
}
//*****************************************************************************************************************
int init()
{
	if (class_part[i] == ";" || class_part[i] == ",")
	{
		cout << "in comma (initialization)";
		i--;
		return true;
	}
	if (class_part[i] == "=")
	{
		cout << "AO done (initialization)\n";
		i++;
		if (constants())
		{
			return true;
		}
		else if (class_part[i] == "ID")
		{
			i++;
			if (init())
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}

}
//*****************************************************************************************************************
int list()
{
	if (class_part[i] == ";")
	{
		cout << "; done (list)\n";
		return true;
	}
	else if (class_part[i] == ",")
	{
		i++;
		if (class_part[i] == "ID")
		{
			i++;
			if (init())
			{
				i++;
				if (list())
				{
					return true;
				}
			}
		}
	}
	else
	{
		return false;
	}

}
//*****************************************************************************************************************
int constants()
{
	if (class_part[i] == "int_const" || class_part[i] == "float_const" || class_part[i] == "char_const" || class_part[i] == "string_const")
	{
		cout << "const done (constants)\n";
		return true;
	}
	else {
		return false;
	}
}
//*****************************************************************************************************************
int however()
{
	if (class_part[i] == "however")
	{
		cout << "however loop done (however) \n";
		i++;
		if (class_part[i] == "(")
		{
			cout << "( done. (however)\n";
			i++;
			if (Arithmaticdecl())
			{
				i++;
				if (cond())
				{
					i++;
					if (class_part[i] == ";")
					{
						cout << "; done (however)\n";
						i++;
						if (Arithm_Incr_Decr())
						{
							i++;
							if (class_part[i] == ")")
							{
								cout << ") done (however)\n";
								i++;
								if (body() || s_st() || m_st())
								{
									cout << "however loop body, sst, mst done\n";
									i++;
									if (body()) {
										i++;
										if (class_part[i] == "}") {
											return true;
										}
									}

								}

							}
						}
					}
				}
			}
		}

	}
	else {
		return false;
	}
}
//*****************************************************************************************************************
int if_st() {
	if (class_part[i] == "if") {
		i++;
		if (class_part[i] == "(") {
			cout << "if ( Done \n";
			i++;
			if (cond()) {
				cout << "if cond() done \n";
				i++;
				if (class_part[i] == ")") {
					cout << "if ) done\n";
					i++;
					if (class_part[i] == "{") {
						cout << "if { done\n";
						i++;
						if (body()) {
							i++;
							cout << "if body() done\n";
							cout << "(if) now here " << class_part[i] << "  " << class_part[i + 1] << endl;
							cout << "(if) now here " << class_part[i] << "  " << class_part[i + 1] << endl;
							return true;

						}
					}
				}
			}
		}
	}

	return false;
}
//*****************************************************************************************************************
int elif() {
	if (class_part[i] == "elif") {
		i++;
		if (class_part[i] == "(") {
			cout << "elif ( Done \n";
			i++;
			if (cond()) {
				cout << "elif cond() done \n";
				if (class_part[i] == ")") {
					cout << "elif ) done\n";
					i++;
					if (class_part[i] == "{") {
						cout << "elif { done\n";
						if (body()) {
							cout << "elif body() done\n";
							i++;
							if (class_part[i] == "}") {
								cout << "elif } done\n";
								return true;

							}
						}
					}
				}
			}
		}
	}
	return false;
}
//*****************************************************************************************************************
int else_st() {
	if (class_part[i] == "else") {
		i++;
		cout << "else done \n";
		if (class_part[i] == "{") {
			cout << "else { done \n";
			if (body()) {
				i++;
				cout << "else body() done \n";
				if (class_part[i] == "}") {
					cout << "else } done\n";
					return true;
				}
			}
		}
	}
	return false;
}
//*****************************************************************************************************************
int loop() {
	if (class_part[i] == "loop") {
		i++;
		cout << "loop done \n";
		if (class_part[i] == "(") {
			i++;
			cout << "loop ( done \n";
			if (cond()) {

				cout << "loop cond() done \n";
				i++;
				if (class_part[i] == ")") {
					i++;
					cout << "loop ) done \n";
					if (class_part[i] == "{") {
						cout << "loop { done \n";
						if (body()) {
							i++;
							cout << "loop body done \n";
							if (class_part[i] == "}") {
								cout << "loop } done \n";
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}
//*****************************************************************************************************************
int do_loop() {
	if (class_part[i] == "do") {
		cout << "do_loop \n";
		i++;
		if (class_part[i] == "{") {
			cout << "do_loop { done \n";
			if (body()) {
				cout << "do_loop body done\n";
				i++;
				if (class_part[i] == "}") {
					cout << "do_loop } done\n";
					i++;
					if (class_part[i] == "do_loop") {
						cout << "do_loop done\n";
						i++;
						if (class_part[i] == "(") {
							cout << "do_loop ( done\n";
							i++;
							if (cond()) {
								cout << "do_loop cond done\n";

								if (class_part[i] == ")") {
									cout << "do_loop ) done\n";
									return true;
								}
								else if (class_part[i + 1] == ")") {
									cout << "do_loop ) done\n";
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}
//*****************************************************************************************************************
int move() {
	if (class_part[i] == "move") {
		cout << "move done\n";
		i++;
		if (class_part[i] == "(") {
			cout << "move ( done\n";
			i++;
			if (Idconst()) {
				cout << "move idconst done\n";
				i++;
				if (class_part[i] == ")") {
					cout << "move ) done \n";
					i++;
					if (class_part[i] == "{") {
						cout << "move { done \n";
						i++;
						if (sample()) {
							cout << "move sample done\n";
							i++;
							if (class_part[i] == "}") {
								cout << "move } done\n";
								return true;
							}
							else if (sample()) {
								cout << "ANOTHER sample done\n";
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}
//*****************************************************************************************************************
int sample() {
	if (class_part[i] == "sample") {
		cout << "sample done \n";
		i++;
		if (constants()) {
			cout << "sample const done\n";
			i++;
			if (class_part[i] == ":") {
				cout << "sample : done \n";
				i++;
				if (body()) {
					cout << "sample body done\n";
					i++;
					cout << class_part[i];
					if (class_part[i] == "break") {
						cout << "sample break done\n";
						return true;
					}
				}
			}
		}
	}
	return false;
}
//*****************************************************************************************************************
int Arithm_Incr_Decr()
{
	if (INCDEC())
	{
		return true;
	}
	else if (Assignment())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//*****************************************************************************************************************
int Arithmaticdecl()
{
	if (decl())
	{
		return true;
	}
	else if (Assignment())
	{
		i++;
		if (class_part[i] == ";")
		{
			cout << "; done (Arithmatic Declaration)\n";
			return true;
		}
	}
	else if (class_part[i] == ";")
	{
		cout << "; done (Arithmatic Declaration)\n";
		return true;
	}
	else
	{
		return false;
	}
}
//*****************************************************************************************************************
int INCDEC()
{
	if (class_part[i] == "ID")
	{
		cout << "ID done (INCDEC)\n";
		i++;
		if (class_part[i] == "incdec")
		{
			cout << "incdec done (INCDEC)\n";
			return true;
		}
	}
	else if (class_part[i] == "incdec")
	{
		cout << "incdec done (INCDEC)\n";
		if (class_part[i] == "ID")
		{
			cout << "ID done (INCDEC)\n";
			return true;
		}
	}
	else
	{
		return false;
	}
}
//*****************************************************************************************************************
int body()
{
	if (class_part[i] == ";")
	{
		cout << "; done (body)\n";
		return true;
	}
	else if (decl()) {
		cout << "BODY declaration done\n";
		return true;
	}
	else if (Assignment()) {
		cout << "BODY assignment done.\n";
		return true;
	}
	else if (class_part[i] == "{")
	{
		cout << "{ done (body)\n";
		i++;
		if (class_part[i] == "}")
		{
			cout << "} done (body)\n";
			return true;
		}

	}
	else if (body()) {
		return true;
	}
	return false;
}
//*****************************************************************************************************************
int cond()
{
	if (c())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//*****************************************************************************************************************
int c()
{
	if (Idconst())
	{
		i++;
		if (class_part[i] == "RO")
		{
			cout << "RO done (c)\n";
			i++;
			if (Idconst())
			{
				return true;
			}
		}
	}
	else {
		return false;
	}
}
//*****************************************************************************************************************
int Idconst()
{
	if (class_part[i] == "ID")
	{
		cout << "ID done (Idconst)\n";
		return true;
	}
	else if (constants())
	{
		return true;
	}
	else
	{
		return false;
	}
}
//*****************************************************************************************************************
int Assignment()
{
	if (class_part[i] == "ID")
	{
		cout << "ID done (Assignment)\n";
		i++;
		if (class_part[i] == "=")
		{
			cout << "AO done (Assignment)\n";
			i++;
			if (class_part[i] == "ADDSUB") {
				i++;
				if (Idconst() || constants()) {
					return true;
				}
			}
			else if (Idconst())
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}
//*****************************************************************************************************************
int s_st() {
	if (Assignment()) {
		return true;
	}
	else if (decl()) {
		return true;
	}
	else if (s_st()) {
		return true;
	}
	return false;
}
//*****************************************************************************************************************
int m_st() {
	if (however()) {
		return true;
	}
	else if (if_st()) {
		return true;
	}
	else if (loop()) {
		return true;
	}
	else if (do_loop()) {
		return true;
	}
	else if (move()) {
		return true;
	}

	else if (if_st()) {
		if (else_st()) {
			return true;
		}
		else if (elif()) {
			return true;
		}
	}
	return false;
}
//*****************************************************************************************************************
int main() {
	ifstream File;
	string str;
	string delimeter = ",";
	File.open("OUTPUT_TOKEN.txt");
	if (!File.is_open()) {
		cout << "Unable to open Token File";
		exit(1);
	}
	int count = 0;
	int i = 0;
	string line;
	while (getline(File, line)) {
		count++;
	}
	cout << "Number of Tokens in File: " << count << endl << endl;
	File.close();
	File.open("token.txt");
	string firstWord;
	string lastword;
	int word = 0;
	while (File >> firstWord)
	{
		class_part[word] = firstWord;
		File.ignore(numeric_limits<streamsize>::max(), '\n');
		word++;
	}
	File.close();
	if (!begin()) {
		cout << "*********************************************\n";
		cout << "               NOT PARSED    \n";
		cout << "*********************************************\n";
	}
	else {
		cout << "\n*******************************************\n";
		cout << "                 PARSED  \n";
		cout << "*********************************************\n";
	}
	return 0;
}
