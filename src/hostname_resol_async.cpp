#include <iostream>
#include <boost/asio.hpp>

int main(){
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver{io_context};
    boost::system::error_code ec;
    resolver.async_resolve("www.google.com", "http",
        [](boost::system::error_code ec, const auto &results)
        {
            if (ec)
            {
                std::cerr << "Error code: " << ec << std::endl;
                return;
            }
            for (auto &&result : results){
                std::cout << result.service_name() << " " << result.host_name() << " " << result.endpoint() << std::endl;
            }
        }
    );
    io_context.run();
}