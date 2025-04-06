#include <iostream>
#include "lexer.h"
#include "parser.h"

int main(int argc, char*argv[]) {
    // Lexer lex("input.c");
    // std::unique_ptr<Token> tok = lex.scan();
    // tok->print();
    // while (!lex.lexer_eof()) {
    //     tok = lex.scan();
    //     tok->print();
    // }

    Parser p("input.c");
    std::unique_ptr<Stmt> ast = std::move(p.program());
    ast->print();


    return 0;
}