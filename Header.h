#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include <SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <string>
#include <fstream>
#include <SFML/Graphics/Color.hpp>
/*
zohaib umer
rehan tajik
f
*/
//#include <SFMLGif.h>
using namespace sf;
using namespace std;
class ZombieFactory {
public:
	virtual void animatezombie(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) = 0;
	virtual void  draw(RenderWindow& window, int i, float x, float y) = 0;
	virtual void animatezombie2(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) = 0;
	virtual void movezombie(float time, float offsetX, float offsetY, RenderWindow& window, int i,int level) = 0;
	virtual bool getalive() = 0;
	virtual void setalive(bool isActive) = 0;
	virtual bool checkend() = 0;
	virtual float getx() = 0;
	virtual float gety() = 0;
	virtual int gethealth() = 0;
	virtual void reducehealth(int hea) = 0;
	virtual void setposition(float x, float y) = 0;
	//virtual void setHealth(int newHealth) = 0;
	virtual void setcollision(bool i) = 0;
	virtual bool getcollision() = 0;
	virtual bool getmoveup() = 0;
};

class Zombie :public ZombieFactory {
public:
	//int getHealth() const { return health; }
	//void setHealth(int newHealth) { health = newHealth; }
	//void setalive(bool isActive) {
	//	alive = isActive;
	//}
	// bool getalive() const {
	//	return alive;
	//}
protected:
	//int level;
	bool collision = false;
	int health;
	int speed;
	float elapsedTime;
	float interval;
	Sprite sprite;
	Clock clock;
	bool alive = false;
	int currentFrame = 0;
	Texture texture;
};

class SimpleZombie :public Zombie {
	int currentFrame2 = 0;
	int textureCount2 = 0;
public:
	SimpleZombie(int h = 100) {
		health = h;
		speed = 3;
		texture.loadFromFile("PVZ/Zombies/simplezombie.png");
		sprite = Sprite(texture);
		sprite.setTextureRect({ 8,696,29,48 });
		sprite.scale(2, 2);
		
	}
	void draw(RenderWindow& window, int i, float x,float y) {

		float positionx[] = { 1078,1059,1040,1089,1110,1078,1059,1040,1089,1110 };
		float positiony[] = { 328,227,142,187,421,328,227,142,187,421 };

		/*sprite.setPosition(positionx[i], positiony[i]);*/
		window.draw(sprite);

		/*window.display();*/

	}
	void setcollision(bool i) {
		collision = i;
	}
	bool getcollision() {
		return collision;
	}
	bool getmoveup() {
		return 0;
	}

	void movezombie(float time, float offsetX, float offsetY, RenderWindow& window, int i,int level) {
		float distx = speed * time * offsetX;
		float disty = speed * time * offsetY;

		float positionx[] = { 1078, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
		float positiony[] = { 100-15,201-15,300-15,400-13,500-13,100-15,200-15,300-15,400-13,500-13 };
		float positiony1[] = { 100 - 65,201 - 55,300 - 55,400 - 43,500 - 40,100 - 55,200 - 55,300 - 55,400 - 43,500 - 40 };
		if (level == 1) {
			sprite.setPosition(positionx[i] + distx, positiony[i] + disty);
		}
		if (level == 2) {
			sprite.setPosition(positionx[i] + distx, positiony1[i] + disty);
		}
		window.draw(sprite);
	}

	bool checkend() {
		int endx[] = { 150,150,150,150,150,150,150,150,150 };
		int endy[] = { 113,171,238,225,303,302,256,409,513,174 };
		for (int j = 0; j < 8; j++) {
			if (sprite.getPosition().x <= endx[j] && sprite.getPosition().y >= endy[j]) {
				return true;
			}
		}
		return false;
	}

	void animatezombie(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		/*static Clock clock; */

		elapsedTime = clock.getElapsedTime().asSeconds();
		interval = 1.0f / 7;

		if (elapsedTime >= interval) {
			clock.restart();
			static int textureCount = 0;
			textureCount = (textureCount + 1) % size;
			/*clock.restart();*/


			sprite.setTexture(textures[currentFrame]);
			sprite.setTextureRect(textureRects[currentFrame]);
			currentFrame = (currentFrame + 1) % size;


			window.draw(sprite);

			/*window.display();*/
		}
	}

	void animatezombie2(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		/*static Clock clock; */

		elapsedTime = clock.getElapsedTime().asSeconds();
		interval = 1.0f / 7;

		if (elapsedTime >= interval) {
			clock.restart();
			
			textureCount2 = (textureCount2 + 1) % size;
			/*clock.restart();*/


			sprite.setTexture(textures[currentFrame2]);
			sprite.setTextureRect(textureRects[currentFrame2]);
			currentFrame2 = (currentFrame2 + 1) % size;


			window.draw(sprite);

			/*window.display();*/
		}
	}

	void setalive(bool isActive) {
		alive = isActive;
	}
	bool getalive() {
		return alive;
	}
	float getx() {
		return sprite.getPosition().x;
	}
	float gety() {
		return sprite.getPosition().y;
	}
	int gethealth() {
		return health;
	}
	void reducehealth(int hea) {
		health -= hea;
	}
	void setposition(float x, float y) {
		sprite.setPosition(x, y);
	}
};
class FootballZombie :public Zombie {
	bool moveUp = true;
	bool moveDown = false;
	int level;
	
public:
	//alive = true;
	FootballZombie(int h =100) {
		health = h;
		speed = 10;
		texture.loadFromFile("PVZ/Zombies/DS_DSi_-_Plants_vs_Zombies_-_Football_Zombie-removebg.png");
		sprite = Sprite(texture);
		sprite.setTextureRect({ 2,225,50,56 });
		sprite.scale(2, 2);
	}
	void setcollision(bool i) {
		collision = i;
	}
	bool getcollision() {
		return collision;
	}
	void reducehealth(int hea) {
		health -= hea;
	}
	void animatezombie2(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		/*static Clock clock; */

	}
	void animatezombie(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		/*static Clock clock; */
		elapsedTime = clock.getElapsedTime().asSeconds();
		interval = 1.0f / 8;

		if (elapsedTime >= interval) {
			clock.restart();
			static int textureCount = 0;
			textureCount = (textureCount + 1) % size;
			/*clock.restart();*/


			sprite.setTexture(textures[currentFrame]);
			sprite.setTextureRect(textureRects[currentFrame]);
			currentFrame = (currentFrame + 1) % size;


			window.draw(sprite);

			/*window.display();*/
		}
	}

	bool checkend() {
		if (level == 1) {
			int endx[] = { 150,150,150,150,150,150,150,150 };
			int endy[] = { 113,171,238,225,303,302,256,409,513 };
			for (int j = 0; j < 8; j++) {
				if (sprite.getPosition().x <= endx[j] && sprite.getPosition().y >= endy[j]) {
					return true;
				}
			}
			return false;
		}
	}


	//void movefootballzombie(float time, RenderWindow& window, int i) {
	// float positionx[] = { 1078, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
	// float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };
	// //x = x - 0.1;
	// //y = 0;
	// float distx = speed * time * x;
	// float disty = speed * time * y;

	// sprite.setPosition(positionx[i] + distx, positiony[i] + disty);
	// x = x - 0.1;
	// y = 0;
	// window.draw(sprite);
	//}

	void movezombie(float time, float offsetX, float offsetY, RenderWindow& window, int i,int level) {
		float distx = speed * time * offsetX;
		float disty = speed * time * offsetY;
		cout << "giki";
		float positionx[] = { 1378, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
		float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };
		if (level == 1) {
			if (sprite.getPosition().y >= 7 && sprite.getPosition().y <= 12) {
				moveUp = false;
			}
			else if (sprite.getPosition().y >= 376 && sprite.getPosition().y <= 381) {
				moveUp = true;
			}

			sprite.setPosition(positionx[i] + distx, positiony[i] + disty);
			window.draw(sprite);
		}
		if (level == 2) {
			if (sprite.getPosition().y >= 7 && sprite.getPosition().y <= 12) {
				moveUp = false;
			}
			else if (sprite.getPosition().y >= 450 && sprite.getPosition().y <= 455) {
				moveUp = true;
			}

			sprite.setPosition(positionx[i] + distx, positiony[i] + disty);
			window.draw(sprite);
		}
	}


	bool getmoveup() {
		return moveUp;
	}
	void setalive(bool isActive) {
		alive = isActive;
	}
	bool getalive() {
		return alive;
	}
	float getx() {
		return sprite.getPosition().x;
	}
	float gety() {
		return sprite.getPosition().y;
	}
	void setposition(float x, float y) {
		sprite.setPosition(x, y);
	}
	int gethealth() {
		return health;
	}
	void draw(RenderWindow& window, int i, float x, float y) {

		float positionx[] = { 1078,1059,1040,1089,1110,1078,1059,1040,1089,1110 };
		float positiony[] = { 188,247,162,207,441,348,247,162,207,441 };

		/*sprite.setPosition(positionx[i], positiony[i]);*/
		window.draw(sprite);

		/*window.display();*/

	}
};

class FlyingZombie :public Zombie {

public:
	FlyingZombie() {
		health = 3;
		speed = 5;
		texture.loadFromFile("PVZ/Zombies/DS DSi - Plants vs Zombies - Balloon Zombie.png");
		sprite = Sprite(texture);
		sprite.setTextureRect({ 1,7,34,51 });
		sprite.scale(3, 3);
	}

	void animate(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		elapsedTime = clock.getElapsedTime().asSeconds();
		interval = 1.0f / 20;
		if (elapsedTime >= interval) {
			clock.restart();
			static int textureCount = 0;
			textureCount = (textureCount + 1) % size;

			sprite.setTexture(textures[currentFrame]);
			sprite.setTextureRect(textureRects[currentFrame]);
			currentFrame = (currentFrame + 1) % size;

			window.draw(sprite);
		}
	}
	void moveflyingzombie(float time, float offsetX, float offsetY, RenderWindow& window, int i) {
		float distx = speed * time * offsetX;
		float disty = speed * time * offsetY;

		/*float positionx[] = { 1078, 1059};*/
		/*float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };*/

		sprite.setPosition(1120 + distx, 9);
		window.draw(sprite);
	}
	bool checkend() {
		int endx[] = { 150,150,150,150,150,150,150,150 };
		int endy[] = { 113,171,238,225,303,302,256,409,513 };
		for (int j = 0; j < 8; j++) {
			if (sprite.getPosition().x <= endx[j] && sprite.getPosition().y >= endy[j]) {
				return true;
			}
		}
		return false;
	}
	float getx() {
		return sprite.getPosition().x;
	}
	float gety() {
		return sprite.getPosition().y;
	}
	int gethealth() {
		return health;
	}
	void reducehealth(int hea) {
		health -= hea;
	}
};

class DancingZombie :public Zombie {
	bool moveUp;

public:
	DancingZombie(int h = 100, float X = 800, float Y = 0) {
		health = h;
		speed = 5;
		texture.loadFromFile("PVZ/Zombies/DS DSi - Plants vs Zombies - Dancing Zombie.png");
		sprite = Sprite(texture);
		sprite.setTextureRect({ 2,5,36,54 });
		sprite.scale(2, 2);
	}
	void setcollision(bool i) {
		collision = i;
	}
	bool getcollision() {
		return collision;
	}
	void animatezombie(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		elapsedTime = clock.getElapsedTime().asSeconds();
		interval = 1.0f / 4;
		if (elapsedTime >= interval) {
			clock.restart();
			static int textureCount = 0;
			textureCount = (textureCount + 1) % size;
			/*clock.restart();*/
			sprite.setTexture(textures[currentFrame]);
			sprite.setTextureRect(textureRects[currentFrame]);
			currentFrame = (currentFrame + 1) % size;
			window.draw(sprite);
			/*window.display();*/
		}
	}
	void movezombie(float time, float offsetX, float offsetY, RenderWindow& window, int i,int level) {
		float distx = speed * time * offsetX;
		float disty = speed * time * offsetY;

		float positionx[] = { 1078, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
		float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };
		if (sprite.getPosition().y >= 7 && sprite.getPosition().y <= 12) {
			moveUp = false;
		}
		else if (sprite.getPosition().y >= 376 && sprite.getPosition().y <= 381) {
			moveUp = true;
		}

		sprite.setPosition(positionx[i] + distx, positiony[i] + disty);
		window.draw(sprite);
	}
	bool getmoveup() {
		return moveUp;
	}
	bool checkend() {
		int endx[] = { 150,150,150,150,150,150,150,150 };
		int endy[] = { 113,171,238,225,303,302,256,409,513 };
		for (int j = 0; j < 8; j++) {
			if (sprite.getPosition().x <= endx[j] && sprite.getPosition().y >= endy[j]) {
				return true;
			}
		}
		return false;
	}
	void setalive(bool isActive) {
		alive = isActive;
	}
	bool getalive() {
		return alive;
	}
	float getx() {
		return sprite.getPosition().x;
	}
	float gety() {
		return sprite.getPosition().y;
	}
	void setposition(float x, float y) {
		sprite.setPosition(x, y);
	}
	int gethealth() {
		return health;
	}
	void draw(RenderWindow& window, int i, float x, float y) {

		float positionx[] = { 1078,1059,1040,1089,1110,1078,1059,1040,1089,1110 };
		float positiony[] = { 188,247,162,207,441,348,247,162,207,441 };

		/*sprite.setPosition(positionx[i], positiony[i]);*/
		window.draw(sprite);

		/*window.display();*/

	}
	void reducehealth(int hea) {
		health -= hea;
	}
	void animatezombie2(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		/*static Clock clock; */

	}
};

class DolphinRiderZombie :public Zombie {
	bool firstspawn = false;
	int currentFrame2 = 0;
public:
	DolphinRiderZombie(int h = 5, float X = 0.0, float Y = 0.0) {
		health = h;
		speed = 6;
		texture.loadFromFile("PVZ/Zombies/DolphinRider.png");
		sprite = Sprite(texture);
		sprite.setTextureRect({ 38,357,40,42 });
		sprite.scale(3, 3);
	}
	void animate1(Texture* textures, IntRect* textureRects, const int size, Texture* textures2, IntRect* textureRects2, const int size2, RenderWindow& window) {
		if (sprite.getPosition().x >= 940 && sprite.getPosition().x <= 1078) {
			elapsedTime = clock.getElapsedTime().asSeconds();
			interval = 1.0f / 7;
			if (elapsedTime >= interval) {
				clock.restart();
				static int textureCount = 0;
				textureCount = (textureCount + 1) % size;

				sprite.setTexture(textures[currentFrame]);
				sprite.setTextureRect(textureRects[currentFrame]);
				currentFrame = (currentFrame + 1) % size;

				window.draw(sprite);
			}
		}
		else {
			elapsedTime = clock.getElapsedTime().asSeconds();
			interval = 1.0f / 4;
			if (elapsedTime >= interval) {
				clock.restart();
				static int textureCount = 0;
				textureCount = (textureCount + 1) % size2;

				sprite.setTexture(textures2[currentFrame2]);
				sprite.setTextureRect(textureRects2[currentFrame2]);
				currentFrame2 = (currentFrame2 + 1) % size2;

				window.draw(sprite);
			}
		}
	}
	void animate2(Texture* textures, IntRect* textureRects, const int size, RenderWindow& window) {
		elapsedTime = clock.getElapsedTime().asSeconds();
		interval = 1.0f / 4;
		if (elapsedTime >= interval) {
			clock.restart();
			static int textureCount = 0;
			textureCount = (textureCount + 1) % size;

			sprite.setTexture(textures[currentFrame]);
			sprite.setTextureRect(textureRects[currentFrame]);
			currentFrame = (currentFrame + 1) % size;

			window.draw(sprite);
		}
	}
	void movedolphinzombie(float time, float offsetX, float offsetY, RenderWindow& window, int i) {
		float distx = speed * time * offsetX;
		float disty = speed * time * offsetY;

		float positionx[] = { 1078, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
		float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };

		sprite.setPosition(positionx[i] + distx, positiony[i] + disty);
		window.draw(sprite);
	}


