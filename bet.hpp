// **************************************************************************************************************
// * Author: Samuel Lamb                                                                                        *
// * Class: cop4530                                                                                             *
// * Assignment: Assignemnt 4                                                                                   *
// * Filename: bet.hpp                                                                                          *
// * Date Created: 3/1/2020                                                                                     *
// * References: Previous projects ( mainly 3 ), cplusplus, Textbook chapter 4, Dr. Gaitros recursion examples  *
// * Textbook: Wark A. Weiss - Data Structures and Algorithm Analysis in C++                                    *                                                    
// * Description: Using a binary expression tree to convert postfix exxpression to infix. One big aspect        *
// *              of this project is to utilize recursion.                                                      *                                        
// *              Definition file for the BET nodal tree                                                        *            
// **************************************************************************************************************

#include <iostream>
#include <sstream> 
#include <string>
#include <stack>
#include <vector>

// ******************************************************************************************************************
// * Name: BET()                                                                                                    *                                                 
// * Description: Default constructor for the binary BET class.                                                     *                                      
// * Reference: Lecture Slides (COP 4530) & Textbook (For using root)                                                                                      
// * Author: Samuel Lamb                                                                                            *                          
// ******************************************************************************************************************
BET::BET()
{
    root = new BinaryNode;  
}

// ******************************************************************************************************************
// * Name: BET(const string& postfix)                                                                               *                                                 
// * Description: Takes postfix and uses it to build a tree.                                                        *                                      
// * Reference:                                                                                                     *            
// * Author: Samuel Lamb                                                                                            *                          
// ******************************************************************************************************************
BET::BET(const string postfix)
{
    root = new BinaryNode;
    buildFromPostfix(postfix);
}

// ******************************************************************************************************************
// * Name: BET(const BET & rhs)                                                                               *                                                 
// * Description: Copy                                                        *                                      
// * Reference: Textbook, pg. 142                                                                                                    *            
// * Author: Samuel Lamb                                                                                            *                          
// ******************************************************************************************************************
BET::BET(const BET& rhs) : root{nullptr}
{
    root = clone(rhs.root);
}

// ******************************************************************************************************************
// * Name: ~BET()                                                                                                                                
// * Description: Class Destructor, if root does not euqal the nul it means it has an data and needs removal.                                                                                              
// * Reference: Textbook, pg. 141                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
BET::~BET()
{
    makeEmpty(root);
}

// ******************************************************************************************************************
// * Name: bool buildFromPostfix()                                                                                                                               
// * Description: This function will build a tree using the postfix expression, it is also checking for invalid entries.  
// *              I put a few not quite necessary tests within this function but they are useful.                                                                                          
// * Reference: COP4530 Project 3 (functions) and stack overflow (stringstream functions such as tellp)                                                                                                              
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool BET::buildFromPostfix(const string & postfix)
{
    stringstream s(postfix);
    string tempString;
    stack<BinaryNode*> nodeStack;
    int andCount = 0, orCount = 0, count3 = 0;
    // bool spaceFlag;
    if (postfix.empty())
    {
        cout << "Sorry, that is an invalid empty expression, please try again\n";
        root = nullptr;
        return false;
    }
    if (!empty())
    {
        makeEmpty(root);
    }    
    while (s >> tempString)
    {
        BinaryNode *newNode = new BinaryNode(tempString);
        if (s.tellp() == 0 && count3 == 0)
        {
            if (isOperator(tempString) || tempString == "(" || tempString == ")")
            {
                cout << "Invalid expression, please try again\n";
                root = nullptr;
                return false;
                // andCount += 1;
                // nodeStack.push(newNode);
            }
            count3 += 1;
        }
        // if (tempString == " ")
        // {
        //     if (spaceFlag == true)
        //     {
        //         cout << "Please put one space between each input\n";
        //         root = nullptr;
        //         return false;
        //     }
        //     spaceFlag = true;
        // }
        if (isNotValid(tempString))
        {
            cout << "Invalid postfix expression, please try again\n";
            root = nullptr;
            return false;
        }
        if (isOperand(tempString))
        {
            andCount += 1;
            nodeStack.push(newNode);
        }
        else if (checkPrecedence(tempString) != 0)
        {
            orCount += 1;
            if (andCount == orCount)
            {
                cout << "Too few operands or incorrect order, please try again\n";
                root = nullptr;
                return false;
            }
            else
            {
                newNode -> left = nodeStack.top();
                nodeStack.pop();
                newNode -> right = nodeStack.top();
                nodeStack.pop();
                nodeStack.push(newNode);
            }
        }
    }
    if (andCount != orCount)
    {
        root = nodeStack.top();
    }
    if (nodeStack.empty())
    {
        cout << "There was an invalid space character, please try again\n";
        root = nullptr;
        return false;
    }
    return true;
}

