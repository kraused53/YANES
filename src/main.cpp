#include <iostream>
#include <Logger.h>

int main( int argc, char** argv ) {

    Logger::Log( "My Logger Is Here!" );
    Logger::Err( "My Logger Is Here!" );

    return EXIT_SUCCESS;
}