cmake_minimum_required(VERSION 3.20)
project(ShowInTerminal C)

set(CMAKE_C_STANDARD 99)

#add_compile_options(-march=x86-64)
add_link_options(-lncurses)
add_link_options(-lm)

add_executable(ShowInTerminal main.c src/console_screen.c src/console_screen.h stb/stb_image.h stb/stb_image_resize.h src/images.c src/images.h src/utils.c src/utils.h main.h)
