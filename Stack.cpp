//Ferguson, Matthew c59740856
//cpsc 212 pargas lab02
#include "Stack.h"
using namespace std;

infixToPostfix::infixToPostfix()
{
  postfix = "";
}

infixToPostfix::infixToPostfix(const string infix)
{
  postfix = "";
  for(int index = 0; index < infix.size(); ++index)
  {
    
    //remove blank space
    while( infix[index] == ' ')
      ++index;  
    
    //if parenthesis
    if( infix[index] == '(')
      operatorStack.push('(');

    // if an operator
    else if( isOperator( infix[index]))
    {
      //test for empty stack and operator precedence
      while( !operatorStack.empty() &&\
        testPreced(operatorStack.top(), infix[index]))
      {
        //concat to string postfix
        postfix += operatorStack.top();
        operatorStack.pop(); 
      }
    
      //push operator
      operatorStack.push(infix[index]);
    }

    // if an operand
    else if( isOperand( infix[index]))
    {
      //concat to string postfix
      postfix += infix[index];
    }

    //if a closing parenthesis
    else if( infix[index] == ')')
    {
      //while the stack is not empty and opposite parenthesis not found
      while(!operatorStack.empty() && operatorStack.top() != '(')
      {
        //concat to string postfix
        postfix += operatorStack.top();
        operatorStack.pop();
      }
    
    //pop operator
    operatorStack.pop();
    }
  } 

  //while the stack is not empty
  while( !operatorStack.empty())
  {
    //concat operators to string postfix
    postfix += operatorStack.top();
    operatorStack.pop();
  }
}
  
//get string postfix
string infixToPostfix::getPostfix()
{
  return postfix;
}
  
//finds whether input is int or variable
bool infixToPostfix::isOperand( const char temp)
{
  if(temp >= '0' && temp <='9')
    return true;
  if(temp>= 'a' && temp <= 'z')
    return true;
  if(temp>='A' && temp <= 'Z')
    return true;
  return false;
}  

//finds whether input is an acceptable operator
bool infixToPostfix::isOperator( const char temp)
{
  if( temp == '-' || temp == '+' || temp == '/' || temp == '*'\
    || temp == '^')
    return true;
  return false;
}

//finds whether the operator is right associative
bool infixToPostfix::isRightAssoc( const char temp)
{
  if(temp == '^')
    return true;
  return false;
}

//finds operator precedence
int infixToPostfix::getPreced( const char temp)
{
  int weight = -1;
  switch( temp)
  {
    case'+':
    case'-':
      weight = 1; break;
    case'*':
    case'/':
      weight = 2; break;
    case'^':
      weight = 3; break;
  }
    
  return weight;
}

//tests the precedence of two operators
bool infixToPostfix::testPreced(const char temp1, const char temp2)
{
  int temp1Weight = getPreced( temp1);
  int temp2Weight = getPreced( temp2);
  if( temp1Weight == temp2Weight)
  {
    if( isRightAssoc(temp1))
      return false;
    return true;
  }
  
  return temp1Weight > temp2Weight ? true : false;
}
  
//default destructor
infixToPostfix::~infixToPostfix()
{
}
