#pragma once
#include <wx/wx.h>
#include "WeatherData.h"

class cFrameMain : public wxFrame
{
private:
	WeatherData w;
public:
	cFrameMain();
	~cFrameMain();
	void OnButtonClicked(wxCommandEvent& evt);
public:
	wxPanel* m_panel = nullptr;
	wxStaticText* m_weatherText = nullptr;
	wxTextCtrl* m_stationSelector = nullptr;
	wxButton* m_searchButton = nullptr;
};

