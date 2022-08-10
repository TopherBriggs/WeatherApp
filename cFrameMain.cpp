#include "cFrameMain.h"

cFrameMain::cFrameMain() : wxFrame(nullptr, wxID_ANY, "Weather", wxPoint(30, 30), wxSize(800, 800))
{
	WeatherData w;
	int results = w.retrieveWeather("Detroit");
	m_list1 = new wxTextCtrl(this, wxID_ANY, "Detroit: " + std::to_string(results) + "F", wxPoint(10, 100), wxSize(300, 30));
}

cFrameMain::~cFrameMain()
{
}
