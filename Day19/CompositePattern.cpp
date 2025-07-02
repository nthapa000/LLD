#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Base interface for files and folders
class FileSystemItem {
public:
    virtual ~FileSystemItem(){}
    virtual void ls(int indent = 0) = 0;
    virtual void openAll (int indent = 0) = 0;
    virtual int getSize() = 0;
    // not supported in file
    virtual FileSystemItem* cd(const string& name) = 0;
    // return its name
    virtual string getName() = 0;
    // when we implement cd
    virtual bool isFolder() = 0;
};

// leaf : file
class File : public FileSystemItem{
    string name;
    int size;

public:
    File(const string& n, int s){
        name = n;
        size = s;
    }

    // indent is basically default argument we basically wanted to print with an indentation just to look good visually
    void ls(int indent = 0) override{
        // simply name print
        cout<< string(indent, ' ') <<name <<"\n";
    }

    void openAll(int indent = 0) override {
        // to extract everyone it simply print its name, it the end node
        cout<<string(indent,' ') <<name <<"\n";
    }

    int getSize() override {
        return size;
    }

    FileSystemItem* cd(const string&) override{
        // directory cant change in file
        return nullptr;
    }

    string getName() override{
        return name;
    }

    bool isFolder() override{
        // since it is not a folder
        return false;
    }
};

// is a relationship
class Folder : public FileSystemItem{
    string name;
    // has a relationship
    vector<FileSystemItem*> children;

public:
    Folder(const string &n){
        name = n;
    }

    ~Folder(){
        for(auto c: children) delete c;
    }

    // adding item it can be file or folder
    void add(FileSystemItem* item){
        children.push_back(item);
    }

    // bs apni directory kai andhar ke files folder bta do
    void ls(int indent = 0) override{
        for(auto child: children){
            if(child->isFolder()){ //folder
                cout<<string(indent, ' ')<<"+ "<<child->getName()<<"\n";
            }else{ //file
                cout<<string(indent,' ')<<child->getName()<<"\n";
            }
        }
    }

    // sabko expand kardo
    void openAll(int indent = 0) override{
        cout<<string(indent, ' ')<<"+ "<<name<<"\n";
        for(auto child: children){ // till it reaches leaf node
            child->openAll(indent + 4); // indent + 4 just to give space 
        }
    }

    // folder ka size , jo vector mai saare element ke size hoga
    int getSize() override{
        int total = 0;
        for (auto child: children){
            total += child->getSize();
        }
        return total;
    }

    FileSystemItem* cd(const string& target) override{
        // kya child folder hai and if equal to target then return its child
        for(auto child: children){
            if(child->isFolder() && child->getName() == target){
                return child;
            }
        }
        // not found or not a folder
        return nullptr;
    }

    string getName() override{
        return name;
    }

    bool isFolder() override{
        return true;
    }
};

int main() {
    // Build file system
    Folder* root = new Folder("root");
    // size
    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 1));

    Folder* docs = new Folder("docs");
    docs->add(new File("resume.pdf", 1));
    docs->add(new File("notes.txt", 1));
    root->add(docs);

    Folder* images = new Folder("images");
    images->add(new File("photo.jpg", 1));
    root->add(images);

    root->ls();

    docs->ls();

    root->openAll();

    // docs folder agya
    FileSystemItem* cwd = root->cd("docs");
    if (cwd != nullptr) {
        cwd->ls();
        // resume.txt
        // notes.pdf 
    } else {
        cout << "\n Could not cd into docs \n";
    }

    // jitna bhi element hai milake size : 5
     cout << root->getSize();

    // Cleanup
    delete root;
    return 0;
}