#include <iostream>
#include "src/lexer.h"
#include "src/parser.h"

int main(int argc, char*argv[]) {
    // Lexer lex("input.c");
    // std::unique_ptr<Token> tok = lex.scan();
    // tok->print();
    // while (tok->tag != '/') {
    //     tok = lex.scan();
    //     tok->print();
    // }

    Parser p("input.c");
    p.program();


    return 0;
}