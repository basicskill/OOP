#include "Compiler.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

void SimpleCompilationStrategy::compile(string filepath) {
    string line, outpath;
    outpath = filepath.substr(0, filepath.length()-4) + ".imf";

    ifstream inFile(filepath);
    ofstream outFile(outpath);

    int tmpCounter = 1;
    string tmpMem;
    int operation = 1;
    string x, op1, op2;
    while (inFile.peek() != EOF) {
        int it = 0;
        stack<string> S;
        getline(inFile, line);
        line = inf2post(line);

        x = readNext(line, &it);
        while (x != "") {
            if (!checkOperation(x))
                S.push(x);
            else {
                op2 = S.top(); S.pop();
                op1 = S.top(); S.pop();

                if (x == "=")
                    outFile << "[" << operation++ << "] = " 
                            << op1 << " " << op2 << endl;
                else {
                    tmpMem = "t" +  to_string(tmpCounter++);

                    outFile << "[" << operation++ << "] " << x
                            << " " << tmpMem << " "
                            << op1 << " " << op2 << endl;
                    S.push(tmpMem); 
                }
            }
            x = readNext(line, &it);
        }
    }
    inFile.close();
    outFile.close();
}

int ipr(char c);
int spr(char c);

string CompilationStrategy::inf2post(string infix) {
    stack<string> S;
    string next, postfix = "";
    string x;

    int rank = 0;
    int it = 0;
    if (infix[infix.length()-1] == '\r')
        infix = infix.substr(0, infix.length()-1);

    next = readNext(infix, &it); // fist var
    postfix += next;
    next = readNext(infix, &it); // '=' sign
    next = readNext(infix, &it); // equation
    while (next != "") {
        if(!(checkOperation(next))) {
            postfix += " " + next;
            ++rank;
        }
        else {
            while (!S.empty() && (ipr(next[0]) <= spr(S.top()[0]))) {
                x = S.top();
                postfix += " " + x;
                S.pop();
            }

            if (next != ")")
                S.push(next);
            else S.pop();
        }
        next = readNext(infix, &it);
    }
    while (!S.empty()) {
        x = S.top();
        postfix += " " + x;
        S.pop();
    }
    postfix += " =";
    return postfix;
}

string CompilationStrategy::readNext(string input, int* it) {
    string el = "";
    while ((*it < input.length()) && input[*it] == ' ')
        (*it)++;

    if (*it > input.length()) return el;

    if ((input[*it] == '-') && (isdigit(input[(*it)+1]))) {
        el += "-";
        ++(*it);
    }

    if (checkOperation(input[*it])) el = input[(*it)++];
    else
        while ((*it < input.size()) && !checkOperation(input[*it]) && input[*it] != ' ')
            el += input[(*it)++];
    
    return el;
}

bool CompilationStrategy::checkOperation(string c) {
    return ((c.size() == 1) && ((c[0] == '+') || (c[0] == '-') || \
            (c[0] == '*') || (c[0] == '/') || (c[0] == '^') || \
            (c[0] == '(') || (c[0] == ')') || (c[0] == '=')));
}

bool CompilationStrategy::checkOperation(char c) {
    return ((c == '+') || (c == '-') || \
            (c == '*') || (c == '/') || (c == '^') || \
            (c == '(') || (c == ')') || (c == '='));
}

// Helper functions for 
int ipr(char c) {
    switch (c) {
    case '+': case '-':
        return 2;
        break;
    
    case '*': case '/':
        return 3;
        break;

    case '^':
        return 5;
        break;
        
    case '(':
        return 6;
        break;
        
    case ')':
        return 1;
        break;

    case '=':
        return 0;
        break;

    default:
        // TODO: Exception!
        break;
    }
}

int spr(char c) {
    switch (c) {
    case '+': case '-':
        return 2;
        break;
    
    case '*': case '/':
        return 3;
        break;

    case '^':
        return 4;
        break;
        
    case '(':
        return 0;
        break;
        
    case ')':
        return 0;
        break;

    case '=':
        return 1;
        break;

    default:
        // TODO: Exception!
        break;
    }
}
