#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

bool is_ws(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char c) { return std::isspace(c); });
}

void process(const std::string& in_path, const std::string& out_path) {
    std::ifstream ifs(in_path);
    std::ofstream ofs(out_path);
    std::string line;
    bool in_raw = false;
    while (std::getline(ifs, line)) {
        bool starts_raw = (line.find("R\"(") != std::string::npos);
        if (in_raw || starts_raw || !is_ws(line)) {
            ofs << line << "\n";
        }

        if (starts_raw) in_raw = true;
        if (line.find(")\"") != std::string::npos) in_raw = false;
    }
}

int main() {
    process("test_in.txt", "test_out.txt");
    return 0;
}
