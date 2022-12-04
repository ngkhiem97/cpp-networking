#include <boost/asio.hpp>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

std::string request(std::string,boost::asio::io_context&);

int main(){
    boost::asio::io_context io_context;
    try{
        const auto response = request("www.google.com",io_context);
        std::cout << response << std::endl;
        std::cout << response.size() << " bytes" << std::endl;
    }
    catch(boost::system::system_error& se){
        std::cerr << "Error: " << se.what() << std::endl;
    }
    return 0;
}

std::string request(std::string host, boost::asio::io_context& io_context){
    // Prepare the request
    std::stringstream request_stream;
    request_stream << "GET / HTTP/1.1\r\n"
                      "HOST: " << host << "\r\n"
                      "Accept: text/html\r\n"
                      "Accept-Language: en-us\r\n"
                      "Accept-Encoding: identity\r\n"
                      "Connection: close\r\n\r\n";
    const auto request = request_stream.str();

    // Resolve the host name into an IP address.
    boost::asio::ip::tcp::resolver resolver{io_context};
    const auto endpoints = resolver.resolve(host, "http");

    // Create a socket and connect using the socket
    boost::asio::ip::tcp::socket socket{io_context};
    const auto connected_endpoint = boost::asio::connect(socket, endpoints);

    // Send the request
    boost::asio::write(socket, boost::asio::buffer(request));

    // Read the response
    std::string response;
    boost::system::error_code ec;
    boost::asio::read(socket, boost::asio::dynamic_buffer(response), ec);
    if(ec && ec.value() !=2)
        throw boost::system::system_error{ec};
    return response;
}