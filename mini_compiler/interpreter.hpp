#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

class Interpreter {
private:
    std::unordered_map<std::string, int> env;  // Symbol table

public:
    void eval(const std::shared_ptr<ASTNode>& node) {
        if (auto n = std::dynamic_pointer_cast<Number>(node)) {
            // Do nothing, Number just returns value when needed
            return;
        }
        else if (auto v = std::dynamic_pointer_cast<Variable>(node)) {
            if (env.find(v->name) == env.end()) {
                throw std::runtime_error("Undefined variable: " + v->name);
            }
            return;
        }
        else if (auto a = std::dynamic_pointer_cast<Assignment>(node)) {
            int value = eval_expr(a->expr);
            env[a->var_name] = value;
        }
        else if (auto p = std::dynamic_pointer_cast<Print>(node)) {
            int value = eval_expr(p->expr);
            std::cout << value << std::endl;
        }
        else {
            throw std::runtime_error("Unknown node type in eval()");
        }
    }

    int eval_expr(const std::shared_ptr<ASTNode>& node) {
        if (auto n = std::dynamic_pointer_cast<Number>(node)) {
            return n->value;
        }
        else if (auto v = std::dynamic_pointer_cast<Variable>(node)) {
            if (env.find(v->name) != env.end()) {
                return env[v->name];
            } else {
                throw std::runtime_error("Undefined variable: " + v->name);
            }
        }
        else if (auto b = std::dynamic_pointer_cast<BinOp>(node)) {
            // Check for square pattern
            if (b->op == "*") {
                auto left = std::dynamic_pointer_cast<Variable>(b->left);
                auto right = std::dynamic_pointer_cast<Variable>(b->right);
                if (left && right && left->name == right->name) {
                    int x = env[left->name];
                    return x * x;  // Optimized square calculation
                }
            }
            // Regular binary operation
            int left = eval_expr(b->left);
            int right = eval_expr(b->right);
            if (b->op == "+") {
                return left + right;
            }
            else if (b->op == "*") {
                return left * right;
            }
            else {
                throw std::runtime_error("Unsupported operator: " + b->op);
            }
        }
        else {
            throw std::runtime_error("Unknown node type in eval_expr()");
        }
    }
};

#endif // INTERPRETER_HPP
