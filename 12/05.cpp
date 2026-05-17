#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <print>

double factorial(double n) {
    if (n < 0) throw std::runtime_error("Factorial of negative number");
    if (n == 0) return 1;
    double res = 1;
    for (int i = 1; i <= static_cast<int>(n); ++i) res *= i;
    return res;
}

class TokenStream {
public:
    TokenStream(std::string_view s) : input(s), pos(0) {}

    struct Token {
        char kind;
        double value;
    };

    Token get() {
        while (pos < input.size() && std::isspace(input[pos])) pos++;
        if (pos == input.size()) return {0};

        char ch = input[pos++];
        switch (ch) {
            case '(': case ')': case '[': case ']': case '{': case '}':
            case '+': case '-': case '*': case '/': case '%': case '^': case '!':
                return {ch};
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case '.': {
                pos--;
                char* end;
                double val = std::strtod(&input[pos], &end);
                pos += (end - &input[pos]);
                return {'8', val};
            }
            default:
                throw std::runtime_error("Bad token");
        }
    }

    void putback(Token t) {
        if (t.kind == 0) return;
        last = t;
        full = true;
    }

    Token get_token() {
        if (full) { full = false; return last; }
        return get();
    }

private:
    std::string_view input;
    size_t pos;
    Token last{0};
    bool full = false;
};

// Grammar:
// Expression -> Term | Expression + Term | Expression - Term
// Term -> Power | Term * Power | Term / Power | Term % Power
// Power -> Factor | Factor ^ Power
// Factor -> Primary | Primary !
// Primary -> Number | (Expression) | [Expression] | {Expression} | -Primary | +Primary

double expression(TokenStream& ts);

double primary(TokenStream& ts) {
    auto t = ts.get_token();
    switch (t.kind) {
        case '(': {
            double d = expression(ts);
            if (ts.get_token().kind != ')') throw std::runtime_error("')' expected");
            return d;
        }
        case '[': {
            double d = expression(ts);
            if (ts.get_token().kind != ']') throw std::runtime_error("']' expected");
            return d;
        }
        case '{': {
            double d = expression(ts);
            if (ts.get_token().kind != '}') throw std::runtime_error("'}' expected");
            return d;
        }
        case '8': return t.value;
        case '-': return -primary(ts);
        case '+': return primary(ts);
        default: throw std::runtime_error("Primary expected");
    }
}

double factor(TokenStream& ts) {
    double left = primary(ts);
    TokenStream::Token t = ts.get_token();
    if (t.kind == '!') return factorial(left);
    ts.putback(t);
    return left;
}

double power(TokenStream& ts) {
    double left = factor(ts);
    TokenStream::Token t = ts.get_token();
    if (t.kind == '^') return std::pow(left, power(ts));
    ts.putback(t);
    return left;
}

double term(TokenStream& ts) {
    double left = power(ts);
    while (true) {
        TokenStream::Token t = ts.get_token();
        switch (t.kind) {
            case '*': left *= power(ts); break;
            case '/': {
                double d = power(ts);
                if (d == 0) throw std::runtime_error("Division by zero");
                left /= d;
                break;
            }
            case '%': {
                double d = power(ts);
                if (d == 0) throw std::runtime_error("Modulo by zero");
                left = std::fmod(left, d);
                break;
            }
            default: ts.putback(t); return left;
        }
    }
}

double expression(TokenStream& ts) {
    double left = term(ts);
    while (true) {
        TokenStream::Token t = ts.get_token();
        switch (t.kind) {
            case '+': left += term(ts); break;
            case '-': left -= term(ts); break;
            default: ts.putback(t); return left;
        }
    }
}

int main() {
    std::string_view tests[] = {
        "2 + 3 * 4",
        "(2 + 3) * 4",
        "10 % 3",
        "2 ^ 3",
        "5!",
        "2 ^ 3!",      // 2 ^ 6 = 64
        "[2 + {3 * 4}]",
        "10 % [2 ^ 2]" // 10 % 4 = 2
    };

    for (auto s : tests) {
        try {
            TokenStream ts(s);
            std::print("{} = {}\n", s, expression(ts));
        } catch (const std::exception& e) {
            std::print("{} -> Error: {}\n", s, e.what());
        }
    }
    return 0;
}
