#include "TetrahedronDlg.hpp"
#include <wx/pen.h>
BEGIN_EVENT_TABLE(TetrahedronDlg, wxDialog)
    EVT_CLOSE(TetrahedronDlg::OnClose)
    EVT_SIZE(TetrahedronDlg::TetrahedronDlgSize)
    EVT_PAINT(TetrahedronDlg::TetrahedronDlgPaint)
    EVT_TIMER(ID_WXTIMER1, TetrahedronDlg::OnTimer)
END_EVENT_TABLE()

TetrahedronDlg::TetrahedronDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
    : wxDialog(parent, id, title, position, size, style)
{
    CreateGUIControls();
}

TetrahedronDlg::~TetrahedronDlg()
{
}

void TetrahedronDlg::CreateGUIControls()
{
    SetIcon(wxNullIcon);
    SetSize(8, 8, 509, 412);
    Center();
	/* -------------------------
    //  	   4
    //  	 / | \
    //  	/  |  \
    //     /   |   \
    //    1 - -|- - 3
    //  	`  2  
	--------------------------- */
    // init member variables

    // Tetraeder-Höhe
    const double th(sqrt(2/3.0)*300);

    // Höhe des Tetraeder-Mittelpunkts
    const double tm(sqrt(1/24.0)*300);

    // Strecke Ecke-Mittelpunkt eines Dreiecks
    const double em(sqrt(1/3.0)*300);

    // Strecke Seite-Mittelpunkt eines Dreiecks
    const double sm(sqrt(1/12.0)*300);

    // 4 Eckpunkte im lokalen Tetraeder-Koordinatensystem
    // Nullpunkt = Mittelpunkt
    m_p[0][X] = -150; m_p[0][Y] = -tm;    m_p[0][Z] = +sm;
    m_p[1][X] =    0; m_p[1][Y] = -tm;    m_p[1][Z] = -em;
    m_p[2][X] = +150; m_p[2][Y] = -tm;    m_p[2][Z] = +sm;
    m_p[3][X] =    0; m_p[3][Y] = +th-tm; m_p[3][Z] =   0;

    // y-Werte spiegeln
    for (int i=0;i<4;++i) 
        m_p[i][Y] = -m_p[i][Y];

	m_angle_x = 0.02;
	m_angle_y = 0.0075;
	m_angle_z = 0.005;

    m_timer = new wxTimer();
    m_timer->SetOwner(this, ID_WXTIMER1);
    m_timer->Start(40);
}

void TetrahedronDlg::OnClose(wxCloseEvent& WXUNUSED(event))
{
    Destroy();
}

