#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

// Abstraction for document elements
class DocumentElement{
public:
    virtual string render() = 0;
};

// Concrete implementation for text elements
class TextElement: public DocumentElement{
private:
    string text;

public:
    TextElement(string text){
        this->text = text;
    }

    string render() override{
        return text;
    }
};

// Concrete implementation for image elements
class ImageElement: public DocumentElement{
private:
    string imagePath;

public:
    ImageElement(string imagePath){
        this->imagePath = imagePath;
    }

    string render() override {
        return "[Image: " + imagePath + "]";
    }
};

// NewLineElement represents a line break in the document
class NewLineElement: public DocumentElement{
public:
    string render() override{
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document
class TabSpaceElement: public DocumentElement{
public:
    string render() override{
        return "\t";
    }
};

// Document class responsible for holding a collection of elements
class Document{
private:
    vector<DocumentElement*> documentElements;

public:
    void addElement(DocumentElement* element){
        documentElements.push_back(element);
    }

    // Render the document by concatenating the render output of all the elements
    string render(){
        string result;
        // loop throught the list and calls the element own render method
        for(auto element: documentElements){
            result += element -> render();
        }
        return result;
    }
};

// Persistence Interface
class Persistence{
public:
    virtual void save(string data) = 0;
};

// FileStorage implementation of Persistence
class FileStorage : public Persistence{
public:
    void save(string data) override {
        ofstream outFile("document.txt");
        if(outFile){
            outFile << data;
            outFile.close();
            cout<<"Document saved to document.txt"<<endl;
        }else{
            cout<<"Error: Unable to open file for writing"<<endl;
        }
    }
};

// DbStorage implementation
class DBStorage : public Persistence{
public:
    void save(string data) override {
        // Save to DB
    }  
};

// DocumentEditor class managing client interactions
class DocumentEditor{
private:
    Document* document;
    Persistence* storage;
    string renderedDocument;

public:
// any type of storage can come here due to polymorphism whatever it comes we will pass to the reference variable
    DocumentEditor(Document* document, Persistence* storage){
        this->document = document;
        this->storage = storage;
    }

    void addText(string text){
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath){
       document->addElement(new ImageElement(imagePath)); 
    }

    // Adds a new line to the document.
    void addNewLine(){
        document->addElement(new NewLineElement());
    }

    // Adds a tab space to the document.
    void addTabSpace(){
        document->addElement(new TabSpaceElement());
    }

    string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument = document->render();
        }
        // if not empty directly return renderedDocument or if empty then call the render function and then store in the renderedDocument and then return  
        return renderedDocument;
    }

    void saveDocument(){
        storage->save(renderDocument());
    }
};

// Client usage examples
int main(){
    Document* document = new Document();
    Persistence* persistence = new FileStorage();
    // Object passed is of File Type
    DocumentEditor* editor = new DocumentEditor(document,persistence);

    // Simulate a client using the editor with common text formatting features.
     editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    // Render and display the final document.
    cout << editor->renderDocument() << endl;
    // Here fileStorage ka object call hoga
    editor->saveDocument();

    return 0;
}