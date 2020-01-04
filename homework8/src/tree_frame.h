#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "./filesystem/filesystem_builder.cpp"
#include "text_frame.cpp"
#include "./filesystem/update_path_visitor.cpp"
using namespace std;
class TreeFrame : public wxFrame
{
public:
  TreeFrame(const wxChar *title, wxString rootPath, int xpos, int ypos, int width, int height):wxFrame((wxFrame *) nullptr, -1, title, wxPoint(xpos, ypos), wxSize(width, height))
  {
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(xpos,ypos), wxSize(width,height),  wxTR_HAS_BUTTONS  | wxTR_SINGLE );
    _textCtrl = new wxTextCtrl(_tree, -1, _T("Type some text..."),wxPoint(180,0), wxSize(300,300), wxTE_MULTILINE);
    _textCtrl->Enable(false);
    _saveButton = new wxButton(this,BUTTON_Hello,_T("Save"),wxPoint(180,310),wxSize(300,20),0);
    _saveButton->Enable(false);
    string get_root_folder = string(rootPath);
    FileSystemBuilder * fb = FileSystemBuilder::instance();
    fb->build(get_root_folder.c_str());
    Node* root = fb->getRoot();   //SetFileSystem
    _root = root;
    Folder * rootFolder = dynamic_cast<Folder *> (root); // down cast
    if(rootFolder != nullptr){
      firstWXFolder(rootFolder);
    }
    else{
      wxString fileName(wxT_2(root->name()));
      wxTreeItemId fileId = _tree->AddRoot(fileName);
    }

    _textCtrl->Bind(wxEVT_KEY_DOWN ,wxKeyEventHandler(TreeFrame::KeyDownEvent),this);
    _textCtrl->Bind(wxEVT_KEY_UP ,wxKeyEventHandler(TreeFrame::KeyReleaseEvent),this);

