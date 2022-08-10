#include <iostream>
#include <curl/curl.h>
#include <string>


//function that is called when curl when retreiving contents which turns the output to a string
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


int main() {
    CURL* curl;
    CURLcode res;

    std::string apiResponse;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.weather.gov/stations/KARB/observations/latest");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mr. Weatherman");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cout << "curl_easy_preform() return " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);

        std::cout << "data:\n" << apiResponse << std::endl;
    }
    curl_global_cleanup();
    return 0;
}