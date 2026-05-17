#include <iostream>
#include <filesystem>
#include <regex>
#include <string>

namespace fs = std::filesystem;

void list_directory(const fs::path& p, const std::string& pattern) {
    std::regex re(pattern);
    if (!fs::exists(p) || !fs::is_directory(p)) return;
    for (const auto& entry : fs::directory_iterator(p)) {
        std::string filename = entry.path().filename().string();
        if (std::regex_search(filename, re)) {
            std::cout << filename << (entry.is_directory() ? "/" : "") << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    std::string pattern = ".*\\.cpp";
    if (argc > 1) pattern = argv[1];
    list_directory(".", pattern);
    return 0;
}

/*
Сравнение с утилитой grep:
1. Это решение фильтрует имена файлов (метаданные), а не их содержимое.
2. Использование directory_iterator эффективнее, чем ls | grep, так как нет вызова внешних процессов.
3. В отличие от grep, поиск ограничен только текущей директорией (без -r).
*/
