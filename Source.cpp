
#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <string>
#include <fstream>
#include <SFML/Graphics/Color.hpp>
#include"Header.h"
/*
zohaib umer
rehan tajik 
f
*/
//#include"../SFML/Images
using namespace sf;
using namespace std;
struct coordinats {
	int x;
	int y;
};
void createBack(RenderWindow& window) {
	Image map_image;
	map_image.loadFromFile("Images/Frontyard_dim.png");
	Texture map;
	map.loadFromFile("Images/Frontyard_dim.png");
	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(0, 0);
	sf::Music bgMusic;
	bgMusic.openFromFile("Images/Voices evillaugh.mp3");
	bgMusic.play();
	bgMusic.setVolume(100);
	while (window.isOpen()) {
		window.clear();
		window.draw(s_map);
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {

					return;
				}


			}
		}
		window.display();
	}

}
int main()
{
	
	RenderWindow window(VideoMode(1050, 600), "Plants Vs Zombies");
	//Game icon
	Image icon;
	if (!icon.loadFromFile("Images/icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());
	 int y = 0;
	///////////////////////////////////////

	//Game field (5*9)
	//Point 137*79 - leftmost point
	//length 41; width 53
	const int ROWS = 5;
	const int COLS = 9;
	
	
	Clock timeMoney;
	int blockWidth = 110;
	int blockHeight = 100;
	Clock clock;

	ScoreManager scoreManager;

	Texture* textures = new Texture[7];
	for (int i = 0; i < 7; i++) {
		textures[i].loadFromFile("PVZ/Zombies/simplezombie.png");
	}
	for (int i = 0; i < 7; i++) {
		textures[i].setRepeated(true);
		textures[i].setSmooth(true);
	}
	Texture* attacktexture = new Texture[7];
	IntRect attacktextureRects[7] = {
		IntRect({4,230,33,44}),
		IntRect({49,230,33,44}),
		IntRect({94,230,33,44}),
		IntRect({138,230,35,44}),
		IntRect({186,232,31,42}),
		IntRect({232,230,30,44}),
		IntRect({275,229,32,45})
	};
	for (int i = 0; i < 7; i++) {
		attacktexture[i].loadFromFile("PVZ/Zombies/simplezombie.png");
	}
	for (int i = 0; i < 7; i++) {
		attacktexture[i].setRepeated(true);
		attacktexture[i].setSmooth(true);
	}
	Credentials c(1050,600);
	int score = 0;
	bool le = false;
	mainmenu menu(window.getSize().x, window.getSize().y);
	sf::Music bgMusic;
	bgMusic.openFromFile("Images/03. Choose Your Seeds.mp3");
	bgMusic.setLoop(1);
	bgMusic.play();
	bgMusic.setVolume(50);
	game gamer;
	gameforlevel2 gamer1;
	Highscore h(1050, 600);
	string playername;
	ScoreManager sv;
	gameforlevel3 sg;
	while (window.isOpen())
	{

		
		float time = clock.getElapsedTime().asMicroseconds();
		float moneyTime = timeMoney.getElapsedTime().asSeconds();

		clock.restart();
		time = time / 800;
	
		Event event;
		while (window.isOpen()) {
			sf::Event event;
			menu.draw(window);
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up) {
						menu.moveup();
					}
					else if (event.key.code == sf::Keyboard::Down) {
						menu.movedown();
					}
					else if (event.key.code == sf::Keyboard::Return) {
						int selectedIdx = menu.getSelectedIndex();
						switch (selectedIdx)
						{
						case 0:
							std::cout << "Play selected!" << std::endl;
							//sg.gameLoop(textures, attacktexture, window, score, le);
							//gamer1.gameLoop(textures, attacktexture, window, score, le);
							//c.draw(window,playername);
							gamer.gameLoop(textures, attacktexture, window, score, le);
								if (le) {
									gamer1.gameLoop(textures, attacktexture, window, score, le);
									if (le) {
										sg.gameLoop(textures, attacktexture, window, score, le); {
											if (le) {
												return 0;
											}
											if (!le) {
												createBack(window);
											}

										}
									}
									if (!le) {
										createBack(window);
									}
								}
								if (!le) {
									createBack(window);
								}
								sv.updateTopScores(playername, score);
							break;
						case 1:
							std::cout << "Option selected!" << std::endl;
							break;
						case 2:
							std::cout << "About selected!" << std::endl;
							h.draw(window);
							break;
						case 3:
							std::cout << "Exit selected!" << std::endl;
							window.close();
							break;
						default:
							break;
						}
					}
				}
			}
		}
		}

		return 0;
	}



