#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

namespace sam {
    enum types {
        INT,    // integer
        FLOAT,  // floating point
        CH,     // character
        MA,     // memory address
        PA      // program address
    };

    enum opcodes {
        // type converters
        FTOI, FTOIR, ITOF,
        // stack insertions
        PUSHIMM, PUSHIMMF, PUSHIMMCH, PUSHIMMMA, PUSHIMMPA, PUSHIMMSTR,
        // register manipulation
        PUSHSP, PUSHFBR, POPSP, POPFBR,
        // stack manipulation
        DUP, SWAP,
        // stack/heap allocation
        ADDSP, MALLOC, FREE,
        // absolute store/retrieve
        PUSHIND, STOREIND, PUSHABS, STOREABS,
        // relative store/retrieve
        PUSHOFF, STOREOFF,
        // integer algebra
        ADD, SUB, TIMES, DIV, MOD,
        // floating point algebra
        ADDF, SUBF, TIMESF, DIVF,
        // shifts
        LSHIFT, LSHIFTIND, RSHIFT, RSHIFTIND,
        // logic
        AND, OR, NOR, NAND, XOR, NOT,
        // bitwise logic
        BITAND, BITOR, BITNOR, BITNAND, BITXOR, BITNOT,
        // comparison
        CMP, CMPF, GREATER, LESS, EQUAL, ISNIL, ISPOS, ISNEG,
        // jumps
        JUMP, JUMPC, JUMPIND, RST, JSR, JSRIND, SKIP,
        // stack frames
        LINK, UNLINK,
        // i/o
        READ, READF, READCH, READSTR, WRITE, WRITEF, WRITECH, WRITESTR,
        // program control
        STOP
    };

    struct data {
        types type;
        int32_t value;
    };

    struct instruction {
        opcodes opcode;
        void *operand;
    };

    std::vector<std::string> load(std::string path = "") {
        std::vector<std::string> program;
        std::string line;

        // try to open file, fallback to stdin
        if (!path.empty()) {
            std::ifstream file(path);
            while (!file.eof()) {
                std::getline(file >> std::ws, line);
                program.push_back(line);
            }
            return program;
        }

        while (!std::cin.eof()) {
            std::getline(std::cin >> std::ws, line);
            program.push_back(line);
        }
        return program;
    }

    void tokenize(std::vector<std::string> program) {
        ;
    }

    void interpret(void) {
        uint8_t halt = 0;
        uint32_t pc = 0;
        uint32_t sp = 0;
        uint32_t fbr = 0;

        std::stack<data> stack;
        std::map<int, data> memory;
        std::map<std::string, uint32_t> symbol_table;
        std::map<std::string, std::vector<uint32_t>> reference_table;
        std::vector<std::string> instructions;
        while (halt == 0) {
            int32_t opcode;
            switch (opcode) {
                case FTOI:
                    // TODO: implement
                    break;
                case FTOIR:
                    // TODO: implement
                    break;
                case ITOF:
                    // TODO: implement
                    break;
                case PUSHIMM:
                    // TODO: implement
                    break;
                case PUSHIMMF:
                    // TODO: implement
                    break;
                case PUSHIMMCH:
                    // TODO: implement
                    break;
                case PUSHIMMMA:
                    // TODO: implement
                    break;
                case PUSHIMMPA:
                    // TODO: implement
                    break;
                case PUSHIMMSTR:
                    // TODO: implement
                    break;
                case PUSHSP:
                    // TODO: implement
                    break;
                case PUSHFBR:
                    // TODO: implement
                    break;
                case POPSP:
                    // TODO: implement
                    break;
                case POPFBR:
                    // TODO: implement
                    break;
                case DUP:
                    // TODO: implement
                    break;
                case SWAP:
                    // TODO: implement
                    break;
                case ADDSP:
                    // TODO: implement
                    break;
                case MALLOC:
                    // TODO: implement
                    break;
                case FREE:
                    // TODO: implement
                    break;
                case PUSHIND:
                    // TODO: implement
                    break;
                case STOREIND:
                    // TODO: implement
                    break;
                case PUSHABS:
                    // TODO: implement
                    break;
                case STOREABS:
                    // TODO: implement
                    break;
                case PUSHOFF:
                    // TODO: implement
                    break;
                case STOREOFF:
                    // TODO: implement
                    break;
                case ADD:
                    // TODO: implement
                    break;
                case SUB:
                    // TODO: implement
                    break;
                case TIMES:
                    // TODO: implement
                    break;
                case DIV:
                    // TODO: implement
                    break;
                case MOD:
                    // TODO: implement
                    break;
                case ADDF:
                    // TODO: implement
                    break;
                case SUBF:
                    // TODO: implement
                    break;
                case TIMESF:
                    // TODO: implement
                    break;
                case DIVF:
                    // TODO: implement
                    break;
                case LSHIFT:
                    // TODO: implement
                    break;
                case LSHIFTIND:
                    // TODO: implement
                    break;
                case RSHIFT:
                    // TODO: implement
                    break;
                case RSHIFTIND:
                    // TODO: implement
                    break;
                case AND:
                    // TODO: implement
                    break;
                case OR:
                    // TODO: implement
                    break;
                case NOR:
                    // TODO: implement
                    break;
                case NAND:
                    // TODO: implement
                    break;
                case XOR:
                    // TODO: implement
                    break;
                case NOT:
                    // TODO: implement
                    break;
                case BITAND:
                    // TODO: implement
                    break;
                case BITOR:
                    // TODO: implement
                    break;
                case BITNOR:
                    // TODO: implement
                    break;
                case BITNAND:
                    // TODO: implement
                    break;
                case BITXOR:
                    // TODO: implement
                    break;
                case BITNOT:
                    // TODO: implement
                    break;
                case CMP:
                    // TODO: implement
                    break;
                case CMPF:
                    // TODO: implement
                    break;
                case GREATER:
                    // TODO: implement
                    break;
                case LESS:
                    // TODO: implement
                    break;
                case EQUAL:
                    // TODO: implement
                    break;
                case ISNIL:
                    // TODO: implement
                    break;
                case ISPOS:
                    // TODO: implement
                    break;
                case ISNEG:
                    // TODO: implement
                    break;
                case JUMP:
                    // TODO: implement
                    break;
                case JUMPC:
                    // TODO: implement
                    break;
                case JUMPIND:
                    // TODO: implement
                    break;
                case RST:
                    // TODO: implement
                    break;
                case JSR:
                    // TODO: implement
                    break;
                case JSRIND:
                    // TODO: implement
                    break;
                case SKIP:
                    // TODO: implement
                    break;
                case LINK:
                    // TODO: implement
                    break;
                case UNLINK:
                    // TODO: implement
                    break;
                case READ:
                    // TODO: implement
                    break;
                case READF:
                    // TODO: implement
                    break;
                case READCH:
                    // TODO: implement
                    break;
                case READSTR:
                    // TODO: implement
                    break;
                case WRITE:
                    // TODO: implement
                    break;
                case WRITEF:
                    // TODO: implement
                    break;
                case WRITECH:
                    // TODO: implement
                    break;
                case WRITESTR:
                    // TODO: implement
                    break;
                case STOP:
                    // TODO: implement
                    break;

                default:
                    std::cerr << "ERROR: Unexpected opcode {" << opcode << "}";
                    exit(1);
                    break;
            }
        }
    }
} // namespace sam



int main(int argc, char **argv) {
    std::vector<std::string> p;
    if (argv[1] != nullptr) {
        p = sam::load(argv[1]);
    } else {
        p = sam::load();
    }
    for (const auto &line : p) {
        std::cout << line;
    }
}
