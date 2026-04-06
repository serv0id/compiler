#ifndef COMPILER_INTERPRETER_H
#define COMPILER_INTERPRETER_H
#include "expr.h"
#include "stmt.h"
#include <vector>

class interpreter: public expr_visitor, public stmt_visitor {
    std::any visit_literal(const literal &e) override;

    std::any visit_grouping(const grouping &e) override;

    std::any visit_unary(const unary &e) override;

    std::any visit_binary(const binary &e) override;

    std::any visit_expr_stmt(const expr_stmt &e) override;

    std::any visit_print(const print &e) override;

    bool is_truthy(const std::any& val);

    bool is_equal(const std::any &left, const std::any &right);

    std::any evaluate(const expr &e);

    void execute(std::unique_ptr<stmt> &stmt);

public:
    void interpret(std::vector<std::unique_ptr<stmt>>& stmts);
};


#endif //COMPILER_INTERPRETER_H