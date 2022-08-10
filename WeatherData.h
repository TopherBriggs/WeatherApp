#pragma once
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <json/json.h>

static int celsiusToFahrenheit(int temp)
{
    return round(temp * 1.8 + 32);
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class WeatherData
{
private:
    CURL* curl;
    CURLcode res;
public:
    WeatherData();
    ~WeatherData();
    int retrieveWeather(std::string city);


};
