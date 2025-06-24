#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class DocumentEditor{
private:
    // list of document elements
    vector<string> documentElements;
    // save the document rendered such that we dont have to render document again and again
    string renderedDocument;

public:
    // Adds text as a plain string
    void addText(string text){
        documentElements.push_back(text);
    }

    // Adds an image represented by its file path
    void addImage(string imagePath){
        documentElements.push_back(imagePath);
    }

    // Renders the document by checking the type of each element at runtime
    // Bussiness logic kitna acha doesn't matter much in lld interview what matters is how good our code is
    string renderDocument(){
        if(renderedDocument.empty()){
            string result;
            for(auto element: documentElements){
                // size greater than 4 and at last .jpg or .png is the way we are checking
                if(element.size() > 4 && (element.substr(element.size()-4)==".jpg" || element.substr(element.size()-4)==".png")){
                    result += "[Image: " + element + "]"+"\n"; 
                }else{
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }
        // if renderedDocument is not empty we will directly return
        return renderedDocument;
    }

    // Our main problem is not how we deal with the bussiness logic our main issue is how we deal with the overall architecture
    void saveToFile(){
        // file created
        ofstream file("document.txt");
        // file opened
        if(file.is_open()){
            // renderedDocument returned is stored in file
            file<<renderDocument();
            file.close();
            cout<<"Document saved to document.txt"<<endl;
        }else{
            cout<<"Error: Unable to open file for writing"<<endl;
        }
    }
};

int main(){
    // client code
    // client is someone who will use our DocumentEditor code
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("picture.jpg");
    editor.addText("This is a document editor");

    cout<<editor.renderDocument()<<endl;
    editor.saveToFile();
    return 0;
}