#include "ExpressionManager.h"
#include <vector>
#include <string>
#include <locale>

ExpressionManager::ExpressionManager(){
    
}
ExpressionManager::~ExpressionManager(){
    
}

/*
* Checks whether an expression is balanced on its parentheses
*
* - The given expression will have a space between every number or operator
*
* @return true if expression is balanced
* @return false otherwise
*/

bool ExpressionManager::isBalanced(string expression){
    
}

/**
* Converts a postfix expression into an infix expression
* and returns the infix expression.
*
* - The given postfix expression will have a space between every number or operator.
* - The returned infix expression must have a space between every number or operator.
* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix expression.
* otherwise, return the correct infix expression as a string.
*/
string ExpressionManager::postfixToInfix(string postfixExpression){
    
}
/*
* Evaluates a postfix expression returns the result as a string
*
* - The given postfix expression will have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix Expression
* otherwise, return the correct evaluation as a string
*/
string ExpressionManager::postfixEvaluate(string postfixExpression){
    stack<int> operands;
    vector<string> tokens;
    int right_operand;
    int left_operand;
    int token_temp;
    string final_answer;
    locale loc;
    tokens = parseTokens(postfixExpression);
    //for(int i = 0; i < postfixExpression.length(); i++){  //move the string into a vector of tokens
        //if(postfixExpression.at(i) != ' '){
            //tokens.push_back(postfixExpression.at(i));
        //}
    //}
    for(int i = 0; i < tokens.size(); i++){     //put the digits 
        if(is_digit(tokens[i])){
            token_temp = stoi(tokens[i]);
            operands.push(token_temp);
        }
        else if(is_operator(tokens[i])){
            if(operands.size() >= 2){
                right_operand = operands.top();
                operands.pop();
                left_operand = operands.top();
                operands.pop();
                if(tokens[i] == "+"){
                    operands.push(left_operand + right_operand);
                } else if(tokens[i] == "-"){
                    operands.push(left_operand - right_operand);
                } else if(tokens[i] == "/"){
                    operands.push(left_operand / right_operand);
                } else if(tokens[i] == "*"){
                    operands.push(left_operand * right_operand);
                }
            }
            
        } else {
            cout << "Error, all tokens must be integers or operators." << endl;
        }
    }
    final_answer = to_string(operands.top());
    operands.pop();
    if(!operands.empty()){
        cout << "Invalid expression" << endl;
        return "";
    }
    return final_answer;
}


/*
* Converts an infix expression into a postfix expression
* and returns the postfix expression
*
* - The given infix expression will have a space between every number or operator.
* - The returned postfix expression must have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if infixExpression is not a valid infix expression.
* otherwise, return the correct postfix expression as a string.
*/
string ExpressionManager::infixToPostfix(string infixExpression){
    string postfix;
    stack<string> operators;
    vector<string> tokens;
    tokens = parseTokens(infixExpression);
    for(int i = 0; i < tokens.size(); i++){
        if(is_digit(tokens[i])){
            postfix += tokens[i];
            postfix += " ";
        } else if(is_operator(tokens[i])){
            //process_operator(stack and postfix);
            //if(process operator fails){
                //cout << "an error" << endl;
            //}
        } else{
            cout << "SYNTAX ERROR, all tokens must be digits or operators." << endl;
        }
    }
    postfixEvaluate(postfix);
    
}

vector<string> ExpressionManager::parseTokens(string expression)
{
  stringstream ss(expression);
  string token;
  vector<string> tokens;
  while(getline(ss, token, ' '))
  {
    tokens.push_back(token);
  }
  return tokens;
}

bool ExpressionManager::is_digit(string s){
    if((s == "0") || (s == "1") || (s == "2") || (s == "3") || (s == "4") || (s == "5") || (s == "6") || (s == "7") || (s == "8") || (s == "9")){
        return true;
    }else{
        return false;
    }
}

bool ExpressionManager::is_operator(string s){
    if((s == "*") || (s == "+") || (s == "-") || (s == "/")){
        return true;
    }else{
        return false;
    }
}