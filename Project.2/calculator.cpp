#include"calculator.h"
#include <iostream>

calculator myCalculator;

bool calculator::hasPrecedence(char a, char b)
{
	if(a == '*' || a == '/')
		return true;
	if(b == '*' || b == '/')
		return false;
	if(a == '+' || a == '-')
		return true;
	return false;
}

bool calculator::isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

/*string calculator::VariableExtractor(string s, int index)
{
	string varName = "";
	for(int i = index; i <= s.length(); i++)
	{
		
		if(!isOperator(s[i]))
		{
			varName += s[i];
		}
		else 
		{
			break;
		}
		
	}
	return varName;
}*/

Fraction calculator::PerformTopOperation()
{

    Fraction a = numStack.pop();
    Fraction b = numStack.pop();
    char c = opStack.pop();
    if(c == '+')
    {
    	return (a+b);
    }
    else if(c == '-')
    {
    	return (a-b);
    }
    else if(c == '*')
    {
    	return (a*b);
    }
    else if( c == '/')  
    { 
   	   return (a/b);
    }
    else 
    	return 0;
}




void calculator::ProcessSymbol(string s, int &first)
{	
	int digitVal = 0;
	string varName= "";
	//std::cout << "x" << std::endl;
	while(first<s.length()) 
	{
	//std::cout << "x" <<first << std::endl;
		if(isdigit(s[first]))
		{
		  digitVal = 0;
		   while(isdigit(s[first])) 
		    {
			digitVal = 10*digitVal + s[first] - '0';
			first++;
	     	}
		 numStack.push(Fraction(digitVal));
//		 first++;
	    }
	    else if(isalpha(s[first]) || s[first] == '_')
	    {
	     while(first<s.length() && (isalnum(s[first]) || s[first] == '_'))
	     {
	     	varName += s[first];
	     	first++;
	     }
	     numStack.push(varValues.search(varName));
	 
	    }
		else if(s[first] == '(')
		{
			opStack.push(s[first]);
			first ++;
		}
		else if(s[first] == ')')
		{
			while(opStack.peek() != '(')
			{
				numStack.push(myCalculator.PerformTopOperation());
			}
			opStack.pop();
			first++;
		}
		else if(isOperator(s[first]))
		{
			while(myCalculator.hasPrecedence(opStack.peek(), s[first]))
			{
			 numStack.push(myCalculator.PerformTopOperation());
			}
			opStack.push(s[first]);
			first++;
		}
		else
			first++;
	}

}
void calculator::Evaluate(string s)
{
	numStack.clear();
	opStack.clear();
	opStack.push('$');
	int first = 0;
	string dest = "";

 	for(int i = first; i < s.length(); i++)
 	{
 		if(s[i] == '=')
 		{
 			first = i+1;
 			int index = 0;
			while(index < s.length() && (isalnum(s[index]) || s[index] == '_'))
			{
				dest += s[index];
				index++;
			}
					
 		}

 	}
// 	std::cout << first << dest << std::endl;

 	while (first < s.length()) {
	 	myCalculator.ProcessSymbol(s,first);

 	}
 

	while(opStack.peek() != '$')
	{
	 numStack.push(myCalculator.PerformTopOperation());
	}
	if(dest != "")
	{
	varValues.insert(dest, numStack.peek());
	}
 std::cout << "Answer = " << numStack.peek() << endl;
 
}


int main(int argc, char const *argv[])
{
	string s;

	while(true)
	{
	std::cout << "Enter the values which needs to be Evaluated" << std::endl;
	getline(cin,s);
	myCalculator.Evaluate(s);
	if(!cin)
	 {
	 	break;
	 }
	
	}



	return 0;
}
