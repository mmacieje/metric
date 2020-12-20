#ifndef HANDLER_H
#define HANDLER_H
#include <string>

#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <openssl/evp.h>

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class Handler
{
    public:
        Handler();
        Handler(utility::string_t url);
        virtual ~Handler();

        pplx::task<void>open(){return listener_.open();}
        pplx::task<void>close(){return listener_.close();}

    private:
        void handlePost(http_request message);
        json::value calculateMetric(json::value input);
        utility::string_t calculateSHA256(utility::string_t& input);
        http_listener listener_;
};

#endif // HANDLER_H