	void setfirstspawn(bool isspawn) {
		firstspawn = isspawn;
	}

	bool getfirstspawn() const {
		return firstspawn;
	}
	bool checkend() {
		int endx[] = { 150,150,150,150,150,150,150,150 };
		int endy[] = { 113,171,238,225,303,302,256,409,513 };
		for (int j = 0; j < 8; j++) {
			if (sprite.getPosition().x <= endx[j] && sprite.getPosition().y >= endy[j]) {
				return true;
			}
		}
		return false;
	}
	float getx() {
		return sprite.getPosition().x;
	}
	float gety() {
		return sprite.getPosition().y;
	}
	int gethealth() {
		return health;
	}
	void reducehealth(int hea) {
		health -= hea;
	}
};
/// <summary>
/// fffffffffffffffffffffffffffffffff
/// 
/// 
/// 
/// 
/// 
/// 
/// </summary>

class shoot {
private:
	float x;
	float y;
	Clock peaclock;
public:
	Sprite pea;
	shoot() {
	}
	void settexture(Texture& texture) {
		//pea = texture;
		pea.setTexture(texture);
		pea.setTextureRect(sf::IntRect(77, 33, 12, 29));
		pea.setScale(1.7f, 1.7f);
	}
	void setposition(float x, float y) {
		this->x = x;
		this->y = y;
		//	pea.setPosition(x, y);
			//pea.setPosition(x, y);
	}
	void drawpeas(RenderWindow& window) {
		pea.setPosition(x, y);
		window.draw(pea);
		//this->movepea(window);
	}
	void movepea(RenderWindow& window) {
		if (peaclock.getElapsedTime().asMilliseconds() < 1 / 144444)
			return;
		x += 10;
		this->peaclock.restart();
		this->con(window);
	}
	void con(RenderWindow& window) {
		pea.setPosition(x, y);
		window.draw(pea);
	}
	float getx() const { return pea.getPosition().x; }
	float gety() const { return pea.getPosition().y; }
};
class plant {
private:

public:
	virtual void setposition(float x,float y) {

	}
	virtual void setposition3(float x, float y) {

	}
	virtual void set(){}
	virtual void settexture(Texture& texture) {
		//cout << "l";
	}
	virtual void settexture1(Texture& texture) {
		cout << "l";
	}
	virtual void draw(sf::RenderWindow& window) {

	}
	virtual void animate(Texture* textures, IntRect* textureRects, const int numTextures, RenderWindow& window) {

	}
	virtual void animate2(RenderWindow& window) {
		cout << "l";
	}
	virtual int getHealth() const { 
		return 0;
	}
	virtual float getX() const {
		return 0;
	}
	virtual float getY() const {
		return 0;
	}
	virtual float getx1() const{
		return 0;
	}
	virtual float gety1() const {
		return 0;
	}
	virtual bool checkforcollision(float x,float y) {
		return 0;

	}
	virtual bool checkforcollision1(float x, float y) {
		return 0;

	}
	virtual bool checkforcollisionforshoot(float x, float y) {
		
		return 0;

	}
	virtual void reducehealth(int hea) {
	}
	virtual int getrow()  {
		return 0;
	}
	virtual int getcol()  {
		return 0;
	}
	virtual void setrow(int row) {
		//return 0;
	}
	virtual void setcol(int col) {
		//return 0;
	}
	virtual bool checkforclickmouse(int x, int y) {
		return 0;
	}
	bool checkforcollision3(float x, float y) {
		return 0;
	}
};

class Peashooter : public plant {
private:
	int health = 100;
	float shootrate = 1.5;
	sf::Clock clock;
	Clock clock1;
	float x;
	float y;
	int row;
	int col;
	Sprite peashotersprite;
	Texture* texture = new Texture[7];
	IntRect textureRects[7] = {
		IntRect({0,0,26,32}),
		IntRect({27,0,27,33}),
		IntRect({53,1,28,32}),
		IntRect({81,0,26,34}),
		IntRect({1,31,26,31}),
		IntRect({27,33,24,30}),
		IntRect({50,32,27,30})
	};
	int textureCount;
	shoot peaShoot;  // Compose shoot functionality

public:
	Peashooter(float X = 0, float Y = 0) : x(X), y(Y), textureCount(0) {
		// Initialize peashooter sprite and textures
		peashotersprite.setScale(2.0f, 2.0f);
		settexture(texture[0]);  // Set initial texture
	}
	void setposition3(float x, float y) {
		peaShoot.setposition(-1,-50);
	}
	void setposition(float x, float y) {
		this->x = x;
		this->y = y;
		peashotersprite.setPosition(x, y);
		peaShoot.setposition(x + 25, y-10);  // Offset for shoot position
	}

	int getHealth() const { return health; }

	float getX() const {
		return peashotersprite.getPosition().x;
	}

	float getY() const {
		return peashotersprite.getPosition().y;
	}

	void settexture(Texture& texture) {
		for (int i = 0; i < 7; i++) {
			this->texture[i] = texture;
		}
		peashotersprite.setTexture(this->texture[0]);
		peashotersprite.setTextureRect(sf::IntRect(0, 0, 26, 32));
		peaShoot.settexture(this->texture[0]);  // Set shoot texture
	}

	void draw(sf::RenderWindow& window) override {
		peashotersprite.setPosition(x, y);
		animate(texture, textureRects, 7, window);  // Animate peashooter
		window.draw(peashotersprite);

		if (clock.getElapsedTime().asMilliseconds() >= 1.0f / 18.0f) {
			peaShoot.movepea(window);  // Move the pea
			clock.restart();
		}

		if (peaShoot.getx() > 1050) {
			peaShoot.setposition(x + 25, y-10);  // Reset shoot position
		}
	}

	void animate(Texture* textures, IntRect* textureRects, const int numTextures, RenderWindow& window) {
		if (clock1.getElapsedTime().asSeconds() >= 0.5) {
			textureCount = (textureCount + 1) % numTextures;
			peashotersprite.setTexture(textures[textureCount]);
			peashotersprite.setTextureRect(textureRects[textureCount]);
			clock1.restart();
		}
	}

	void reducehealth(int hea) {
		health -= hea;
	}
	bool checkforcollision(float x, float y) {
		sf::FloatRect spriteBounds = peashotersprite.getGlobalBounds();
		if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {
			
			return 1;
		}
		return 0;
	}
	bool checkforcollisionforshoot(float x, float y) {
		sf::FloatRect spriteBounds = peaShoot.pea.getGlobalBounds();
		//cout<<peaShoot.getx();
		if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {

			return 1;
		}
		return 0;
	}
	int getrow() {
		return row;
	}
	 int getcol() {
		return col;
	}
	 void setrow(int row) {
		 this->row = row;
	}
	 void setcol(int col) {
		 this->col = col;
	}
	
};
class madeforsunforsunflower {
public:
	float x;
	float y;
	Clock clock;
	int quantity;
	//Sprite sun;
	//Texture suntexture;
	bool isActive;
	Sprite sunsprites;
	Texture suntexture;

	//

	madeforsunforsunflower() {
		quantity = 0;
		suntexture.loadFromFile("Images/sun.png");
		sunsprites.setTexture(suntexture);
		isActive = false;
		sunsprites.setTextureRect(sf::IntRect(0, 0, 120, 120));
	}
	void draw(RenderWindow& window) {
		if (isActive) {
			sunsprites.setPosition(x, y);
			window.draw(sunsprites);
		}
		/*if (clock.getElapsedTime().asSeconds() >= 5) {
			x = rand() % 800;
			y = -10;
			clock.restart();
		}*/
	}
	void setActive(bool active) {
		isActive = active;
	}
	bool getActive() {
		return isActive;
	}
	void setPosition(float posX, float posY) {
		x = posX;
		y = posY;
	}
	void addSun(int amount) {
		quantity += amount;
	}
	int getQuantity() const {
		return quantity;
	}
	float getx() const {
		cout << "dkkdkd";
		return sunsprites.getPosition().x;
		
	}
	float gety() const {
		return sunsprites.getPosition().y;
	}


};
	class Sunflower:public plant {
	private:
		int row;
		int col;
		Clock clock1;
		Clock clock;
		Clock c;
		float x;
		float y;
		Sprite sunflower;
		Texture* sunflowertexture=new Texture[7];
		IntRect textureRects[7] = {
	IntRect({1,1,31,37}),
	IntRect({31,1,30,38}),
	IntRect({60,1,30,38}),
	IntRect({89,1,30,38}),
	IntRect({120,1,28,38}),
	IntRect({177,0,29,39}),
	IntRect({0,38,33,28})
		};
		int textureCount1;
		int health = 150;
		madeforsunforsunflower s;
		bool checker;
	public:
		Sunflower() {
			this->x = 0;
			this->y = 0;
			textureCount1=0;
		}
			void setposition(float x, float y) {
			this->x = x;
			this->y = y;
			s.setPosition(x-10, y-25);
			this->sunflower.setPosition(x, y);
		}
		void settexture(Texture& texture) {
			for (int i = 0; i < 7; i++) {
				this->sunflowertexture[i] = texture;
			}
			sunflower.setTexture(this->sunflowertexture[0]);
			sunflower.setTextureRect(sf::IntRect(0, 0, 26, 32));
			sunflower.setScale(2.0f, 2.0f);
			

		}
		void draw(RenderWindow& window) {
			this->sunflower.setPosition(x, y);
			this->animate(this->sunflowertexture, textureRects, 7, window);
			s.setPosition(x - 10, y - 25);
			window.draw(sunflower);
			for (int i = 0; i < 7; i++) {
				sunflowertexture[i].setRepeated(true);
				sunflowertexture[i].setSmooth(true);
			}
			if (textureCount1 == 6) {
				checker = true;
				s.setActive(1);
			}
			//if (checker) {
		s.draw(window);
			//}
			if (clock.getElapsedTime().asSeconds() >=5 ) {
				s.setActive(0);
			clock.restart();
		}

		}
	    void animate(Texture* textures, IntRect* textureRects, const int numTextures, RenderWindow& window) {
			if (clock1.getElapsedTime().asSeconds() >= 0.5) {
				textureCount1 = (textureCount1 + 1) % numTextures;
				//if (c.getElapsedTime().asSeconds() <= 50) {
				//	if (textureCount1 == 6) {
				//		textureCount1 == 0;
				//	}
				//}
				//else {
				//	c.restart();
				//}
				///*if (textureCount1 == 6) {

				//}*/
				if (c.getElapsedTime().asSeconds() >= 8) {
					// Reset the clock to start counting again
					c.restart();
				}

				// If textureCount1 is 6 and less than 20 seconds have passed, skip to the next texture
				if (textureCount1 == 6 && c.getElapsedTime().asSeconds() < 5) {
					textureCount1 = (textureCount1 + 1) % numTextures;
				}
				sunflower.setTexture(textures[textureCount1]);
				sunflower.setTextureRect((textureRects[textureCount1]));

				clock1.restart();
			}

		}
		bool checkforcollision(float x, float y) {
			sf::FloatRect spriteBounds = sunflower.getGlobalBounds();
			if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {
				return 1;
			}
			return 0;
		}
		bool checkforclickmouse(int x1, int y1) {
			if (s.getActive()) {
				cout << "Checking mouse click position (" << x1 << ", " << y1 << ")" << endl;

				// Assuming sunsprites is correctly initialized and represents the sprite to check
				sf::FloatRect spriteBounds = s.sunsprites.getGlobalBounds();

				// Output sprite bounds for debugging
				/*spriteBounds.left = s.getx();
				spriteBounds.top = s.gety();*/
				/*<< ", width=" << spriteBounds.width
				<< ", height=" << spriteBounds.height << endl;*/

				// Check if the mouse click position is within the sprite's bounds
				if (spriteBounds.contains(static_cast<float>(x1), static_cast<float>(y1))) {
					cout << "Mouse click inside sprite bounds." << endl;
					s.setActive(0);  // Assuming setActive is a valid method
					return true;
				}
			}
			cout << "Mouse click outside sprite bounds." << endl;
			return false;
		}

				
				
		
		
		
		float getX() const {
			return sunflower.getPosition().x;
		}
		float getY() const {
			return sunflower.getPosition().y;
		}
		int getHealth() const { return health; }
		void reducehealth(int hea) {
			this->health -= hea;
		}
		int getrow() {
			return row;
		}
		int getcol() {
			return col;
		}
		void setrow(int row) {
			this->row = row;
		}
		void setcol(int col) {
			this->col = col;
		}

};
	class cherrybomb:public plant {
	private:
		Clock clock1;
		int row;
		int col;
		float x;
		float y;
		Sprite cherry;
		Texture* cherrytexture = new Texture[7];
		IntRect textureRects[7] = {
	IntRect({1,9,32,33}),
	IntRect({33,9,37,32}),
	IntRect({70,4,48,35}),
	IntRect({115,4,47,37}),
	IntRect({161,0,51,41}),
	IntRect({212,0,53,41}),
	IntRect({212,0,53,41})
		};
		IntRect textureRects2[7] = {
	IntRect({1,49,67,56}),
	IntRect({68,41,82,64}),
	IntRect({149,38,97,67}),
	IntRect({246,38,93,67}),
	IntRect({339,40,93,65}),
	IntRect({432,42,93,63}),
	IntRect({620,44,72,56})
		};
		int textureCount1 ;
		int textureCount2 ;
		bool check = false;
		int health = 200;
	public:
		cherrybomb() {
			this->x = 0;
			this->y = 0;
			textureCount1 = 0;
			textureCount2 = 0;
		}
		void setposition(float x, float y) {
			cout << "jfshjsfsi654";
			this->x = x;
			this->y = y;
			this->cherry.setPosition(x, y);
		}
		void settexture(Texture& texture) {
			for (int i = 0; i < 7; i++) {
				this->cherrytexture[i] = texture;
			}
			cherry.setTexture(this->cherrytexture[0]);
			cherry.setTextureRect(sf::IntRect(0, 0, 26, 32));
			cherry.setScale(1.7f, 1.7f);

		}
		void draw(RenderWindow& window) {
			this->cherry.setPosition(x, y);
			if (this->textureCount1 != 6) {
				this->animate(this->cherrytexture, 7, window);

			}
			else {
				check = true;
			}
			window.draw(cherry);
			for (int i = 0; i < 7; i++) {
				cherrytexture[i].setRepeated(true);
				cherrytexture[i].setSmooth(true);
			}
		}
		