// ******************************************************************************************************************
// * Name: const BET(const BET& rhs)                                                                                                                               
// * Description: Assignment Operator                                                                                             
// * Reference: Copy(function) + cplusplusreference                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
const BET & BET::operator=(const BET & r)
{
    root = clone(r.root);
    return *this;
}

// ******************************************************************************************************************
// * Name: void BET::printInfixExpression()                                                                                                                               
// * Description: Prints the infix form using recursion                                                                                             
// * Reference:                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
void BET::printInfixExpression()
{
    printInfixExpression(root);
    cout << endl;
}

// ******************************************************************************************************************
// * Name: void BET::printPostfixExpression()                                                                                                                               
// * Description: Prints the postfix form using recursion                                                                                             
// * Reference:                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
void BET::printPostfixExpression()
{
    printPostfixExpression(root);
    cout << endl;
}

// ******************************************************************************************************************
// * Name: size_t size()                                                                                                                               
// * Description: Returns size
// * Reference:                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
size_t BET::size()
{
    return (size(root));
}

// ******************************************************************************************************************
// * Name: size_t leaf_nodes()                                                                                                                               
// * Description: Returns number of leaf nodes                                                                                             
// * Reference:                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
size_t BET::leaf_nodes()
{
    return (leaf_nodes(root));
}

