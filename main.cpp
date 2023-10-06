#include "parse.h"
#include "tseitin.h"


int main() {
    Nodes nodes = {};
    std::string filename = "test.txt";
    std::string output_node = parse_bench(filename, nodes);
    solve(output_node, nodes);
}