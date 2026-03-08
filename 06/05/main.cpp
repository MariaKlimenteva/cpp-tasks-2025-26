#include <iostream>
#include <string>
#include <boost/dll.hpp>
#include <boost/function.hpp>

int main()
{
    std::string lib_name;
    std::cout << "Enter library name (plugin_one or plugin_two): ";
    std::cin >> lib_name;

    boost::filesystem::path lib_path = boost::dll::shared_library::suffix(); 
    lib_path = "./lib" + lib_name + lib_path.string();

    try 
    {
        std::cout << "Loading: " << lib_path << std::endl;
        
        auto test_func = boost::dll::import_symbol<void()>(
            lib_path,
            "test",
            boost::dll::load_mode::append_decorations
        );

        test_func();
    }
    catch (const boost::system::system_error& e) 
    {
        std::cerr << "Error loading library: " << e.what() << std::endl;
    }
}

/*
Сборка и запуск:
mkdir build && cd build
cmake ..
cmake --build .
./loader
(введите plugin_one или plugin_two)
*/