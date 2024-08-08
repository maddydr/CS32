

#include <iostream>
#include "Set.h"
#include <stack>

using namespace std;



int precedence (char operation)
{
    int precedence = 0;
    
    if (operation == '!')
        precedence = 2;
    if (operation == '&')
        precedence = 1;
    if (operation == '|')
        precedence = 0;
    
    return precedence;
}

string removeSpaces(string infix)
{
    string finalresult;
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix.at(i) != ' ')
            finalresult+= infix.at(i);
    }
    
    return finalresult;
}


bool isValidString(string infix)
{
    int operatorCounter = 0;
    
    
    if (infix == "") // infix is empty
        return false;
    if(infix.at(0) == ')') // starts with a ')' char
        return false;
    if (infix.at(infix.size() - 1) == '!' || infix.at(infix.size() - 1) == '&' || infix.at(infix.size() - 1) == '|') // ends in a ! & or |
        return false;
    if (infix.at(0) == '!' || infix.at(0) == '&' || infix.at(0) == '|') // infix starts with an operator
        return false;
    
    
    int openparenCounter = 0;
    int closedparenCounter = 0;
    int chars = 0;
    
    infix = removeSpaces(infix);
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix.at(i) == '&' || infix.at(i) == '|' || infix.at(i) == '!') // ensures there are operators in the input
            operatorCounter++;
        // AFTER removing spaces, make sure no 2 letters consecutive
        if (infix.at(i) != '&' && infix.at(i) != '|' && infix.at(i) != '!' && isalpha(infix.at(i)) == 0 && infix.at(i) != '(' && infix.at(i) != ')')
            return false;
        if (infix.at(i) == '(')
        {
            if (infix.find(')') == false) // can't find matching closed parenthesis
                return false;
        }
        if (isupper(infix.at(i))) // IS AN UPPERCASE LETTER INVALID
            return false;
        if (infix.at(i) == '(')
            openparenCounter++;
        if (infix.at(i) == ')')
            closedparenCounter++;
        if (isalpha(infix.at(i)))
            chars++;
    }
    
    if (infix.size() == 1 && !isalpha(infix.at(0))) // single inputs only valid if its a char
        return false;
    
    if (chars == 1 && operatorCounter != 0)
        return false;
    
    if (openparenCounter != closedparenCounter)
        return false;

    if (operatorCounter == 0 && chars != 1) // no operators in the infix
        return false;
    
    for (int i = 0; i < infix.size() - 1; i++)
    {
        if (isalpha(infix.at(i)) == 1 && isalpha(infix.at(i + 1))) // checks for no 2 consecutive letters
            return false;
        if (infix.at(i) == '(' && infix.at(i + 1) == ')') // two parenthese () back to back
            return false;
        if (infix.at(i) == '&' || infix.at(i) == '|')
        {
            if (infix.at(i + 1) == '&' || infix.at(i + 1) == '|') // two consecutive operators VALID FOLLOWING AN EXCLAMATION POINT back to back
                return false;
        }
        if (infix.at(i) == '(' && i != 0)
        {
            if (infix.at(i - 1) != '&' && infix.at(i - 1) != '|' && infix.at(i-1) != '(')
                return false;
        }
        if (isalpha(infix.at(i))) // every char must follow one operator or parenthesis
        {
            if (infix.at(i+1) != '&' && infix.at(i+1) != '|' && infix.at(i+1) != '!' && infix.at(i+1) != '(' && infix.at(i+1) != ')')
                return false;
        }
    }
    return true;
    
}
            
            
            
            
            
