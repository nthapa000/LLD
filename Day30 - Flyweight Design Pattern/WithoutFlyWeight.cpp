#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

using namespace std;

class Asteroid{
private:
    // Intrinsic properties (same for many asteroids) - Duplicated for each object
    int length;
    int width;
    int weight;
    string color;
    string texture;
    string material;

    // Extrinsic properties (unique for each asteroid)
    int posX, posY;
    int velocityX, velocityY;

public:
    Asteroid(int l, int w, int wt, string col, string tex, string mat, int posX, int posY, int velX, int velY){
        this->length = l;
        this->width = w;
        this->weight = wt;
        this->color = col;
        this->texture = tex;
        this->material = mat;
        this->posX = posX;
        this->posY = posY;
        this->velocityX = velX;
        this->velocityY = velY;
    }

    // printing the values, inactually it will render html in the screen
    void render() {
        cout << "Rendering " << color <<", " << texture << ", " << material 
            <<" asteroid at (" << posX << "," << posY 
            << ") Size: " << length << "x" << width
            << " Velocity: (" << velocityX << ", " 
            << velocityY << ")" << endl;
    }

    // Calculate approximate memory usage per object
    static size_t getMemoryUsage() {
        return sizeof(int) * 7 +                // length, width, weight, x, y, velocityX, velocityY 
               sizeof(string) * 3 +             // color, texture, material string objects
               32 * 3;                          // Approximate string data (assuming average 10 chars each): kitna store karenge in that string
    }
};

class SpaceGame {
private:
    vector<Asteroid*> asteroids;
    
public:
    void spawnAsteroids(int count) {
        cout << "\n=== Spawning " << count << " asteroids ===" << endl;
        
        vector<string> colors = {"Red", "Blue", "Gray"};
        vector<string> textures = {"Rocky", "Metallic", "Icy"};
        vector<string> materials = {"Iron", "Stone", "Ice"};
        int sizes[] = {25, 35, 45};
        
        // create new Asteroid
        for (int i = 0; i < count; i++) {
            int type = i % 3;

            // Unreadable 
            // we can use the builder pattern
            asteroids.push_back(new Asteroid(
                sizes[type], sizes[type], sizes[type] * 10,
                colors[type], textures[type], materials[type],
                100 + i * 50,          // Simple x: 100, 150, 200, 250... // varying value of postion of X and Y
                200 + i * 30,          // Simple y: 200, 230, 260, 290...
                1,                     // All move right with velocity 1
                2                      // All move down with velocity 2
            ));
        }
        
        cout << "Created " << asteroids.size() << " asteroid objects" << endl;
    }
    
    void renderAll() {
        cout << "\n--- Rendering first 5 asteroids ---" << endl;
        for (int i = 0; i < min(5, (int)asteroids.size()); i++) {
            asteroids[i]->render();
        }
    }
    
    size_t calculateMemoryUsage() {
        return asteroids.size() * Asteroid::getMemoryUsage();
    }
    
    int getAsteroidCount() { 
        return asteroids.size(); 
    }
};

int main() {    
    const int ASTEROID_COUNT = 1000000; 
    
    cout << "\n TESTING WITHOUT FLYWEIGHT PATTERN" << endl;
    SpaceGame* game = new SpaceGame();

    game->spawnAsteroids(ASTEROID_COUNT);

    // Show first 5 asteroids to see the pattern
    game->renderAll();

    // Calculate and display memory usage
    size_t totalMemory = game->calculateMemoryUsage();

    cout << "\n=== MEMORY USAGE ===" << endl;
    cout << "Total asteroids: " << ASTEROID_COUNT << endl;                           
    cout << "Memory per asteroid: " << Asteroid::getMemoryUsage() << " bytes" << endl; 
    cout << "Total memory used: " << totalMemory << " bytes" << endl;           
    cout << "Memory in MB: " << totalMemory / (1024.0 * 1024.0) << " MB" << endl;     
    // to create one crore asteroid object we required 2GB data of RAM, it fucked up my system and chrome close at the moment and laptop hanged
    return 0;
}
