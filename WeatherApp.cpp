#include <iostream>
#include <curl/curl.h>

int main() {
    CURL* curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.weather.gov/");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mr. Weatherman");
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cout << "curl_easy_preform() return " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}