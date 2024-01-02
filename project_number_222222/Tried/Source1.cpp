#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

class character {
	int health; string name;
	string TextureName;
	vector<vector<sf::Texture>> Textures_Moves;
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
			switch{
			case direct == 0:
				Filename += "Left";
				break;
			case direct == 1:
				Filename += "Right";
				break;
			case direct == 2:
				Filename += "Up";
				break;
			case direct == 3:
				Filename += "Down";
				break;
			}
			for (int i = 0; i < a.size(); i++) {
				string FilenameEnd = Filename + char(i + '1');
				string AllPath = TextureName + "\\" + Filename + "\\" + FilenameEnd;
				a[i].loadFromFile(AllPath);
			}
			direct++;
		}
	}
};

int32_t main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");
	character BigBoss;
	BigBoss.SetSettingTo(10, "Big Boss", "BigBoss", 4, 2);
	BigBoss.LoadTextures();
}