// Unicode UTF-8 version 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Program takes decimal, converts to unicode number, utf code and a symbol (if not shown on screen then you can see in txt file)
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <clocale>
#include <codecvt>
#include <locale>
#include <sstream>
#include<map>
#define UNICODE
#define _UNICODE
using namespace std;
class converter {
private:
	int dec;
	int decimal;
	string binary;
	string hex;
	vector <string> bytes = {};
public:
	converter() :dec(0), decimal(0), binary(""), hex("") {};

	void input() {
		cout << "Enter decimal number: ";
		cin >> dec;
		decimal = dec;
		cout << endl;
	}
	void fillDec(int a) {
		dec = a;
		decimal = dec;
		bytes = {};
	}
	void decToBinary()
	{
		// array to store binary number 
		int binaryNum[32];

		// counter for binary array 
		int i = 0;
		while (dec > 0) {

			// storing remainder in binary array 
			binaryNum[i] = dec % 2;
			dec = dec / 2;
			i++;
		}
		// printing binary array in reverse order 
		for (int j = i - 1; j >= 0; j--)
		{
			binary += to_string(binaryNum[j]);
		}
		if (binary.length() % 4 != 0) {
			for (i = 0; i < binary.length() % 4; i++)
			{
				binary = "0" + binary;
			}
		}
		//cout << "Bin:" << binary << endl;
	}
	char getHexCharacter(string str)
	{
		if (str.compare("1111") == 0) return 'F';
		else if (str.compare("1110") == 0) return 'E';
		else if (str.compare("1101") == 0) return 'D';
		else if (str.compare("1100") == 0) return 'C';
		else if (str.compare("1011") == 0) return 'B';
		else if (str.compare("1010") == 0) return 'A';
		else if (str.compare("1001") == 0) return '9';
		else if (str.compare("1000") == 0) return '8';
		else if (str.compare("0111") == 0) return '7';
		else if (str.compare("0110") == 0) return '6';
		else if (str.compare("0101") == 0) return '5';
		else if (str.compare("0100") == 0) return '4';
		else if (str.compare("0011") == 0) return '3';
		else if (str.compare("0010") == 0) return '2';
		else if (str.compare("0001") == 0) return '1';
		else if (str.compare("0000") == 0) return '0';
		else if (str.compare("111") == 0) return '7';
		else if (str.compare("110") == 0) return '6';
		else if (str.compare("101") == 0) return '5';
		else if (str.compare("100") == 0) return '4';
		else if (str.compare("011") == 0) return '3';
		else if (str.compare("010") == 0) return '2';
		else if (str.compare("001") == 0) return '1';
		else if (str.compare("000") == 0) return '0';
		else if (str.compare("11") == 0) return '3';
		else if (str.compare("10") == 0) return '2';
		else if (str.compare("01") == 0) return '1';
		else if (str.compare("00") == 0) return '0';
		else if (str.compare("1") == 0) return '1';
		else if (str.compare("0") == 0) return '0';
	}
	string getHex()
	{
		for (int i = 0; i < binary.length(); i = i + 4)
		{
			hex += getHexCharacter(binary.substr(i, 4));
		}
		return hex;
	}

