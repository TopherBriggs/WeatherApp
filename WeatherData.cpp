#include "WeatherData.h"

WeatherData::WeatherData()
{
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
}

WeatherData::~WeatherData()
{
	curl_global_cleanup();
}

int WeatherData::retrieveWeather(std::string city)
{
    Json::Value root;
    Json::Reader reader;
    std::string apiResponse;
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.weather.gov/stations/KDET/observations/latest");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mr. Weatherman");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cout << "curl_easy_preform() return " << curl_easy_strerror(res) << std::endl;
    }
    curl_easy_cleanup(curl);

    //std::cout << "data:\n" << apiResponse << std::endl;
    if (!(reader.parse(apiResponse, root)))
    {
        std::cout << "Error parsing the string" << std::endl;
    }
    //std::cout << root << std::endl;
    int temperature = root["properties"]["temperature"]["value"].asInt();

   // std::cout << "Tempature in Detroit: " << celsiusToFahrenheit(temperature) << "F" << std::endl;

    return celsiusToFahrenheit(temperature);
}
