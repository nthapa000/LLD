// #pragma once is a non-standard but widely supported preprocessor directive that ensures a particular header file is included only once per translation unit, even if it’s #include-d multiple times in your project.
#pragma once
#include <string>
#include <iostream>

using namespace std;

class Song{
private:
    string title;
    string artist;
    string filePath;

public:
    Song(string t, string a, string f){
        title = t;
        artist = a;
        filePath = f;
    }

    string getTitle(){
        return title;
    }

    string getArtist(){
        return artist;
    }

    string getFilePath(){
        return filePath;
    }
};

