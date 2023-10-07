#include "parse/parse.h"
#include "tseitin/tseitin.h"
#include "validation/validate.h"
#include <iostream>


void solve(std::string& output_node, Nodes& nodes) {
    z3::context context;
    z3::expr_vector clauses(context);
    std::vector<bool> visited(nodes.size());

    std::cout << "Tseitin started..." << std::endl;
    tseitin(output_node, nodes, context, clauses, visited);
    std::cout << "[OK] Tseitin finished" << std::endl;

    z3::solver solver(context);

    // output node should always be of a true value
    clauses.push_back(context.bool_const(output_node.c_str()));
    std::cout << "Number of clauses: " << clauses.size() << std::endl;

    solver.add(z3::mk_and(clauses));
    std::cout << "Solving sat..." << std::endl;
    std::cout << "[OK] Result: " << solver.check() << std::endl;
}


void clean_nodes(Nodes& nodes) {
    for (auto& [name, node] : nodes) {
        delete node;
    }
}

int main() {
    Nodes nodes = {};
    std::string filename = "test.txt";

    std::cout << "Reading from file..." << std::endl;
    std::string output_node = parse_bench(filename, nodes);
    std::cout << "[OK] Got the circuit!" << std::endl;

    std::cout << "Checking cycles..." << std::endl;
    check_cycles(output_node, nodes);
    std::cout << "[OK] Finished checking cycles" << std::endl;

    solve(output_node, nodes);

    clean_nodes(nodes);
}