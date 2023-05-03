#include <iostream>
#include <curl/curl.h>
#include "ligma.h"

static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    // Write the received data to stdout
    std::cout << std::string(ptr, size * nmemb);
    
    // Return the number of bytes processed
    return size * nmemb;
}


void ligmaWhat(){
    CURL* curl = curl_easy_init();
    if (curl)
    {
        // Set the URL to retrieve
        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/samerbahri98/cpp-project-skeleton/main/content/ligmawhat.txt");
        
        // Set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        
        // Perform the request
        CURLcode res = curl_easy_perform(curl);
        
        // Check for errors
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        
        // Cleanup
        curl_easy_cleanup(curl);
    }
    
}