		void animate(Texture* textures, const int numTextures, RenderWindow& window) {
			if (clock1.getElapsedTime().asSeconds() >= 1/7) { 
				textureCount1 = (textureCount1 + 1) % numTextures;

				cherry.setTexture(textures[textureCount1]);
				cherry.setTextureRect((textureRects[textureCount1]));

				clock1.restart();
			}


		}
		void animate2(RenderWindow& window) {
			cout << "animate";
				while (textureCount2 != 6) {
					if (clock1.getElapsedTime().asSeconds() >= 0.01) {
						textureCount2 = (textureCount2 + 1) % 7;

						cherry.setTexture(this->cherrytexture[textureCount1]);
						cherry.setTextureRect((textureRects2[textureCount2]));

						clock1.restart();
						window.draw(cherry);
					}
					
			    //draw(window);
				//cout << "zohaib";
				}
			
			
		}
		float getX() const {
			return cherry.getPosition().x;
		}
		float getY() const {
			return cherry.getPosition().y;
		}
		int getHealth() const { return health; }
		void reducehealth(int hea) {
			this->health -= hea;
		}
		bool checkforcollision1(float x, float y) {
			sf::FloatRect spriteBounds = cherry.getGlobalBounds();
			if (spriteBounds.contains(static_cast<float>(x+40), static_cast<float>(y+40))) {
				return 1;
			}
			return 0;
		}
		int getrow() {
			return row;
		}
		int getcol() {
			return col;
		}
		void setrow(int row) {
			this->row = row;
		}
		void setcol(int col) {
			this->col = col;
		}
	};
	class walnut:public plant {

	private:
		int row;
		int col;
		Clock clock1;
		float x;
		float y;
		Sprite walnutsprite;
		Texture* walnutstexture = new Texture[7];
		IntRect textureRects[8] = {
	IntRect({0,93,28,32}),
	IntRect({28,93,29,32}),
	IntRect({56,93,31,35}),
	IntRect({86,94,31,31}),
	IntRect({116,93,28,35}),
	IntRect({143,93,30,35}),
	IntRect({172,93,32,35}),
	IntRect({204,93,32,35})
		};
		int health=100;
		int textureCount1;
	public:

		walnut() {
			this->x = 0;
			this->y = 0;
			textureCount1 = 0;
		}
		void setposition(float x, float y) {
			this->x = x;
			this->y = y;
			this->walnutsprite.setPosition(x, y);
		}
		void settexture(Texture& texture) {
			for (int i = 0; i < 7; i++) {
				this->walnutstexture[i] = texture;
			}
			walnutsprite.setTexture(this->walnutstexture[0]);
			walnutsprite.setTextureRect(sf::IntRect(0, 0, 26, 32));
			walnutsprite.setScale(2.0f, 2.0f);

		}
		void draw(RenderWindow& window) {
			this->walnutsprite.setPosition(x, y);
			cout << "ho rha ha";
				this->animate(this->walnutstexture, 7, window);

			
			window.draw(walnutsprite);
			for (int i = 0; i < 7; i++) {
				walnutstexture[i].setRepeated(true);
				walnutstexture[i].setSmooth(true);
			}
			x += 5;

		}
		void animate(Texture* textures, const int numTextures, RenderWindow& window) {
			if (clock1.getElapsedTime().asSeconds() >= 1/7) {
				textureCount1 = (textureCount1 + 1) % numTextures;

				walnutsprite.setTexture(textures[textureCount1]);
				walnutsprite.setTextureRect((textureRects[textureCount1]));

				clock1.restart();
			}

		}
		float getX() const {
			return walnutsprite.getPosition().x;
		}
		float getY() const {
			return walnutsprite.getPosition().y;
		}
		int getHealth() const { return health; }
		void reducehealth(int hea) {
			this->health -= hea;
		}
		bool checkforcollision3(float x, float y) {
			sf::FloatRect spriteBounds = walnutsprite.getGlobalBounds();
			if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {
				return 1;
			}
			return 0;
		}
		int getrow() {
			return row;
		}
		int getcol() {
			return col;
		}
		void setrow(int row) {
			this->row = row;
		}
		void setcol(int col) {
			this->col = col;
		}



	};
	class snowpeas {
	private:
		float x;
		float y;
		Clock peaclock;
	public:
		Sprite pea;
		snowpeas() {
		}
		void settexture(Texture& texture) {
			pea.setTexture(texture);
			pea.setTextureRect(sf::IntRect(92, 49, 21, 15));
			pea.setScale(1.7f, 1.7f);
		}
		void setposition1(float x, float y) {
			this->x = x;
			this->y = y;
		}
		void drawpeas(RenderWindow& window) {
			pea.setPosition(x, y);
			window.draw(pea);
		}
		void movepea(RenderWindow& window) {
			if (peaclock.getElapsedTime().asMilliseconds() < 1 / 144444)
				return;
			x += 10;
			this->peaclock.restart();
			this->con(window);
		}
		void con(RenderWindow& window) {
			pea.setPosition(x, y);
			window.draw(pea);
		}
		float getx() const { return pea.getPosition().x; }
		float gety() const { return pea.getPosition().y; }

	};
	class snowpeashoter:public plant  {
		int row;
		int col;
		 int health = 100;
		sf::Clock clock;
		Clock clock1;
		float x;
		float y;
		Sprite  snowshotersprite;
		Texture* texture1 = new Texture[11];
		IntRect textureRects1[11] = {
		IntRect({0,0,31,32}),
		IntRect({31,0,30,32}),
		IntRect({60,0,31,32}),
		IntRect({90,0,30,32}),
		IntRect({121,0,30,32}),
		IntRect({151,0,30,32}),
		IntRect({181,0,30,32}),
		IntRect({211,0,30,32}),
		IntRect({0,31,31,32}),
		IntRect({30,31,28,32}),
		IntRect({57,31,34,32})
		};
		snowpeas p;
		int textureCount;
		bool check = false;
	public:
		snowpeashoter() {
			x = 0;
			y = 0;
			textureCount = 0;
		}
		void setposition(float x, float y) {
			this->x = x;
			this->y = y;
			this->snowshotersprite.setPosition(x, y);

			p.setposition1(x + 25, y);

		}
		void setposition3(float x, float y) {
			
			p.setposition1(-10, -100);
		}
		int getHealth() const { return health; }
		float getX() const {
			return snowshotersprite.getPosition().x;
		}
		float getY() const {
			return snowshotersprite.getPosition().y;
		}
		
		void settexture(Texture& texture) {
			for (int i = 0; i < 11; i++) {
				this->texture1[i] = texture;
			}
			snowshotersprite.setTexture(texture);
			snowshotersprite.setTextureRect(sf::IntRect(0, 0, 31, 32));

			snowshotersprite.setScale(2.0f, 2.0f);

			p.settexture(this->texture1[0]);
		}
		void draw(sf::RenderWindow& window) {
			snowshotersprite.setPosition(x, y);
			//window.draw(peashotersprite);

			this->animate(this->texture1, 11, window);

			window.draw(snowshotersprite);
			for (int i = 0; i < 11; i++) {
				texture1[i].setRepeated(true);
				texture1[i].setSmooth(true);
			}
			if (check) {
				if (clock.getElapsedTime().asMilliseconds() >= 1 / 2000) {
					p.movepea(window);
					p.drawpeas(window); // Draw the pea

					clock.restart();
				}
			}
			if (textureCount==10) {
				this->p.setposition1(x + 25, y);
				//movepea(window);
				check = true;
			}
		}
		void animate(Texture* textures, const int numTextures, RenderWindow& window) {
			if (clock1.getElapsedTime().asSeconds() >= 0.5) { 

				textureCount = (textureCount + 1) % numTextures;

				snowshotersprite.setTexture(textures[textureCount]);
				snowshotersprite.setTextureRect((textureRects1[textureCount]));

				clock1.restart();
			}
		}
		void reducehealth(int hea) {
			this->health -= hea;
		}
		bool checkforcollision(float x, float y) {
			sf::FloatRect spriteBounds = snowshotersprite.getGlobalBounds();
			if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {
				return 1;
			}
			return 0;
		}
		bool checkforcollisionforshoot(float x, float y) {
			sf::FloatRect spriteBounds = p.pea.getGlobalBounds();
			if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {
				return 1;
			}
			return 0;

		}
		int getrow() {
			return row;
		}
		int getcol() {
			return col;
		}
		void setrow(int row) {
			this->row = row;
		}
		void setcol(int col) {
			this->col = col;
		}
	};
	class plantfactory {
	public:
		virtual ~plantfactory() {}  // Virtual destructor
		virtual plant* createPlant() = 0;  // Pure virtual function
	};
	class PeashooterFactory : public plantfactory {
	public:
		plant* createPlant()  {
			return new Peashooter();
		}
	};
	class SunflowerFactory : public plantfactory {
	public:
		plant* createPlant() override {
			return new Sunflower();
		}
	};
	class CherryBombFactory : public plantfactory {
	public:
		plant* createPlant() override {
			return new cherrybomb();
		}
	};
	class WalnutFactory : public plantfactory {
	public:
		plant* createPlant() override {
			return new walnut();
		}
	};
	class SnowPeashooterFactory : public plantfactory {
	public:
		plant* createPlant() override {
			return new snowpeashoter();
		}
	};
	class Sun {
	public:
		sf::Text amountOfSun; 
		sf::Font font; 
		float x;
		float y;
		Clock clock;
		int quantity;          
		Sprite sunsprite;
		Texture suntexture;
		bool isActive;
		void updateDisplay() {
			amountOfSun.setString(std::to_string(quantity));
		}
		Texture grid;
		Sprite gridsprite;
		Texture sungrid;
		Sprite sungridsprite;
	//public:
		Sun() : quantity(100) {  
			if (!font.loadFromFile("Images/CombackHomeRegular-jEMd9.ttf")) {
				exit(1);
			}
			isActive = true;
			srand(time(0));
			x = rand() % 800;
			y = -100;
			suntexture.loadFromFile("Images/sun.png");
			amountOfSun.setFont(font);
			amountOfSun.setPosition(0,0);
			amountOfSun.setCharacterSize(50);
			sunsprite.setTexture(suntexture);
			updateDisplay();
		}
		void draw(RenderWindow& window) {
			if (isActive) {
				sunsprite.setPosition(x,y);
				window.draw(sunsprite);
				if (!(y > 400)) {
					y += 5;
				}
			}
			if (clock.getElapsedTime().asSeconds() >=10) {
				x = rand() % 800;
				y = -10;
				clock.restart();
				isActive = 1;
			}
			window.draw(amountOfSun);
		}
		void setActive(bool active) {
			isActive = active;

			clock.restart();
		}
		void setPosition(float posX, float posY) {
			x = posX;
			y = posY;
		}
		void display(RenderWindow* window) {
			window->draw(amountOfSun);
		}
		bool collected() const {
			return !isActive;
		}
		void addSun(int amount) {
			quantity += amount;
			updateDisplay(); 
		}
		int getQuantity() const {
			return quantity;
		}
		void reduceSun(int amount) {
			quantity -= amount;
			if (quantity < 0) {
				quantity = 0; 
			}
			updateDisplay(); 
		}
		Sprite checkerg() {
			return sunsprite;
		}
		float getX() {
			return sunsprite.getPosition().x;
		}
		float gety() {
			return sunsprite.getPosition().y;
		}
	};

