#include <iostream>
#include <boost/asio.hpp>

int main(){
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver{io_context};
    boost::asio::ip::tcp::socket socket(io_context);
    try{
        auto endpoints = resolver.resolve("www.google.com", "http");
        auto connected_to = boost::asio::connect(socket, endpoints);
        std::cout << "Connected to : " << connected_to << std::endl;
    }
    catch(boost::system::system_error& se){
        std::cerr << "Error: " << se.what() << std::endl;
    }
}