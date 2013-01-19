#include "TetrahedronApp.hpp"
#include "TetrahedronDlg.hpp"

IMPLEMENT_APP(TetrahedronDlgApp)

bool TetrahedronDlgApp::OnInit()
{
    TetrahedronDlg* dialog = new TetrahedronDlg(NULL);
    SetTopWindow(dialog);
    dialog->Show(true);
    return true;
}

int TetrahedronDlgApp::OnExit()
{
    return 0;
}
