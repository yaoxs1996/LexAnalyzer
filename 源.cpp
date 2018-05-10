#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

ofstream outFile;
ofstream errFile;
int lineNum = 1;

bool isLetter(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}

//判断是否为数字
bool isDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

int isReverse(char *token)
{
	if (strcmp(token, "begin") == 0)
		return 1;
	else if (strcmp(token, "end") == 0)
		return 2;
	else if (strcmp(token, "integer") == 0)
		return 3;
	else if (strcmp(token, "if") == 0)
		return 4;
	else if (strcmp(token, "then") == 0)
		return 5;
	else if (strcmp(token, "else") == 0)
		return 6;
	else if (strcmp(token, "function") == 0)
		return 7;
	else if (strcmp(token, "read") == 0)
		return 8;
	else if (strcmp(token, "write") == 0)
		return 9;
	else
		return 0;
}

void retract(char &ch)
{
	ungetc(ch, stdin);
	ch = NULL;
}

void error(int lineNum, int errType)
{
	char errInfo[16] = { 0 };
	if (errType == 1)
	{
		strcpy(errInfo, "未知运算符");
	}
	else if (errType == 2)
	{
		strcpy(errInfo, "非法字符");
	}
	else
	{
		strcpy(errInfo, "未知错误");
	}

	errFile << "***第" << lineNum << "行  " << errInfo << endl;
}

char getnbc(char ch)
{
	while (true)
	{
		//'\r'仅针对windows平台文件
		if (ch == '\r' || ch == '\t' || ch == ' ')
		{
			ch = getchar();
		}
		else
			break;
	}
	return ch;
}

bool LexAnalyze()
{
	int num = 0;
	int val = 0;
	char token[17] = "\0";
	char ch;
	ch = getchar();
	ch = getnbc(ch);		//“过滤”空白字符

	switch (ch)
	{
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		while (isLetter(ch) || isDigit(ch))
		{
			char temp[2] = { ch };
			strcat(token, temp);
			ch = getchar();
		}
		retract(ch);
		num = isReverse(token);
		if (num != 0)
		{
			outFile << setw(16) << token << " " << setw(2) << num << endl;
		}
		else
		{
			outFile << setw(16) << token << " " << setw(2) << 10 << endl;
		}
		break;

	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
		while (isDigit(ch))
		{
			char temp[2] = { ch };
			strcat(token, temp);
			ch = getchar();
		}
		retract(ch);
		outFile << setw(16) << token << " " << setw(2) << 11 << endl;
		break;

	case '=':
		outFile << setw(16) << ch << " " << setw(2) << 12 << endl;
		break;

	case '<':
		ch = getchar();
		if (ch == '>')
		{
			outFile << setw(16) << "<>" << " " << setw(2) << 13 << endl;
		}
		else if (ch == '=')
		{
			outFile << setw(16) << "<=" << " " << setw(2) << 14 << endl;
		}
		else
		{
			retract(ch);
			outFile << setw(16) << "<" << " " << setw(2) << 15 << endl;
		}
		break;

	case '>':
		ch = getchar();
		if (ch == '=')
		{
			outFile << setw(16) << ">=" << " " << setw(2) << 16 << endl;
		}
		else
		{
			retract(ch);
			outFile << setw(16) << ">" << " " << setw(2) << 17 << endl;
		}
		break;

	case '-':
		outFile << setw(16) << "-" << " " << setw(2) << 18 << endl;
		break;

	case '*':
		outFile << setw(16) << "*" << " " << setw(2) << 19 << endl;
		break;

	case ':':
		ch = getchar();
		if (ch == '=')
		{
			outFile << setw(16) << ":=" << " " << setw(2) << 20 << endl;
		}
		else
		{
			error(lineNum, 1);
		}
		break;

	case '(':
		outFile << setw(16) << "(" << " " << setw(2) << 21 << endl;
		break;

	case ')':
		outFile << setw(16) << ")" << " " << setw(2) << 22 << endl;
		break;

	case ';':
		outFile << setw(16) << ";" << " " << setw(2) << 23 << endl;
		break;

	case '\n':
		outFile << setw(16) << "EOLN" << " " << setw(2) << 24 << endl;
		lineNum++;
		break;

	case EOF:
		outFile << setw(16) << "EOF" << " " << setw(2) << 25;
		return 0;

	default:
		error(lineNum, 2);
	}
}

int main()
{
	cout << "正在读入test.pas文件......" << endl;
	cout << "正在创建输出文件......" << endl;
	outFile.open("test.dyd");
	errFile.open("test.err");

	if (freopen("test.pas", "r", stdin) != NULL)
	{
		while (LexAnalyze());
		cout << "分析完成" << endl;
	}
	
	outFile.close();
	errFile.close();

	system("pause");
}