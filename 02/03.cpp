#include <iostream>

int main() {
    char c;
    std::cin >> c;
    
    switch (c) {
        case 'A'...'Z':
            std::cout << "uppercase letter\n";
            break;
        case 'a'...'z':
            std::cout << "lowercase letter\n";
            break;
        case '0'...'9':
            std::cout << "digit\n";
            break;
        case ' ': case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': 
        case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': 
        case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': 
        case '|': case '}': case '~':
            std::cout << "punctuation\n";
            break;
        default:
            std::cout << "other\n";
            break;
    }
    
    return 0;
}

// g++ -Wall -Wextra -pedantic 03.cpp