#pragma once
#include <wx/wx.h>
#include "WeatherData.h"

class cFrameMain : public wxFrame
{
public:
	cFrameMain();
	~cFrameMain();

public:
	wxTextCtrl* m_list1 = nullptr;
};

