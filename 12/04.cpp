#include <iostream>
#include <regex>
#include <string>
#include <print>

int main() {
    std::string text = R"(
        Contact us at support@example.com or info@domain.org.
        For sales, email sales.dept@company.co.uk.
        Incorrect emails: plain-text, @no-user.com, user@.no-tld.
    )";

    std::regex email_pattern(R"(([a-zA-Z0-9._%+-]+@([a-zA-Z0-9.-]+\.[a-zA-Z]{2,})))");

    auto begin = std::sregex_iterator(text.begin(), text.end(), email_pattern);
    auto end = std::sregex_iterator();

    std::print("Extracted emails and domains:\n");
    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;
        std::print("Email: {:25} | Domain: {}\n", match[1].str(), match[2].str());
    }

    return 0;
}
