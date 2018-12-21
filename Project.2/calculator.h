#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include<iostream>
#include<string>
#include<cstdlib>
#include"fraction.h"
#include"stack.h"
#include"dictionary.h"


class calculator {
public:
		void ProcessSymbol(string s, int &first);
		Fraction PerformTopOperation();
		bool isOperator(char c);
		//int IntegerExtractor(string s, int index);
		//string VariableExtractor(string s, int index);
		bool hasPrecedence(char a, char b);
		void Evaluate(string s);
		 


private: 
	 Stack<Fraction> numStack;
	 Stack<char> opStack;
	 Dictionary varValues;
};


#endif

