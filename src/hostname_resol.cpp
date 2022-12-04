#include <iostream>
#include <boost/asio.hpp>

int main(){
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver{io_context};
    boost::system::error_code ec;
    for(auto&& result: resolver.resolve("www.google.com", "http", ec)){
        std::cout << result.service_name() << " " << result.host_name() << " " << result.endpoint() << std::endl;
    }
    if(ec){
        std::cout << "Error code: " << ec << std::endl;
    }
}