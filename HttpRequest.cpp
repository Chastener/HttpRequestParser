#include "HttpRequest.h"
#include <algorithm>

HttpRequest::HttpRequest(const std::string &header)
{
    _httpMethod = FindHttpMethod(header);
    _headerValues = FindHeaderValues(header);
}

HttpMethod HttpRequest::GetHttpMethod()
{
    return _httpMethod;
}

std::string HttpRequest::GetUrl()
{
    return _headerValues->operator[]("host");
}

std::string HttpRequest::GetValue(std::string header)
{
    std::for_each(header.begin(), header.end(),
        [](char& c){ c = std::tolower(c); });
    return _headerValues->operator[](header);
}

std::shared_ptr<std::unordered_map<std::string, std::string> > HttpRequest::GetHeaderValues()
{
    return _headerValues;
}

inline HttpMethod HttpRequest::FindHttpMethod(const std::string &header)
{
    if( header[0] == 'G' && header[1] == 'E' && header[2] == 'T'
                         && header[3] == ' ' )
    {
        return HttpMethod::GET;
    }
    else if( header[0] == 'P' )
    {
        if( header[1] == 'O' && header[2] == 'S' && header[3] == 'T'
                             && header[4] == ' ')
        {
            return HttpMethod::POST;
        }
        else if( header[1] == 'U' && header[2] == 'T'
                                  && header[3] == ' ')
        {
            return HttpMethod::PUT;
        }
    }
    else if( header[0] == 'H' && header[1] == 'E' && header[2] == 'A'
                              && header[3] == 'D' && header[4] == ' ' )
    {
        return HttpMethod::HEAD;
    }
    else if( header[0] == 'C' && header[1] == 'O' && header[2] == 'N'
                              && header[3] == 'N' && header[4] == 'E'
                              && header[5] == 'C' && header[6] == 'T'
                              && header[7] == ' ')
    {
        return HttpMethod::CONNECT;
    }
    return HttpMethod::UNKNOWN;
}

std::string HttpRequest::FindUrl(const std::string &header)
{
    static std::string name, value;
    static size_t startSub = 0, endSub = 0;
    while( header[endSub] != '\n' ) ++endSub;
    ++endSub;
    startSub = endSub;
    while( header[endSub] != '\n' && endSub < header.size() )
    {
        while(header[endSub] != ':' && endSub < header.size() )
        {
            ++endSub;
        }
        name = header.substr(startSub, endSub - startSub);
        std::transform(name.begin(), name.end(), name.begin(),
            [](unsigned char c){ return std::tolower(c); });
        endSub += 2;

        startSub = endSub;
        while(header[endSub] != '\n' && endSub < header.size() )
        {
            ++endSub;
        }
        if( name == "host" ) return header.substr(startSub, endSub - startSub);
        ++endSub;
    }
    return "";
}

inline std::shared_ptr<std::unordered_map<std::string, std::string> > HttpRequest::FindHeaderValues(const std::string &header)
{
    static std::string name, value;
    static size_t startSub = 0, endSub = 0;
    std::shared_ptr<std::unordered_map<std::string, std::string>> headerValues(std::make_shared<std::unordered_map<std::string, std::string>>());
    while( header[endSub] != '\n' ) ++endSub;
    ++endSub;
    startSub = endSub;
    while( header[endSub] != '\n' && endSub < header.size() )
    {
        while(header[endSub] != ':' && endSub < header.size() )
        {
            ++endSub;
        }
        name = header.substr(startSub, endSub - startSub);
        std::transform(name.begin(), name.end(), name.begin(),
            [](unsigned char c){ return std::tolower(c); });
        endSub += 2;

        startSub = endSub;
        while(header[endSub] != '\n' && endSub < header.size() )
        {
            ++endSub;
        }
        value = header.substr(startSub, endSub - startSub);
        ++endSub;
        if( name.size() && value.size() ) headerValues->emplace(name, value);
    }
    return headerValues;
}
