#ifndef COMPILER_STMT_H
#define COMPILER_STMT_H
#include <any>
#include "expr.h"

struct stmt_visitor {
    virtual ~stmt_visitor() = default;
    virtual std::any visit_expr_stmt() = 0;
    virtual std::any visit_print() = 0;
};

struct stmt {
    virtual ~stmt() = default;
    virtual std::any accept(stmt_visitor& v) const = 0;
};

struct expr_stmt: stmt {
    std::unique_ptr<expr> expression;
    expr_stmt(std::unique_ptr<expr> expression) : expression(std::move(expression)) {}

    std::any accept(stmt_visitor& v) const override {
        return v.visit_expr_stmt();
    }
};

struct print: stmt {
    std::unique_ptr<expr> expression;
    print(std::unique_ptr<expr> expression) : expression(std::move(expression)) {}

    std::any accept(stmt_visitor &v) const override {
        return v.visit_print();
    }
};

#endif //COMPILER_STMT_H