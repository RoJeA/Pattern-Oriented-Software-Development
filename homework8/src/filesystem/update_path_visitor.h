#ifndef UPDATE_PATH_VISITOR_H
#define UPDATE_PATH_VISITOR_H

#include "visitor.h"
class Folder;
class File;
class Link;

class UpdatePathVisitor: public Visitor {
    public:
        UpdatePathVisitor();
        void visitFolder(Folder * folder);
        void visitFile(File * file);
        void visitLink(Link * link);
};

#endif
