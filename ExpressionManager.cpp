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

bool ExpressionManager::isBalanced(string expression){ /// good
    stack<char> paren;
    bool balanced = true;
    int index = 0;
    while((balanced == true) && (index < expression.length())){
        if(isleftParen(expression[index])){
            paren.push(expression[index]);
        } else if(isrightParen(expression[index])){
            if(paren.empty()){
                balanced = false;
            }
            else if(!isPair(paren.top(), expression[index])){
                balanced = false;
            } else {
                paren.pop();
            }
        }
        index += 1;
    }
    if(balanced && paren.empty()){
        return true;
    }else{
        return false;
    }
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
string ExpressionManager::postfixToInfix(string postfixExpression){ //need to fix, too many invalids
    stack<string> expression;
    vector<string> tokens;
    string left_part;
    string right_part;
    string final_answer;
    string new_expression;
    tokens = parseTokens(postfixExpression);
    for(int i = 0; i < tokens.size(); i++){
        if(is_digit(tokens[i])){
            expression.push(tokens[i]);
        } else if(is_operator(tokens[i])){
            if(expression.size() >= 2){
                if(is_operator(tokens[i])){
                    right_part = expression.top();
                    expression.pop();
                    left_part = expression.top();
                    expression.pop();
                    new_expression = "( " + left_part + " " + tokens[i] + " " + right_part + " )";
                    expression.push(new_expression);
                }
            }else{
                return "invalid";
            }
        } 
    }
    if(expression.size() == 1){
        return expression.top();
    }
    else{
        return "invalid";
    }
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
                    if(right_operand != 0)
                        operands.push(left_operand / right_operand);
                } else if(tokens[i] == "*"){
                    operands.push(left_operand * right_operand);
                } else if(tokens[i] == "%"){
                    if(right_operand != 0)
                        operands.push(left_operand % right_operand);
                }
            }
            
        } else {
            return "invalid";
        }
    }
    if(!operands.empty()){
        final_answer = to_string(operands.top());
        operands.pop();
    }
    if(!operands.empty()){
        return "invalid";
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
string ExpressionManager::infixToPostfix(string infixExpression){ // only prints invalids
    string postfix;
    stack<char> operators;
    vector<string> tokens;
    tokens = parseTokens(infixExpression);
    for(int i = 0; i < tokens.size(); i++){
        if(is_digit(tokens[i])){
            postfix += tokens[i];
            postfix += " ";
        } else if(is_operator(tokens[i])){
            bool success = process_operator(operators, postfix, tokens[i][0]);
            if(!success){
                return "invalid";
            }
            //if(process operator fails){
                //cout << "an error" << endl;
            //}
        } else{
            return "invalid";
        }
    }
    while(!operators.empty()){
        postfix += operators.top();
        operators.pop();
        if(!operators.empty()){
            postfix += " ";
        }
    }
    if(postfixEvaluate(postfix) != "invalid"){
        return postfix;
    } else{
        return "invalid";
    }
    
}

bool ExpressionManager::process_operator(stack<char> &opStack, string &postfix, char &op){
    cout << op << endl;
    if((opStack.empty()) || (isleftParen(opStack.top())) || (isleftParen(op))){
        opStack.push(op);
        return true;
    } else if(isrightParen(op)){
        while(!isPair(opStack.top(), op)){
            postfix += opStack.top();
            postfix += " ";
            opStack.pop();
            if(opStack.empty()){
                return false;
            }
        }
        opStack.pop();
        return true;
    } else {
        while((!opStack.empty()) && (hasPrecendence(op, opStack.top()))){
            postfix += opStack.top();
            postfix += " ";
            opStack.pop();
        }
        opStack.push(op);
        return true;
    }
}

bool ExpressionManager::hasPrecendence(char op, char stackTop){
    if((stackTop == '*') || (stackTop == '/') || (stackTop == '%')){
        return true;
    } else if(((stackTop == '+') || (stackTop == '-')) && ((op != '*') && (op != '/') && (op != '%'))){
        return true;
    } else if(((isleftParen(stackTop)) || (isrightParen(stackTop))) && ((isleftParen(op)) || isrightParen(op))){
        return true;
    } else{
        return false;
    }
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

bool ExpressionManager::is_digit(string str){
    for(int i = 0; i < str.length(); i++){
        char s = str[i];
        if(!((s == '0') || (s == '1') || (s == '2') || (s == '3') || (s == '4') || (s == '5') || (s == '6') || (s == '7') || (s == '8') || (s == '9'))){
            return false;
        }
    }
    return true;
}

bool ExpressionManager::is_operator(string s){
    if((s == "*") || (s == "+") || (s == "-") || (s == "/") || (s == "%")){
        return true;
    }else{
        return false;
    }
}

bool ExpressionManager::isleftParen(char s){
    if((s == '[') || (s == '{') || (s == '(')){
        return true;
    }else{
        return false;
    }
}

bool ExpressionManager::isrightParen(char s){
    if((s == ']') || (s == '}') || (s == ')')){
        return true;
    }else{
        return false;
    }
}

bool ExpressionManager::isPair(char left, char right){
    if(((left == '[') && (right == ']')) || ((left == '{') && (right == '}')) || ((left == '(') && (right == ')'))){
        return true;
    }else{
        return false;
    }
}

//bool ExpressionManager::isPrecedent(string on_stack, string in_expression){
    
//}