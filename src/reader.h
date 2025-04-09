#pragma once

#include <fstream>
#include <string>

/**
 * @brief The Reader class provides an interface for reading characters from a
 * file.
 *
 * This class encapsulates an input file stream and provides methods for
 * checking the end-of-file status and reading individual characters.
 */
class Reader {
public:
    /**
     * @brief Checks if the end of the file has been reached.
     * @return True if the end of the file has been reached, false otherwise.
     */
    bool reader_eof() const;

    /**
     * @brief Reads a single character from the input stream.
     * @param peek Reference to a character variable where the read character
     * will be stored.
     */
    void read_symbol(char &peek);

    /**
     * @brief Constructs a Reader object and opens the specified file.
     * @param file_name The name of the file to open.
     */
    Reader(const std::string &file_name);

    /**
     * @brief Destroys the Reader object and closes the file if it is open.
     */
    virtual ~Reader();

private:
    std::ifstream input_text_;  ///< The input file stream.
};