#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/algorithm/string/case_conv.hpp>

void handle(boost::asio::ip::tcp::socket&);

int main(){
    try{
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor{io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1895)};
        while (true)
        {   
            boost::asio::ip::tcp::socket socket{io_context};
            acceptor.accept(socket);
            handle(socket);
        }
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

void handle(boost::asio::ip::tcp::socket& socket){
    boost::system::error_code ec;
    std::string message;
    do{
        boost::asio::read_until(socket, boost::asio::dynamic_buffer(message), "\n");
        boost::algorithm::to_upper(message);
        boost::asio::write(socket, boost::asio::buffer(message), ec);
        if (message == "\n")
            return;
        message.clear();
    } while(!ec);
}