#include "parse.h"
#include <fstream>
#include <iostream>
#include <algorithm>


CircuitNode::CircuitNode(size_t node_id, std::string& name, OP op = OP::NONE)
: idx(node_id), name(name), op(op)
{}

size_t calculate_idx() {
    static size_t idx = 0;
    size_t prev = idx;
    ++idx;
    return prev;
}

std::string get_name_in_brackets(std::string& line) {
    std::string name;
    size_t left_bracket = line.find('(');
    size_t right_bracket = line.find(')');
    return line.substr(left_bracket + 1, right_bracket - left_bracket - 1);
}

OP find_op(std::string& line) {

    size_t eq = line.find('=');
    size_t bracket = line.find('(');

    auto value = line.substr(eq + 1, bracket - eq - 1);

    if (value.find("NOR") != std::string::npos) {
        return OP::NOR;
    } else if (value.find("NAND") != std::string::npos) {
        return OP::NAND;
    } else if (value.find("XOR") != std::string::npos) {
        return OP::XOR;
    } else if (value.find("OR") != std::string::npos) {
        return OP::OR;
    } else if (value.find("AND") != std::string::npos) {
        return OP::AND;
    } else if (value.find("NOT") != std::string::npos) {
        return OP::NOT;
    }

    throw std::runtime_error("Cannot parse the operation");
}


void parse_line(std::string& line, std::string& output_node, Nodes& nodes) {

    if (line[0] == '#') {
        return;
    }

    size_t idx = calculate_idx();
    std::string name_in_brackets = get_name_in_brackets(line);
    if (line.find("INPUT") != std::string::npos) {
        auto node = new CircuitNode(idx, name_in_brackets);
        nodes.insert({name_in_brackets, node});
        return;
    } else if (line.find("OUTPUT") != std::string::npos) {
        output_node = name_in_brackets;
        return;
    }

    size_t eq = line.find('=');
    size_t first_space = line.find(' ');
    std::string name_before_eq = line.substr(0, std::min(eq, first_space));
    auto node = new CircuitNode(idx, name_before_eq, find_op(line));
    nodes.insert({name_before_eq, node});

    size_t comma = name_in_brackets.find(',');

    // if there is more than one child
    if (comma != std::string::npos) {
        std::string first_child = name_in_brackets.substr(0, comma);
        std::string second_child = name_in_brackets.substr(comma + 2);

        if (first_child.empty() || second_child.empty() ) {
            throw std::runtime_error(node->name + " represents a binary operator, but only one value was provided");
        }

        node->left = first_child;
        node->right = second_child;
        return;
    }

    node->left = name_in_brackets;
}

std::string parse_bench(std::string& filename, Nodes& nodes) {
    std::ifstream bench_file(filename);
    // TODO: can be several output_nodes?
    std::string output_node;

    if (!bench_file.is_open()) {
        throw std::runtime_error("No such file");
    }

    std::string line;

    while (bench_file) {
        std::getline(bench_file, line);

        if (line.empty())
            continue;

        parse_line(line, output_node, nodes);
    }
    return output_node;
}