	#define maxmainmenu  4
	class mainmenu {
	private:
		int mainmenuselected;
		sf::Font font;
		sf::Text main[maxmainmenu];
		sf::Texture texture;
		sf::Sprite background;
		sf::Music bgMusic;
		
	public:
		mainmenu(float width, float height) {
			if (!font.loadFromFile("Images/CombackHomeRegular-jEMd9.ttf")) {
				std::cerr << "Error loading font file!" << std::endl;
			}

			if (!texture.loadFromFile("Images/m.jpg")) {
				std::cerr << "Error loading texture file!" << std::endl;
			}
			background.setTexture(texture);
			bgMusic.openFromFile("Images/VideoGameMenuSoundsMenu-Selection-Change-O-www.fesliyanstudios.com (1).mp3");
			
			main[0].setFont(font);
			main[0].setFillColor(sf::Color::Red);
			main[0].setString("Play");
			main[0].setCharacterSize(50);
			main[0].setPosition(500, 90);

			main[1].setFont(font);
			main[1].setFillColor(sf::Color::Red);
			main[1].setString("Option");
			main[1].setCharacterSize(50);
			main[1].setPosition(500, 190);

			main[2].setFont(font);
			main[2].setFillColor(sf::Color::Red);
			main[2].setString("High scores");
			main[2].setCharacterSize(50);
			main[2].setPosition(500, 290);

			main[3].setFont(font);
			main[3].setFillColor(sf::Color::Red);
			main[3].setString("Exit");
			main[3].setCharacterSize(50);
			main[3].setPosition(500, 390);

			mainmenuselected = 0;
			main[mainmenuselected].setFillColor(sf::Color::Blue);
		}

		void draw(sf::RenderWindow& window) {
			window.clear();
			window.draw(background);
			for (int i = 0; i < maxmainmenu; i++) {
				window.draw(main[i]);
			}
			window.display();
		}

		void moveup() {
			if (mainmenuselected > 0) {
				bgMusic.play();
				bgMusic.setVolume(80);
				main[mainmenuselected].setFillColor(sf::Color::Red);
				mainmenuselected--;
				main[mainmenuselected].setFillColor(sf::Color::Blue);
			}
		}

		void movedown() {
			if (mainmenuselected < maxmainmenu - 1) {

				bgMusic.play();
				bgMusic.setVolume(80);
				main[mainmenuselected].setFillColor(sf::Color::Red);
				mainmenuselected++;
				main[mainmenuselected].setFillColor(sf::Color::Blue);
			}
		}

		int getSelectedIndex() const {
			return mainmenuselected;
		}
	};

	// scoring 
	
	struct HighScoreEntry {
	std::string playerName;
	int score;
};
#define  MAX_SCORES 5
class ScoreManager {
public:
	ScoreManager() {
		// Load top scores from file when creating ScoreManager instance
		loadTopScores();
	}

	// Method to display the top 5 scores
	void displayTopScores() const {
		std::cout << "Top 5 Scores:\n";
		for (int i = 0; i < numScores && i < MAX_SCORES; ++i) {
			std::cout << i + 1 << ". " << topScores[i].playerName << ": " << topScores[i].score << std::endl;
		}
	}

	// Method to update top scores with a new score
	void updateTopScores(const std::string& playerName, int newScore) {
		if (newScore > 0) {
			// Insert new score into topScores if it's among the top 5
			if (numScores < MAX_SCORES || newScore > topScores[MAX_SCORES - 1].score) {
				// Insert the new score into the array
				topScores[numScores] = { playerName, newScore };
				++numScores;
				sortScores();
				if (numScores > MAX_SCORES) {
					numScores = MAX_SCORES;
				}
				saveTopScores();
			}
		}
	}
	void saveGameplayScore(const std::string& playerName, int score) const {
		std::ofstream file("gameplayscore.txt");
		if (file.is_open()) {
			file << playerName << " " << score;
			file.close();
		}
		else {
			std::cerr << "Failed to open gameplay score file for writing." << std::endl;
		}
	}
	int getNumScores() const {
		return numScores;
	}

	// Method to get a reference to the top scores array (read-only)
	const HighScoreEntry* getTopScores() const {
		return topScores;
	}

private:
	HighScoreEntry topScores[MAX_SCORES];
	int numScores = 6;
	void loadTopScores() {
		std::ifstream file("topscores.txt");
		if (file.is_open()) {
			numScores = 0;
			while (numScores < MAX_SCORES && file >> topScores[numScores].playerName >> topScores[numScores].score) {
				++numScores;
			}
			sortScores();
			file.close();
		}
		else {
			std::cerr << "Failed to open topscores.txt for reading." << std::endl;
		}
	}
	void saveTopScores() const {
		std::ofstream file("topscores.txt");
		if (file.is_open()) {
			for (int i = 0; i < numScores; ++i) {
				file << topScores[i].playerName << " " << topScores[i].score << std::endl;
			}
			file.close();
		}
		else {
			std::cerr << "Failed to open topscores.txt for writing." << std::endl;
		}
	}
	void sortScores() {
		for (int i = 0; i < numScores - 1; ++i) {
			for (int j = 0; j < numScores - 1 - i; ++j) {
				if (topScores[j].score < topScores[j + 1].score) {
					HighScoreEntry temp = topScores[j];
					topScores[j] = topScores[j + 1];
					topScores[j + 1] = temp;
				}
			}
		}
	}
};
	struct Block {
		int x1, x2;
		int y1, y2;
	};
	class gridformap{
	private:
		int X_UPPER_LEFT;    // Starting x-coordinate
		int Y_UPPER_LEFT;     // Starting y-coordinate
		int BLOCK_WIDTH;      // Width of each block
		int BLOCK_HEIGHT;
	    int VERT_BLOCK_COUNT = 5; // Number of rows of blocks
	    int HORIZ_BLOCK_COUNT = 9;
		float x1[5];
		float y1[5];
		Texture cartexture;
		Block map[5][9];
		Sprite* carSprites[5];
		bool check[5];
	public:
		gridformap(int x,int y,int w,int height) {
			this->X_UPPER_LEFT = x;
			this->Y_UPPER_LEFT = y;
			this->BLOCK_HEIGHT = height;
			this->BLOCK_WIDTH = w;
			for (int y = 0; y < VERT_BLOCK_COUNT; y++) {
				for (int x = 0; x < HORIZ_BLOCK_COUNT; x++) {
					map[y][x].x1 = X_UPPER_LEFT + (x * BLOCK_WIDTH);  // Example: Assuming each block is 50 units wide
					map[y][x].x2 = X_UPPER_LEFT + ((x + 1) * BLOCK_WIDTH);
					map[y][x].y1 = Y_UPPER_LEFT + (y * BLOCK_HEIGHT);  // Example: Assuming each block is 50 units high
					map[y][x].y2 = Y_UPPER_LEFT + ((y + 1) * BLOCK_HEIGHT);
				}
			}
			cartexture.loadFromFile("images/car-removebg-preview (1).png");
			for (int i = 0; i < 5; i++) {
				carSprites[i] = new Sprite;
				carSprites[i]->setTexture(cartexture);
				x1[i] = 150;
				y1[i] = y + (i * 100);

				carSprites[i]->setPosition(x1[i], y1[i]);
				check[i] = false;
			}
		}
		void drawcar(RenderWindow& window) {
			for (int i = 0; i < 5; i++) {
				if (carSprites[i]) {
					carSprites[i]->setPosition(x1[i], y1[i]);
					window.draw(*carSprites[i]);
					if (check[i]) {
						move1(i);
					}
					if (x1[i] > 1050) {
						delete carSprites[i];
						carSprites[i] = nullptr;
					}
				}
			}
		}
		void move1(int index) {
			if (carSprites[index]) {
				x1[index] += 5;

			}

		}
		bool checkcar(float x, float y) {
			for (int i = 0; i < 5; i++) {
				if (carSprites[i]) {
					sf::FloatRect spriteBounds = (*carSprites[i]).getGlobalBounds();
					if (spriteBounds.contains(static_cast<float>(x), static_cast<float>(y))) {

						check[i] = true;
						return true;
					}
				}
			}
			return false;
		}

		void determine_row_and_col_chosen_by_second_click(int mouse_x, int mouse_y, int& row, int& col) {
			for (int y = 0; y < VERT_BLOCK_COUNT; y++) {
				for (int x = 0; x < HORIZ_BLOCK_COUNT; x++) {
					const Block& currentBlock = map[y][x];
					if (mouse_x > currentBlock.x1 && mouse_x < currentBlock.x2 &&
						mouse_y > currentBlock.y1 && mouse_y < currentBlock.y2) {
						row = y;
						col = x;
						return;
					}
					else {
						row = -1;
						col = -1;
					}
				}
			}
		}

	};
	struct Player {
		string name;
		int sun_count;
		int level;
		bool is_first_click_made;
	};
	
#define ICON_BAR_X1 20
#define ICON_BAR_X2 113
#define ICON_BAR_Y1 102
#define ICON_BAR_Y2 575

#define INIT_SUN_Y 5
#define SUNFLOWER_ICON_Y1 103
#define PEASHOOTER_100_ICON_Y1 167
#define WALNUT_ICON_Y1 231

#define ICON_BAR_WIDTH 95
#define ICON_BAR_HEIGHT 575
#define ICON_WIDTH 89
#define ICON_HEIGHT 60
#define SUN_COUNT_WIDTH 70
#define SUN_COUNT_HEIGHT 30
#define SUN_WIDTH 80
#define SUN_HEIGHT 80
#define PEA_WIDTH 20
#define PEA_HEIGHT 20
class iconsforgrid {
private:
	Sprite icongrid;
	Texture icongridtexture;
	//Icons icones;
	Sprite peashoter;
	Texture peashotertexture[2];
	Sprite sunflower;
	Texture sunflowertexture[2];
	Sprite cherrybomb;
	Texture cherrytexture[2];
	Sprite walnut;
	Sprite snow;
	Texture walnuttexture[2];
	bool level1;
	bool level2;
	bool level3;
	bool level4;
	int suncount = 100;
	Texture remover;
	Sprite removersprite;
	
public:
	iconsforgrid(bool l1 = 0, bool l2 = 0, bool l3 = 0, bool l4 = 0) {
		icongridtexture.loadFromFile("Images/Item_Bar.png");
		icongrid.setTexture(icongridtexture);
		icongrid.setPosition(0, 60);
		peashotertexture[0].loadFromFile("Images/icon_peashooter_100_dim (1).png");
		peashotertexture[1].loadFromFile("Images/icon_peashooter_100.png");
		sunflowertexture[0].loadFromFile("images/icon_sunflower_dim (1).png");
		sunflowertexture[1].loadFromFile("images/icon_sunflower.png");
		remover.loadFromFile("images/remover.jpg");
		cherrytexture[0].loadFromFile("Images/image.png");
		cherrytexture[1].loadFromFile("Images/chery icon.png");
		walnuttexture[1].loadFromFile("Images/icon_walnut (1) (1).png");
		walnuttexture[0].loadFromFile("Images/icon_walnut_dim (1).png");
		removersprite.setTexture(remover);
		this->level1 = l1;
		this->level2 = l2;
		this->level3 = l3;

	}
	bool is_an_icon_chosen(int mouse_x, int mouse_y) {
		if (mouse_x > ICON_BAR_X1 && mouse_x < ICON_BAR_X2 &&
			mouse_y > ICON_BAR_Y1 && mouse_y < ICON_BAR_Y2)
			return true;
		return false;
	}
	void handle_user_click(int mouse_x, int mouse_y) {
		bool sun_picked = false;

	}
	
	void draw(RenderWindow& window) {
		window.draw(icongrid);
		if (level1) {
			if (suncount < 100) {
				peashoter.setTexture(peashotertexture[0]);

			}
			if (suncount >= 100) {
				peashoter.setTexture(peashotertexture[1]);

			}
			if (suncount < 50) {
				sunflower.setTexture(sunflowertexture[0]);

			}
			if (suncount >= 50) {
				sunflower.setTexture(sunflowertexture[1]);

			}
			sunflower.setPosition(5, 62);
			peashoter.setPosition(5, 62 + 67);

			window.draw(sunflower);
			window.draw(peashoter);


		}
		if (level2) {
			if (suncount >= 150) {
				cherrybomb.setTexture(cherrytexture[1]);
				//cherrybomb.setTextureRect(sf::IntRect(265,11,25,26) );


			}
			if (suncount < 150) {
				cherrybomb.setTexture(cherrytexture[0]);
				//cherrybomb.setTextureRect(sf::IntRect(290, 12, 27, 24));

			}
			cherrybomb.setPosition(5, 62 + 67 + 67);
			window.draw(cherrybomb);


		}
		if (level3) {
			if (suncount < 50) {
				walnut.setTexture(walnuttexture[0]);

			}
			if (suncount >= 50) {
				walnut.setTexture(walnuttexture[1]);

			}
			if (suncount < 150) {
				snow.setTexture(peashotertexture[0]);

			}
			if (suncount >= 150) {
				snow.setTexture(peashotertexture[1]);

			}
			walnut.setPosition(5, 67 + 67 + 62 + 67);
			snow.setPosition(5, 67 + 67 + 62 + 67 + 67);
			window.draw(walnut);
			window.draw(snow);
		}
			
			if (level4) {

			}
			removersprite.setPosition(120 + 20, 60 + 480);
			window.draw(removersprite);

		}
	
