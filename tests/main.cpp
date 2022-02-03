#include <catch2/catch_session.hpp>
#include "Test_PasswordEncrypter.cpp"

int main( int argc, char* argv[] ) {
  int result = Catch::Session().run( argc, argv );
  return result;
}