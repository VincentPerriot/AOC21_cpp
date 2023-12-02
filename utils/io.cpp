#include "io.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace aoc {
    std::string ReadFile(const char *filename)
    {
    std::ifstream stream(filename);

    std::string buffer;
    stream.seekg(0, std::ios::end);
    buffer.resize(stream.tellg());
    stream.seekg(0, std::ios::beg);
    stream.read(&buffer[0], buffer.size());
    stream.close();

    return buffer;
    }

    std::vector<std::string> ReadLines(const char *filename)
    {
        std::ifstream stream(filename);
        
        std::vector<std::string> lines;
        std::string line;

        int i = 0;
        while(std::getline(stream, line))
        {
            if (i == 0)
                line = line.substr(3); 
            lines.emplace_back(std::move(line));
            i++;
        }

        stream.close();

        return lines;
    }

    std::vector<std::string> ReadCommaDelimitedFile(const char* filename) {

        std::string contents = ReadFile(filename);
        std::stringstream strStream(contents);
        std::vector<std::string> strings;

        while (strStream.good()) 
        {
            std::string subStr;
            getline(strStream, subStr, ',');
            strings.push_back(subStr);
        }

        return strings;
    }

    std::vector<int> ParseWhiteSpace(std::string str) {

        std::istringstream strStream(str);
        std::vector<int> res;
        int num;

        while (strStream >> num) 
        {
            res.push_back(num);
        }

        return res;
    }


    std::vector<std::string> strToVecStr(const std::string& str)
    {
        std::vector<std::string> res;
        std::stringstream strStream(str);
        std::string new_str;

        while (strStream >> new_str)
        {
            res.push_back(new_str);
        }

        return res;
    }
}