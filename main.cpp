#include <iostream>
#include <vector>
#include <algorithm>
#include "BoyerMoore.h">
#include <chrono>
#include <cassert>

 void make_file(const std::string& path, unsigned long long size) {
    const std::string chars{ "QWERTYUIOPASDFGHJKLZXCVBNM" };
    std::ofstream file(path);
    std::random_device rd;
    for (unsigned long long i = 0; i != size; ++i) {
        file << chars[rd() % 26];
    }
}
 std::string make_exist_pattern(std::string str,unsigned long long size,unsigned long long ind)
 {
     std::random_device rd;
     
     return str.substr(ind, size);
 }
std::string make_pattern(unsigned long long size)
{
    std::string pattern="";
    const std::string chars{ "QWERTYUIOPASDFGHJKLZXCVBNM" };
    std::random_device rd;
    for (unsigned long long i = 0; i != size; ++i) {
        
        pattern+=(chars[rd() % 20]);
    }
    return pattern;
}
int main() {

    srand(time(0));
    setlocale(LC_ALL, "ru");
    std::string text;
    
   
    make_file("o.txt", 1000);//здесь можно изменить имя и размер файла 
    file_to_string("o.txt", text);
    std::ofstream file("results.csv");
    file << "size;my_algorithm;std\n";
   
    std::string pattern;
    for (size_t i = 1; i <= 8; i++)
    {
        std::random_device rd;
        pattern = make_exist_pattern(text.substr(0,pow(10,i)), 1000, rd() % (text.substr(0, pow(10, i)).size()-1)/2);
        // Измеряем время выполнения алгоритма Бойера-Мура
        auto start = std::chrono::high_resolution_clock::now();
        int bm_result = BoyerMoore(text, pattern);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> bm_time = end - start;
        file << text.substr(0, pow(10, i)).size() << ";"<< bm_time.count() * 1000 << ";";

        // Измеряем время выполнения стандартной функции find
        start = std::chrono::high_resolution_clock::now();
        size_t find_result = text.find(pattern);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> find_time = end - start;
        file << find_time.count() * 1000 << "\n";
        
        // Выводим результаты
        if (bm_result != -1) {
            std::cout << "Подстрока найдена Бойером-Муром за " << bm_time.count() * 1000 << " мс. Индекс: " << bm_result << std::endl;
        }
        else {
            std::cout << "Подстрока не найдена алгоритмом Бойера-Мура." << bm_time.count()*1000 << std::endl;
        }
        
        if (find_result != std::string::npos) {
            std::cout << "Подстрока найдена функцией find за " << find_time.count()* 1000 << " мс. Индекс: " << find_result  << std::endl;
        }
        else {
            std::cout << "Подстрока не найдена функцией find." << find_time.count()* 1000 << std::endl;
        }
        std::cout << "   ------------------------------------  " << std::endl;
    }
    
    return 0;
  
}