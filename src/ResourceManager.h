#pragma once

//Alan Duong, 03/31/19
//Loads resources and makes it easier to access and share them.
//We only need to load an image and sound once.

#include <unordered_map>
#include <string>
#include "ofMain.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	ofImage* getImage(std::string path);
	ofSoundPlayer* getSound(std::string path);
	ofSoundPlayer* getSoundLoop(std::string path);
	void playSoundLoop(std::string path);
	void stopSoundLoop(std::string path);

	std::unordered_map<std::string, ofImage> images;
	std::unordered_map<std::string, ofSoundPlayer> sounds;
	std::unordered_map<std::string, ofSoundPlayer> soundloops;
};