// ******************************************************************************************************************
// * Name: bool empty()                                                                                                                               
// * Description: Return true if empty                                                                                          
// * Reference: None used                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool BET::empty()
{
    if(root == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// ******************************************************************************************************************
// * Name: isOperand()                                                                                                                        
// * Description: Tests for operand                                                                                            
// * Reference: Samuel Lamb COP4530 Project 3                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool BET::isOperand(const string str)
{
	if(str != "+" &&  str != "-" && str != "*" && str != "/") // && str != "(" && str != ")" && str != "^")
    {
		return true;
    }
	else
    {
		return false;
    }
}

// ******************************************************************************************************************
// * Name: isOperator()                                                                                                                        
// * Description: Tests for operator                                                                                            
// * Reference: Samuel Lamb COP4530 Project 3                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool BET::isOperator(string &str)
{
	if(str == "+" ||  str == "-" || str == "*" || str == "/") //  || str == "^")
    {
		return true;
    }
	else
    {
		return false;
    }
}

// ******************************************************************************************************************
// * Name: int checkPrecedence                 
// * Description: Gives a numberical precedence for operations                                                                                            
// * Reference: COP4530 Project 3 (Did not really use this in project 3 but I was origionally going to)                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
int BET::checkPrecedence(const string str)
{
    if(str == "("|| str == ")")
        return (3);
	else if(str == "*" || str == "/")
		return (2);
	else if(str == "+" || str == "-")
		return (1);
	else
		return 0;
}

// ******************************************************************************************************************
// * Name: isNotValid()                                                                                                                        
// * Description: Simple test for common mistakes this program will not calculate (parens as operators, carrots, etc.)                                                                                            
// * Reference: None used                                                                                                              
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
bool BET::isNotValid(string str)
{
	if(str == "(" ||  str == ")" || str == "^" || str == "_" || str == "&" || str == "%" || str == "$" || str == "#" || str == "@" || str == "!" || str == "~") // && str != "(" && str != ")" && str != "^")
    {
		return true;
    }
	else
    {
		return false;
    }
}

// ******************************************************************************************************************
// ******************************************************************************************************************
// * Private Functions   
// ******************************************************************************************************************                                                                                                                           
// ******************************************************************************************************************


// ******************************************************************************************************************
// * Name: void printInfixExpression(BinaryNode *n) private                                                                                                                               
// * Description: Print the infix expression, making sure to constantly check for parentheses needing closure.  
// *              Using precedence, the function can ensure parens are placed correctly and the expression is posted
// *              within specifications. cplusplus was used for the logic and stackoverflow for the paren flag.                                                                                          
// * Reference: cplusplus.com & stackoverflow.com                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
void BET::printInfixExpression(BinaryNode *n)
{
	bool parenFlag = false;
    if(n != nullptr)
    {
        if(n -> left == nullptr && n -> right == nullptr)
            cout << n -> data << " ";
        else
        {
            if(checkPrecedence(n -> data) != 0 && checkPrecedence(n -> right -> data) != 0)
            {
                if(checkPrecedence(n -> data) >= checkPrecedence(n -> right -> data))
                {
					if(checkPrecedence(n -> data) == 2)
                    {
						cout << "( ";
						parenFlag = true;
					}
				}
            }
            printInfixExpression(n -> right);
            if(parenFlag == true)
            {
				cout << ") ";
            }
            parenFlag = false;
            cout << n -> data << " ";
            if(checkPrecedence(n -> data) != 0 && checkPrecedence(n -> left -> data) != 0)
            {
				if(checkPrecedence(n -> data) >= checkPrecedence(n -> left -> data))
                {
				    cout << "( ";
					parenFlag = true;
				}
            }
            printInfixExpression(n -> left);
            if(parenFlag == true)
            {
				cout << ") ";
            }
			parenFlag = false;
        }
    }    
}

// ******************************************************************************************************************
// * Name: makeEmpty()          
// * Description: Deletes element of tree pointed to                                                                                           
// * Reference: Textbook, pg. 141                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
void BET::makeEmpty(BinaryNode* &t)
{
    if (t != nullptr)
    {
        makeEmpty(t -> right);
        makeEmpty(t -> left);
        delete t;
    }
    t = nullptr;
}



// ******************************************************************************************************************
// * Name: clone(BinaryNode *t) const                     
// * Description: Clone nodes to a subtree                                                                                            
// * Reference: Textbook, Chapter 4 pg. 142                                                                                                                
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
BET::BinaryNode* BET::clone(BinaryNode *t) const
{
    if (t == nullptr)
    {
        return nullptr; 
    }
    else
    {
        return new BinaryNode(t -> data, clone(t -> left), clone(t -> right));
    }
}

// ******************************************************************************************************************
// * Name: void printPostfixfixExpression(BinaryNode *n) private                                                                                                                               
// * Description: Print the postfix expression                                                                                            
// * Reference: Textbook, lecture slides                                                                                                               
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
void BET::printPostfixExpression(BinaryNode *n)
{
    if(n != nullptr)
    {
        printPostfixExpression(n -> left);
        printPostfixExpression(n -> right);
        cout << n -> data << " ";
    }    
}

// ******************************************************************************************************************
// * Name: size_t size(BinaryNode *t)                                                                                                                                
// * Description: Returns number of nodes in subtree                                                                                            
// * Reference: Textbook chapter 4, previous size functions from past projects.
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
size_t BET::size(BinaryNode *t)
{
    if (t == nullptr)
    {
        return 0;
    }
    else
    {
        return (size(t -> right) + size(t -> left) + 1);
    }
}

// ******************************************************************************************************************
// * Name: size_t leaf_nodes(BinaryNode *t)                                                                                                                              
// * Description: Return number of leaf nodes in subtree                                                                                           
// * Reference: Textbook chapter 4                                                                                                          
// * Author: Samuel Lamb                                                                                                                      
// ******************************************************************************************************************
size_t BET:: leaf_nodes(BinaryNode *t)
{
    if(t == nullptr)
		return 0;
	else if((t -> left == nullptr) && (t -> right == nullptr))
		return 1;
	else
		return (leaf_nodes(t -> left) + leaf_nodes(t -> right)); 
}
