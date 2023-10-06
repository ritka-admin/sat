#include <string>
#include <vector>

enum OP { NOT, AND, OR, NOR, NAND, XOR , NONE};

struct CircuitNode {
    std::string name;
    size_t id;
    OP op;
    std::string left;
    std::string right;

    CircuitNode(size_t node_id, std::string& name, OP op);
};

std::string parse_bench(std::string& filename);