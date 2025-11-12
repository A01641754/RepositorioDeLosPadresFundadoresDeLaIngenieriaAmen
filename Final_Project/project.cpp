/*----------------------------------------------------------
 * Project: Spell Checker
 *
 * Date: 03-Dec-2025
 * Authors:
 *           A01641754 Eduardo Márquez López 
 *           A01       Ángel Adrik Merino Cedeño 
 *----------------------------------------------------------*/
#include <fstream>
#include <regex>
#include <vector>

struct word {
    std::string text;
    int line;
    int column;
};

bool read_words(
        const std::string input_file_name,
        std::vector<word>& words)
{
    std::ifstream input_file(input_file_name);
    if (input_file.fail()) {
        return false;
    }
    std::regex reg_exp("[a-zA-Z]+");
    std::smatch match;
    std::string text;
    int line = 0;
    int column = 0;
    while (std::getline(input_file, text)) {
        ++line;
        column = 1;
        while (std::regex_search(text, match, reg_exp)) {
            column += match.position();
            words.push_back({match.str(), line, column});
            column += match.length();
            text = match.suffix().str();
        }
    }
    return true;
}





//The following code shows how you can use the read_words function from some other part of your program:

std::string file_name = "tooinkle.txt";
std::vector<word> words;

if (read_words(file_name, words)) {
    for (word w : words) {
        std::cout << w.text << "  (line " << w.line
            << ", column " << w.column << ")\n";
    }
} else {
    std::cout << "Unable to read file: "
        << file_name << "\n";
}