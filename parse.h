#pragma once
#include <string>
#include <vector>
#include <unordered_map>

enum OP { NOT, AND, OR, NOR, NAND, XOR, NONE};

struct CircuitNode {
    std::string name;
    OP op;
    size_t idx;
    std::string left;
    std::string right;

    CircuitNode(size_t idx, std::string& name, OP op);
};

using Nodes = std::unordered_map<std::string, CircuitNode*>;

std::string parse_bench(std::string& filename, Nodes& nodes);