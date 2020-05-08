//
// Created by Lionel on 2019-10-31.
//

#ifndef TEAM44_MATH_H
#define TEAM44_MATH_H

struct token {
    int type;
    int value;
    char op;
};

class Math {
public:
    Math();
    static std::string process_command(const std::string& command);
private:
    static double evaluate_expression(const std::vector<token *>& expr);
};

#endif //TEAM44_MATH_H
