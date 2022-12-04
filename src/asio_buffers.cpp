#include <iostream>
#include <boost/asio.hpp>
#include <string>

int main(){
    // Create a Mutable Buffer
    std::string str {"Hello mutable buffer"};
    boost::asio::mutable_buffer mb(str.data(), str.size());
    std::cout << "Mutable buffer: " << mb.size() << std::endl;

    // Create a Constant Buffer
    boost::asio::const_buffer cb{mb};
    std::cout << "Constant buffer: " << cb.size() << std::endl;
    
    // Create a Resizable Buffer
    boost::asio::streambuf sb;
    std::ostream os{&sb};
    os << "Hello streambuf!";
    std::cout << "Stream buffer size: " << sb.size() << std::endl;
    std::istream is{&sb};
    std::string command;
    is >> command;
    std::cout << "String from Stream buffer: " << command << std::endl;
    std::cout << "Stream buffer size: " << sb.size() << std::endl;
}