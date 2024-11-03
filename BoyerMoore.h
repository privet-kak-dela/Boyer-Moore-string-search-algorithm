#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <ostream>
#include <random>

int BoyerMoore(const std::string& haystack, const std::string& needle);

void file_to_string(const std::string&path, std::string&text);



