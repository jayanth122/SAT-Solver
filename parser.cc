#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include <iostream>

FormulaParser::FormulaParser(std::string ln) : tknzr{new Tokenizer{ln, true}}
{
}

TreeNode *FormulaParser::parseFormula()
{
    // your code starts here
    TreeNode *leftChild = parseConjTerm();
    TreeNode *root;
    if (tknzr->getToken().content == "+")
    {
        root = new OperatorNode("+");
        tknzr->advanceToken();
        TreeNode *rightChild = parseFormula();
        root->updateChildren(leftChild, rightChild);
        return root;
    }

    return leftChild;
}

TreeNode *FormulaParser::parseConjTerm()
{
    // your code starts here
    TreeNode *leftChildCT = parseTerm();
    TreeNode *root;
    if (tknzr->hasToken() && tknzr->getToken().content == "*")
    {
        root = new OperatorNode("*");
        tknzr->advanceToken();
        TreeNode *rightChildCT = parseConjTerm();
        root->updateChildren(leftChildCT, rightChildCT);
        return root;
    }
    return leftChildCT;
}
TreeNode *FormulaParser::parseTerm()
{
    // your code starts here
    TreeNode *t;
    if (tknzr->getToken().type == "constant")
    {
        t = new ConstantNode(tknzr->getToken().content);
        tknzr->advanceToken();
       checkSyntax('c');
        return t;
    }
    else if (tknzr->getToken().type == "variable")
    {
        t = new VariableNode(tknzr->getToken().content);
        tknzr->advanceToken();
        checkSyntax('v');
        return t;
    }
    else if (tknzr->getToken().content == "-")
    {
        t = new OperatorNode("-");
        tknzr->advanceToken();
        checkSyntax('-');
        TreeNode *lchild = parseTerm();
        t->updateLeftChild(lchild);
        return t;
    }
    else if (tknzr->getToken().content == "(")
    {
        tknzr->advanceToken();
        t = parseFormula();
        if (tknzr->hasToken() && tknzr->getToken().content == ")")
        {
            tknzr->advanceToken();
            if(tknzr->getToken().content=="(" || tknzr->getToken().type=="constant" || tknzr->getToken().type=="variable"){
                throw "Error: invalid input";
            }
            return t;
        }
        else{
            throw "Error: invalid input";
        }
    }
    else{
        throw "Error: invalid input";
    }

}

void FormulaParser::checkSyntax(char ch){
    switch (ch)
            {
                case 'c':
                    if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant"
                        || tknzr->getToken().content == "-" || tknzr->getToken().content == "(")
                    {
                         throw "Error: invalid input";
                    }
                    break;
 
                case 'v':
                    if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant"
                        || tknzr->getToken().content == "-" || tknzr->getToken().content == "(")
                    {
                        throw "Error: invalid input";
                    }
                    break;
             
                case '-':
                     if(tknzr->getToken().content == ")" || tknzr->getToken().content == "*" || tknzr->getToken().content == "+")
                     {
                     throw "Error: invalid input";
                     }
                    break;
 
                 
                default:
                    std::cout<<"INVALID INPUT";
                    break;
            }
}

TreeNode *FormulaParser::getTreeRoot()
{
    // your code starts here
    return parseFormula();
}

FormulaParser::~FormulaParser()
{
    // your code starts here
    delete tknzr;
}

