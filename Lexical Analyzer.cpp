// Omar Ashraf  - ID: 200036952//
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define L_PAREN 25
#define R_PAREN 26
#define EXP_OP 27
#define SEMICOLON 28
#define FOR 29
#define L_BRACE 30
#define R_BRACE 31
#define End_OF_File -1

int charClass;
string lexeme;
char nextChar;
int nextToken;
string input;
size_t pos = 0;

void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);
string Token_type(int token);

int main() {
    cout << "Enter an expression:   ";
    getline(cin, input);
    
    getChar();
    do {
        lex();
    } while (nextToken != End_OF_File);

    return 0;
}

string Token_type(int token) {
    switch (token) {
        case INT_LIT: return "INTEGER LITERAL";
        case IDENT: return "IDENTIFIER";
        case ASSIGN_OP: return "ASSIGNMENT OPERATOR";
        case ADD_OP: return "ADDITION OPERATOR";
        case SUB_OP: return "SUBTRACTION OPERATOR";
        case MULT_OP: return "MULTIPLICATION OPERATOR";
        case DIV_OP: return "DIVISION OPERATOR";
        case L_PAREN: return "LEFT PARENTHESIS";
        case R_PAREN: return "RIGHT PARENTHESIS";
        case EXP_OP: return "EXPONENT OPERATOR";
        case SEMICOLON: return "SEMICOLON";
        case FOR: return "FOR";
        case L_BRACE: return "LEFT BRACE";
        case R_BRACE: return "RIGHT BRACE";
        case End_OF_File: return "END OF FILE";
        default: return "UNKNOWN TOKEN";
    }
}

int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = L_PAREN;
            break;
        case ')':
            addChar();
            nextToken = R_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '{':
            addChar();
            nextToken = L_BRACE;
            break;
        case '}':
            addChar();
            nextToken = R_BRACE;
            break;
        default:
            addChar();
            nextToken = End_OF_File;
            break;
    }
    return nextToken;
}

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (pos < input.length()) {
        nextChar = input[pos++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    } else {
        charClass = End_OF_File;
    }
}

void getNonBlank() {
    while (isspace(nextChar) && charClass != End_OF_File)
        getChar();
}

int lex() {
    lexeme = "";
    getNonBlank();

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while ((charClass == LETTER || charClass == DIGIT) && charClass != End_OF_File) {
                addChar();
                getChar();
            }
            if (lexeme == "for") {
                nextToken = FOR;
            } else {
                nextToken = IDENT;
            }
            break;
            
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT && charClass != End_OF_File) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        case End_OF_File:
            nextToken = End_OF_File;
            lexeme = "End_OF_File";
            break;
    }

    if (nextToken != End_OF_File) {
        cout << "Next token is: " << nextToken << " (" << Token_type(nextToken) 
             << "), Next lexeme is '" << lexeme << "'" << endl;
    }
    return nextToken;
}