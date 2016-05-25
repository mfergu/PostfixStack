//Ferguson, Matthew c59740856
//cpsc 212 pargas assignment 2
#include "Stack.h"
using namespace std;

//default constructor
infixToPostfix::infixToPostfix()
{
}

//test the parenthesis of input and make it postfix
infixToPostfix::infixToPostfix(const string infix)
{
  
  if(testParenths(infix) == false)
    cout << "\nparenthesis are bad\n"; 

  if(testSequence(infix) == false)
    cout << "\n operator sequence is bad\n"; 
  makePostfix(infix);
}

//return postfix string
string infixToPostfix::getPostfix()
{
  return postfix;
}
  
  
//create a stack to test the parenthesis of the input string
bool infixToPostfix::testParenths( const string input)
{
  string temp = input;
  stack<char> *parenStack = new stack<char>;
  //for each element of the string
  for(unsigned int index = 0; index < temp.size(); index++)
  {
    //if opening parenthesis push to stack
    if(temp[index] == '(' || temp[index] == '{' || temp[index] == '[')
      parenStack->push(temp[index]);
    //if closing parenthesis pop from stack
    else if(temp[index] == ')' || temp[index] == '}' || temp[index] == ']')
    {
      //if closing parenthesis and stack is empty
      if(parenStack->empty()) 
      {
        //parenthesis are incorrect
        delete parenStack;
        return false;
      }
      
      //if closing parenthesis and stack is not empty
      else
        parenStack->pop();
    }
  }
  //after all elements pushed or popped if empty stack parenthesis are good
  return parenStack->empty()? true : false;
}

bool infixToPostfix::testSequence(const string infix)
{
  unsigned int index = 0;
  queue<char> *testQueue = new queue<char>;
  while( index < infix.size())
  {
    if(isOperand(infix[index]) || isOperator(infix[index]))
    {
      testQueue->push(infix[index]);
    }
    index++;
  }

  char temp;
  for(index = 0; index<infix.size(); index++)
  { 
    temp = testQueue->front();
      cout << temp;
    testQueue->pop();
    if(isOperator(testQueue->front()) && isOperator(temp) &&  temp != '-')
      return false;
  }
  return true;
}
    
//takes infix string converts it to postfix accounting for unary '-'
void infixToPostfix::makePostfix(const string infix)
{  
  string temp = infix;
  for(unsigned int index = 0; index < infix.size(); ++index)
  {
    

    //if parenthesis
    if( temp[index] == '(')
    {
      operatorStack.push('(');
    }
      

    // find unary minus and replace with '~'
    else if( temp[index] == '-')
    {
      //find previous operator
      unsigned int jndex = index;
      do{
        jndex--;
        if(isOperator(temp[jndex]))
        { 
          temp[index] = '~';
          break;
        }
      }
      while(temp[jndex] == ' ');

      //if the last input were two consecutive operators 
    }
        
        
    if(isOperator( temp[index]))
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
      operatorStack.push(temp[index]);
    }

    // if an operand
    else if( isOperand( temp[index]))
    {
      //concat to string postfix
      postfix += temp[index];
    }

    //if a closing parenthesis
    else if( temp[index] == ')')
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


//finds whether input is int or variable
bool infixToPostfix::isOperand( const char temp)
{
  if(temp >='0' && temp <='9')
    return true;
  if(temp >='a' && temp <= 'z')
    return true;
  if(temp >='A' && temp <= 'Z')
    return true;
  return false;
}  

//finds if input is an acceptable operator
bool infixToPostfix::isOperator( const char temp)
{
  if( temp == '-' || temp == '+' || temp == '/' || temp == '*'\
    || temp == '^' || temp == '~' || temp == '=')
  {
    return true;
  }
  return false;
}

//finds whether the operator is right associative
bool infixToPostfix::isRightAssoc( const char temp)
{
  if(temp == '^' || temp == '~')
    return true;
  return false;
}

//finds operator precedence
int infixToPostfix::getPreced( const char temp)
{
  int weight = -1;
  switch( temp)
  {
    case'=':
      weight = -1; break;
    case'+':
    case'-':
      weight = 1; break;
    case'*':
    case'/':
      weight = 2; break;
    case'^':
      weight = 3; break;
    case'~':
      weight = 4; break;
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
