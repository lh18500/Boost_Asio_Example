#include <iostream>
#include "boost/asio.hpp"
#include "boost/thread.hpp"

using namespace std;
using namespace boost::asio;

int main() {
    // 所有asio类都需要io_service对象
    io_service iosev;

    //创建用于接收客户端连接的acceptor对象
    ip::tcp::acceptor acceptor(iosev,ip::tcp::endpoint(ip::tcp::v4(), 8890));

    while (true)
    {
        // socket对象
        ip::tcp::socket socket(iosev);
        // 等待直到客户端连接进来
        acceptor.accept(socket);
        // 显示连接进来的客户端
        std::cout <<"remote ip:"<<socket.remote_endpoint().address()<<endl;
        std::cout <<"remote port:"<<socket.remote_endpoint().port() << std::endl;

        char buf[2048];
        boost::system::error_code ec;
        while(true)
        {
            socket.read_some(buffer(buf),ec);
            if (ec)
            {
                std::cout << boost::system::system_error(ec).what() << std::endl;
                break ;
            }
            std::cout<<"recv msg:"<<buf<<endl;
            if(strcmp(buf,"Bye, cruel world.")==0)//收到结束消息结束客户端连接
            {
                std::cout << "See ya." << std::endl;
                break;
            }
            socket.write_some(buffer("I heard you."),ec);
            if (ec)
            {
                std::cout <<boost::system::system_error(ec).what() << std::endl;
                break ;
            }
        }
        socket.close();
        // 与当前客户交互完成后循环继续等待下一客户连接
    }
    return 0;
}