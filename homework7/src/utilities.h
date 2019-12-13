#ifndef UTILITIES_H
#define UTILITIES_H

#include "node.h"
#include "folder.h"

class Utilities
{
public:
    string listNode(Node* node)
    {
        Folder * folder = dynamic_cast<Folder *> (node); // down cast
        if (folder != nullptr) { //it's a folder
            Iterator * it = folder->createIterator();
            string folderList="";
            for(it->first(); !it->isDone(); it->next()){
                folderList += it->currentItem()->name();
                folderList+=" ";
            }
            if(folderList!="")
                folderList.erase (folderList.end()-1, folderList.end());
            return folderList;
        }
        else{
            throw(string("Not a directory"));
        }
    }

    string findNode(Node* node, string name)
    {
        std::map<string,Node*> get;
        string allFile="";
        Folder * folder = dynamic_cast<Folder *> (node); // down cast
        if (folder != nullptr) { //it's a folder
            findfolder(node,get,name);
            std::string topPath = folder->name();
            for(map<string,Node*>::iterator it=get.begin();it!=get.end();it++){
                string cut=it->first;
                std::size_t pos = cut.find("/"+topPath);      // position of "/" in str
                allFile += "."+cut.substr (pos+topPath.size()+1);     // get from "/" to the end
                allFile += "\n";
            }
            if(allFile!="")
                allFile.erase (allFile.end()-1, allFile.end());
        }
        else{
            allFile=node->name();
        }
        return allFile;
    }
    void findfolder(Node* node,std::map<string,Node*> &get, string name){
        Folder * folder = dynamic_cast<Folder *> (node); // down cast
        if (folder != nullptr) {
            Iterator * it = folder->createIterator();
            for(it->first();!it->isDone();it->next()){
                if(it->currentItem()->name()==name){
                    get.insert(std::pair<string,Node*>(it->currentItem()->getPath(),it->currentItem()));
                }
                findfolder(it->currentItem(),get,name);
            }
        }
        else{

            if(node->name()==name)
            get.insert(std::pair<string,Node*>(node->getPath(),node));
        }
    }
};

#endif
