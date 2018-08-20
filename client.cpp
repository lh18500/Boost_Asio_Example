#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

int main() {
    io_service likeCTX;
    ip::tcp::socket socket(likeCTX);
    ip::address_v4 addr = ip::address_v4::from_string("127.0.0.1");
    ip::tcp::endpoint endpoint(addr, 8890);
    boost::system::error_code error_code;
    socket.connect(endpoint, error_code);
    if (error_code) {
        std::cout << boost::system::system_error(error_code).what() << std::endl;
        return -1;
    }
    for (int i=0; i<10; ++i) {
        socket.write_some(buffer("Hello, I'm a client."), error_code);
        char buf[100];

        size_t len = socket.read_some(buffer(buf), error_code);
        std::cout << buf << std::endl;
        sleep(3);
    }
    socket.write_some(buffer("Bye, cruel world."), error_code);
    return 0;
}