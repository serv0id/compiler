#include "astprinter.h"
#include <vector>

std::string astprinter::print(const expr& e) {
    return std::any_cast<std::string>(e.accept(*this));
}

std::any astprinter::visit_binary(const binary& e) {
    std::vector<expr*> values;
    values.push_back(e.left.get());
    values.push_back(e.right.get());

    return parenthesize(e.op.get_lexeme(), values);
}

std::any astprinter::visit_unary(const unary& e) {
    std::vector<expr*> values;
    values.push_back(e.expression.get());

    return parenthesize(e.op.get_lexeme(), values);
}

std::any astprinter::visit_grouping(const grouping& e) {
    std::vector<expr*> values;
    values.push_back(e.expression.get());

    return parenthesize("group", values);
}

// gpt generated
std::any astprinter::visit_literal(const literal& e) {
    if (!e.value.has_value()) {
        return std::string("nil");
    }

    if (e.value.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(e.value));
    }

    if (e.value.type() == typeid(bool)) {
        return std::any_cast<bool>(e.value) ? "true" : "false";
    }

    if (e.value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(e.value);
    }

    return std::string("unknown");
}

std::string astprinter::parenthesize(const std::string& name, const std::vector<expr*>& values) {
    std::string final_string("(" + name);

    for (const expr* value: values) {
        final_string += " ";
        final_string += std::any_cast<std::string>(value->accept(*this));
    }

    final_string += ")";

    return final_string;
}