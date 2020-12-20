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
    json::value response;
    json::value input_json;
    try
    {
        input_json = message.extract_json().get();
    }
    catch (const std::exception & ex)
    {
        message.reply(status_codes::BadRequest, response);
        return ;
    }

    try
    {
        response = calculateMetric(input_json);
    }
    catch (const std::exception & ex)
    {
        message.reply(status_codes::InternalError, ex.what());
        //message.reply(status_codes::BadRequest, response);
        return ;
    }
    message.reply(status_codes::OK, response);
    return ;
}

json::value Handler::calculateMetric(json::value input)
{
    json::value response = json::value::object();

    if(input.has_field("data") == false || input["data"].is_array() == false)
    {
        throw std::exception();
    }
    json::value data = input["data"];

    utility::string_t concatenated_data;

    int number_of_items = data.size();
    for(int i=0; i<number_of_items;++i)
    {
        json::value el = data[i];
        if(el.has_field("signature") == false || el["signature"].is_string() == false)
        {
            throw std::exception();
        }
        concatenated_data += el["signature"].as_string();
    }
    json::value metric = json::value::object();
    metric["signature"] = json::value::string(concatenated_data);
    metric["number-of-items"] = json::value::number(number_of_items);
    response["metric"] = metric;
    return response;
}