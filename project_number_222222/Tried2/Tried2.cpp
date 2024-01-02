#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class character {
public:
    int health, direct_main = 0; string name;
    string TextureName;
    vector<vector<sf::Texture>> Textures_Moves;
    sf::Sprite CharacterSprite;
    void SetSettingTo(int health_in, string name_in, string FilenameOfTexture_in, int count_of_directions, int count_of_moves) {
        health = health_in;
        name = name_in;
        TextureName = FilenameOfTexture_in;
        Textures_Moves.resize(count_of_directions);
        for (vector<sf::Texture>& a : Textures_Moves)
            a.resize(count_of_moves);
    }

    //0 -- left, 1 -- right, 2 -- up, 3 -- down
    void LoadTextures() {
        int direct = 0;
        for (vector<sf::Texture>& a : Textures_Moves) {
            string Filename = TextureName;

            /*
            switch (direct) {
            case 0:
                Filename += "Left";
            }
            case 1:
            */

            if (direct == 0)
                Filename += "Left";
            if (direct == 1)
                Filename += "Right";
            if (direct == 2)
                Filename += "Up";
            if (direct == 3)
                Filename += "Down";

            for (int i = 0; i < a.size(); i++) {
                string FilenameEnd = Filename + char(i + '1');
                string AllPath = TextureName + "\\" + Filename + "\\" + FilenameEnd + ".png";
                cout << AllPath << "\n";
                a[i].loadFromFile(AllPath);
            }
            direct++;
        }
    }
    
    void SetTextureByDirect(int move) {
        CharacterSprite.setTexture(Textures_Moves[direct_main][move]);
    }
};

int32_t main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
    character BigBoss;
    BigBoss.SetSettingTo(10, "Big Boss", "BigBoss", 4, 2);
    BigBoss.LoadTextures();
    BigBoss.SetTextureByDirect(0);
    BigBoss.CharacterSprite.scale(3, 3);
    //0 -- staying, 1 -- running
    sf::Clock clock;
    window.setFramerateLimit(30);
    
    int q = 0;
    bool move = false;
    while (window.isOpen()) {
        cout << q << "\n";
        q++;
        float currentTime = clock.restart().asSeconds();
        float fps = 1.0f / (currentTime);
        //cout << fps << "\n";
        if (q > 12)
            q = 0;
        if (move == true) {
            if (q > 6) {
                if (q <= 12) {
                    BigBoss.SetTextureByDirect(1);
                    
                }
                if (q > 12)
                    q = 0;
            }
            else {
                BigBoss.SetTextureByDirect(0);
            }
        }
        else {
            BigBoss.SetTextureByDirect(0);
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(BigBoss.CharacterSprite);
        window.display();

        //0 -- left, 1 -- right, 2 -- up, 3 -- down
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            BigBoss.CharacterSprite.move(-10.f, 0.f);
            BigBoss.direct_main = 0;
            move = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            BigBoss.CharacterSprite.move(10.f, 0.f);
            BigBoss.direct_main = 1;
            move = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            BigBoss.CharacterSprite.move(0.f, 10.f);
            BigBoss.direct_main = 3;
            move = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            BigBoss.CharacterSprite.move(0.f, -10.f);
            BigBoss.direct_main = 2;
            move = true;
        }
        else {
            move = false;
        }
    }
}


/*#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
//DEBUG -- туда пихай файлы для проигрывания
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
    sf::SoundBuffer BigBossTheme;
    if (!BigBossTheme.loadFromFile("Music\\1-19 Beyond Big Boss NES (Final Boss 2 ~ Escape).mp3"))
    {
        cout << "Error while loading music" << endl;
        sf::sleep(sf::seconds(5));
        return -1;
    }
    sf::Sound sound;
    sound.setBuffer(BigBossTheme);
    sound.play();

    sf::Texture BigBossTexture;
    if (!BigBossTexture.loadFromFile("BigBoss\\BigBossLeft\\BigBossLeft1.png")) {
        cout << "Error while loading image" << endl;
        sf::sleep(sf::seconds(5));
        return -1;
    }
    sf::Sprite BigBossSprite(BigBossTexture);
    BigBossSprite.scale(sf::Vector2f(3, 3));

    sf::Clock clock;
    window.setFramerateLimit(30);


    while (window.isOpen()) {
        float currentTime = clock.restart().asSeconds();
        float fps = 1.0f / (currentTime);
        cout << fps << "\n";

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(BigBossSprite);
        window.display();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            BigBossSprite.move(-10.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            BigBossSprite.move(10.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            BigBossSprite.move(0.f, 10.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            BigBossSprite.move(0.f, -10.f);
        }
    }
}*/