    // wxTreeItemId rootId = _tree->AddRoot(wxT("Root"));
    // wxTreeItemId folder1Id = _tree->AppendItem(rootId, wxT("Folder1"));
    // wxTreeItemId file1Id = _tree->AppendItem(folder1Id, wxT("File1"));
    // wxTreeItemId file2Id = _tree->AppendItem(rootId, wxT("File2"));
    // _tree->ExpandAllChildren(rootId);
  }
  void KeyDownEvent(wxKeyEvent& event)//Subject(Ctrl+S)
  {
    if(_keyVector.size()>1)
    {
      _keyVector.clear();
    }
    _keyVector.push_back(event.GetKeyCode());
    if(_keyVector.at(0)==308)
    {
      cout<<"Ctrl key"<<endl;
      if(_keyVector.size()<=1){
        return;
      }
      if(_keyVector.at(1)==83)
      {
        cout<<"S key"<<endl;
        saveAction();
      }
    }
    else
    {
      _keyVector.clear();
      event.Skip();
    }
  }
  void KeyReleaseEvent(wxKeyEvent& event)
  {
    _keyVector.clear();
    event.Skip();
    cout<<"Key Released"<<endl;
  }
  void firstWXFolder(Node * root)
  {
    wxString fileName(wxT_2(root->name()));
    wxTreeItemId rootId = _tree->AddRoot(fileName + ", "+to_string(root->size()));
    root->setWxTreeItemId(rootId);
    Iterator* it=root->createIterator();
    for(it->first();!it->isDone();it->next()){
      Node* node=it->currentItem();
      Folder * rootFolder = dynamic_cast<Folder *> (node); // down cast
      wxTreeItemId folderId = _tree->AppendItem(rootId, wxT_2(node->name()+", "+to_string(node->size())));
      node->setWxTreeItemId(folderId);
      if(rootFolder!=nullptr){//is folder
        findWXFolder(folderId, rootFolder);
      }
    }
    _tree->ExpandAllChildren(rootId);
  }
  void findWXFolder(wxTreeItemId wxTId, Node * node)
  {
    Folder * WXfolder = dynamic_cast<Folder *> (node); // down cast
    if (WXfolder != nullptr) {
      Iterator * it = WXfolder->createIterator();
      for(it->first();!it->isDone();it->next()){
        Node * currentNode = it->currentItem();
        wxTreeItemId folderId = _tree->AppendItem(wxTId, wxT_2(currentNode->name()+", "+to_string(currentNode->size())));
        currentNode->setWxTreeItemId(folderId);
        Folder * folder = dynamic_cast<Folder *> (currentNode); // down cast
        if (folder != nullptr) {
          findWXFolder(folderId, it->currentItem());
        }
      }
    }
  }
  Node * getNodeById(wxTreeItemId id, Node * rootNode)
  {
    Node * tarNode = nullptr;
    cout<<"find id:"<<id<<endl;
    cout<<"the folder id is :"<<rootNode->getPath()<<"  "<<rootNode->getWxTreeItemId()<<endl;
    if(rootNode->getWxTreeItemId() == id){
      cout<<"id Same as Root"<<endl;
      tarNode = rootNode;
    }
    Folder * folder = dynamic_cast<Folder *>(rootNode);
    if (folder!=nullptr) {
      Iterator* it = folder->createIterator();
      for(it->first();!it->isDone();it->next()){
        Node* node = it->currentItem();
        if(node->getWxTreeItemId() == id){
          tarNode = node;
          cout<<"FOUND"<<endl;
        }
        if(node->fileOrfolder(node->name()) == "Folder"){
          getDeeperNodeById(id,node,tarNode);
        }
      }
    }
    return tarNode;
  }
  void getDeeperNodeById(wxTreeItemId id, Node * root, Node* &target)
  {
    Iterator* it=root->createIterator();
    for(it->first();!it->isDone();it->next()){
      Node* node=it->currentItem();
      cout<<"current id :"<<node->getWxTreeItemId()<<endl;
      if(node->getWxTreeItemId()==id){
        target=node;
      }
      if(node->fileOrfolder(node->name()) == "Folder"){
        getDeeperNodeById(id,node,target);
      }
    }
  }
  string getWxItemName(string itemName)
  {
    size_t pos = itemName.find(",");
    string name = itemName.substr (0,pos);     // get from "/" to the en
    cout<<"getWxItemName："<<name;
    return name;
  }
  void OnEdit(wxTreeEvent& event)
  {
    wxTreeItemId itemId = event.GetItem();
    cout << itemId<< "edited" << endl;
    Node* node = getNodeById(itemId, _root);
    string new_name = getWxItemName(event.GetLabel().ToStdString());
    string old_name = getWxItemName(_tree->GetItemText(itemId).ToStdString());
    if(new_name=="")
    {
      return;
    }
    bool renameStat = ShowMessageRename(new_name,old_name);
    if(!renameStat){
      _tree->SetItemText(itemId,wxString(old_name+", "+to_string(node->size())));
      event.Veto();
      return;
    }
    UpdatePathVisitor * upv = new UpdatePathVisitor();
    node->renameNode(new_name);
    node->accept(upv);
    _tree->SetItemText(itemId,wxString(new_name+", "+to_string(node->size())));
    event.Veto();
  }
  void DoubleClick(wxTreeEvent& event)
  {
    std::cout << "double click" << std::endl;
    _tree->EditLabel(event.GetItem());
  }
  void ReadOnClick(wxTreeEvent &event)
  {
    wxTreeItemId id = event.GetItem();
    _itemId = id;
    std::cout << id<< std::endl;
    Node * node = getNodeById(id,_root);
    if(!node)
      std::cout << "nothing to show" << endl;
    else{
      _fpath = node->getPath();
      if(node->fileOrfolder(node->name()) == "Link")
      {
        _textCtrl->ChangeValue(wxT_2("The file is not displayed in the editor because it uses an unsupported text encoding."));
        _textCtrl->Enable(false);
        _saveButton->Enable(false);
      }
      else if(node->fileOrfolder(node->name()) == "File"){
        readWxFile();
        // _textCtrl->Enable(true);
        // _saveButton->Enable(true);
        // _textCtrl->LoadFile(wxT_2(node->getPath()));
      }
      else if(node->fileOrfolder(node->name()) == "Folder"){
        _textCtrl->ChangeValue(wxT_2("This is a folder"));
        _textCtrl->Enable(false);
        _saveButton->Enable(false);
      }
    }
  }
  void SaveButton(wxCommandEvent& event)//Subject
  {
    cout<<"EVENT ID:"<<event.GetId()<<endl;
    saveAction();
  }
  void saveAction()//Set State
  {
    Node* node = getNodeById(_itemId,_root);
    if(node->fileOrfolder(node->name()) == "File"){
      bool saveResult = showSaveMessage();
      if(saveResult){
        cout<<"save " <<_fpath<<endl;
      }
      else{
        return ;
      }
    }
    _textCtrl->SaveFile(wxT_2(_fpath));
    wxUpdateSize();
  }
  void wxUpdateSize()//Update
  {
    Node* node = getNodeById(_itemId,_root);
    cout<<"Update Size from: "<<node->size();
    node->updateSize();
    cout<<",to: "<<node->size()<<endl;
    _tree->SetItemText(_itemId,wxString(node->name()+", "+to_string(node->size())));
    _tree->Refresh();
  }
  void readWxFile()
  {
    ifstream wxfile (_fpath);
    char c;
    while (wxfile.get(c))
    {
      int isAscii = int(c);
      if(isAscii<-1 || isAscii>255)
      {
        _textCtrl->ChangeValue(wxT_2("The file is not displayed in the editor because it uses an unsupported text encoding."));
        _textCtrl->Enable(false);
        _saveButton->Enable(false);
        return;
      }
    }
    _textCtrl->Enable(true);
    _saveButton->Enable(true);
    _textCtrl->LoadFile(wxT_2(_fpath));
  }
  bool showSaveMessage()
  {
    wxMessageDialog *wxdialog= new wxMessageDialog(NULL,wxT("You want save?"), wxT("Confirm"),wxYES_NO | wxCANCEL | wxNO_DEFAULT | wxICON_QUESTION);
    return comfirmSaveStat(wxdialog);
  }
  bool comfirmSaveStat(wxMessageDialog * wxdialog)
  {
    if(wxdialog->ShowModal()==wxID_YES)
      return true;
    else
      return false;
  }
  bool ShowMessageRename(string new_name,string old_name)
  {
    wxMessageDialog * dialog= new wxMessageDialog(NULL,wxT("label edited: "+new_name+"-- old name was "+old_name), wxT("Confirm"),wxYES_NO | wxCANCEL | wxNO_DEFAULT | wxICON_QUESTION);
    return comfirmSaveStat(dialog);
  }

  wxTreeCtrl *_tree;
private:
  DECLARE_EVENT_TABLE()
  Node * _root;
  wxTextCtrl *_textCtrl;
  wxButton * _saveButton;
  wxTreeItemId _itemId;
  string _fpath;
  vector<int> _keyVector;
};
BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
  EVT_TREE_END_LABEL_EDIT (wxID_ANY, TreeFrame::OnEdit)
  EVT_TREE_ITEM_ACTIVATED(wxID_ANY,TreeFrame::DoubleClick)
  EVT_TREE_SEL_CHANGED(wxID_ANY,TreeFrame::ReadOnClick)
  EVT_BUTTON(wxID_ANY, TreeFrame::SaveButton)
END_EVENT_TABLE()
#endif
