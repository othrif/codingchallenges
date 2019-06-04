// Compile with: g++-9 -g -Wreturn-type -Wmain -Werror=return-type -Werror=main -pipe -O2 -std=c++14  `pkg-config --cflags jsoncpp` filter.cpp  -o solution -lm -lpthread `pkg-config --libs jsoncpp` && ./solution


#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class AlphaNumericPredicate {
public:
bool operator() (char c)
{
    return (isalnum(c));
}
};

template<typename InputIterator, typename OutputIterator, typename UnaryPredicate>
OutputIterator filter(InputIterator first, InputIterator last,
                      OutputIterator result,
                      UnaryPredicate predicate,
                      size_t history_size)
{
    while (first!=last) {
        bool skip = false;
        if(predicate(*first)){
            //std::cout << "\n**" << *first << "**" << *result << "**" << std::endl;
            for (int i = history_size; i > 0; i--){
                auto itr = prev(first, i);
                while(!predicate(*itr))
                    itr = prev(itr, 1);
                //std::cout << i << "*" << *first << "*" << *itr << "*" << std::endl;
                if(*itr == *first){
                    //std::cout << "Remove " << *first << std::endl;
                    skip = true;
                    break;
                }
            }
            if(!skip){
                *result = *first;
                //std::cout << "***" << *first << "***" << *result << "***" << std::endl;
                *result++; *first++;
            }
            else{
                *first++;
            }
        }
        else
            *first++;
    }
    return result;
}

//
// Filter string. Helper for mapping binary blobs to strings.
//
std::string filter_string(std::string source, size_t history_size)
{
   source.erase(filter(std::begin(source), std::end(source),
                        std::begin(source),
                        AlphaNumericPredicate{}, history_size),
                 std::end(source));
    return source;
}

//
// Main entry point.
//
int main()
{
    while (!std::cin.eof())
    {
        size_t history_size;
        std::cin >> history_size;
        std::string source;
        std::getline(std::cin, source);
        std::cout << "history_size: " << history_size << ", source: " << source << std::endl;
        std::cout << filter_string(source, history_size) << std::endl;
    }
    return 0;
}