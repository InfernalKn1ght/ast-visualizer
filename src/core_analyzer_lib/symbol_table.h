#pragma once

#include <string>
#include <unordered_map>

#include "inter.h"

/**
 * @brief The STable class implements a symbol table with scoping support.
 *
 * This class represents a symbol table that can chain to a parent table,
 * allowing for nested scopes in the language. It provides operations
 * for adding and looking up identifiers in the current scope and all
 * enclosing parent scopes.
 */
class STable {
public:
    /**
     * @brief Looks up an identifier by name in the symbol table chain.
     * @param lexeme The name of the identifier to find.
     * @return Unique pointer to the found Id object, or nullptr if not found.
     *
     * The search proceeds from the current scope outward through all
     * enclosing parent scopes until the identifier is found or all
     * scopes have been exhausted.
     */
    std::unique_ptr<Id> get(std::string &lexeme);

    /**
     * @brief Adds a new identifier to the current scope.
     * @param lexeme The name of the identifier to add.
     * @param id The Id object representing the identifier.
     *
     * The identifier is added only to the current scope, shadowing
     * any identifiers with the same name in outer scopes.
     */
    void put(std::string lexeme, Id id);

    /**
     * @brief Constructs a new symbol table.
     * @param prev Shared pointer to the parent symbol table (nullptr by
     * default).
     */
    STable(std::shared_ptr<STable> prev = nullptr);

    virtual ~STable() = default;

private:
    std::shared_ptr<STable>
        prev_;  ///< Pointer to the parent symbol table scope.
    std::unordered_map<std::string, Id>
        table_;  ///< Map storing identifiers in current scope.
};