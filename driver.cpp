//Ferguson, Matthew c59740856
//cpsc 212 pargas lab02
#include "Stack.h"
using namespace std;

int main ()
{
  string infix;
  cout << "\nenter an infix expression to return postfix:\n";
  getline( cin, infix);
  
  infixToPostfix test(infix);
  string post;
  post = test.getPostfix();
  cout << "\n" << post << "\n" << endl;
  
  return 0;
  
}
