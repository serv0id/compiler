#ifndef COMPILER_EXPR_H
#define COMPILER_EXPR_H
#include <memory>
#include "token.h"

struct literal;
struct grouping;
struct unary;
struct binary;

struct expr_visitor {
    virtual ~expr_visitor() = default;
    virtual std::any visit_binary(const binary& e)     = 0;
    virtual std::any visit_unary(const unary& e)       = 0;
    virtual std::any visit_grouping(const grouping& e) = 0;
    virtual std::any visit_literal(const literal& e)   = 0;
};

struct expr {
    virtual ~expr() = default;
    virtual std::any accept(expr_visitor& v) const = 0;
};

struct binary: expr {
    std::unique_ptr<expr> left;
    token op;
    std::unique_ptr<expr> right;

    binary(std::unique_ptr<expr> left, token op, std::unique_ptr<expr> right) : left(
            std::move(left)), op(std::move(op)), right(std::move(right)) {}

    std::any accept(expr_visitor& v) const override {
        return v.visit_binary(*this);
    }
};

struct unary: expr {
    token op;
    std::unique_ptr<expr> expression;

    unary(token op, std::unique_ptr<expr> expression)
    : op(std::move(op))
    , expression(std::move(expression)) {}

    std::any accept(expr_visitor& v) const override {
        return v.visit_unary(*this);
    }
};

struct grouping : expr {
    std::unique_ptr<expr> expression;

    grouping(std::unique_ptr<expr> expression)
        : expression(std::move(expression)) {}

    std::any accept(expr_visitor& v) const override {
        return v.visit_grouping(*this);
    }
};

struct literal : expr {
    std::any value;

    literal(std::any value)
        : value(std::move(value)) {}

    std::any accept(expr_visitor& v) const override {
        return v.visit_literal(*this);
    }
};


#endif //COMPILER_EXPR_H