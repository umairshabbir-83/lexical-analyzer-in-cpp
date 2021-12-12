#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool isPunctuator(char Character)
{
    if (Character == ' ' || Character == '+' || Character == '-' || Character == '*' ||
        Character == '/' || Character == ',' || Character == ';' || Character == '>' ||
        Character == '<' || Character == '=' || Character == '(' || Character == ')' ||
        Character == '[' || Character == ']' || Character == '{' || Character == '}' ||
        Character == '&' || Character == '|')
    {
        return true;
    }
    return false;
}

bool isValidIdentifier(char* CharacterStream)
{
    if (CharacterStream[0] == '0' || CharacterStream[0] == '1' || CharacterStream[0] == '2' ||
        CharacterStream[0] == '3' || CharacterStream[0] == '4' || CharacterStream[0] == '5' ||
        CharacterStream[0] == '6' || CharacterStream[0] == '7' || CharacterStream[0] == '8' ||
        CharacterStream[0] == '9' || isPunctuator(CharacterStream[0]) == true)
    {
        return false;
    }

    int StreamLength = strlen(CharacterStream);

    if (StreamLength == 1)
    {
        return true;
    }
    else
    {
        for (int i = 1; i < StreamLength; i++)
        {
            if (isPunctuator(CharacterStream[i]) == true)
            {
                return false;
            }
        }
    }
    return true;
}

bool isOperator(char Character)
{
    if (Character == '+' || Character == '-' || Character == '*' ||
        Character == '/' || Character == '>' || Character == '<' ||
        Character == '=' || Character == '|' || Character == '&')
    {
        return true;
    }
    return false;
}

bool isKeyword(char* CharacterStream)
{
    if (!strcmp(CharacterStream, "cout") || !strcmp(CharacterStream, "cin")
        || !strcmp(CharacterStream, "if") || !strcmp(CharacterStream, "else")
        || !strcmp(CharacterStream, "while") || !strcmp(CharacterStream, "do")
        || !strcmp(CharacterStream, "break") || !strcmp(CharacterStream, "continue")
        || !strcmp(CharacterStream, "int") || !strcmp(CharacterStream, "double")
        || !strcmp(CharacterStream, "float") || !strcmp(CharacterStream, "return")
        || !strcmp(CharacterStream, "char") || !strcmp(CharacterStream, "case")
        || !strcmp(CharacterStream, "long") || !strcmp(CharacterStream, "short")
        || !strcmp(CharacterStream, "typedef") || !strcmp(CharacterStream, "switch")
        || !strcmp(CharacterStream, "unsigned") || !strcmp(CharacterStream, "void")
        || !strcmp(CharacterStream, "static") || !strcmp(CharacterStream, "struct")
        || !strcmp(CharacterStream, "sizeof") || !strcmp(CharacterStream, "long")
        || !strcmp(CharacterStream, "volatile") || !strcmp(CharacterStream, "bool")
        || !strcmp(CharacterStream, "enum") || !strcmp(CharacterStream, "const")
        || !strcmp(CharacterStream, "union") || !strcmp(CharacterStream, "extern"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isNumber(char* CharacterStream)
{
    int StreamLength = strlen(CharacterStream), numOfDecimal = 0;
    if (StreamLength == 0)
    {
        return false;
    }
    for (int i = 0; i < StreamLength; i++)
    {
        if (numOfDecimal > 1 && CharacterStream[i] == '.')
        {
            return false;
        }
        else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (CharacterStream[i] != '0' && CharacterStream[i] != '1' && CharacterStream[i] != '2'
            && CharacterStream[i] != '3' && CharacterStream[i] != '4' && CharacterStream[i] != '5'
            && CharacterStream[i] != '6' && CharacterStream[i] != '7' && CharacterStream[i] != '8'
            && CharacterStream[i] != '9' || (CharacterStream[i] == '-' && i > 0))
        {
            return false;
        }
    }
    return true;
}

char* subString(char* CharacterStream, int left, int right)
{
    char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

    for (int i = left; i <= right; i++)
    {
        subStr[i - left] = CharacterStream[i];
        subStr[right - left + 1] = '\0';
    }
    return subStr;
}


void Tokenize(char* CharacterStream)
{
    int left = 0, right = 0;
    int StreamLength = strlen(CharacterStream);

    while (right <= StreamLength && left <= right)
    {
        if (isPunctuator(CharacterStream[right]) == false)
        {
            right++;
        }

        if (isPunctuator(CharacterStream[right]) == true && left == right)
        {
            if (isOperator(CharacterStream[right]) == true)
            {
                cout << CharacterStream[right] << "\t\tOperator\n";
            }
            right++;
            left = right;
        }
        else if (isPunctuator(CharacterStream[right]) == true && left != right || (right == StreamLength && left != right))
        {
            char* subStr = subString(CharacterStream, left, right - 1);

            if (isKeyword(subStr) == true)
            {
                cout << subStr << "\t\tKeyword\n";
            }
            else if (isNumber(subStr) == true)
            {
                cout << subStr << "\t\tNumber\n";
            }
            else if (isValidIdentifier(subStr) == true && isPunctuator(CharacterStream[right - 1]) == false)
            {
                cout << subStr << "\t\tIdentifier\n";
            }
            else if (isValidIdentifier(subStr) == false && isPunctuator(CharacterStream[right - 1]) == false)
            {
                cout << subStr << "\t\tIdentifier not valid\n";
            }
            left = right;
        }
    }
    return;
}

//MAIN BODY
int main()
{
    char CharacterStream[128];

    cout << string(32, '-') << endl;
    cout << "Lexeme\t\tToken" << endl;
    cout << string(32, '-') << endl;

    fstream CodeFile;
    CodeFile.open("Source.txt", ios::in);
    if (!CodeFile) {
        cout << "\n** NO SUCH FILE **\n";
    }
    else {

        while (true)
        {
            CodeFile >> CharacterStream;
            if (CodeFile.eof())
            {
                break;
            }

            Tokenize(CharacterStream);
        }

    }

    CodeFile.close();
    return 0;
}