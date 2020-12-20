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

    int number_of_items = data.size();
    utility::string_t signature;

    for(int i=0; i<number_of_items;++i)
    {
        json::value el = data[i];
        if(el.has_field("signature") == false || el["signature"].is_string() == false)
        {
            throw std::exception();
        }
        signature += el["signature"].as_string();
    }

    utility:string_t hashed_signature = calculateSHA256(signature);

    json::value metric = json::value::object();
    metric["signature"] = json::value::string(hashed_signature);
    metric["number-of-items"] = json::value::number(number_of_items);
    response["metric"] = metric;
    return response;
}

utility::string_t Handler::calculateSHA256(utility::string_t& input)
{
    utility::string_t output;
    bool success = false;

    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if(context != NULL)
    {
        if(EVP_DigestInit_ex(context, EVP_sha256(), NULL))
        {
            if(EVP_DigestUpdate(context, input.c_str(), input.length()))
            {
                unsigned char hash[EVP_MAX_MD_SIZE];
                unsigned int lengthOfHash = 0;

                if(EVP_DigestFinal_ex(context, hash, &lengthOfHash))
                {
                    std::stringstream ss;
                    for(unsigned int i = 0; i < lengthOfHash; ++i)
                    {
                        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
                    }

                    output = ss.str();
                    success = true;
                }
            }
        }

        EVP_MD_CTX_free(context);
    }

    if(success)
    {
        return output;
    }
    else
    {
        throw std::exception();
    }
    
}