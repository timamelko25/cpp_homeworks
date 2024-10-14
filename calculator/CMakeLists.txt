cmake_minimum_required(VERSION 3.30)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем проект
project("Calculator")

# Устанавливаем папку вывода исполняемых файлов для каждого конфигурационного типа (Debug/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)

# Добавляем исполняемый файл
add_executable(Calculator "main.cpp" "calculator.h" "calculator.cpp" "loader.h" "loader.cpp")

# Указываем путь к заголовочным файлам
target_include_directories(Calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Указываем, что будем использовать Windows API
add_custom_target(NewPlugins ALL)

# Копируем plugins в конфигурационную папку (Debug/Release)
add_custom_command(
    TARGET NewPlugins
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/plugins ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins
)

add_dependencies(Calculator NewPlugins)