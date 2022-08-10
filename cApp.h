#pragma once

#include <wx/wxprec.h>
#include "cFrameMain.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class cApp : public wxApp
{
private:
	cFrameMain* m_frame1 = nullptr;
public:
	cApp();
	~cApp();
	virtual bool OnInit();
};

