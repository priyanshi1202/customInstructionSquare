#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "token.hpp"

std::vector<Token> tokenize(const std::string& code) {
    std::vector<std::pair<std::string, std::string>> token_specs = {
        {"INT", "int"},
        {"PRINT", "print"},
        {"NUMBER", "\\d+"},
        {"ID", "[a-zA-Z_]\\w*"},
        {"ASSIGN", "="},
        {"MUL", "\\*"},
        {"ADD", "\\+"},
        {"LPAREN", "\\("},
        {"RPAREN", "\\)"},
        {"SEMICOLON", ";"},
        {"SKIP", "[ \\t]+"},
        {"NEWLINE", "\\n"},
        {"MISMATCH", "."}
    };

    std::string combined_regex;
    for (const auto& spec : token_specs) {
        if (!combined_regex.empty()) combined_regex += "|";
        combined_regex += "(?P<" + spec.first + ">" + spec.second + ")";
    }

    // Convert Python-style named groups to C++ group order
    std::string regex_pattern;
    std::vector<std::string> group_names;
    for (const auto& spec : token_specs) {
        group_names.push_back(spec.first);
        if (!regex_pattern.empty()) regex_pattern += "|";
        regex_pattern += "(" + spec.second + ")";
    }

    std::regex token_regex(regex_pattern);
    std::sregex_iterator it(code.begin(), code.end(), token_regex);
    std::sregex_iterator end;

    std::vector<Token> tokens;
    size_t pos = 0;

    while (it != end) {
        std::smatch match = *it;
        std::string value = match.str();
        bool matched = false;

        for (size_t i = 1; i < match.size(); ++i) {
            if (match[i].matched) {
                std::string kind = group_names[i - 1];
                if (kind == "SKIP" || kind == "NEWLINE") {
                    // Do nothing
                } else if (kind == "MISMATCH") {
                    throw std::runtime_error("Unexpected token '" + value + "' at position " + std::to_string(pos));
                } else {
                    tokens.push_back({kind, value});
                }
                matched = true;
                break;
            }
        }

        pos = match.position() + match.length();
        ++it;
    }

    return tokens;
}

#endif // LEXER_HPP
