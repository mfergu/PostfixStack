 //Ferguson, Matthew c59740856
//cpsc 212 pargas lab02
#ifndef Stack_h
#define Stack_h
#include <iostream>
#include <stack>
#include <iomanip>
#include <fstream>
#include <string>

class infixToPostfix{
  public:
    infixToPostfix();
    infixToPostfix(const std::string); //changes infix string to postfix
    std::string getPostfix();
    ~infixToPostfix();
  private:
    bool isOperand(const char);
    bool isOperator(const char);
    bool isRightAssoc(const char);
    int getPreced(const char); //checks precedence
    bool testPreced(const char, const char); //finds operator of greatest precedence
    std::stack<char> operatorStack;
    std::string postfix;
  
};
#endif
