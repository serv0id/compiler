#include "interpreter.h"
#include <iostream>
#include <utility>
#include "lox.h"
#include "runtimeerror.h"

std::any interpreter::visit_literal(const literal& e) {
    return e.value;
}

std::any interpreter::visit_grouping(const grouping& e) {
    return evaluate(*e.expression);
}

void check_number_operand(token op, const std::any& operand) {
    if (operand.type() == typeid(double)) return;
    throw RuntimeError(std::move(op), "Operand must be a number.");
}

void check_number_operands(token op, const std::any& left, const std::any& right) {
    if (left.type() == typeid(double) && right.type() == typeid(double)) return;
    throw RuntimeError(std::move(op), "Operands must be numbers.");
}


std::any interpreter::visit_unary(const unary& e) {
    const std::any right = evaluate(*e.expression);

    switch (e.op.get_type()) {
        case BANG:
            return !is_truthy(right);
        case MINUS:
            check_number_operand(e.op, right);
            const auto value = std::any_cast<double>(right);
            return -value;
    }

    return nullptr;
}

std::any interpreter::visit_binary(const binary& e) {
    const std::any left = evaluate(*e.left);
    const std::any right = evaluate(*e.right);

    switch (e.op.get_type()) {
        case MINUS:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) - std::any_cast<double>(right);
        case STAR:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) * std::any_cast<double>(right);
        case SLASH:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) / std::any_cast<double>(right);
        case PLUS:
            if (left.type() == typeid(double) && right.type() == typeid(double)) {
                return std::any_cast<double>(left) + std::any_cast<double>(right);
            }
            if (left.type() == typeid(std::string) && right.type() == typeid(std::string)) {
                return std::any_cast<std::string>(left) + std::any_cast<std::string>(right);
            }
            throw RuntimeError(e.op, "Operands must be two numbers or two strings.");
        case GREATER:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) > std::any_cast<double>(right);
        case GREATER_EQUAL:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) >= std::any_cast<double>(right);
        case LESS:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) < std::any_cast<double>(right);
        case LESS_EQUAL:
            check_number_operands(e.op, left, right);
            return std::any_cast<double>(left) <= std::any_cast<double>(right);
        case BANG_EQUAL:
            return !is_equal(left, right);
        case EQUAL_EQUAL:
            return is_equal(left, right);
    }

    return std::any{};
}

std::string stringify(const std::any& val) {
    if (!val.has_value()) return "nil";
    if (val.type() == typeid(double)) {
        std::string s = std::to_string(std::any_cast<double>(val));
        s.erase(s.find_last_not_of('0') + 1);
        if (s.back() == '.') s.pop_back();
        return s;
    }
    if (val.type() == typeid(bool)) {
        return std::any_cast<bool>(val) ? "true" : "false";
    }
    if (val.type() == typeid(std::string)) {
        return std::any_cast<std::string>(val);
    }
    return "<unknown>";
}

std::any interpreter::visit_expr_stmt(const expr_stmt &e) {
    evaluate(*e.expression);
    return {};
}

std::any interpreter::visit_print(const print& e) {
    std::any val = evaluate(*e.expression);
    std::cout << stringify(val) << std::endl;
    return {};
}

bool interpreter::is_truthy(const std::any& val) {
    if (!val.has_value()) return false;
    if (val.type() == typeid(bool)) return std::any_cast<bool>(val);
    return true;
}

bool interpreter::is_equal(const std::any& left, const std::any& right) {
    if (!left.has_value() && !right.has_value()) return true;
    if (!left.has_value()) return false;

    if (left.type() == typeid(bool) && right.type() == typeid(bool)) {
        return std::any_cast<bool>(left) == std::any_cast<bool>(right);
    }

    if (left.type() == typeid(double) && right.type() == typeid(double)) {
        return std::any_cast<double>(left) == std::any_cast<double>(right);
    }

    if (left.type() == typeid(std::string) && right.type() == typeid(std::string)) {
        return std::any_cast<std::string>(left) == std::any_cast<std::string>(right);
    }

    return false;
}

std::any interpreter::evaluate(const expr& e) {
    return e.accept(*this);
}

void interpreter::execute(std::unique_ptr<stmt>& stmt) {
    stmt->accept(*this);
}

void interpreter::interpret(std::vector<std::unique_ptr<stmt>>& stmts) {
    try {
        for (auto& stmt : stmts) {
            execute(stmt);
        }
    } catch (RuntimeError& e) {
        lox::runtime_error(e);
    }
}