#pragma once
#include "z3++.h"

z3::expr tseitin(std::string& current_node, Nodes& nodes, z3::context& context, z3::expr_vector& clauses, std::vector<bool>& visited);