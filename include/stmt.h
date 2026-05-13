#ifndef COMPILER_STMT_H
#define COMPILER_STMT_H
#include <any>
#include "expr.h"

struct print;
struct expr_stmt;
struct var;

struct stmt_visitor {
    virtual ~stmt_visitor() = default;
    virtual std::any visit_expr_stmt(const expr_stmt &e) = 0;
    virtual std::any visit_print(const print &e) = 0;
    virtual std::any visit_var(const var &e) = 0;
};

struct stmt {
    virtual ~stmt() = default;
    virtual std::any accept(stmt_visitor& v) const = 0;
};

struct expr_stmt: stmt {
    std::unique_ptr<expr> expression;
    expr_stmt(std::unique_ptr<expr> expression) : expression(std::move(expression)) {}

    std::any accept(stmt_visitor& v) const override {
        return v.visit_expr_stmt(*this);
    }
};

struct print: stmt {
    std::unique_ptr<expr> expression;
    print(std::unique_ptr<expr> expression) : expression(std::move(expression)) {}

    std::any accept(stmt_visitor &v) const override {
        return v.visit_print(*this);
    }
};

struct var: stmt {
    token name;
    std::unique_ptr<expr> initializer;
    var(token name, std::unique_ptr<expr> initializer)
        : name(std::move(name))
        , initializer(std::move(initializer)) {}

    std::any accept(stmt_visitor &v) const override {
        return v.visit_var(*this);
    }
};

#endif //COMPILER_STMT_H