#include "compile_and_run.hpp"

int main() {
    std::string src = R"(
int i = 5;
int result = i * i;
print(result);
)";

    CompileAndRun compiler(src);
    return 0;
}
