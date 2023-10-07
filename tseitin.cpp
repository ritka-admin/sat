#include "z3++.h"
#include "parse.h"
#include "tseitin.h"


// TODO: allocate instead of pushing back
z3::expr tseitin(std::string& current_node, Nodes& nodes, z3::context& context, z3::expr_vector& clauses) {
    auto cur_var = context.bool_const(current_node.c_str());

    if (nodes[current_node]->op == OP::NONE) {
        return cur_var;
    }

    auto left_var = tseitin(nodes[current_node]->left, nodes, context, clauses);

    if (nodes[current_node]->op == OP::NOT) {
        z3::expr_vector clause1(context);
        clause1.push_back(left_var);
        clause1.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause1));

        z3::expr_vector clause2(context);
        clause2.push_back(!left_var);
        clause2.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause2));

        return cur_var;
    }

    auto right_var = tseitin(nodes[current_node]->right, nodes, context, clauses);

    if (nodes[current_node]->op == OP::AND) {
        z3::expr_vector clause1(context);
        clause1.push_back(!left_var);
        clause1.push_back(!right_var);
        clause1.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause1));

        z3::expr_vector clause2(context);
        clause2.push_back(left_var);
        clause2.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause2));

        z3::expr_vector clause3(context);
        clause3.push_back(right_var);
        clause3.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause3));

        return cur_var;
    }

    if (nodes[current_node]->op == OP::OR) {
        z3::expr_vector clause1(context);
        clause1.push_back(left_var);
        clause1.push_back(right_var);
        clause1.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause1));

        z3::expr_vector clause2(context);
        clause2.push_back(!left_var);
        clause2.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause2));

        z3::expr_vector clause3(context);
        clause3.push_back(!right_var);
        clause3.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause3));

        return cur_var;
    }

    if (nodes[current_node]->op == OP::NAND) {
        z3::expr_vector clause1(context);
        clause1.push_back(!left_var);
        clause1.push_back(!right_var);
        clause1.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause1));

        z3::expr_vector clause2(context);
        clause2.push_back(left_var);
        clause2.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause2));

        z3::expr_vector clause3(context);
        clause3.push_back(right_var);
        clause3.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause3));

        return cur_var;
    }

    if (nodes[current_node]->op == OP::NOR) {
        z3::expr_vector clause1(context);
        clause1.push_back(left_var);
        clause1.push_back(right_var);
        clause1.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause1));

        z3::expr_vector clause2(context);
        clause2.push_back(!left_var);
        clause2.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause2));

        z3::expr_vector clause3(context);
        clause3.push_back(!right_var);
        clause3.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause3));

        return cur_var;
    }

    if (nodes[current_node]->op == OP::XOR) {
        z3::expr_vector clause1(context);
        clause1.push_back(!left_var);
        clause1.push_back(!right_var);
        clause1.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause1));

        z3::expr_vector clause2(context);
        clause2.push_back(left_var);
        clause2.push_back(right_var);
        clause2.push_back(!cur_var);
        clauses.push_back(z3::mk_or(clause2));

        z3::expr_vector clause3(context);
        clause3.push_back(left_var);
        clause3.push_back(!right_var);
        clause3.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause3));

        z3::expr_vector clause4(context);
        clause4.push_back(!left_var);
        clause4.push_back(right_var);
        clause4.push_back(cur_var);
        clauses.push_back(z3::mk_or(clause4));

        return cur_var;
    }

    throw std::runtime_error("No such operation");
}

void solve(std::string& output_node, Nodes& nodes) {
    z3::context context;
    z3::expr_vector clauses(context);
    std::cout << "Tseitin started" << std::endl;
    tseitin(output_node, nodes, context, clauses);
    z3::solver solver(context);

    z3::expr_vector output_clause(context);
    clauses.push_back(context.bool_const(output_node.c_str()));

    solver.add(z3::mk_and(clauses));
    std::cout << "Tseitin finished..." << std::endl;
    std::cout << solver.check() << std::endl;
}