	int checkonclick(int mouse_x, int mouse_y) {
		if (this->is_an_icon_chosen(mouse_x, mouse_y)) {
			if (mouse_y > 62 + 66 && mouse_y < 62 + 66 + 67) {
				if (suncount >= 100) {
					return 2;
				}
			}
			

		}
		sf::FloatRect spriteBounds = sunflower.getGlobalBounds();
		if (spriteBounds.contains(static_cast<float>(mouse_x), static_cast<float>(mouse_y))) {

			if (suncount >= 50) {
				return 1;
			}
		}
		sf::FloatRect spriteBounds4 = walnut.getGlobalBounds();
		if (spriteBounds4.contains(static_cast<float>(mouse_x), static_cast<float>(mouse_y))) {

			if (suncount >= 50) {
				return 4;
			}
		}
		sf::FloatRect spriteBounds5 = snow.getGlobalBounds();
		if (spriteBounds5.contains(static_cast<float>(mouse_x), static_cast<float>(mouse_y))) {

			if (suncount >= 150) {
				return 5;
			}
		}
		sf::FloatRect spriteBounds2 = removersprite.getGlobalBounds();
		if (spriteBounds2.contains(static_cast<float>(mouse_x), static_cast<float>(mouse_y))){
			return 8;
			//cout << "L:";
			}
		sf::FloatRect spriteBounds1 = cherrybomb.getGlobalBounds();
		if (spriteBounds1.contains(static_cast<float>(mouse_x), static_cast<float>(mouse_y))) {
			return 3;
		}
			return -1;
		}
		void add(Sun& sun1, int mouseX, int mouseY) {
			suncount = sun1.quantity;
			sf::FloatRect spriteBounds = sun1.sunsprite.getGlobalBounds();
			
			if (spriteBounds.contains(static_cast<float>(mouseX), static_cast<float>(mouseY))){
				suncount += 50;
				sun1.addSun(50);
				sun1.setActive(0);
			}

		}
		void reduce(int quantity) {
			suncount -= quantity;
			if (suncount < 0) {
				suncount = 0;
			}
		}
		void addquantity(int quantity) {
			suncount += quantity;
			
		}

	};
	
class level1 {
private:
	int score;
	bool loseourwin;
	plant* plants[50];
	gridformap map;
	//Sun suning;
	bool finalwave = false;
	Texture peashouterTexture;
	Texture sunflower1;
	int numofplant;
	const static int ROWS = 5;
	const static int COLS = 9;
	bool isOccupied[ROWS][COLS];
	int current;
	Clock spawn;
	float j[10] = { 0,0,0,0,0,0,0,0,0,0 };
	ZombieFactory* ptr[10];
	float time = 10;
	float speed = 0.1;
	sf::Music bMusic;
	sf::Music bgMusic;
	sf::Music bgMusic1;
public:
	level1() :map(257, 83, 81, 101) {
		score = 0;
		loseourwin = false;
		finalwave = false;
		peashouterTexture.loadFromFile("Images/Peashooter-removebg-preview.png");
		sunflower1.loadFromFile("Images/sunflower-removebg-preview.png");
		current = 0;
		for (int i = 0; i < 10; i++) {
			ptr[i] = new SimpleZombie();
		}
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				isOccupied[i][j] = false;
			}
		}

		bMusic.openFromFile("Images/Voices evillaugh.mp3");
		bgMusic.openFromFile("Images/SFX chomp.mp3");

