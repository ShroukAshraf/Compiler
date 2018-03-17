//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_CODEPARSER_H
#define COMPILER_CODEPARSER_H


class CodeParser {

public:
    explicit CodeParser(std::string fileName);

    std::vector<char> parseFile();

    char getChar();

    void setStartIndex(int i);

    int getCurIndex();

    std::string getSubString(int startIndex , int lastIndex);

    bool hasChars();

private:
    std::string codeFile;
    int index = 0;
    std::vector<char> chars;

};


#endif //COMPILER_CODEPARSER_H