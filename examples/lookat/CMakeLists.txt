project(lookat)
add_executable(${PROJECT_NAME} camera.cpp ground.cpp main.cpp openglwindow.cpp pacman.cpp model.cpp  parede.cpp)
enable_abcg(${PROJECT_NAME})
