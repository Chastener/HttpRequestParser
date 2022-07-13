#include "HttpRequest.h"
#include <iostream>

int main(int argc, char *argv[])
{
    std::string header("GET /wiki/HTTP HTTP/1.0\nHost: ru.wikipedia.org");
    HttpRequest req(header);
    std::cout << req.GetHttpMethod() << std::endl;
    for(auto it = req.GetHeaderValues()->begin(); it != req.GetHeaderValues()->end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << req.FindUrl(header) << std::endl;

    return 0;
}
