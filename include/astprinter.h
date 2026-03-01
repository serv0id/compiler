#ifndef COMPILER_ASTPRINTER_H
#define COMPILER_ASTPRINTER_H
#include <vector>
#include "expr.h"


class astprinter: public expr_visitor {
public:
    std::string print(const expr& e);
    std::any visit_binary(const binary &e) override;
    std::any visit_unary(const unary &e) override;
    std::any visit_grouping(const grouping &e) override;
    std::any visit_literal(const literal &e) override;

    std::string parenthesize(const std::string &name, const std::vector<expr *> &values);
};


#endif //COMPILER_ASTPRINTER_H