void TetrahedronDlg::TetrahedronDlgPaint(wxPaintEvent& WXUNUSED(event))
{
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    wxBufferedPaintDC dc(this);

    // Get window dimensions
    wxSize sz = GetClientSize();
	// determine the center of the canvas
    const wxPoint center(wxPoint(sz.x / 2, sz.y / 2));

    // create background color
    wxColour powderblue = wxColour(176,224,230);

    // draw powderblue background
    dc.SetPen(powderblue);
    dc.SetBrush(powderblue);
    dc.DrawRectangle(0, 0, sz.x, sz.y);


    // draw clock border
	wxPen Pen(*wxBLACK_PEN);
	Pen.SetWidth(1);
    dc.SetPen(Pen);
    dc.SetBrush(*wxBLACK_BRUSH);

    // initial cube coordinates:
    // --> use center.x (center.y) to ensure the tetrahedron stays allways in the center of the canvas
    dc.DrawLine((int)(m_p[0][X])+center.x,(int)(m_p[0][Y])+center.y,(int)(m_p[1][X])+center.x,(int)(m_p[1][Y])+center.y);
    dc.DrawLine((int)(m_p[1][X])+center.x,(int)(m_p[1][Y])+center.y,(int)(m_p[2][X])+center.x,(int)(m_p[2][Y])+center.y);
    dc.DrawLine((int)(m_p[2][X])+center.x,(int)(m_p[2][Y])+center.y,(int)(m_p[0][X])+center.x,(int)(m_p[0][Y])+center.y);
    dc.DrawLine((int)(m_p[0][X])+center.x,(int)(m_p[0][Y])+center.y,(int)(m_p[3][X])+center.x,(int)(m_p[3][Y])+center.y);
    dc.DrawLine((int)(m_p[1][X])+center.x,(int)(m_p[1][Y])+center.y,(int)(m_p[3][X])+center.x,(int)(m_p[3][Y])+center.y);
    dc.DrawLine((int)(m_p[2][X])+center.x,(int)(m_p[2][Y])+center.y,(int)(m_p[3][X])+center.x,(int)(m_p[3][Y])+center.y);

    // Kreuzprodukt der eine Flaeche aufspannenden Vektoren bilden
    // Wenn Betrag der z-Koordinate positiv: Flaeche anzeigen
	if(((m_p[0][X]-m_p[1][X])*(m_p[2][Y]-m_p[1][Y])-(m_p[0][Y]-m_p[1][Y])*(m_p[2][X]-m_p[1][X])) > 0)
	{
		wxPoint pt[3];
		pt[0].x = (m_p[0][X])+center.x;
		pt[1].x = (m_p[1][X])+center.x;
		pt[2].x = (m_p[2][X])+center.x; 

		pt[0].y = (m_p[0][Y])+center.y;
		pt[1].y = (m_p[1][Y])+center.y;
		pt[2].y = (m_p[2][Y])+center.y; 

    	dc.SetBrush(*wxRED_BRUSH);
		dc.DrawPolygon(3,pt);	  
	}
	if(((m_p[2][X]-m_p[1][X])*(m_p[3][Y]-m_p[1][Y])-(m_p[2][Y]-m_p[1][Y])*(m_p[3][X]-m_p[1][X])) > 0)
	{
		wxPoint pt[3];
		pt[0].x = (m_p[2][X])+center.x;
		pt[1].x = (m_p[1][X])+center.x;
		pt[2].x = (m_p[3][X])+center.x; 

		pt[0].y = (m_p[2][Y])+center.y;
		pt[1].y = (m_p[1][Y])+center.y;
		pt[2].y = (m_p[3][Y])+center.y; 

    	dc.SetBrush(*wxGREEN_BRUSH);
		dc.DrawPolygon(3,pt);	  
	}
	if(((m_p[3][X]-m_p[1][X])*(m_p[0][Y]-m_p[1][Y])-(m_p[3][Y]-m_p[1][Y])*(m_p[0][X]-m_p[1][X])) > 0)
	{
		wxPoint pt[3];
		pt[0].x = (m_p[3][X])+center.x;
		pt[1].x = (m_p[1][X])+center.x;
		pt[2].x = (m_p[0][X])+center.x; 

		pt[0].y = (m_p[3][Y])+center.y;
		pt[1].y = (m_p[1][Y])+center.y;
		pt[2].y = (m_p[0][Y])+center.y; 

    	dc.SetBrush(*wxBLUE_BRUSH);
		dc.DrawPolygon(3,pt);	  
	}
	if(((m_p[2][X]-m_p[3][X])*(m_p[0][Y]-m_p[3][Y])-(m_p[2][Y]-m_p[3][Y])*(m_p[0][X]-m_p[3][X])) > 0)
	{
		wxPoint pt[3];
		pt[0].x = (m_p[2][X])+center.x;
		pt[1].x = (m_p[3][X])+center.x;
		pt[2].x = (m_p[0][X])+center.x; 

		pt[0].y = (m_p[2][Y])+center.y;
		pt[1].y = (m_p[3][Y])+center.y;
		pt[2].y = (m_p[0][Y])+center.y; 

    	dc.SetBrush(*wxGREY_BRUSH);
		dc.DrawPolygon(3,pt);	  
	}
}

void TetrahedronDlg::TetrahedronDlgSize(wxSizeEvent& WXUNUSED(event))
{
    Refresh();
}

void TetrahedronDlg::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	 double px, py, pz;

	 // rotate
	 for (unsigned int i=0;i<4;i++) 
	 {
	 	 px = m_p[i][X];
	 	 py = m_p[i][Y];
	 	 pz = m_p[i][Z];

	 	 // Rotate x-axis
	 	 m_p[i][Y] = py*cos(m_angle_x)-pz*sin(m_angle_x);
	 	 m_p[i][Z] = py*sin(m_angle_x)+pz*cos(m_angle_x);

	 	 py = m_p[i][Y];
	 	 pz = m_p[i][Z];

	 	 // Rotate y-axis
	 	 m_p[i][X] = px*cos(m_angle_y)+pz*sin(m_angle_y);
	 	 m_p[i][Z] =-px*sin(m_angle_y)+pz*cos(m_angle_y);

	 	 px = m_p[i][X];

	 	 // Rotate z-axis
	 	 m_p[i][X] = px*cos(m_angle_z)-py*sin(m_angle_z);
	 	 m_p[i][Y] = py*cos(m_angle_z)+px*sin(m_angle_z);
	 }

	// force refresh
    Refresh();
}
