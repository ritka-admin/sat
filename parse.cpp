#include "parse.h"
#include <fstream>


// TODO: add node destructors
CircuitNode::CircuitNode(std::string& name, OP op = OP::NONE)
: name(name), op(op)
{}


std::string get_name_in_brackets(std::string& line) {
    std::string name;
    size_t left_bracket = line.find('(');
    size_t right_bracket = line.find(')');
    return line.substr(left_bracket + 1, right_bracket - left_bracket - 1);
}

// TODO: maybe make faster
OP find_op(std::string& line) {
    if (line.find("NOR") != std::string::npos) {
        return OP::NOR;
    } else if (line.find("NAND") != std::string::npos) {
        return OP::NAND;
    } else if (line.find("OR") != std::string::npos) {
        return OP::OR;
    } else if (line.find("AND") != std::string::npos) {
        return OP::AND;
    } else if (line.find("NOT") != std::string::npos) {
        return OP::NOT;
    } else if (line.find("XOR") != std::string::npos) {
        return OP::XOR;
    }

    throw std::runtime_error("Cannot parse the operation");
}


void parse_line(std::string& line, std::string& output_node, Nodes& nodes) {

    if (line[0] == '#') {
        return;
    }

    std::string name_in_brackets = get_name_in_brackets(line);
    if (line.find("INPUT") != std::string::npos) {
        auto node = new CircuitNode(name_in_brackets);
        nodes.insert({name_in_brackets, node});     // TODO: name_before_eq copies or what??
        return;
    } else if (line.find("OUTPUT") != std::string::npos) {
        output_node = name_in_brackets;
        return;
    }

    size_t eq = line.find('=');
    size_t first_space = line.find(' ');
    std::string name_before_eq = line.substr(0, std::min(eq, first_space));
    auto node = new CircuitNode(name_before_eq, find_op(line));
    nodes.insert({name_before_eq, node});

    size_t comma = name_in_brackets.find(',');

    // if there is more than one child
    if (comma != std::string::npos) {
        // TODO: check spaces!
        std::string first_child = name_in_brackets.substr(0, comma);
        std::string second_child = name_in_brackets.substr(comma + 2);

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