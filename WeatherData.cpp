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

void WeatherData::setStation(std::string station, std::string time)
{
    Json::Reader reader;
    std::string apiResponse;
    std::string temp = "https://api.weather.gov/stations/" + station + "/observations/latest";
    const char* url = temp.c_str();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mr. Weatherman");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cout << "curl_easy_preform() return " << curl_easy_strerror(res) << std::endl;
    }
    //IDK where to put this because it crashes here when I run a second time
    //curl_easy_cleanup(curl);

    if (!(reader.parse(apiResponse, root)))
    {
        std::cout << "Error parsing the string" << std::endl;
        return;
    }
    if (root["status"] == "404")
    {
        return;
    }
    if (root["properties"]["temperature"]["value"].asString() == "")
    {
        //TODO: figure out how find latest complete data(sometimes the stations have null for tempature)
    }
}

std::string WeatherData::getStationURL()
{
    std::string station = root["properties"]["station"].asString();
    return station;
}

std::string WeatherData::getCity()
{
    Json::Reader reader;
    std::string apiResponse;
    std::string temp = this->getStationURL();
    const char* url = temp.c_str();
    Json::Value tempRoot;   //root only for this function
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mr. Weatherman");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &apiResponse);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cout << "curl_easy_preform() return " << curl_easy_strerror(res) << std::endl;
    }
    if (!(reader.parse(apiResponse, tempRoot)))
    {
        return "error - parsing the string";
    }
    if (tempRoot["status"] == "404")
    {
        return "error - station not found";
    }

    return tempRoot["properties"]["name"].asString();
}

int WeatherData::getWeather()
{
    //std::cout << root << std::endl;
    int temperature = root["properties"]["temperature"]["value"].asInt();
    return celsiusToFahrenheit(temperature);
}
