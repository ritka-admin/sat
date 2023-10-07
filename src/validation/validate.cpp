#include "validate.h"
#include <vector>
#include <stdexcept>


void dfs(std::string& current_node, std::vector<bool>& visited, std::vector<bool>& stack, Nodes& nodes) {

    auto cur_idx = nodes[current_node]->idx;
    if (stack[cur_idx]) {
        throw std::runtime_error("Invalid schema: cycle");
    }

    if (visited[cur_idx])
        return;

    visited[cur_idx] = true;
    stack[cur_idx] = true;

    if (!nodes[current_node]->left.empty()) {
        dfs(nodes[current_node]->left, visited, stack, nodes);
    }

    if (!nodes[current_node]->right.empty()) {
        dfs(nodes[current_node]->right, visited, stack, nodes);
    }
    stack[cur_idx] = false;
}

void check_cycles(std::string& output_node, Nodes& nodes) {
    std::vector<bool> visited(nodes.size(), false);
    std::vector<bool> stack(nodes.size());
    dfs(output_node, visited, stack, nodes);
}
