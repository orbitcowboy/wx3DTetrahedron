#ifndef __TetrahedronDlgApp_h__
#define __TetrahedronDlgApp_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#else
#include <wx/wxprec.h>
#endif

class TetrahedronDlgApp : public wxApp
{
    public:
        bool OnInit();
        int OnExit();
};

#endif // __TetrahedronDlgApp_h__
