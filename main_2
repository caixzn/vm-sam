#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

enum class OpCode {
    ADDSP,
    PUSHIMM,
    STOREABS,
    PUSHABS,
    PUSHOFF,
    LESS,
    JUMPC,
    STOP,
    TIMES,
    ADD,
    SUB,
    ISNIL,
    JUMP,
    STOREOFF,
    GREATER,
    LINK,
    POPFBR,
    INVALID
};

class VirtualMachine {
  private:
    std::vector<int> stack;
    std::unordered_map<std::string, OpCode> opcodeMap{
        {"ADDSP", OpCode::ADDSP},       {"PUSHIMM", OpCode::PUSHIMM},
        {"STOREABS", OpCode::STOREABS}, {"PUSHABS", OpCode::PUSHABS},
        {"LESS", OpCode::LESS},         {"JUMPC", OpCode::JUMPC},
        {"STOP", OpCode::STOP},         {"TIMES", OpCode::TIMES},
        {"ADD", OpCode::ADD},           {"SUB", OpCode::SUB},
        {"ISNIL", OpCode::ISNIL},       {"GREATER", OpCode::GREATER},
        {"LINK", OpCode::LINK},         {"POPFBR", OpCode::POPFBR},
        {"PUSHOFF", OpCode::PUSHOFF},   {"STOREOFF", OpCode::STOREOFF},
        {"JUMP", OpCode::JUMP}};
    std::unordered_map<std::string, int> labels;

    OpCode getOpCode(const std::string &op) {
        auto it = opcodeMap.find(op);
        if (it != opcodeMap.end()) {
            return it->second;
        }
        return OpCode::INVALID;
    }

  public:
    VirtualMachine(const std::unordered_map<std::string, int> &labelMap)
        : labels(labelMap) {}

    void execute(const std::vector<std::vector<std::string>> &program) {
        int FBR = -1;
        for (size_t pc = 0; pc < program.size(); ++pc) {
            const auto &instruction = program[pc];
            OpCode code = getOpCode(instruction[0]);
            int operand = 0;
            std::string label;

            // Tratar as instruções JUMPS
            if (code == OpCode::JUMP || code == OpCode::JUMPC ||
                code == OpCode::LINK || code == OpCode::STOREOFF ||
                code == OpCode::PUSHOFF) {
                label = instruction[1];
            } else if (instruction.size() > 1) {
                try {
                    operand = std::stoi(instruction[1]);
                } catch (const std::invalid_argument &e) {
                    std::cerr << "Invalid argument for stoi: " << instruction[1]
                              << std::endl;
                    continue;
                } catch (const std::out_of_range &e) {
                    std::cerr
                        << "Argument out of range for stoi: " << instruction[1]
                        << std::endl;
                    continue;
                }
            }
            switch (code) {
            case OpCode::SUB: {
                int a = stack.back();
                stack.pop_back();
                int b = stack.back();
                stack.pop_back();
                stack.push_back(b - a);
            } break;
            case OpCode::TIMES: {
                int a = stack.back();
                stack.pop_back();
                int b = stack.back();
                stack.pop_back();
                stack.push_back(a * b);
            } break;
            case OpCode::ADD: {
                int a = stack.back();
                stack.pop_back();
                int b = stack.back();
                stack.pop_back();
                stack.push_back(a + b);

            } break;
            case OpCode::ADDSP:
                stack.resize(stack.size() + operand);
                break;
            case OpCode::PUSHIMM:
                stack.push_back(operand);
                break;
            case OpCode::STOREABS:
                stack[operand] = stack.back();
                stack.pop_back();
                break;
            case OpCode::STOREOFF:
                stack[FBR + operand] = stack.back();
                stack.pop_back();
                break;
            case OpCode::PUSHOFF:
                stack.push_back(stack[FBR + operand]);
                break;
            case OpCode::PUSHABS:
                stack.push_back(stack[operand]);
                break;
            case OpCode::LESS: {
                int a = stack.back();
                stack.pop_back();
                int b = stack.back();
                stack.pop_back();
                stack.push_back(b < a ? 1 : 0);
            } break;

            case OpCode::ISNIL: {
                int value = stack.back();
                stack.pop_back();
                stack.push_back(value == 0 ? 1 : 0);
            } break;

            case OpCode::JUMP:
                pc = labels[label] - 1;
                break;
            case OpCode::JUMPC:
                if (stack.back() != 0) {
                    pc = labels[instruction[1]] - 1;
                }
                stack.pop_back();
                break;
            case OpCode::GREATER: {
                int a = stack.back();
                stack.pop_back();
                int b = stack.back();
                stack.pop_back();
                stack.push_back(b > a ? 1 : 0);
            } break;
            case OpCode::LINK:
                stack.push_back(FBR);
                FBR = stack.size() - 1;
                break;

            case OpCode::POPFBR:
                stack.resize(FBR);
                FBR = stack.back();
                stack.pop_back();
                break;
            case OpCode::STOP:
                return;
            default:
                std::cerr << "Unknown instruction: " << instruction[0]
                          << std::endl;
                return;
            }
        }
    }

    void printStack() const {
        for (int num : stack) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};
std::vector<std::vector<std::string>>
lerInstrucao(const std::string &filename,
             std::unordered_map<std::string, int> &labels) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> instructions;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return instructions;
    }

    while (getline(file, line)) {
        // 去除注释
        std::size_t commentIndex = line.find("//");
        if (commentIndex != std::string::npos) {
            line = line.substr(0, commentIndex);
        }

        // 去除行尾的空格
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        if (!line.empty()) {
            std::istringstream iss(line);
            std::vector<std::string> tokens;
            std::string token;

            // 分割行到单词
            while (iss >> token) {
                tokens.push_back(token);
            }

            if (!tokens.empty()) {
                if (tokens[0].back() == ':') {
                    // Deletar ":" e registrar posição
                    std::string label =
                        tokens[0].substr(0, tokens[0].length() - 1);
                    labels[label] = instructions.size();
                } else {
                    // Adicionar não label na matriz
                    instructions.push_back(tokens);
                }
            }
        }
    }

    file.close();
    return instructions;
}

int main() {
    const std::string filename = "./entradas/SAM-functions.sam";
    std::unordered_map<std::string, int> labels; // Salvar label e posição

    // Carregar conteúdo de arquivo
    auto instructions = lerInstrucao(filename, labels);

    if (instructions.empty()) {
        std::cerr << "Instrução vazia." << std::endl;
        return -1;
    }

    // Criar VM
    VirtualMachine vm(labels);

    // Executar instruções
    vm.execute(instructions);

    // Imprimir Stack
    vm.printStack();

    return 0;
}
