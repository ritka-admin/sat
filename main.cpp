#include "parse.h"
#include "tseitin.h"
#include <iostream>


int main() {
    Nodes nodes = {};
    std::string filename = "test.txt";
    std::cout << "Reading from file..." << std::endl;
    // TODO: clean all nodes after work
    std::string output_node = parse_bench(filename, nodes);
    std::cout << "Solving..." << std::endl;
    solve(output_node, nodes);
}