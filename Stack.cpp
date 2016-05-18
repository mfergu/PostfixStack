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
    
    while( infix[index] == ' ')
      ++index;  
    
    if( infix[index] == '(')
      operatorStack.push('(');

    else if( isOperator( infix[index]))
    {
      while( !operatorStack.empty() &&\
        testPreced(operatorStack.top(), infix[index]))
      {
        postfix += operatorStack.top();
        operatorStack.pop(); 
      }
    
      operatorStack.push(infix[index]);
    }

    else if( isOperand( infix[index]))
    {
      postfix += infix[index];
    }

    else if( infix[index] == ')')
    {
      while(!operatorStack.empty() && operatorStack.top() != '(')
      {
        postfix += operatorStack.top();
        operatorStack.pop();
      }
    
    operatorStack.pop();
    }
  } 

  while( !operatorStack.empty())
  {
    postfix += operatorStack.top();
    operatorStack.pop();
  }
}
  
string infixToPostfix::getPostfix()
{
  return postfix;
}
  
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

bool infixToPostfix::isOperator( const char temp)
{
  if( temp == '-' || temp == '+' || temp == '/' || temp == '*'\
    || temp == '^')
    return true;
  return false;
}

bool infixToPostfix::isRightAssoc( const char temp)
{
  if(temp == '^')
    return true;
  return false;
}

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
  
infixToPostfix::~infixToPostfix()
{
}
