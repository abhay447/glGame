#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace std;

void backgroundMusic()
{
		sf::Music music;
		sf::Time delayTime = sf::milliseconds(1000000);
		if (music.openFromFile("audio/Deeper.ogg"))
		{
			music.play();
			music.setLoop(true);
			sf::sleep(delayTime);
			cout<<"bolo";
		}
		else
			cout<<"olo";
}

