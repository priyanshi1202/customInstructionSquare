#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "token.hpp"

class ASTNode {
public:
    virtual std::string repr() const = 0;
    virtual ~ASTNode() {}
};

// Add operator<< for ASTNode
inline std::ostream& operator<<(std::ostream& os, const ASTNode& node) {
    os << node.repr();
    return os;
}

class Number : public ASTNode {
public:
    int value;
    Number(const std::string& val) : value(std::stoi(val)) {}
    std::string repr() const override {
        return "Number(" + std::to_string(value) + ")";
    }
};

class Variable : public ASTNode {
public:
    std::string name;
    Variable(const std::string& n) : name(n) {}
    std::string repr() const override {
        return "Variable(" + name + ")";
    }
};

class BinOp : public ASTNode {
public:
    std::shared_ptr<ASTNode> left;
    std::string op;
    std::shared_ptr<ASTNode> right;
    BinOp(std::shared_ptr<ASTNode> l, const std::string& o, std::shared_ptr<ASTNode> r)
        : left(l), op(o), right(r) {}
    std::string repr() const override {
        return "BinOp(" + left->repr() + ", " + op + ", " + right->repr() + ")";
    }
};

class Assignment : public ASTNode {
public:
    std::string var_name;
    std::shared_ptr<ASTNode> expr;
    Assignment(const std::string& name, std::shared_ptr<ASTNode> e)
        : var_name(name), expr(e) {}
    std::string repr() const override {
        return "Assignment(" + var_name + ", " + expr->repr() + ")";
    }
};

class Print : public ASTNode {
public:
    std::shared_ptr<ASTNode> expr;
    Print(std::shared_ptr<ASTNode> e) : expr(e) {}
    std::string repr() const override {
        return "Print(" + expr->repr() + ")";
    }
};

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos = 0;

    Token current() {
        if (pos < tokens.size()) return tokens[pos];
        return { "EOF", "" };
    }

    std::string eat(const std::string& expected_type) {
        Token tok = current();
        if (tok.type == expected_type) {
            pos++;
            return tok.value;
        } else {
            throw std::runtime_error("Expected " + expected_type + " got " + tok.type);
        }
    }

public:
    Parser(const std::vector<Token>& t) : tokens(t) {}

    std::vector<std::shared_ptr<ASTNode>> parse() {
        std::vector<std::shared_ptr<ASTNode>> statements;
        while (current().type != "EOF") {
            statements.push_back(statement());
        }
        return statements;
    }

    std::shared_ptr<ASTNode> statement() {
        Token tok = current();

        if (tok.type == "INT") {
            eat("INT");
            std::string var_name = eat("ID");
            eat("ASSIGN");
            auto expr = expression();
            eat("SEMICOLON");
            return std::make_shared<Assignment>(var_name, expr);
        } else if (tok.type == "PRINT") {
            eat("PRINT");
            eat("LPAREN");
            auto expr = expression();
            eat("RPAREN");
            eat("SEMICOLON");
            return std::make_shared<Print>(expr);
        } else {
            throw std::runtime_error("Unexpected statement start: " + tok.type);
        }
    }

    std::shared_ptr<ASTNode> expression() {
        auto node = term();
        while (current().type == "ADD") {
            std::string op = eat("ADD");
            node = std::make_shared<BinOp>(node, op, term());
        }
        return node;
    }

    std::shared_ptr<ASTNode> term() {
        auto node = factor();
        while (current().type == "MUL") {
            std::string op = eat("MUL");
            node = std::make_shared<BinOp>(node, op, factor());
        }
        return node;
    }

    std::shared_ptr<ASTNode> factor() {
        Token tok = current();
        if (tok.type == "NUMBER") {
            eat("NUMBER");
            return std::make_shared<Number>(tok.value);
        } else if (tok.type == "ID") {
            eat("ID");
            return std::make_shared<Variable>(tok.value);
        } else if (tok.type == "LPAREN") {
            eat("LPAREN");
            auto expr = expression();
            eat("RPAREN");
            return expr;
        } else {
            throw std::runtime_error("Unexpected token in factor: " + tok.type);
        }
    }
};

#endif // PARSER_HPP