	void getBinUtf()
	{
		int x_vietu(0);
		int pildyt_nuliais(0);
		int pildyt_bin = 0;
		//cout << endl;

		if (decimal <= 127) //Byte 1
		{
			bytes.push_back("0xxxxxxx");
			x_vietu = 7;
			pildyt_nuliais = x_vietu - binary.length();
		}
		else if (decimal <= 2047) //Byte 2
		{
			bytes.push_back("110xxxxx");
			bytes.push_back("10xxxxxx");
			x_vietu = 16 - 5;
			pildyt_nuliais = x_vietu - binary.length();
			//uzpildo nuliais vietas iki binary


		}
		else if (decimal <= 65535) //Byte 3
		{
			//1110xxxx 10xxxxxx 10xxxxxx
			bytes.push_back("1110xxxx");
			bytes.push_back("10xxxxxx");
			bytes.push_back("10xxxxxx");
			x_vietu = 8 * 3 - 8;
			pildyt_nuliais = x_vietu - binary.length();

		}
		else if (decimal <= 1114111) //Byte 4
		{
			//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
			bytes.push_back("11110xxx");
			bytes.push_back("10xxxxxx");
			bytes.push_back("10xxxxxx");
			bytes.push_back("10xxxxxx");
			x_vietu = 8 * 4 - 11;
			pildyt_nuliais = x_vietu - binary.length();

		}
		if (pildyt_nuliais > 0) {

			for (int i = 0; i < bytes.size(); i++)
			{
				if (pildyt_nuliais > 0)
				{
					for (int j = 0; j < bytes[i].length(); j++)
					{
						if (bytes[i][j] == 'x' && pildyt_nuliais > 0)
						{
							bytes[i][j] = '0';
							pildyt_nuliais--;
						}
					}
				}
			}
		}
		else {
			int kiekis(binary.length() - x_vietu);
			while (binary[pildyt_bin] == '0' && kiekis > 0)
			{
				pildyt_bin++;
				kiekis--;
			}
		}

		for (int i = 0; i < bytes.size(); i++)
		{
			for (int j = 0; j < bytes[i].length(); j++)
			{
				if (bytes[i][j] == 'x')
				{
					bytes[i][j] = binary[pildyt_bin];
					pildyt_bin++;
				}
			}
		}
		//cout << "utf binary: ";
	//for (int i = 0; i < bytes.size(); i++)
	//		cout << bytes[i] << " ";
	//	cout << endl;
	}
	void getUtf(vector <string>& utf8) {
		string hexadecimal = "";
		for (int i = 0; i < bytes.size(); i++)
		{
			binary = bytes[i];
			for (int j = 0; j < binary.length(); j = j + 4)
			{
				hexadecimal += getHexCharacter(binary.substr(j, 4));
			}
			utf8.push_back(hexadecimal);
			hexadecimal = "";
		}
	}
	~converter() {};
};
int main()
{
	//stringstream str;
	vector <string> utf;
	setlocale(LC_ALL, "");
	//http://cppwhispers.blogspot.com/2012/11/unicode-and-your-application-3-of-n.html
	converter utf8;
	string shex; //string hex
	string uhex; //unicode string
	const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	utf8.input();
	utf8.decToBinary();
	shex = utf8.getHex();
	utf8.getBinUtf();
	utf8.getUtf(utf);
	///////////////////////
	//cout << "HEX: "<<utf8.getHex();
	cout << endl;
	//for(int i=0;i<4;i++)
	//cout<<s[i]<<" ";
	//////////////////////
	uhex = shex;
	while (uhex.length() != 4)
	{
		uhex = '0' + uhex;
	}
	////// OUT //////////
	cout << "UNICODE: U+" << uhex;
	cout << endl;
	cout << "UTF-8: ";
	for (int i = 0; i < utf.size(); i++)
	{
		cout << utf[i] << " ";
	}
	cout << endl;
	cout << "CHAR: ";
	//Pavercia su wchar_t string hexadecimal i simboli
	wchar_t symbol = strtol(shex.c_str(), NULL, 16);
	wcout << symbol << endl;
	//cout << shex << "-this" << endl;
	////To File Symbol/////
	wofstream df(L"symbol.txt");
	df.imbue(utf8_locale);
	df << symbol;
	cout << endl;
	cout << "If there is no symbol, open symbol.txt" << endl;


	///////////////////////////////Part2 bellow ///////////////////////////////////////////
	wstring line;
	map<int, string> table;
	int input_table_dec;
	string input_table_hex;
	ifstream rftable("437.txt");
	int map_index(0);
	while (rftable >> input_table_dec)  //Nuskaito cp437
	{
		rftable >> input_table_hex;
		table[input_table_dec] = input_table_hex;
	}
	map<int, string>::iterator itr;
	wifstream myfile(L"file.txt");
	wofstream dfresult(L"convertedfile.txt");
	if (myfile)
	{
		string hexadecimal;
		int rastas(0);
		int spausdinti(1);
		unsigned char sim_from_text;
		converter change_simbol;
		while (getline(myfile, line))
		{
			rastas = 0;
			spausdinti = 1;;
			for (int i = 0; i < line.length(); i++)
			{
				vector <string> utf_file;
				sim_from_text = line[i];
				int symbol_value = int(sim_from_text);
				//cout << "numFromStringElement:" << symbol_value << endl;
				if (symbol_value > 127 && symbol_value < 256)
				{
					spausdinti = 0;
					for (itr = table.begin(); itr != table.end(); ++itr)
					{
						if (itr->first == symbol_value)
						{
							hexadecimal = itr->second;
							rastas = 1;
						}
					}
					if (rastas)
					{
						int decimal_converted = stoi(hexadecimal, 0, 16);
						//cout << "New sim value: " << decimal_converted << endl;
						change_simbol.fillDec(decimal_converted);
						change_simbol.decToBinary();
						shex = change_simbol.getHex();
						change_simbol.getBinUtf();
						change_simbol.getUtf(utf_file);
						wchar_t output = strtol(hexadecimal.c_str(), NULL, 16);
						dfresult.imbue(utf8_locale);
						dfresult << output;
					}
					rastas = 0;
				}
				else
				{
					dfresult << line[i];
				}

			}
			dfresult << endl;
		}

	}
	else cout << "No txt file by the name file.txt";
	myfile.close();

}
//Need to get bytes from simbols
/*

gauni is simbolio skaiciu, tuomet paimi jo utf ir utf spausdini i faila po baita kaip skaiciu
ir atspausdinti po baita is unsigned char masyvo skaiciu forma

*/

//galima spausdinti is desimtainio skaiciaus simboli su unsigned char


//Ar reikia duoti pasirinkima ivedineti savo dec arba is failo paimt ?

//Get dec from hex:
		//number = stoi(utf8.getHex(), 0, 16);	

/*		Atspausdina string hex kaip int

	std::string your_string_rep{ shex };
	int int_rep = stoi(your_string_rep, 0, 16);
	std::cout << int_rep << '\n';
	std::cout << std::hex << std::showbase << int_rep << '\n';
	cout << int_rep;

	___________________________________________________________________
	std::vector<char> bytes(myString.begin(), myString.end());
bytes.push_back('\0');
char *c = &bytes[0];

__________________________________________________________________

ostringstream os;
	cout << "hex: ";
	for(int i=0; i<text.size();i++)
		for (int j = 0; j < text[i].length(); j++)
		{
			os << hex << uppercase << (int)text[i][j];
			string hextext = os.str();
			cout << hextext << endl;
	}
	*/
	/*
			to get utf string from simbol
	ostringstream os;
		cout << "hex: ";
		for (int i = 0; i < text.size(); i++)
			for (int j = 0; j < text[i].length(); j++)
			{
				os << hex << uppercase << (int)text[i][j];
			}
		string hextext = os.str();
		cout << hextext << endl;
		int text_get_utf = 4;
		string text_utf = "";
		while (text_get_utf) {
			text_utf = text_utf + hextext[hextext.length() - text_get_utf];
			text_get_utf--;
		}
		cout << endl;
		cout << text_utf;
		*/