#include<iostream>
#include<string>

using namespace std;

// interface
class IImage { 
public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
    string filename;
public:

    RealImage(string file) {
        this->filename = file;
        // Heavy Operation
        cout << "[RealImage] Loading image from disk: " << filename << "\n";
    }

    void display() override {
        cout << "[RealImage] Displaying " << filename << "\n";
    }
};

class ImageProxy : public IImage {
    RealImage* realImage;
    string filename;
public:
// is not heavy op, not create object now will create when display is called
    ImageProxy(string file) {
        this->filename = file;
        realImage = nullptr;
    }

    void display() override {
        // Lazy initialization of RealImage
        // Lazy loading
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

int main() {
    IImage* image1 = new ImageProxy("sample.jpg");
    image1->display();
}
    