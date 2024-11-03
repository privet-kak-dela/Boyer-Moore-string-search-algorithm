#include "BoyerMoore.h"
//проверяте является ли подстрока str[p:end] префиксом строки str
bool isPrefix(const std::string& str, int p)
{
    for (int i = p, j = 0; i < str.size(); ++i, ++j)
    {
        if (str[i] != str[j]) 
            return false;
    }
    return true;
}
//Функция возвращает длину суффикса, то есть количество символов, которые совпадают с концом строки str начиная с индекса p.
int suffixLength(const std::string& str, int p) {
    int len = 0;
    while (p >= 0 && str[p] == str[str.size() - 1 - len])
    {
        ++len;
        --p;
    }
    return len;
}
//создает и возвращает вектор table, содержащий смещения для каждой позиции в строке str
std::vector<int> makeOffsetTable(const std::string& str) {
    std::vector<int> table(str.size());
    int lastPrefixPosition = str.size();// хранит позицию последнего префикса
    for (int i = str.size(); i > 0; --i)
    {
        if (isPrefix(str, i))
        {
            lastPrefixPosition = i;// Если подстрока является префиксом, обновляется lastPrefixPosition до текущего индекса i
        }
        table[str.size() - i] = lastPrefixPosition - i + str.size();
    }
    for (int i = 0; i < str.size() - 1; ++i) {
        int slen = suffixLength(str, i);
        table[slen] = str.size() - 1 - i + slen;
    }
    return table;
}


int BoyerMoore(const std::string& T, const std::string& P)
{
    size_t n = T.size();
    size_t m = P.size();

    std::vector<int> charTable(256, P.size());
    for (int i = 0; i < m; ++i)
    {
        charTable[P[i]] = m - 1 - i;
    }

    std::vector<int> offsetTable = makeOffsetTable(P);

    int i = m - 1;
    while (i < n)
    {
        int j = m - 1;
        while (j >= 0 && P[j] == T[i])
        {    
            if (j == 0) {
                return i;
            }
            --i; --j;
        }
        int maxShift = std::max(offsetTable[m - 1 - j], charTable[T[i]]);
        i += maxShift;
    }
    return -1;
}



void file_to_string(const std::string& path, std::string& text) {
    std::fstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    text = buffer.str();
}



