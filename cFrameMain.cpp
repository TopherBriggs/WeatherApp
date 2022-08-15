#include "cFrameMain.h"

cFrameMain::cFrameMain() : wxFrame(nullptr, wxID_ANY, "Weather", wxPoint(30, 30), wxSize(800, 800))
{
	w.setStation("KDET");
	int results = w.getWeather();
	m_panel = new wxPanel(this);
	m_weatherText = new wxStaticText(m_panel, wxID_ANY, "Detroit: " + std::to_string(results) + "F", wxPoint(10, 100), wxSize(300, 30));
	m_stationSelector = new wxTextCtrl(m_panel, wxID_ANY, "", wxPoint(10, 50), wxSize(200, -1));
	m_searchButton = new wxButton(m_panel, wxID_ANY, "Search", wxPoint(230, 50), wxSize(-1, -1));

	m_searchButton->Bind(wxEVT_BUTTON, &cFrameMain::OnButtonClicked, this);

	CreateStatusBar();
}

cFrameMain::~cFrameMain()
{
}

void cFrameMain::OnButtonClicked(wxCommandEvent& evt)
{
	std::string station = m_stationSelector->GetLineText(0).ToStdString();
	w.setStation(station);
	int results = w.getWeather();
	m_weatherText->SetLabelText(w.getCity() + ": " + std::to_string(results) + "F");
	wxLogStatus("Button Clicked");
}
