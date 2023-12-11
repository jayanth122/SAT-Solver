#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
struct Token
{
    std::string content;
    std::string type;
};
// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
    // your code starts here
    std::string ln;
    int token_index = 0;
    bool token_flag;
    Token *tokenArray;
    int tokenArraySize;


public:
    Tokenizer(std::string ln, bool flag);
    bool advanceToken();   // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken();      // returns the token being processed
    bool appendOptrVector(char  ch); // generate Operator Vector;
    bool isOperator(int i);     // Check if the given string is operator;
    bool isConstant(int i);     // Check if the given string is operator;
    std::vector<char> optr_vector;
    void genFormulaTokens(std::string ln);
    void genAssignmentTokens(std::string ln);
};

#endif
