#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <string>
#include <memory>

enum HttpMethod
{
    UNKNOWN,
    GET,
    POST,
    CONNECT,
    PUT,
    HEAD
};

class HttpRequest
{
public:
    HttpRequest(const std::string& header);
    HttpMethod GetHttpMethod();
    std::string GetUrl();
    std::string GetValue(std::string header);
    std::shared_ptr<std::unordered_map<std::string, std::string>> GetHeaderValues();


    static HttpMethod FindHttpMethod(const std::string& header);
    static std::string FindUrl(const std::string& header);
    static std::shared_ptr<std::unordered_map<std::string, std::string>> FindHeaderValues(const std::string& header);

private:
    HttpMethod                                          _httpMethod;
    std::shared_ptr<std::unordered_map<std::string, std::string>> _headerValues;
};

#endif // HTTPREQUEST_H
