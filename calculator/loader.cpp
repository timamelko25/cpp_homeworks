#include "loader.h"

namespace fs = std::filesystem;

Loader::Loader(const std::string& directory) {
    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.path().extension() == ".dll" && entry.path().stem().string().find("dynamic_") == 0) {
                HMODULE hModule = LoadLibraryA(entry.path().string().c_str());
                if (!hModule) {
                    throw std::runtime_error("Failed to load DLL: " + entry.path().string());
                }
                
                lodaded_modules.push_back(hModule);
                std::cout << "DLL " << entry.path() << " loaded!" << std::endl;

                std::string function_suffix = entry.path().stem().string().substr(8);
                std::string fullfunction_name = "calc_" + function_suffix;

                FARPROC func = GetProcAddress(hModule, fullfunction_name.c_str());
                if (func) {
                    functionMap[function_suffix] = func;
                    std::cout << "Function " << fullfunction_name << " loaded from " << entry.path() << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error while loading plugins: " << e.what() << std::endl;
        abort();
    }
}

Loader::~Loader() {
    for (auto hModule : lodaded_modules) {
        FreeLibrary(hModule);
        std::cout << "DLL free!" << std::endl;
    }
}

double Loader::method_function(const std::string& function_name, double arg) {
    auto it = functionMap.find(function_name);
    if (it != functionMap.end()) {
        using FunctionType = double(*)(double);
        FunctionType func = reinterpret_cast<FunctionType>(it->second);
        return func(arg);
    }

    throw std::runtime_error("Can't find function: " + function_name);
}