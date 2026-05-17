#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <print>

double factorial(double n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

class TokenStream {
public:
    struct Token { char kind; double value; };
    TokenStream(std::istream& is) : input(is), full(false), last{0} {}
    Token get();
    void putback(Token t) { last = t; full = true; }
private:
    std::istream& input;
    bool full;
    Token last;
};

TokenStream::Token TokenStream::get() {
    if (full) { full = false; return last; }
    char ch;
    if (!(input >> ch)) return {0};
    switch (ch) {
        case '(': case ')': case '[': case ']': case '{': case '}':
        case '+': case '-': case '*': case '/': case '%': case '^': case '!':
            return {ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            input.putback(ch);
            double val;
            input >> val;
            return {'8', val};
        }
        default: return {ch};
    }
}

double expression(TokenStream& ts);

double primary(TokenStream& ts) {
    auto t = ts.get();
    switch (t.kind) {
        case '(': { double d = expression(ts); ts.get(); return d; }
        case '[': { double d = expression(ts); ts.get(); return d; }
        case '{': { double d = expression(ts); ts.get(); return d; }
        case '8': return t.value;
        case '-': return -primary(ts);
        case '+': return primary(ts);
        default: return 0;
    }
}

double factor(TokenStream& ts) {
    double left = primary(ts);
    auto t = ts.get();
    if (t.kind == '!') return factorial(left);
    ts.putback(t);
    return left;
}

double power(TokenStream& ts) {
    double left = factor(ts);
    auto t = ts.get();
    if (t.kind == '^') return std::pow(left, power(ts));
    ts.putback(t);
    return left;
}

double term(TokenStream& ts) {
    double left = power(ts);
    while (true) {
        auto t = ts.get();
        switch (t.kind) {
            case '*': left *= power(ts); break;
            case '/': left /= power(ts); break;
            case '%': left = std::fmod(left, power(ts)); break;
            default: ts.putback(t); return left;
        }
    }
}

double expression(TokenStream& ts) {
    double left = term(ts);
    while (true) {
        auto t = ts.get();
        switch (t.kind) {
            case '+': left += term(ts); break;
            case '-': left -= term(ts); break;
            default: ts.putback(t); return left;
        }
    }
}

int main() {

    std::ifstream ifs("input.txt");
    if (!ifs) return 1;
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        TokenStream ts(ss);
        try {
            std::print("{} = {}\n", line, expression(ts));
        } catch (...) {}
    }
    return 0;
}
