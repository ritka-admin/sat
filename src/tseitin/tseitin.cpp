#include "z3++.h"
#include "../parse/parse.h"
#include "tseitin.h"
#include <vector>


z3::expr tseitin(std::string& current_node, Nodes& nodes, z3::context& context, z3::expr_vector& clauses, std::vector<bool>& visited) {
    auto cur_var = context.bool_const(current_node.c_str());
    visited[nodes[current_node]->idx] = true;

    if (nodes[current_node]->op == OP::NONE) {
        return cur_var;
    }

    auto left_idx = nodes[nodes[current_node]->left]->idx;
    // skip visiting left node if all the clauses were added already
    auto left_var = visited[left_idx] ?
            context.bool_const(nodes[current_node]->left.c_str())
            : tseitin(nodes[current_node]->left, nodes, context, clauses, visited);

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

    auto right_idx = nodes[nodes[current_node]->right]->idx;
    // skip visiting right node if all the clauses were added already
    auto right_var = visited[right_idx] ?
            context.bool_const(nodes[current_node]->right.c_str())
            : tseitin(nodes[current_node]->right, nodes, context, clauses, visited);

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