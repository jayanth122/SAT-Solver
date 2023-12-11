#include "tokenizer.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cctype>
#include <regex>

Tokenizer::Tokenizer(std::string ln, bool flag)
{
    // complete the constructor
    Tokenizer::ln = ln;
    this->tokenArray = new Token[int(ln.length())];
    this->tokenArraySize = 0;
    Tokenizer::token_index = 0;
    this->token_flag = flag;
    if (this->token_flag)
    {
        genFormulaTokens(this->ln);
    }
}

bool Tokenizer::advanceToken()
{
    // your code starts here
    if (int(this->tokenArraySize) < this->token_index + 1)
    {
        return false;
    }
    this->token_index++;
    return true;
}
bool Tokenizer::hasToken() const
{
    // your code starts here
    if (int(this->tokenArraySize) < this->token_index + 1)
    {
        return false;
    }
    return true;
}

bool Tokenizer::appendOptrVector(char ch){
     this->optr_vector.push_back(ch);
     return true;
}

bool Tokenizer::isOperator(int i){
    appendOptrVector('(');
    appendOptrVector(')');
    appendOptrVector('+');
    appendOptrVector('-');
    appendOptrVector('*');
    appendOptrVector(':');

    if(std::count(optr_vector.begin(), optr_vector.end(), ln[i])){
        return true;
    }
    return false;
}

bool Tokenizer::isConstant(int i){
  if(isdigit(ln[i])){
     throw "Error: invalid input";
  }
}
void Tokenizer::genFormulaTokens(std::string ln)
{
    int i = 0;
    bool isVar = false;
    bool isSpace = false;
    while (i < int(ln.length()))
    {
        Token token;
        if(isblank(ln[i])){
            i++;
            continue;
        }
        if (isOperator(i))
        {
            token.content = this->ln[i];
            token.type = "operator";
            i++;
        }
        else if (isConstant(i))
        {
                token.content = this->ln[i];
                token.type = "constant";
                i++;
        }
        else
        {
            std::string varname = "";
            while (i < int(ln.length()))
            {
                if (isOperator(i))
                {
                    break;
                }
                else if(isblank(ln[i])){
                    isSpace = true;
                    if(isalnum(ln[i-1]) && isalnum(ln[i+1])){
                        throw "Error: invalid input";
                    }
                    i++;
                    continue;
                }
                if(isVar&&isSpace){
                      throw "Error: invalid input";
                }
                varname += ln[i];
                if(isVar==false && varname.size()>0){
                   isVar = true;
                }
                i++;
                
            }
            if (varname.length() > 10)
            {
                throw "Error: invalid input";
            }
            token.type = "variable";
            token.content = varname;
            isVar = false;
            isSpace = false;
        }
        this->tokenArray[this->tokenArraySize].content = token.content;
        this->tokenArray[this->tokenArraySize].type = token.type;
         this->tokenArraySize++;
    }
}

void Tokenizer::genAssignmentTokens(std::string ln)
{
    int i = 0;
    bool isVar = false;
    bool isSpace = false;
    while (i < int(ln.length()))
    {
        Token token;
        if(isblank(ln[i])){
            i++;
            continue;
        }
        if (isConstant(i))
        { 
            token.type = "constant";
            token.content = ln[i];
            i++;
        }
        else if (ln[i] == ',')
        {
            i++;
            continue;
        }
        else
        {
            std::string varname = "";
            while (i < int(ln.length()))
            {
                if (ln[i] == ':')
                {
                    i++;
                    break;
                }
                else if(isblank(ln[i])){
                     isSpace = true;
                    if(isalnum(ln[i-1]) && isalnum(ln[i+1])){
                        throw "Error: invalid input";
                    }
                    i++;
                    continue;
                }
                if(isVar&&isSpace){
                      throw "Error: invalid input";
                }
                varname += ln[i];
                i++;
                if(isVar==false && varname.size()>0){
                   isVar = true;
                }
            }
            token.type = "variable";
            token.content = varname;
            isVar = false;
            isSpace = false;
        }
        this->tokenArray[this->tokenArraySize].content = token.content;
        this->tokenArray[this->tokenArraySize].type = token.type;
        this->tokenArraySize++;
        
    }
    if(this->tokenArraySize != count(ln.begin(),ln.end(),':')*2){
        throw "Error: invalid input";
    }
}
// only can be called when hasToken() is true
Token Tokenizer::getToken()
{
    Token resultToken;
    if (hasToken())
        resultToken = this->tokenArray[this->token_index];
    return resultToken;
}
