#include <iostream>
#include <thread>
#include <chrono>

#include "handler.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

int main(int argc, char *argv[])
{
    std::unique_ptr<Handler> http_handler;

    utility::string_t port = U("9000");
    utility::string_t address = U("http://127.0.0.1:");
    address.append(port);
    uri_builder uri(address);
    auto addr = uri.to_uri().to_string();
    http_handler = std::unique_ptr<Handler>(new Handler(addr));
    http_handler->open().wait();

    while(true) { std::this_thread::sleep_for(std::chrono::seconds(5)); }

    http_handler->close().wait();
    return 0;
}