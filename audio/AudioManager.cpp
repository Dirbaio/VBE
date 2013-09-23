#include "AudioManager.hpp"

std::map<std::string,sf::Music*> AudioManager::musicBank;
std::map<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>> AudioManager::effectBank;

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
}

bool AudioManager::loadMusic(const std::string &trackID, const std::string &filePath) {
	VBE_ASSERT(musicBank.find(trackID) == musicBank.end(), "Loading failed: track " << trackID << " already exists")
	std::cout << "* Loading new music track: \"" << trackID << "\" from " << filePath << std::endl;
	sf::Music * newTrack = new sf::Music();
	if (!newTrack->openFromFile(filePath)) {
		std::cout << "#ERROR " << filePath << " didn't load" << std::endl;
		return false;
	}
	musicBank.insert(std::pair<std::string,sf::Music*>(trackID,newTrack));
	return true;
}

void AudioManager::eraseMusic(const std::string &trackID) {
	VBE_ASSERT(musicBank.find(trackID) != musicBank.end(), "Deleting failed: track " << trackID << " doesn't exist")
	std::cout << "* Deleting music track \"" << trackID << "\"" << std::endl;
	delete musicBank.at(trackID);
	musicBank.erase(trackID);
}

bool AudioManager::loadEffect(const std::string &effectID, const std::string &filePath) {
	VBE_ASSERT(effectBank.find(effectID) == effectBank.end(), "Loading failed: effect " << effectID << " already exists")
	std::cout << "* Loading new sound effect: \"" << effectID << "\" from " + filePath << std::endl;
	std::pair<sf::SoundBuffer*,sf::Sound*> newEffect = std::pair<sf::SoundBuffer*,sf::Sound*>(new sf::SoundBuffer(),new sf::Sound());
	if (!newEffect.first->loadFromFile(filePath)) {
		std::cout << "#ERROR " << filePath << " didn't load" << std::endl;
		return false;
	}
	newEffect.second->setBuffer(*newEffect.first);
	effectBank.insert(std::pair<std::string,std::pair<sf::SoundBuffer*,sf::Sound*>>(effectID,newEffect));
	return true;
}

void AudioManager::eraseEffect(const std::string &effectID) {
	VBE_ASSERT(effectBank.find(effectID) != effectBank.end(), "Deleting failed: effect " << effectID << " doesn't exist")
	std::cout << "* Deleting sound effect \"" << effectID << "\"" << std::endl;
	delete effectBank.at(effectID).first;
	delete effectBank.at(effectID).second;
	effectBank.erase(effectID);
}


void AudioManager::clear() {
	while(!effectBank.empty())
		eraseEffect(effectBank.begin()->first);
	while(!musicBank.empty())
		eraseMusic(musicBank.begin()->first);
}