int infixToPostfix(string infix, string& postfix)
{
        //if item is an OPERAND (A LETTER) append it to result sequence
        // else if item is '(' push it onto stack
        // else if current item is ')' pop OPERATORS off the stack, appending them to result sequence until you pop a '(' which you do not append
        // else the current item is an OPERATOR
            //if the operator stack empty, push current operator on stack
            // else if top of stack is ( push the current operator on stack
            // else if current operator has precedence strictly greater than operator at top, push the current operator onto the stack
            // else pop the top operator from the stack and append it to result
    
    postfix = "";
    stack<char> operators;
    
    
    if (!isValidString(infix))
    {
        // EVALUATE THE EXPRESSION TO POSTFIX
        return false;
    }
    
    // iterate over each char in the string
    infix = removeSpaces(infix);
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix.at(i);
        switch (ch)
            
        {
            case '(':
                operators.push(ch);
                break;
            case ')':
                while(operators.top() != '(')
                {
                    char popped = operators.top(); // saves top item
                    postfix+=popped; //appends to postfix expresion
                    operators.pop(); // removes item from operations stack
                }
                operators.pop(); // removes the ( from the operator stack
                break;
            case '|':
            case '&':               // DOES THIS FOLLOW PRECEDENCE RULE?
            case '!':
            {
                if (operators.empty())
                    operators.push(ch); // if stack is empty, put the operande on the stack
                else
                {
                    int opprec = precedence(ch);
                    int stackprec = precedence(operators.top());
                    while (!operators.empty() && operators.top() != '('&& opprec <= stackprec)
                    {
                        char popped = operators.top();
                        postfix += popped;
                        operators.pop(); // removes the top operator after storing it in postfix
                        if (!operators.empty())
                            stackprec = precedence(operators.top());
                    }
                    operators.push(ch);
                    break;
                    
                }
                break;
            }
                
            default :
                postfix+=ch;
                
        }
    }
        
        
    while (!operators.empty())
    {
        char popped = operators.top();
        postfix += popped;
        operators.pop();
    }

    return true;
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    if(isValidString(infix))
    {
        infixToPostfix(infix, postfix); // valid expression, set postfix to postfix version
    }
    else
        return 1; // not valid expression return 1
    
    if (isValidString(infix))
    {
        for (int i = 0; i < postfix.size(); i++)
        {
            if (postfix.at(i) != '!' && postfix.at(i) != '&' && postfix.at(i) != '|')
            {
                if (trueValues.contains(postfix.at(i)) && falseValues.contains(postfix.at(i)))
                    return 3;
                if (!trueValues.contains(postfix.at(i)) && !falseValues.contains(postfix.at(i)))
                    return 2;
            }
        }
    }
    
    
    
    stack <bool> stackOperands;
    for (int i = 0; i < postfix.size(); i++)
    {
        char ch = postfix.at(i);
        if (isalpha(ch))
        {
            if (trueValues.contains(ch))
                stackOperands.push(true);
            else if (falseValues.contains(ch))
                stackOperands.push(false);
        }
        
        else
        {
            bool operand1 = false;
            bool operand2 = false;
            switch (ch)
            {
                case '&':
                case '|':
                    if (stackOperands.size() < 2)
                        return 1;
                    operand2 = stackOperands.top();
                    stackOperands.pop();
                    operand1 = stackOperands.top();
                    stackOperands.pop();
                    
                    if (ch == '&')
                    {
                        stackOperands.push(operand2 && operand1);
                        
                    }
                    else
                    {
                        stackOperands.push(operand2 || operand1);
                    }
                    break;
                case '!':
                    if (stackOperands.size() < 1)
                        return 1;
                    operand1 = stackOperands.top();
                    stackOperands.pop();
                    stackOperands.push(!operand1);
                    break;
            }
            
        }
        
    }
    result = stackOperands.top();
    return 0;
}



int main()
        {
            string trueChars  = "tywz";
            string falseChars = "fnx";
            Set trues;
            Set falses;
            for (int k = 0; k < trueChars.size(); k++)
            {
                trues.insert(trueChars[k]);
            }
            for (int k = 0; k < falseChars.size(); k++)
                falses.insert(falseChars[k]);

            string pf;
            bool answer;
            assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
            assert(evaluate("y|", trues, falses, pf, answer) == 1);
            assert(evaluate("n t", trues, falses, pf, answer) == 1);
            assert(evaluate("nt", trues, falses, pf, answer) == 1);
            assert(evaluate("()", trues, falses, pf, answer) == 1);
            assert(evaluate("()z", trues, falses, pf, answer) == 1);
            assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
            assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
            assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
            assert(evaluate("n+y", trues, falses, pf, answer) == 1);
            assert(evaluate("", trues, falses, pf, answer) == 1);
            assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
                                   &&  pf == "ff!tn&&|"  &&  !answer);
            assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
            trues.insert('x');
            assert(evaluate("((x))", trues, falses, pf, answer) == 3);
            falses.erase('x');
            assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
            trues.erase('w');
            assert(evaluate("w| f", trues, falses, pf, answer) == 2);
            falses.insert('w');
            assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
            cout << "Passed all tests" << endl;
        }