		bgMusic1.openFromFile("Images/SFX firepea.mp3");
	}
	void makingplants(int type, int row, int col) {
		if (type == 1) {
			if (!isOccupied[row][col]) { // Check if the cell is not occupied
				plantfactory* factory = new SunflowerFactory();
				plants[current] = factory->createPlant();
				delete factory;
				plants[current]->settexture(sunflower1);
				plants[current]->setposition(256 + (81 * col), 83 + (101 * row));
				plants[current]->setrow(row);
				plants[current]->setcol(col);
				current++;
				isOccupied[row][col] = true; // Set the cell as occupied

			}
		}
		else if (type == 2) {
			if (!isOccupied[row][col]) { // Check if the cell is not occupied
				plantfactory* factory = new PeashooterFactory();
				plants[current] = factory->createPlant();
				delete factory;
				plants[current]->settexture(peashouterTexture);
				plants[current]->setposition(256 + (81 * col), 83 + (101 * row));
				plants[current]->setrow(row);
				plants[current]->setcol(col);
				current++;
				isOccupied[row][col] = true; // Set the cell as occupied
			}
		}
	}
	bool checkclickongridandplacing(int mouseX, int mouseY, int type) {
		int row, col;
		map.determine_row_and_col_chosen_by_second_click(mouseX, mouseY, row, col);
		if (row != -1) {
			if (isOccupied[row][col] != true) {
				makingplants(type, row, col);
				cout << row << " " << col;

				;					return true;
			}
			if (type == 8) {
				if (isOccupied[row][col] == true) {
					for (int i = 0; i < current; i++) {
						if (plants[i]) {

							if (plants[i]->getrow() == row && plants[i]->getcol() == col) {
								isOccupied[plants[i]->getrow()][plants[i]->getcol()] = false;
								delete plants[i];
								plants[i] = nullptr;
								for (int j = i; j < current - 1; j++) {
									plants[j] = plants[j + 1];
								}
								current--;
							}
						}
					}
				}
			}
		}
		return false;
	}
	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < current; i++) {
			if (plants[i]) {
				plants[i]->draw(window);
			}
		}
		map.drawcar(window);
	}
	void spawn1(Texture* textures, Texture* textures2, IntRect* textureRects, IntRect* textureRects2, const int size, const int size2, RenderWindow& window) {

		for (int i = 0; i < 10; i++)
		{
			if (ptr[i] != nullptr) {
				if (spawn.getElapsedTime().asSeconds() >= time) {
					spawn.restart();
					/*ptr[i] = new SimpleZombie();*/
					int empty = -1;
					for (int k = 0; k < 10; ++k) {
						if (ptr[k] != nullptr) {
							if (!ptr[k]->getalive()) {
								empty = k;
								break;
							}
						}

					}
					if (empty != -1) {
						/*zombie[empty] = SimpleZombie(); */
						if (ptr[empty] != nullptr) {
							ptr[empty]->setalive(true);
						}
					}
				}
				if (ptr[i]->getalive() && !ptr[i]->checkend()) {
					//cout << "x: " << ptr[0]->getx() << endl;
					/*zombie[i].draw(window, i);*/
					if (!(ptr[i]->getcollision())) {
						ptr[i]->movezombie(1.0f, 0.0f + j[i], 0.0f, window, i,1);
						j[i] = j[i] - speed;
						ptr[i]->animatezombie(textures, textureRects, size, window);
					}
					else {
						/*ptr[i]->movezombie2(1.0f, ptr[i]->getx() + 0, 0.0f, window, i);*/
						bgMusic.play();
						bgMusic.setVolume(100);
						ptr[i]->animatezombie(textures2, textureRects2, size2, window);
						ptr[i]->draw(window, i, ptr[i]->getx(), ptr[i]->gety());
						/*j[i] = j[i] - 0.01;*/
						/*ptr[i]->animatezombie(textures2, textureRects2, size2, window);*/
					}
				}
				//zombie[i].movesimplezombie(1.0f, 0.0f + j[i], 0.0f, window, i);
				//j[i] = j[i] - 0.01;
			}
			/*}*/
		}
	}
	

	void checkfocollision() {
		for (int i = 0; i < current; i++) {
			if (plants[i]) {
				for (int j = 0; j < 10; j++) {
					if (ptr[j]) {
						if (plants[i]->checkforcollision(ptr[j]->getx(), ptr[j]->gety())) {
							plants[i]->reducehealth(5);
							cout << "l";
							ptr[j]->setcollision(1);
							cout << ptr[j]->getcollision();
							if (plants[i]->getHealth() <= 0) {
								ptr[j]->setcollision(0);
							}
						}
						if (plants[i]->checkforcollisionforshoot(ptr[j]->getx(), ptr[j]->gety())) {
							bgMusic1.play();
							bgMusic1.setVolume(100);
							ptr[j]->reducehealth(7);
							plants[i]->setposition3(-10, -10);
							if (ptr[j]->gethealth() <= 0) {
								score += 10;
								delete ptr[j];
								ptr[j] = nullptr;
							}
						}

					}
				}
			}
		}
	}
	int getscore() {
		return score;
	}
	void checkforwave() {
		int check = false;
		for (int i = 0; i < 10; i++) {
			if ((ptr[i] == nullptr)) {
				check = true;
			}
			else {
				check = false;
			}
		}
		if ((check) && (!(finalwave))) {
			bMusic.play();
			bMusic.setVolume(100);
			for (int i = 0; i < 10; i++) {
				ptr[i] = new SimpleZombie();
				j[i] = 0;
			}
			finalwave = true;
			time = 1;

		}
		check = false;
	}
	bool addsunflowersun(int mouseX, int mouseY) {
		for (int i = 0; i < current; i++) {
			if (plants[i]) {
				if(plants[i]->checkforclickmouse((mouseX),(mouseY))) {
					return true;
				}
			}
		}
	
		return 0;
	}
	void winandlose() {
		if ((finalwave)) {
			bool check = false;
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] == nullptr)) {
					//loseourwin = true;
					check = true;
				}
				else {
					check = false;
					break;
				}
			}
			if (check) {
				loseourwin = true;
			}
		}
	}
	bool  getloseourwiner() {
		return loseourwin;
	}
	void checkcollision() {
		for (int i = 0; i < 10; i++) {
			if ((ptr[i] != nullptr)) {
				if (map.checkcar(ptr[i]->getx(), ptr[i]->gety())) {
					score += 10;
					delete ptr[i];
					ptr[i] = nullptr;
				}
			}
		}
	}
	bool checkforlose() {
		for (int i = 0; i < 10; i++) {
			if ((ptr[i] != nullptr)) {
				if(ptr[i]->getx() <125 && ptr[i]->getx()>0) {
					cout << ptr[i]->getx();
					return true;
				}
			}
		}
		return false;
	}


			void deletingplants() {
				for (int i = 0; i < current; i++) {
					if (plants[i]) {
						if (plants[i]->getHealth() <= 0) {
							
							isOccupied[plants[i]->getrow()][ plants[i]->getcol()] = false;
							
							delete plants[i];
							plants[i] = nullptr;
							for (int j = i; j < current - 1; j++) {
								plants[j] = plants[j + 1];
							}

							current--;
						}
					}
				}
			}
	};
	
	class game {
	private:
		level1 l1; 
		iconsforgrid icon;
		Sun sn;
		bool check;
		Clock clock;
		int iconvalue;
		Clock dancespawn; 
		Clock spawn;
		bool zombieSpawned = false;
		Clock timeMoney;
		const int size = 7;
		IntRect textureRects[7] = {
		IntRect({8,696,29,48}),
		IntRect({60,696,27,48}),
		IntRect({108,697,30,47}),
		IntRect({154,698,29,48}),
		IntRect({206,694,25,49}),
		IntRect({249,696,33,49}),
		IntRect({299,697,33,46})
		};
		IntRect attacktextureRects[7] = {
	IntRect({4,230,33,44}),
	IntRect({49,230,33,44}),
	IntRect({94,230,33,44}),
	IntRect({138,230,35,44}),
	IntRect({186,232,31,42}),
	IntRect({232,230,30,44}),
	IntRect({275,229,32,45})
		};

		bool b = false;
		//RenderWindow window;
	public:
		game():icon(1,0,0,0) {
			
			check = false;
			iconvalue = -1;
			
		}
		void draw(RenderWindow& window,Texture* textures, Texture* textures1) {
			//icon.draw(window);
			sn.draw(window);
			l1.draw(window);

			l1.spawn1(textures, textures1,textureRects, attacktextureRects, 7, 7, window);
			
		}
		bool checkclickongrid(int mouseX, int mouseY) {
			iconvalue = icon.checkonclick(mouseX, mouseY);
			if (iconvalue != -1) {
				check = true;
				cout << "true";
				return true;
			}
			else
			{
				return false;
			}
		}
		void createBack2(RenderWindow& window) {
			Image map_image;
			map_image.loadFromFile("Images/Frontyard_dim1.jpeg");
			Texture map;
			map.loadFromFile("Images/Frontyard_dim1.jpeg");
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(0, 0);

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
		void checkclickonmap(int mouseX, int mouseY) {
			if (check) {
				cout << "icon";
				if (iconvalue == 1) {
					if (l1.checkclickongridandplacing(mouseX, mouseY, 1)) {
						sn.reduceSun(50);
						icon.reduce(50);
						cout << "extra";

					}
					else {
						cout << "false";
					}

				}
				else if (iconvalue == 2) {
					if (l1.checkclickongridandplacing(mouseX, mouseY, 2)) {
						sn.reduceSun(100);
						icon.reduce(100);
					}
					else
					{
						check = false;
					}
				}
				else if (iconvalue == 8) {
			    if (l1.checkclickongridandplacing(mouseX, mouseY, 8)) {

					}
				}
			}
		}
		void sunadding(int mouseX, int mouseY) {
			cout << mouseX << "    " << mouseY;
			icon.add(sn, mouseX, mouseY);
			if (l1.addsunflowersun(mouseX, mouseY)) {
				sn.addSun(50);
				icon.addquantity(50);
			}
		}
		
	    
		void updatinggame() {
			l1.checkfocollision();
			l1.deletingplants();
			l1.checkforwave();
		}
		void createBack(RenderWindow& window) {
			//Drawing the background
			Image map_image;
			map_image.loadFromFile("Images/level2.jpg");
			Texture map;
			map.loadFromFile("Images/level1.png");
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(0, 0);
			//s_map.scale(2, 2);
			window.draw(s_map);
		}
		void createMap(RenderWindow& window) {
			//Drawing a map
			Image map_image;//?????? ??????????? ??? ?????
			map_image.loadFromFile("Images/grid.png");//load the file for the map
			Texture map;
			map.loadFromImage(map_image);
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(240, 60);

			//window.draw(s_map);
		}
		void gameLoop(Texture* textures, Texture* textures1, RenderWindow& window,int& scores,bool& levelcheck) {
			//sf::RenderWindow window(sf::VideoMode(1400, 600), "Your Game Title");

			while (window.isOpen()) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}
					else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;
						sunadding(mouseX, mouseY);
						if (b) {
							checkclickonmap(mouseX, mouseY);
						}
						if (checkclickongrid(mouseX, mouseY)) {
							b = true;
						}
					}
					else if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == sf::Keyboard::Escape) {
							createBack2(window);
						}
					}
				}
				l1.checkfocollision();
				l1.deletingplants();
				l1.checkforwave();
				l1.winandlose();
				l1.checkcollision();
				window.clear();
				createBack(window);
				//createMap(window);
				icon.draw(window);
				scores = l1.getscore();
				if (l1.checkforlose()) {
					levelcheck = false;
					cout << "kfkj";
					return ;
				}
				if (l1.getloseourwiner()) {
					levelcheck = true;
					cout << "L";
					return;
				}
				//icon.move(window, 2);
				draw(window, textures1, textures1);
				//gamer.updatinggame();

				//h3.draw(window);
				window.display();
			}
		}
	};
	
	class Highscore {
	private:
		ScoreManager scoremanager;
		Font font;
		Texture texture;
		Sprite background;
	public:
		Highscore(float width, float height) {
			if (!font.loadFromFile("Images/CombackHomeRegular-jEMd9.ttf")) {
				std::cerr << "Error loading font file!" << std::endl;
			}

			if (!texture.loadFromFile("Images/m.jpg")) {
				std::cerr << "Error loading texture file!" << std::endl;
			}
			background.setTexture(texture);
		}
		void draw(sf::RenderWindow& window) {

			while (window.isOpen()) {
				window.clear();
				window.draw(background);
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
					window.clear();
					window.draw(background);
				Text topScoresText;
				topScoresText.setFont(font);
				topScoresText.setFillColor(sf::Color::Red);
				topScoresText.setString("Top Scores");
				topScoresText.setCharacterSize(80);
				topScoresText.setPosition(650, 50);
				window.draw(topScoresText);

				// Get top 3 scores for display (assuming you want to show top 3)
				for (int i = 0; i < 5 && i < scoremanager.getNumScores(); ++i) {
					std::string scoreText = std::to_string(i + 1) + " " +
						scoremanager.getTopScores()[i].playerName + " " +
						std::to_string(scoremanager.getTopScores()[i].score);
					sf::Text scoreDisplay;
					scoreDisplay.setFont(font);
					scoreDisplay.setFillColor(sf::Color::Black);
					scoreDisplay.setString(scoreText);
					scoreDisplay.setCharacterSize(50);
					scoreDisplay.setPosition(700, 150 + i * 50); // Adjust position as needed
					window.draw(scoreDisplay);
					//window.display();
				}
				window.display();
				}
					//window.display();
				
			
		}
	};
	class level2 {
	private:
		int score;
		bool loseourwin;
		plant* plants[50];
		gridformap map;
		//Sun suning;
		bool finalwave = false;
		Texture peashouterTexture;
		Texture sunflower1;
		Texture cherry;
		int numofplant;
		const static int ROWS = 5;
		const static int COLS = 9;
		bool isOccupied[ROWS][COLS];
		int current;
		Clock spawn;
		Clock spawn9;
		float j[10] = { 0,0,0,0,0,0,0,0,0,0 };
		ZombieFactory* ptr[10];
		float time = 10;
		float speed = 0.1;
		sf::Music bMusic;
		sf::Music bgMusic;
		float footx[10] = { 0,0,0,0,0,0,0,0,0,0 };
		float footy[10] = { 0,0,0,0,0,0,0,0,0,0 };
		float positionx[10] = { 1078, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
		/*float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };*/
		float positiony[10] = { 100,201,300,391,485,100,201,300,391,485 };
		sf::Music bgMusic1;
	public:
		level2() :map(256,40, 90, 112) {
			score = 0;
			loseourwin = false;
			finalwave = false;
			peashouterTexture.loadFromFile("Images/Peashooter-removebg-preview.png");
			sunflower1.loadFromFile("Images/sunflower-removebg-preview.png");
			cherry.loadFromFile("Images/cherry_bomb-removebg-preview.png");
			current = 0;
			
			for (int i = 3; i < 10; i++) {
				ptr[i] = new SimpleZombie();
			}
			for (int i = 0; i <3; i++) {
				ptr[i] = new FootballZombie();
			}
			
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					isOccupied[i][j] = false;
				}
			}

			bMusic.openFromFile("Images/Voices evillaugh.mp3");
			bgMusic.openFromFile("Images/SFX chomp.mp3");
			bgMusic1.openFromFile("Images/SFX firepea.mp3");
		}
		void makingplants(int type, int row, int col) {
			if (type == 1) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new SunflowerFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(sunflower1);
					plants[current]->setposition(266 + (90 * col), 20 + (110 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied

				}
			}
			else if (type == 2) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new PeashooterFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(peashouterTexture);
					plants[current]->setposition(266 + (90 * col), 20 + (110 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied
				}
			}
			else if (type == 3) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new CherryBombFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(cherry);
					plants[current]->setposition(266 + (90 * col), 20 + (110 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied
				}

			}
		}
		bool checkclickongridandplacing(int mouseX, int mouseY, int type) {
			int row, col;
			map.determine_row_and_col_chosen_by_second_click(mouseX, mouseY, row, col);
			if (row != -1) {
				if (isOccupied[row][col] != true) {
					makingplants(type, row, col);
					cout << row << " " << col;

					;					return true;
				}
				if (type == 8) {
					if (isOccupied[row][col] == true) {
						for (int i = 0; i < current; i++) {
							if (plants[i]) {

								if (plants[i]->getrow() == row && plants[i]->getcol() == col) {
									isOccupied[plants[i]->getrow()][plants[i]->getcol()] = false;
									delete plants[i];
									plants[i] = nullptr;
									for (int j = i; j < current - 1; j++) {
										plants[j] = plants[j + 1];
									}
									current--;
								}
							}
						}
					}
				}
			}
			return false;
		}
		void draw(sf::RenderWindow& window) {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					plants[i]->draw(window);
				}
			}
			map.drawcar(window);
		}
		
		void spawn1(Texture* textures, Texture* textures2, IntRect* textureRects, IntRect* textureRects2, const int size, const int size2, RenderWindow& window) {

			for (int i = 3; i < 10; i++)
			{
				if (ptr[i] != nullptr) {
					if (spawn.getElapsedTime().asSeconds() >= time) {
						spawn.restart();
						/*ptr[i] = new SimpleZombie();*/
						int empty = -1;
						for (int k = 3; k < 10; ++k) {
							if (ptr[k] != nullptr) {
								if (!ptr[k]->getalive()) {
									empty = k;
									break;
								}
							}

						}
						if (empty != -1) {
							/*zombie[empty] = SimpleZombie(); */
							if (ptr[empty] != nullptr) {
								ptr[empty]->setalive(true);
							}
						}
					}
					if (ptr[i]->getalive() && !ptr[i]->checkend()) {
						//cout << "x: " << ptr[0]->getx() << endl;
						/*zombie[i].draw(window, i);*/
						if (!(ptr[i]->getcollision())) {
							ptr[i]->movezombie(1.0f, 0.0f + j[i], 0.0f, window, i,2);
							j[i] = j[i] - speed;
							ptr[i]->animatezombie(textures, textureRects, size, window);
						}
						else {
							/*ptr[i]->movezombie2(1.0f, ptr[i]->getx() + 0, 0.0f, window, i);*/
							bgMusic.play();
							bgMusic.setVolume(100);
							ptr[i]->animatezombie(textures2, textureRects2, size2, window);
							ptr[i]->draw(window, i, ptr[i]->getx(), ptr[i]->gety());
							/*j[i] = j[i] - 0.01;*/
							/*ptr[i]->animatezombie(textures2, textureRects2, size2, window);*/
						}
					}
					//zombie[i].movesimplezombie(1.0f, 0.0f + j[i], 0.0f, window, i);
					//j[i] = j[i] - 0.01;
				}
				/*}*/
			}
		}
		void spawn2(Texture* textures, Texture* textures2, IntRect* textureRects, IntRect* textureRects2, const int size, const int size2, RenderWindow& window) {

			for (int i = 1; i < 3; i++) {
				if (ptr[i] != nullptr) {
					//cout << "l";
					if (spawn9.getElapsedTime().asSeconds() >= 10) {
						spawn9.restart();
						int empty = -1;
						for (int k = 1; k < 3; ++k) {
							if (ptr[k] != nullptr) {
								if (!ptr[k]->getalive()) {
									empty = k;
									break;
								}
							}
						}
						if (empty != -1) {
							if (ptr[empty] != nullptr) {
								ptr[empty]->setalive(true);
							}
						}
					}
					if (ptr[i]->getalive()) {
						if (!(ptr[i]->getcollision())) {
							/* if (ptr[i]->getx() >= 500) {*/
							cout << "y: " << ptr[i]->gety() << endl;
							ptr[i]->movezombie(1.0f, 0.0f + footx[i], 0.0f + footy[i], window, i, 2);
							footx[i] -= 0.1;
							if (ptr[i]->getmoveup()) {
								footy[i] -= 0.1;
							}
							else {
								footy[i] += 0.1;
							}

							ptr[i]->animatezombie(textures, textureRects, size2, window);
						}

						/*}*/
						else {
							///*eat.setLoop(true);*/
							//eat.play();
							/*ptr[i]->movezombie2(1.0f, ptr[i]->getx() + 0, 0.0f, window, i);*/
							ptr[i]->animatezombie(textures2, textureRects2, size2, window);
							ptr[i]->draw(window, i, ptr[i]->getx(), ptr[i]->gety());
							/*j[i] = j[i] - 0.01;*/
							/*ptr[i]->animatezombie(textures2, textureRects2, size2, window);*/
						}
					}
				}
			}
		}
			
		
		void checkfocollision() {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					for (int j = 0; j < 10; j++) {
						if (ptr[j]) {
							if (plants[i]->checkforcollision(ptr[j]->getx(), ptr[j]->gety())) {
								plants[i]->reducehealth(5);
								cout << "l";
								ptr[j]->setcollision(1);
								cout << ptr[j]->getcollision();
								if (plants[i]->getHealth() <= 0) {
									ptr[j]->setcollision(0);
								}
							}
							if (plants[i]->checkforcollisionforshoot(ptr[j]->getx(), ptr[j]->gety())) {
								bgMusic1.play();
								bgMusic1.setVolume(200);
								ptr[j]->reducehealth(10);
								plants[i]->setposition3(-10, -10);
								if (ptr[j]->gethealth() <= 0) {
									score += 10;
									delete ptr[j];
									ptr[j] = nullptr;
								}
							}
								
						}
					}
				}
			}
		}
		void checkfocollision1(RenderWindow& window) {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					for (int j = 0; j < 10; j++) {
						if (ptr[j]) {
							if (plants[i]->checkforcollision1(ptr[j]->getx(), ptr[j]->gety())) {
								plants[i]->reducehealth(200);
								plants[i]->animate2(window);
								/*delete plants[i];
								plants[i] = nullptr;
								for (int j = i; j < current - 1; j++) {
									plants[j] = plants[j + 1];
								}

								current--;*/
								delete ptr[i];
								ptr[i] = nullptr;
							}
						}
					}
				}
			}
		}
		int getscore() {
			return score;
		}
		void checkforwave() {
			int check = false;
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] == nullptr)) {
					check = true;
				}
				else {
					check = false;
					//break;
				}
			}
			if ((check) && (!(finalwave))) {
				bMusic.play();
				bMusic.setVolume(100);
				for (int i = 0; i <2; i++) {
					ptr[i] = new FootballZombie();
					j[i] = 0;
					this->footx[i] = 0;
					this->footy[i] = 0;
				}
				for (int i = 3; i < 6; i++) {
					ptr[i] = new SimpleZombie;
					j[i] = 0;
				}
				finalwave = true;
				time = 1;

			}
			check = false;
		}
		bool addsunflowersun(int mouseX, int mouseY) {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					if (plants[i]->checkforclickmouse((mouseX), (mouseY))) {
						return true;
					}
				}
			}

			return 0;
		}
		void winandlose() {
			if ((finalwave)) {
				bool check = false;
				for (int i = 0; i < 10; i++) {
					if ((ptr[i] == nullptr)) {
						//loseourwin = true;
						check = true;
					}
					else {
						check = false;
						break;
					}
				}
				if (check) {
					loseourwin = true;
				}
			}
		}
		bool  getloseourwiner() {
			return loseourwin;
		}
		void checkcollision() {
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] != nullptr)) {
					if (map.checkcar(ptr[i]->getx(), ptr[i]->gety())) {
						delete ptr[i];
						ptr[i] = nullptr;
						score +=10;
					}
				}
			}
		}
		bool checkforlose() {
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] != nullptr)) {
					if (ptr[i]->getx() < 135 && ptr[i]->getx() > 0) {
						cout << ptr[i]->getx();
						return true;
					}
				}
			}
			return false;
		}


		void deletingplants() {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					if (plants[i]->getHealth() <= 0) {

						isOccupied[plants[i]->getrow()][plants[i]->getcol()] = false;

						delete plants[i];
						plants[i] = nullptr;
						for (int j = i; j < current - 1; j++) {
							plants[j] = plants[j + 1];
						}

						current--;
					}
				}
			}
		}
	};

	class gameforlevel2{
	private:
		level2 l2;
		iconsforgrid icon;
		Sun sn;
		bool check;
		Clock clock;
		int iconvalue;
		Clock dancespawn;
		Clock spawn;
		bool zombieSpawned = false;
		Clock timeMoney;
		const int size = 7;
		IntRect textureRects[7] = {
		IntRect({8,696,29,48}),
		IntRect({60,696,27,48}),
		IntRect({108,697,30,47}),
		IntRect({154,698,29,48}),
		IntRect({206,694,25,49}),
		IntRect({249,696,33,49}),
		IntRect({299,697,33,46})
		};
		IntRect attacktextureRects[7] = {
	IntRect({4,230,33,44}),
	IntRect({49,230,33,44}),
	IntRect({94,230,33,44}),
	IntRect({138,230,35,44}),
	IntRect({186,232,31,42}),
	IntRect({232,230,30,44}),
	IntRect({275,229,32,45})
		};
		IntRect footballtextureRects[8] = {  //Frames
IntRect({2,225,50,56}),
IntRect({61,227,57,54}),
IntRect({127,225,55,51}),
IntRect({188,223,57,51}),
IntRect({248,228,59,53}),
IntRect({310,228,52,53}),
IntRect({374,223,55,53}),
IntRect({435,222,56,54})
		};
		Texture* footballtextures = new Texture[8];
		Texture* footballattacktextures = new Texture[6];
		IntRect footballattacktextureRects[6] = {
IntRect({10,499,44,57}),
IntRect({74,500,43,57}),
IntRect({137,503,43,54}),
IntRect({201,502,44,55}),
IntRect({269,500,40,56}),
IntRect({329,503,43,54})
		};
		//Clock dancespawn;
		bool b = false;
		//RenderWindow window;
	public:
		gameforlevel2() :icon(1, 1, 0, 0) {
			for (int i = 0; i < 8; i++) {
				footballtextures[i].loadFromFile("PVZ/Zombies/DS_DSi_-_Plants_vs_Zombies_-_Football_Zombie-removebg.png"); //File Source
			}
			for (int i = 0; i < 8; i++) {
				footballtextures[i].setRepeated(true); //Repetition
				footballtextures[i].setSmooth(true);
			}
			for (int i = 0; i < 6; i++) {
				footballattacktextures[i].loadFromFile("PVZ/Zombies/DS_DSi_-_Plants_vs_Zombies_-_Football_Zombie-removebg.png"); //File Source
			}
			for (int i = 0; i < 6; i++) {
				footballattacktextures[i].setRepeated(true); //Repetition
				footballattacktextures[i].setSmooth(true);
			}
			check = false;
			iconvalue = -1;

		}
		void draw(RenderWindow& window, Texture* textures, Texture* textures1) {
			//icon.draw(window);
			sn.draw(window);
			l2.draw(window);

			l2.spawn1(textures, textures1, textureRects, attacktextureRects, 7, 7, window);
			l2.spawn2(footballtextures, footballattacktextures, footballtextureRects, footballattacktextureRects, 8, 6, window);

		}
		bool checkclickongrid(int mouseX, int mouseY) {
			iconvalue = icon.checkonclick(mouseX, mouseY);
			if (iconvalue != -1) {
				check = true;
				cout << "true";
				return true;
			}
			else
			{
				return false;
			}
		}
		void checkclickonmap(int mouseX, int mouseY) {
			if (check) {
				if (iconvalue == 1) {
					if (l2.checkclickongridandplacing(mouseX, mouseY, 1)) {
						sn.reduceSun(50);
						icon.reduce(50);
						cout << "extra";

					}
					else {
						cout << "false";
					}

				}
				else if (iconvalue == 2) {
					if (l2.checkclickongridandplacing(mouseX, mouseY, 2)) {
						sn.reduceSun(100);
						icon.reduce(100);
					}
					else
					{
						check = false;
					}
				}
				else if (iconvalue == 3) {
					cout<<"zohaib";
					if (l2.checkclickongridandplacing(mouseX, mouseY, 3)) {
						sn.reduceSun(150);
						icon.reduce(150);
					}
					else
					{
						check = false;
					}
				}
				else if (iconvalue == 8) {
					if (l2.checkclickongridandplacing(mouseX, mouseY, 8)) {

					}
				}
			}
		}
		void sunadding(int mouseX, int mouseY) {
			cout << mouseX << "    " << mouseY;
			icon.add(sn, mouseX, mouseY);
			if (l2.addsunflowersun(mouseX, mouseY)) {
				sn.addSun(50);
				icon.addquantity(50);
			}
		}


		void updatinggame() {
			l2.checkfocollision();
			l2.deletingplants();
			l2.checkforwave();
		}
		void createBack(RenderWindow& window) {
			//Drawing the background
			Image map_image;
			map_image.loadFromFile("Images/level2.jpg");
			Texture map;
			map.loadFromFile("Images/level2.png");
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(0, 0);
			//s_map.scale(2, 2);
			window.draw(s_map);
		}
		void createMap(RenderWindow& window) {
			//Drawing a map
			Image map_image;//?????? ??????????? ??? ?????
			map_image.loadFromFile("Images/grid.png");//load the file for the map
			Texture map;
			map.loadFromImage(map_image);
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(256, 5);

			window.draw(s_map);
		}
		void createBack2(RenderWindow& window) {
			Image map_image;
			map_image.loadFromFile("Images/Frontyard_dim1.jpeg");
			Texture map;
			map.loadFromFile("Images/Frontyard_dim1.jpeg");
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(0, 0);
			
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
		void gameLoop(Texture* textures, Texture* textures1, RenderWindow& window, int& scores, bool& levelcheck) {
			//sf::RenderWindow window(sf::VideoMode(1400, 600), "Your Game Title");

			while (window.isOpen()) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}
					else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;
						sunadding(mouseX, mouseY);
						if (b) {
							checkclickonmap(mouseX, mouseY);
						}
						if (checkclickongrid(mouseX, mouseY)) {
							b = true;
						}
					}
					else if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == sf::Keyboard::Escape) {
							createBack2(window);
							//return;
						}
					}
				}
				l2.checkfocollision();
				l2.checkfocollision1(window);
				l2.deletingplants();
				l2.checkforwave();
				l2.winandlose();
				l2.checkcollision();
				window.clear();
				createBack(window);
				createMap(window);
				icon.draw(window);
				scores = l2.getscore();
				if (l2.checkforlose()) {
					levelcheck = false;
					cout << "kfkj";
					return;
				}
				if (l2.getloseourwiner()) {
					levelcheck = true;
					cout << "L";
					return;
				}
				
				//icon.move(window, 2);
				draw(window, textures1, textures1);
				//gamer.updatinggame();

				//h3.draw(window);
				window.display();
			}
		}
	};
	class Credentials {
		Font font;
		string s;
		Texture texture;
		Sprite bg;
		int i = 0;
		sf::String userInput;
	public:
		Credentials(float width, float height) {
			if (!font.loadFromFile("Images/CombackHomeRegular-jEMd9.ttf")) {
				std::cerr << "Error loading font file!" << std::endl;
			}

			if (!texture.loadFromFile("Images/m.jpg")) {
				std::cerr << "Error loading texture file!" << std::endl;
			}
			bg.setTexture(texture);
		}
		void draw(RenderWindow& window,string& ss) {
			while (window.isOpen()) {
				window.clear();
				window.draw(bg);
				//for (int i = 0; i < maxmainmenu; i++) {
				// window.draw(main[i]);
				//}
				Event event;
				// Display top scores below menu options
				/*cin >> s;*/
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
					}
					else if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::Enter) {
							cin >> s;
							ss = s;
							return;
						}
						if (event.key.code == Keyboard::Escape) {
							
							return;
						}
					}
					else if (event.type == sf::Event::TextEntered) {
						// Check if the entered character is a printable ASCII character
						if (event.text.unicode >= 32 && event.text.unicode < 128) {
							userInput += static_cast<char>(event.text.unicode);
						}
					}
				}
				window.clear();
				window.draw(bg);
				Text Credentials;
				Credentials.setFont(font);
				Credentials.setFillColor(sf::Color::Black);
				Credentials.setString("Enter Your Name: ");
				Credentials.setCharacterSize(50);
				Credentials.setPosition(650, 50);
				window.draw(Credentials);
				window.display();

			}
		}
	};
	/// level check
	//level 3

	class level3 {
	private:
		int score;
		bool loseourwin;
		plant* plants[50];
		gridformap map;
		//Sun suning;
		bool finalwave = false;
		Texture peashouterTexture;
		Texture sunflower1;
		int numofplant;
		const static int ROWS = 5;
		const static int COLS = 9;
		bool isOccupied[ROWS][COLS];
		int current;
		Clock spawn;
		float dancex[5] = { 0,0,0,0,0 };
		float dancey[5] = { 0,0,0,0,0 };
		float j[10] = { 0,0,0,0,0,0,0,0,0,0 };
		float positionx[10] = { 1078, 1059, 1040, 1089, 1110, 1078, 1059, 1040, 1089, 1110 };
		/*float positiony[] = { 328, 227, 142, 187, 421, 328, 227, 142, 187, 421 };*/
		float positiony[10] = { 100,201,300,391,485,100,201,300,391,485 };
	    ZombieFactory* ptr2[5];
		ZombieFactory* ptr[10];

		float time = 10;
		float speed = 0.1;
		sf::Music bMusic;
		sf::Music bgMusic;
		Texture cherry;
		Texture walnuta;
		Texture d;
		Clock dancespawn;
	public:
		level3() :map(257, 83, 81, 101) {
			score = 0;
			loseourwin = false;
			finalwave = false;
			peashouterTexture.loadFromFile("Images/Peashooter-removebg-preview.png");
			sunflower1.loadFromFile("Images/sunflower-removebg-preview.png");
			cherry.loadFromFile("Images/cherry_bomb-removebg-preview.png");
			walnuta.loadFromFile("Images/wall_nut-removebg.png");
			d.loadFromFile("Images/snow_pea-removebg-preview.png");
			current = 0;
			
			for (int i = 0; i < 5; i++) {
				ptr2[i] = new DancingZombie();
				ptr2[i]->setposition(positionx[i], positiony[i]);
			}
			for (int i = 0; i < 10; i++) {
				ptr[i] = new SimpleZombie();
				ptr[i]->setposition(positionx[i], positiony[i]);
			}
		
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					isOccupied[i][j] = false;
				}
			}

			bMusic.openFromFile("Images/Voices evillaugh.mp3");
			bgMusic.openFromFile("Images/SFX chomp.mp3");

		}
		void makingplants(int type, int row, int col) {
			if (type == 1) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new SunflowerFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(sunflower1);
					plants[current]->setposition(256 + (81 * col), 83 + (101 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied

				}
			}
			else if (type == 2) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new PeashooterFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(peashouterTexture);
					plants[current]->setposition(256 + (81 * col), 83 + (101 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied
				}
			}
			else if (type == 3) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new CherryBombFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(cherry);
					plants[current]->setposition(256 + (81 * col), 83 + (101 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied
				}

			}
			else if (type == 4) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new WalnutFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(walnuta);
					plants[current]->setposition(256 + (81 * col),  83+ (101 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied
				}

			}
			else if (type == 5) {
				if (!isOccupied[row][col]) { // Check if the cell is not occupied
					plantfactory* factory = new SnowPeashooterFactory();
					plants[current] = factory->createPlant();
					delete factory;
					plants[current]->settexture(d);
					cout << row;
					cout <<"    "<< col;
					cout << current;
					plants[current]->setposition(256 + (81 * col), 83 + (101 * row));
					plants[current]->setrow(row);
					plants[current]->setcol(col);
					current++;
					isOccupied[row][col] = true; // Set the cell as occupied
				}

			}
		}
		bool checkclickongridandplacing(int mouseX, int mouseY, int type) {
			int row, col;
			map.determine_row_and_col_chosen_by_second_click(mouseX, mouseY, row, col);
			if (row != -1) {
				if (isOccupied[row][col] != true) {
					makingplants(type, row, col);
					cout << row << " " << col;

					;					return true;
				}
				if (type == 8) {
					if (isOccupied[row][col] == true) {
						for (int i = 0; i < current; i++) {
							if (plants[i]) {

								if (plants[i]->getrow() == row && plants[i]->getcol() == col) {
									isOccupied[plants[i]->getrow()][plants[i]->getcol()] = false;
									delete plants[i];
									plants[i] = nullptr;
									for (int j = i; j < current - 1; j++) {
										plants[j] = plants[j + 1];
									}
									current--;
								}
							}
						}
					}
				}
			}
			return false;
		}
		void draw(sf::RenderWindow& window) {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					plants[i]->draw(window);
				}
			}
			map.drawcar(window);
		}
		void spawn1(Texture* textures, Texture* textures2, Texture* textures3, Texture* textures4, IntRect* textureRects, IntRect* textureRects2, IntRect* textureRects3, IntRect* textureRects4, const int size, const int size2, const int size3, const int size4, RenderWindow& window) {
			for (int i = 0; i < 5; i++) {
				if (ptr2[i]!=nullptr) {
					if (spawn.getElapsedTime().asSeconds() >= 5) {
						spawn.restart();
						int empty = -1;
						for (int k = 0; k < 5; ++k) {
							if (ptr[k]!=nullptr) {
								if (!ptr2[k]->getalive()) {
									empty = k;
									break;
								}
							}
						}
						if (empty != -1) {
							/*zombie[empty] = SimpleZombie();*/
							if (ptr2[empty]) {
								ptr2[empty]->setalive(true);
							}
						}
					}

					if (ptr2[i]->getalive() && !ptr2[i]->checkend()) {

						if (!ptr2[i]->getcollision()) {
							/*footballzombie[i].draw(window, i);*/
							ptr2[i]->movezombie(1.0f, 0.0f + dancex[i], 0.0f + dancey[i], window, i, 0);
							dancex[i] -= 0.2;
							if (ptr2[i]->getmoveup()) {
								dancey[i] -= 0.2;
							}
							else {
								dancey[i] += 0.2;
							}
							ptr2[i]->animatezombie(textures, textureRects, size, window);
						}
						else {
							ptr2[i]->animatezombie(textures3, textureRects3, size3, window);
							ptr2[i]->draw(window, 0, 0, 0);
						}
					}
				}

				if (dancespawn.getElapsedTime().asSeconds() >= 0.5) {
					dancespawn.restart();
					if (ptr[i]) {
						int empty = -1;
						for (int k = 0; k < 10; ++k) {
							if (ptr[k]) {
								if (!ptr[k]->getalive()) {
									empty = k;
									break;
								}
							}
						}
						if (empty != -1) {
							/*zombie[empty] = SimpleZombie(); */
							if (ptr[empty]) {
								ptr[empty]->setalive(true);
							}
						}
					
					if (ptr[i]->getalive() && !ptr[i]->checkend()) {
						/*zombie[i].draw(window, i);*/
						if (!ptr[i]->getcollision()) {
							ptr[i]->animatezombie(textures2, textureRects2, size2, window);
							ptr[i]->movezombie(1.0f, 0.0f + j[i], 0.0f, window, i, 0);
							j[i] = j[i] - 0.1;
						}
						else {
							ptr[i]->draw(window, 0, 0, 0);
							ptr[i]->animatezombie(textures4, textureRects4, size4, window);
						}
						}
					}
				}
			}
		}


		void checkfocollision() {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					for (int j = 0; j < 10; j++) {
						if (ptr[j]) {
							if (plants[i]->checkforcollision(ptr[j]->getx(), ptr[j]->gety())) {
								plants[i]->reducehealth(5);
								cout << "l";
								ptr[j]->setcollision(1);
								cout << ptr[j]->getcollision();
								if (plants[i]->getHealth() <= 0) {
									ptr[j]->setcollision(0);
								}
							}
							if (plants[i]->checkforcollisionforshoot(ptr[j]->getx(), ptr[j]->gety())) {
								ptr[j]->reducehealth(7);
								plants[i]->setposition3(-10, -10);
								if (ptr[j]->gethealth() <= 0) {
									score += 10;
									delete ptr[j];
									ptr[j] = nullptr;
								}
							}

						}
					}
					//
					for (int j = 0; j < 5; j++) {
						if (ptr2[j]) {
							if (plants[i]->checkforcollision(ptr2[j]->getx(), ptr2[j]->gety())) {
								plants[i]->reducehealth(5);
								cout << "l";
								ptr2[j]->setcollision(1);
								cout << ptr2[j]->getcollision();
								if (plants[i]->getHealth() <= 0) {
									ptr2[j]->setcollision(0);
								}
							}
							if (plants[i]->checkforcollisionforshoot(ptr2[j]->getx(), ptr2[j]->gety())) {
								ptr2[j]->reducehealth(7);
								plants[i]->setposition3(-10, -10);
								if (ptr2[j]->gethealth() <= 0) {
									score += 10;
									delete ptr2[j];
									ptr2[j] = nullptr;
								}
							}

						}
					}
				}
			}
		}
		int getscore() {
			return score;
		}
		void checkforwave() {
			int check = false;
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] == nullptr)) {
					check = true;
				}
				else {
					check = false;
				}
			}
			if ((check) && (!(finalwave))) {
				bMusic.play();
				bMusic.setVolume(100);
				for (int i = 0; i < 10; i++) {
					ptr[i] = new SimpleZombie();
					j[i] = 0;
				}
				finalwave = true;
				time = 1;

			}
			check = false;
		}
		bool addsunflowersun(int mouseX, int mouseY) {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					if (plants[i]->checkforclickmouse((mouseX), (mouseY))) {
						return true;
					}
				}
			}

			return 0;
		}
		void winandlose() {
			if ((finalwave)) {
				bool check = false;
				for (int i = 0; i < 10; i++) {
					if ((ptr[i] == nullptr)) {
						//loseourwin = true;
						check = true;
					}
					else {
						check = false;
						break;
					}
				}
				if (check) {
					loseourwin = true;
				}
			}
		}
		bool  getloseourwiner() {
			return loseourwin;
		}
		void checkcollision() {
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] != nullptr)) {
					if (map.checkcar(ptr[i]->getx(), ptr[i]->gety())) {
						score += 10;
						delete ptr[i];
						ptr[i] = nullptr;
					}
				}
			}
			for (int i = 0; i < 5; i++) {
				if ((ptr2[i] != nullptr)) {
					if (map.checkcar(ptr2[i]->getx(), ptr2[i]->gety())) {
						score += 10;
						delete ptr2[i];
						ptr2[i] = nullptr;
					}
				}
			}
		}
		bool checkforlose() {
			for (int i = 0; i < 10; i++) {
				if ((ptr[i] != nullptr)) {
					if (ptr[i]->getx() < 135 && ptr[i]->getx() > 0) {
						cout << ptr[i]->getx();
						return true;
					}
				}
			}
			for (int i = 0; i < 5; i++) {
				if ((ptr2[i] != nullptr)) {
					if (ptr2[i]->getx() < 135 && ptr2[i]->getx() > 0) {
						cout << ptr2[i]->getx();
						return true;
					}
				}
			}
			return false;
		}


		void deletingplants() {
			for (int i = 0; i < current; i++) {
				if (plants[i]) {
					if (plants[i]->getHealth() <= 0) {

						isOccupied[plants[i]->getrow()][plants[i]->getcol()] = false;

						delete plants[i];
						plants[i] = nullptr;
						for (int j = i; j < current - 1; j++) {
							plants[j] = plants[j + 1];
						}

						current--;
					}
				}
			}
		}
	};

	class gameforlevel3 {
	private:
		level3 l3;
		iconsforgrid icon;
		Sun sn;
		bool check;
		Clock clock;
		int iconvalue;
		Clock dancespawn;
		Clock spawn;
		bool zombieSpawned = false;
		Clock timeMoney;
		const int size = 7;
		IntRect textureRects[7] = {
		IntRect({8,696,29,48}),
		IntRect({60,696,27,48}),
		IntRect({108,697,30,47}),
		IntRect({154,698,29,48}),
		IntRect({206,694,25,49}),
		IntRect({249,696,33,49}),
		IntRect({299,697,33,46})
		};
		IntRect attacktextureRects[7] = {
	IntRect({4,230,33,44}),
	IntRect({49,230,33,44}),
	IntRect({94,230,33,44}),
	IntRect({138,230,35,44}),
	IntRect({186,232,31,42}),
	IntRect({232,230,30,44}),
	IntRect({275,229,32,45})
		};
		Texture* dancingtextures = new Texture[4];
		IntRect dancingtextureRects[4] = {
		IntRect({2,5,36,54}),
		IntRect({43,5,31,55}),
		IntRect({87,4,32,55}),
		IntRect({124,4,30,52})
		};
		

		const int dancingattacksize = 5;
		Texture* dancingattackingtexture = new Texture[5];
		IntRect dancingattackingtextureRects[5] = {
		IntRect({2,464,35,53}),
		IntRect({44,462,35,55}),
		IntRect({84,464,36,53}),
		IntRect({124,466,38,51}),
		IntRect({167,466,36,51})
		};
		


		bool b = false;
		//RenderWindow window;
	public:
		gameforlevel3() :icon(1, 1, 1, 0) {
			for (int i = 0; i < 4; i++) {
				dancingtextures[i].loadFromFile("PVZ/Zombies/DS DSi - Plants vs Zombies - Dancing Zombie.png");
			}
			for (int i = 0; i < 4; i++) {
				dancingtextures[i].setRepeated(true);
				dancingtextures[i].setSmooth(true);
			}
			check = false;
			iconvalue = -1;
			for (int i = 0; i < 5; i++) {
				dancingattackingtexture[i].loadFromFile("PVZ/Zombies/DS DSi - Plants vs Zombies - Dancing Zombie.png");
			}
			for (int i = 0; i < 4; i++) {
				dancingattackingtexture[i].setRepeated(true);
				dancingattackingtexture[i].setSmooth(true);
			}

		}
		void draw(RenderWindow& window, Texture* textures, Texture* textures1) {
			//icon.draw(window);
			sn.draw(window);
			l3.draw(window);
			l3.spawn1(dancingtextures, textures, dancingattackingtexture, textures1, dancingtextureRects, textureRects, dancingattackingtextureRects, attacktextureRects, 4, 7, 5, 7,window);
			//l3.spawn1(datextures, textures1, textureRects, attacktextureRects, 7, 7, window);

		}
		bool checkclickongrid(int mouseX, int mouseY) {
			iconvalue = icon.checkonclick(mouseX, mouseY);
			if (iconvalue != -1) {
				check = true;
				cout << "true";
				return true;
			}
			else
			{
				return false;
			}
		}
		void createBack2(RenderWindow& window) {
			Image map_image;
			map_image.loadFromFile("Images/Frontyard_dim1.jpeg");
			Texture map;
			map.loadFromFile("Images/Frontyard_dim1.jpeg");
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(0, 0);

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
		void checkclickonmap(int mouseX, int mouseY) {
			if (check) {
				cout << "icon";
				if (iconvalue == 1) {
					if (l3.checkclickongridandplacing(mouseX, mouseY, 1)) {
						sn.reduceSun(50);
						icon.reduce(50);
						cout << "extra";

					}
					else {
						cout << "false";
					}

				}
				else if (iconvalue == 2) {
					if (l3.checkclickongridandplacing(mouseX, mouseY, 2)) {
						sn.reduceSun(100);
						icon.reduce(100);
					}
					else
					{
						check = false;
					}
				}
				else if (iconvalue == 3) {
					if (l3.checkclickongridandplacing(mouseX, mouseY, 3)) {
						sn.reduceSun(150);
						icon.reduce(150);
					}
					else
					{
						check = false;
					}
				}
				else if (iconvalue == 4) {
					cout << "zohaib";
					if (l3.checkclickongridandplacing(mouseX, mouseY, 4)) {
						sn.reduceSun(50);
						icon.reduce(50);
					}
					else
					{
						check = false;
					}
				}
				else if (iconvalue == 5) {
					cout << "zohaib";
					if (l3.checkclickongridandplacing(mouseX, mouseY, 5)) {
						sn.reduceSun(150);
						icon.reduce(150);
					}
					else
					{
						check = false;
					}
				}

				else if (iconvalue == 8) {
					if (l3.checkclickongridandplacing(mouseX, mouseY, 8)) {

					}
				}
			}
		}
		void sunadding(int mouseX, int mouseY) {
			cout << mouseX << "    " << mouseY;
			icon.add(sn, mouseX, mouseY);
			if (l3.addsunflowersun(mouseX, mouseY)) {
				sn.addSun(50);
				icon.addquantity(50);
			}
		}


		void updatinggame() {
			l3.checkfocollision();
			l3.deletingplants();
			l3.checkforwave();
		}
		void createBack(RenderWindow& window) {
			//Drawing the background
			Image map_image;
			map_image.loadFromFile("Images/level4.png");
			Texture map;
			map.loadFromFile("Images/level4.png");
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(0, 0);
			//s_map.scale(2, 2);
			window.draw(s_map);
		}
		void createMap(RenderWindow& window) {
			//Drawing a map
			Image map_image;//?????? ??????????? ??? ?????
			map_image.loadFromFile("Images/grid.png");//load the file for the map
			Texture map;
			map.loadFromImage(map_image);
			Sprite s_map;
			s_map.setTexture(map);
			s_map.setPosition(240, 60);

			//window.draw(s_map);
		}
		void gameLoop(Texture* textures, Texture* textures1, RenderWindow& window, int& scores, bool& levelcheck) {
			//sf::RenderWindow window(sf::VideoMode(1400, 600), "Your Game Title");

			while (window.isOpen()) {
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}
					else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
						int mouseX = event.mouseButton.x;
						int mouseY = event.mouseButton.y;
						sunadding(mouseX, mouseY);
						if (b) {
							checkclickonmap(mouseX, mouseY);
						}
						if (checkclickongrid(mouseX, mouseY)) {
							b = true;
						}
					}
					else if (event.type == sf::Event::KeyPressed) {
						if (event.key.code == sf::Keyboard::Escape) {
							createBack2(window);
						}
					}
				}
				l3.checkfocollision();
				l3.deletingplants();
				l3.checkforwave();
				l3.winandlose();
				l3.checkcollision();
				window.clear();
				createBack(window);
				//createMap(window);
				icon.draw(window);
				scores = l3.getscore();
				if (l3.checkforlose()) {
					levelcheck = false;
					cout << "kfkj";
					return;
				}
				if (l3.getloseourwiner()) {
					levelcheck = true;
					cout << "L";
					return;
				}
				draw(window, textures1, textures1);
				//gamer.updatinggame();

				//h3.draw(window);
				window.display();
			}
		}
	};
