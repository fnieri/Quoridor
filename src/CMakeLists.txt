add_library(src INTERFACE)

add_executable(quoridor
                main.cpp
                PasswordEncrypter.cpp
)
# Link the project libraries to the executable
target_link_libraries(quoridor PRIVATE
       cryptopp-shared 
)
