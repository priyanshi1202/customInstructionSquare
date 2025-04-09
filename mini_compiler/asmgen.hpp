#ifndef ASMGEN_HPP
#define ASMGEN_HPP

#include "parser.hpp"
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class AsmGen {
private:
    std::vector<std::string> instructions;
    std::unordered_map<std::string, std::string> var_registers;  // Map variables to registers
    int register_counter = 0;
    int label_counter = 0;

    std::string get_register(const std::string& var) {
        if (var_registers.find(var) == var_registers.end()) {
            // Use registers in order: eax, ebx, ecx, edx
            std::string reg;
            switch (register_counter % 4) {
                case 0: reg = "eax"; break;
                case 1: reg = "ebx"; break;
                case 2: reg = "ecx"; break;
                case 3: reg = "edx"; break;
            }
            register_counter++;
            var_registers[var] = reg;
        }
        return var_registers[var];
    }

    std::string new_label(const std::string& prefix) {
        return prefix + "_" + std::to_string(label_counter++);
    }

public:
    std::string generate(std::shared_ptr<ASTNode> node) {
        if (auto n = std::dynamic_pointer_cast<Number>(node)) {
            return std::to_string(n->value);
        }
        else if (auto v = std::dynamic_pointer_cast<Variable>(node)) {
            return get_register(v->name);
        }
        else if (auto b = std::dynamic_pointer_cast<BinOp>(node)) {
            if (b->op == "*") {
                auto left = std::dynamic_pointer_cast<Variable>(b->left);
                auto right = std::dynamic_pointer_cast<Variable>(b->right);
                if (left && right && left->name == right->name) {
                    // Square operation - make it explicit
                    std::string reg = get_register(left->name);
                    instructions.push_back("    ; SQUARE instruction: " + left->name + " * " + left->name);
                    instructions.push_back("    mov eax, " + reg);
                    instructions.push_back("    mul eax");
                    return "eax";  // Result is in eax
                }
            }
            // Regular binary operation
            std::string left = generate(b->left);
            std::string right = generate(b->right);
            if (b->op == "+") {
                instructions.push_back("    mov eax, " + left);
                instructions.push_back("    add eax, " + right);
                return "eax";
            }
            else if (b->op == "*") {
                instructions.push_back("    mov eax, " + left);
                instructions.push_back("    mul " + right);
                return "eax";
            }
        }
        else if (auto a = std::dynamic_pointer_cast<Assignment>(node)) {
            std::string reg = get_register(a->var_name);
            if (auto n = std::dynamic_pointer_cast<Number>(a->expr)) {
                instructions.push_back("    mov " + reg + ", " + std::to_string(n->value));
            } else {
                std::string result = generate(a->expr);
                instructions.push_back("    mov " + reg + ", " + result);
            }
            return "";
        }
        else if (auto p = std::dynamic_pointer_cast<Print>(node)) {
            std::string result = generate(p->expr);
            instructions.push_back("    push " + result);
            instructions.push_back("    push format");
            instructions.push_back("    call printf");
            instructions.push_back("    add esp, 8");
            return "";
        }
        return "";
    }

    std::string get_assembly() {
        std::string asm_code = R"(
section .data
    format db "%d", 10, 0

section .text
    global main
    extern printf

main:
)";

        // Add all instructions
        for (const auto& instr : instructions) {
            asm_code += instr + "\n";
        }

        // Add return
        asm_code += R"(
    ret
)";

        return asm_code;
    }
};

#endif // ASMGEN_HPP
