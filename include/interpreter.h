#ifndef COMPILER_INTERPRETER_H
#define COMPILER_INTERPRETER_H
#include "expr.h"


class interpreter: expr_visitor {
    std::any visit_literal(const literal &e) override;

    std::any visit_grouping(const grouping &e) override;

    std::any visit_unary(const unary &e) override;

    std::any visit_binary(const binary &e) override;

    bool is_truthy(const std::any& val);

    bool is_equal(const std::any &left, const std::any &right);

    std::any evaluate(const expr &e);
public:
    void interpret(const expr &expression);
};


#endif //COMPILER_INTERPRETER_H