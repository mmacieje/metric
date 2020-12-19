#include "handler.h"

Handler::Handler()
{

}

Handler::Handler(utility::string_t url):listener_(url)
{
    listener_.support(methods::POST, std::bind(&Handler::handlePost, this, std::placeholders::_1));
}

Handler::~Handler()
{

}

void Handler::handlePost(http_request message)
{
    json::value input_json = message.extract_json().get();
    json::value response;
    try
    {
        response = calculateMetric(input_json);
    }
    catch (...)
    {
        message.reply(status_codes::InternalError, response);
        //message.reply(status_codes::BadRequest, response);
        return ;
    }
    message.reply(status_codes::OK, response);
    return ;
}

json::value Handler::calculateMetric(json::value input)
{
    json::value response = json::value::object();
    response["foo"] = json::value::string("bar");
    return response;
}