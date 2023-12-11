#include "tseitinTransformer.h"
#include "satSolver.h"
#include "treeNode.h"
#include "parser.h"
#include <iostream>
#include <cctype>
// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
bool stringValidity(std::string line)
{
  for (int i = 0; i < int(line.length()); i++)
  {
    if (isalnum(line[i]) || line[i] == '+' || isblank(line[i]) || line[i] == '-' || line[i] == '*' || line[i] == '(' || line[i] == ')')
    {
      continue;
    }
    else
    {
      return false;
    }
  }
  return true;
}
void bracketCount(std::string formula)
{
  int open = 0;
  int closed = 0;
  for (int i = 0; i < int(formula.length()); i++)
  {
    if (formula[i] == '(')
    {
      open++;
    }
    if (formula[i] == ')')
    {
      closed++;
      if (closed > open)
      {
        throw "Error: invalid input";
      }
    }
  }
  if (open != closed)
  {
    throw "Error: invalid input";
  }
}

int main()
{
  std::string line;
  while (getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
    // store each input line

    // your code starts here
    try
    {
      if (stringValidity(line))
      {
        std::string formulaStr = line; // store the formula string
        bracketCount(formulaStr);
        TreeNode *t;
        FormulaParser *formulaParser = new FormulaParser(formulaStr);
        t = formulaParser->getTreeRoot();
        TseitinTransformer *tseitinTransformer = new TseitinTransformer(t);
        std::vector<std::vector<int>> res = tseitinTransformer->transform();
        bool result = satCallingMiniSat(tseitinTransformer->getVarNum(), res);
        if (result)
        {
          std::cout << "sat" << std::endl;
        }
        else
        {
          std::cout << "unsat" << std::endl;
        }
      }
      else
      {
        throw "Error: invalid input";
      }
    }
    catch (const char *error)
    {
      std::cout << error << std::endl;
    }
  }
}
