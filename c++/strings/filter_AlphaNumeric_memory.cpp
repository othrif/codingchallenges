// Compile with: g++-9 -g -Wreturn-type -Wmain -Werror=return-type -Werror=main -pipe -O2 -std=c++14  `pkg-config --cflags jsoncpp` filter_AlphaNumeric_memory.cpp  -o filter_AlphaNumeric_memory -lm -lpthread `pkg-config --libs jsoncpp` && ./filter_AlphaNumeric_memory


#include <iostream>
#include <string>
#include <vector>


//
// Filter function
//
size_t filter(void* destination,
              const void* source,
              size_t source_size,
              size_t history_size)
{
    // Fill implementation here
  char *my_destination = (char *)destination;
    char *my_source = (char *)source;
    int ii = 0;
    for (int i = 0; i < source_size; i++) {
      bool found = false;
      std::cout << "*" << i << "*" << std::endl;
      if (isalnum(my_source[i])) {
        std::cout << "*" << my_source[i] << "*" << std::endl;
        for (int j = i - 1; j >= i - history_size && j > 0; j--)
        {
            int jtemp=j;
            while(!isalnum(my_source[jtemp])){
                jtemp--;
            }
          std::cout << "**" << jtemp << "**" << my_source[i] << "**" << my_source[jtemp]
                    << "**" << std::endl;
          if (my_source[jtemp] == my_source[i]) {
            std::cout << "*" << my_source[i] << "*FOUND" << std::endl;
            found = true;
            break;
          }
        }
        if (!found) {
          std::cout << "*SAVE*" << ii << "*" << my_source[i] << std::endl;
          my_destination[ii] = my_source[i];
          ii++;
        }
      }
    }

    return ii + 1;
}
//
// Filter string. Helper for mapping binary blobs to strings.
//
std::string filter_string(const std::string& source, size_t history_size)
{
    std::vector<char> buffer(source.length());
    char* test = buffer.data();
    std::cout << "*" << source << "*" << *test << "*" << source.length() << "*" << source.c_str() << "*" << std::endl;
    size_t filtered_size = filter(buffer.data(), source.c_str(), source.length(), history_size);
    std::string dest(buffer.data(), filtered_size);
    return dest;
}

//
// Main entry point.
//
int main()
{
    while (!std::cin.eof())
    {
        size_t history_size = 0;
        std::cin >> history_size;
        std::string source;
        std::getline(std::cin, source);
        if (history_size == 123)
        {
            source = "b";
            source.resize(500*1024*1024, 'a');
            history_size = 500*1024*1024-1;
        }
        std::cout << filter_string(source, history_size) << std::endl;
    }
    return 0;
}
