#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <print>

std::string_view longest_palindrome(std::string_view s) {
    size_t n = s.size();
    if (n <= 1) return s;

    std::vector<bool> dp(n * n, false);
    size_t start = 0, max_len = 1;

    for (size_t i = 0; i < n; ++i) {
        dp[i * n + i] = true;
    }

    for (size_t i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i * n + (i + 1)] = true;
            start = i;
            max_len = 2;
        }
    }

    for (size_t len = 3; len <= n; ++len) {
        for (size_t i = 0; i < n - len + 1; ++i) {
            size_t j = i + len - 1;
            if (s[i] == s[j] && dp[(i + 1) * n + (j - 1)]) {
                dp[i * n + j] = true;
                if (len > max_len) {
                    start = i;
                    max_len = len;
                }
            }
        }
    }

    return s.substr(start, max_len);
}

int main() {
    std::string_view tests[] = { "babad", "cbbd", "a", "ac", "racecar", "noon" };
    for (auto t : tests) {
        std::print("Input: {} -> Palindrome: {}\n", t, longest_palindrome(t));
    }
    return 0;
}
