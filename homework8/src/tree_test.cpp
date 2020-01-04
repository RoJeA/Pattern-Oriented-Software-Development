#include <wx/wx.h>
#include "tree_test.h"
#include "tree_frame.h"

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit()
{
  wxString rootPath(wxGetApp().argv[1]);
  wxFrame *frame = new TreeFrame(wxT("***File System***"), rootPath, 0,0,500,500);
  frame->Show(true);
  this->SetTopWindow(frame);
  return true;
}
