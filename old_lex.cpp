#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 128
#define TRUE 1
#define FALSE 0

int generateFile(char *fullName)
{
	char dydName[MAXLINE] = "";
	char errName[MAXLINE] = "";
	char *extension;
	extension = strrchr(fullName, '.');
	if (fullName != NULL && extension != NULL)
	{
		//extension = strrchr(fullName, '.');
		strncpy(dydName, fullName, strlen(fullName) - strlen(extension));

		strcpy(errName, dydName);
		strcat(dydName, ".dyd");
		strcat(errName, ".err");

		//重定向输入输出流，使用目标文件来代替标准输入输出
		if (freopen(fullName, "r", stdin) != NULL && freopen(dydName, "w", stdout) != NULL && freopen(errName, "w", stderr) != NULL)
		{
			printf("分析文件生成成功！\n");
			return TRUE;
		}
		else
		{
			printf("分析文件生成失败！\n");
			return FALSE;
		}
	}
	else
	{
		printf("文件名输入有误！\n");
		return FALSE;
	}
}

//读入非空白字符
char getnbc(char ch)
{
	while (TRUE)
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
//判断是否为字母
int isLetter(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return TRUE;
	else
		return FALSE;
}

//判断是否为数字
int isDigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return TRUE;
	else
		return FALSE;
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

int error(int lineNum, int errType)
{
	char *errInfo = NULL;
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

	if (fprintf(stderr, "***第%d行  %s", lineNum, errInfo) >= 0)
		return 1;
	else
		return 0;
}

int LexAnalyze()
{
	int num = 0;
	int val = 0;
	int lineNum = 1;
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
			char temp[2] = {ch};
			strcat(token, temp);
			ch = getchar();
		}
		retract(ch);
		num = isReverse(token);
		if (num != 0)
		{
			printf("%16s %2d\n", token, num);
		}
		else
		{
			printf("%16s %2d\n", token, 10);
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
		printf("%16s %2d", ch, 11);
		break;

	case '=':
		printf("%16s %2d", ch, 12);
		break;

	case '<':
		ch = getchar();
		if (ch == '>')
		{
			printf("%16s %2d", "<>", 13);
		}
		else if (ch == '=')
		{
			printf("%16s %2d", "<=", 14);
		}
		else
		{
			retract(ch);
			printf("%16s %2d", "<", 15);
		}
		break;

	case '>':
		ch = getchar();
		if (ch == '=')
		{
			printf("%16s %2d", ">=", 16);
		}
		else
		{
			retract(ch);
			printf("%16s %2d", ">", 17);
		}
		break;

	case '-':
		printf("%16s %2d", '-', 18);
		break;

	case '*':
		printf("%16s %2d", '*', 19);
		break;

	case ':':
		ch = getchar();
		if (ch == '=')
		{
			printf("%16s %2d", ":=", 20);
		}
		else
		{
			error(lineNum,1);
		}
		break;

	case '(':
		printf("%16s %2d", '(', 21);
		break;

	case ')':
		printf("%16s %2d", ')', 22);
		break;

	case ';':
		printf("%16s %2d", ';', 23);
		break;

	case '\n':
		printf("%16s %2d", "EOLN", 24);
		lineNum++;
		break;

	case EOF:
		printf("%16s %2d", "EOF", 25);
		return 0;

	default:
		error(lineNum,2);
	}
}




int main()
{
	char fileName[MAXLINE];
	printf("输入待处理源程序名（*.pas文件）：");
	scanf("%s", &fileName);
	
	if (generateFile(fileName))
	{
		while (LexAnalyze());
	}

	fclose(stdin);
	fclose(stdout);
	fclose(stderr);

	system("pause");
	//return 0;
}