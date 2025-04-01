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

int main() {
    cout << "Enter an expression:   ";
    getline(cin, input);
    
   
    getChar();
    do {
        lex();
    } while (nextToken != End_OF_File);

    return 0;
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

    if (nextToken != EOF) {
        cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    }
    return nextToken;
}