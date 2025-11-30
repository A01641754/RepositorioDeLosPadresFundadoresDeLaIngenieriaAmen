/*----------------------------------------------------------
 * Project: Spell Checker
 * Date: 03-Dec-2025
 * Authors:
 *    A0XXXXXXX Nombre
 *    A0XXXXXXX Nombre
 *----------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <regex>
#include <string>

/********** STRUCT WORD **********/
struct word {
    std::string text;
    int line;
    int column;
};

/********** GIVEN FUNCTION **********/
bool read_words(const std::string input_file_name, std::vector<word>& words) {
    std::ifstream input_file(input_file_name);
    if (input_file.fail()) return false;

    std::regex reg_exp("[a-zA-Z]+");
    std::smatch match;
    std::string text;
    int line = 0, column = 0;

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

/********** SOUNDEX FUNCTION **********/
std::string soundex(const std::string& word) {
    if (word.empty()) return "";

    std::string result;
    result += std::toupper(word[0]);

    auto encode = [](char c) -> char {
        c = std::tolower(c);
        if (c=='b'||c=='f'||c=='p'||c=='v') return '1';
        if (c=='c'||c=='g'||c=='j'||c=='k'||c=='q'||c=='s'||c=='x'||c=='z') return '2';
        if (c=='d'||c=='t') return '3';
        if (c=='l') return '4';
        if (c=='m'||c=='n') return '5';
        if (c=='r') return '6';
        return 0;
    };

    for (int i = 1; i < (int)word.size(); i++) {
        char c = std::tolower(word[i]);
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||c=='h'||c=='w'||c=='y') continue;
        char code = encode(c);
        if (code) result += code;
    }

    while (result.size() < 7) result += '0';
    if (result.size() > 7) result = result.substr(0,7);

    return result;
}

/********** MAIN **********/
int main(int argc, char* argv[]) {

    if (argc != 2) return 0;

    std::string input_file = argv[1];

    // Read input words
    std::vector<word> words_in_file;
    if (!read_words(input_file, words_in_file)) return 0;

    // Load dictionary
    std::unordered_set<std::string> dictionary;
    std::unordered_map<std::string, std::vector<std::string>> soundex_map;

    std::ifstream dict("words.txt");
    std::string dword;

    while (dict >> dword) {
        for (auto& c : dword) c = std::tolower(c);

        dictionary.insert(dword);

        std::string code = soundex(dword);
        soundex_map[code].push_back(dword);
    }

    std::unordered_set<std::string> already_reported;

    for (const auto& w : words_in_file) {
        std::string lw = w.text;
        for (auto& c : lw) c = std::tolower(c);

        if (dictionary.count(lw)) continue;

        if (already_reported.count(lw)) continue;
        already_reported.insert(lw);

        std::cout << "Unrecognized word: \"" << w.text
                  << "\". First found at line " << w.line
                  << ", column " << w.column << ".\n";

        std::string code = soundex(lw);

        if (!soundex_map.count(code) || soundex_map[code].empty()) {
            std::cout << "No suggestions.\n\n";
        } else {
            std::cout << "Suggestions: ";
            const auto& vec = soundex_map[code];

            for (size_t i = 0; i < vec.size(); i++) {
                std::cout << vec[i];
                if (i + 1 < vec.size()) std::cout << ", ";
            }
            std::cout << "\n\n";
        }
    }

    return 0;
}
