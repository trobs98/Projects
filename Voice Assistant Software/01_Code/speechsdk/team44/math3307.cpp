/*! \brief C++ Math class, to be used by voice assistant software
*
*  This class evaluates mathematical expressions, which are given in sentence form.
*  It can handle +, -, *, and /, as well as properly implementing the order of
*  operations.
* 
*  @author Lionel Foxcroft
*/

#include <string>
#include <vector>
#include "math3307.h"

#define NUMBER 0
#define OPERATOR 1

using namespace std;

Math::Math(){}

/**
 * @brief This is the main method for this class, which takes a command, and gives a response.
 * @param command This is the command given by the user, with no punctuation
 * @return the text to be spoken out loud
*/
string Math::process_command(const string& command) {
    // split into tokens
    vector<token*> tokens; // array of tokens
    string currentWord;
    bool onlyDigits = true;
    for(auto c: command + " ") {
        if (c == ' ') {
            auto t = new token();
            if (currentWord == "Evaluate") {
                // ignore the word evaluate
            } else if (currentWord == "+") {
                t->type = OPERATOR;
                t->op = '+';
                tokens.emplace_back(t); // add a "+" token to the list
            } else if (currentWord == "-") {
                t->type = OPERATOR;
                t->op = '-';
                tokens.emplace_back(t); // add a "-" token to the list
            } else if (currentWord == "*") {
                t->type = OPERATOR;
                t->op = '*';
                tokens.emplace_back(t); // add a "*" token to the list
            } else if (currentWord == "over") {
                t->type = OPERATOR;
                t->op = '/';
                tokens.emplace_back(t); // add a "/" token to the list
            } else if (onlyDigits) {
                t->type = NUMBER;
                t->value = stoi(currentWord);
                tokens.emplace_back(t); // add a numeric token to the list
            } else {
                return "Sorry, I don't know what you mean."; // If it's not a recognized token, return an error message
            }
            currentWord = ""; // reset the current word
            onlyDigits = true; // indicate that it's all digits
        } else {
            currentWord.push_back(c); // append the character to the current word
            if (c < '0' || c > '9') { // if it's not a digit, set the flag to indicate that
                onlyDigits = false;
            }
        }
    }

    double answer = evaluate_expression(tokens); // get the answer
    string answer_str = to_string(answer); // convert it to a string
    for(int i=0; i<5; i++) // pop 5 decimal places off the end, leaving 1
        answer_str.pop_back();
    return "The answer is " + answer_str; // format it as something that can be said out loud
}

/**
 * @brief Evaluates an array of tokens to a number.
 *
 * It assumes that the only operations are +, -, *, and /, which means that it can be evaluated as a sum/difference
 * of products/quotients. It also assumes that the user won't give an expression that is meaningless (ie. "Evaluate
 * 1 over 0", or "Evaluate 1 + + 2").
 *
 * @param expr The array of tokens
 * @return The result after evaluating the expression
 */
double Math::evaluate_expression(const vector<token *>& expr) {
    double answer = 0; // the current sum of products/quotients
    double currentProduct = 0; // the current product/quotient
    char currentOperator = '+';
    for(auto t: expr) {
        if (t->type == OPERATOR) {
            if (t->op == '+' || t->op == '-') { // if it's a + or -, move onto the next product/quotient
                answer += currentProduct;
                currentProduct = 1;
            }
            currentOperator = t->op;
        } else if (currentOperator == '+') {
            currentProduct = t->value; // it will be the first token in the product/quotient
        } else if (currentOperator == '-') {
            currentProduct = -t->value; // it will be the first token in the product/quotient
        } else if (currentOperator == '*') {
            currentProduct *= t->value; // it modifies the current product/quotient
        } else if (currentOperator == '/') {
            currentProduct /= t->value; // it modifies the current product/quotient
        }
    }
    return answer + currentProduct; // terms are only added after the next +/-, so the last one is added here
}

// This function takes a command, prints it, and prints the sample output.
void test(const string& command) {
    printf("%s\n%s\n\n", command.c_str(), Math::process_command(command).c_str());
}

// The main function is only used for testing purposes. It takes a sequence of commands as arguments, and prints each
// response. An example invocation would be:
// ./math "Evaluate 1 + 1" "Evaluate 2 * 2" "Evaluate 1 + 2 * 3 - 4"

/*
int main(int argc, char* argv[]) {
    for(int i=1; i<argc; i++) {
        test(argv[i]);
    }
    printf("Other test cases:\n");
    test("Evaluate 1 + 1");
    test("Evaluate 6 - 3");
    test("Evaluate 2 * 2");
    test("Evaluate 6 over 3");
    test("Evaluate 1 + 2 * 6 over 3");
}*/
