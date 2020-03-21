// ***********************************************************
// * Author: Samuel Lamb                                     *
// * Class: cop4530                                          *
// * Assignment: Assignemnt 4                                *
// * Filename: bet.h                                         *
// * Date Created: 3/1/2020                                  *
// * References: Previous projects ( mainly 3 ), cplusplus   *
// *                                                         *
// * Description:                                            *
// * Header file for the BET nodal tree                      *
// * Definitions and descriptions can be seen in the         *
// * bet.hpp definition file                                 *
// ***********************************************************

#ifndef BET_H
#define BET_H 

using namespace std;

class BET
{		
	struct BinaryNode
	{
		string data;
		BinaryNode *left; 		
		BinaryNode *right;
		BinaryNode(const string & d = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : data{d}, left{l}, right{r} {}
	};

	public:		
		BET();				
		BET(const string postfix);
		BET(const BET&);							
		~BET();										
		bool buildFromPostfix(const string& postfix); 
		const BET & operator=(const BET &);			
		void printInfixExpression();	
		void printPostfixExpression();		
		size_t size();								
		size_t leaf_nodes();					
		bool empty();
		bool isOperand(string str);
		bool isOperator(string &str);
		int checkPrecedence(string str);		
		bool isNotValid(string str);					
	private:
		BinaryNode *root;
		void printInfixExpression(BinaryNode *n);	 
		void makeEmpty(BinaryNode* &t);				
		BinaryNode * clone(BinaryNode *t) const;	 
		void printPostfixExpression(BinaryNode *n); 
		size_t size(BinaryNode *t);					 
		size_t leaf_nodes(BinaryNode *t);				
};

#include "bet.hpp"

#endif