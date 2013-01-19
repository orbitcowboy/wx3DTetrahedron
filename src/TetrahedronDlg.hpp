#ifndef __TetrahedronDlg_h__
#define __TetrahedronDlg_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dialog.h>
#else
#include <wx/wxprec.h>
#endif

#include <wx/timer.h>
#include <wx/dcbuffer.h>
#include <cmath>
//http://www.jjam.de/Java/Applets/3D_Effekte/Tetraeder_2.html
class TetrahedronDlg : public wxDialog
{
    public:

        TetrahedronDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("wxTetrahedron"), 
				 const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, 
				 long style = wxSUNKEN_BORDER | wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX);

        virtual ~TetrahedronDlg();
	
		// Event handler
        void TetrahedronDlgPaint(wxPaintEvent& event);
        void TetrahedronDlgSize(wxSizeEvent& event);
        void OnTimer(wxTimerEvent& event);

    private:

		// a pointer to a timer object
        wxTimer *m_timer;

		// 4 edges with 3 coordinates each
		double m_p[4][3];

		// aux vars
		enum EKoordinateAxisIndex { X=0, Y, Z };
 		// rotation angles in radian
    	double m_angle_x;
    	double m_angle_y;
    	double m_angle_z;

        enum wxIDs
        {
            ID_WXTIMER1 = 1001,
            ID_DUMMY_VALUE_ 
        };

        void OnClose(wxCloseEvent& event);
        void CreateGUIControls();

        DECLARE_EVENT_TABLE()
};

#endif // __TetrahedronDlg_h__
