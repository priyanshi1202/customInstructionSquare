#ifndef COMPILE_AND_RUN_HPP
#define COMPILE_AND_RUN_HPP

#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "asmgen.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class CompileAndRun
{
public:
    CompileAndRun(const std::string &src)
    {
        std::cout << "\n<---Tokenisation--->\n"
                  << std::endl;

        std::vector<Token> tokens = tokenize(src);
        for (const auto &token : tokens)
        {
            std::cout << "(" << token.type << ", " << token.value << ")" << std::endl;
        }

        std::cout << "\n<---Abstract Parse Tree--->\n"
                  << std::endl;

        Parser parser(tokens);
        std::vector<std::shared_ptr<ASTNode>> ast = parser.parse();
        for (const auto &stmt : ast)
        {
            std::cout << *stmt << std::endl;
        }

        std::cout << "\n<---x86 Assembly Output--->\n"
                  << std::endl;

        AsmGen generator;
        for (const auto &stmt : ast)
        {
            generator.generate(stmt);
        }

        std::string asm_code = generator.get_assembly();
        std::cout << asm_code << std::endl;

        std::ofstream outFile("output.asm");
        outFile << asm_code;
        outFile.close();

        std::cout << "\n\u2705 x86 Assembly code written to ./output.asm" << std::endl;
        std::cout << "Compilation Successful!" << std::endl;

        std::cout << "\n<---Result(s)--->\n"
                  << std::endl;

        Interpreter interpreter;
        for (const auto &stmt : ast)
        {
            interpreter.eval(stmt);
        }
    }
};

#endif // COMPILE_AND_RUN_HPP
