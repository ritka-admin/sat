#include <fstream>
#include <vector>
#include <string>


struct CircuitNode {
    std::string name; // TODO: just number?

    CircuitNode(std::string&& name)
    : name(name)
    {}
};

struct InputNode : CircuitNode {

    InputNode(std::string&& name)
    : CircuitNode(std::move(name))
    {}
};

struct OutputNode : CircuitNode {

    OutputNode(std::string&& name)
    : CircuitNode(std::move(name))
    {}
};

struct InternalNode : CircuitNode {
    std::string op;
};

using Circuit = std::vector<CircuitNode>;


void parse_line(std::string& line, CircuitNode** node) {

    if (line[0] == '#') {
        return;
    }

    if (auto res = line.find("INPUT") != std::string::npos) {
        *node = new InputNode(line.substr(res));
    } else if (auto res = line.find("OUTPUT") != std::string::npos) {
        *node = new OutputNode(line.substr(res));
    }
}

Circuit parse_bench(std::string& filename) {
    std::ifstream bench_file(filename);
    Circuit circuit;

    if (bench_file.is_open()) {
        std::string line;

        while (bench_file) {
            std::getline(bench_file, line);
            CircuitNode* node;
            parse_line(line, &node);

            if (node != nullptr) {

            }

        }

    }
}