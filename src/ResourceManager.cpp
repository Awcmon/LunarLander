#include "ResourceManager.h"

//Alan Duong, 03/31/19
//Loads resources and makes it easier to access and share them.
//We only need to load an image and sound once.

ResourceManager::ResourceManager()
{
	ofDirectory imagesDir("images");
	//only show png files
	imagesDir.allowExt("png");
	//populate the directory object
	imagesDir.listDir();

	//go through and print out all the paths
	for (size_t i = 0; i < imagesDir.size(); i++) {
		std::cout << (imagesDir.getPath(i)) << "\n";
		ofImage temp;
		temp.load(imagesDir.getPath(i));
		images[imagesDir.getPath(i)] = temp;
	}

	ofDirectory soundsDir("sounds");
	//only show png files
	soundsDir.allowExt("wav");
	//populate the directory object
	soundsDir.listDir();

	//go through and print out all the paths
	for (size_t i = 0; i < soundsDir.size(); i++) {
		std::cout << (soundsDir.getPath(i)) << "\n";
		ofSoundPlayer temp;
		temp.setMultiPlay(true);
		temp.load(soundsDir.getPath(i));
		sounds[soundsDir.getPath(i)] = temp;
	}

	ofDirectory soundloopsDir("soundloops");
	//only show png files
	soundloopsDir.allowExt("wav");
	soundloopsDir.allowExt("mp3");
	soundloopsDir.allowExt("ogg");
	//populate the directory object
	soundloopsDir.listDir();

	//go through and print out all the paths
	for (size_t i = 0; i < soundloopsDir.size(); i++) {
		std::cout << (soundloopsDir.getPath(i)) << "\n";
		ofSoundPlayer temp;
		temp.setLoop(true);
		temp.load(soundloopsDir.getPath(i));
		soundloops[soundloopsDir.getPath(i)] = temp;
	}

	ofDirectory modelsDir("models");
	//only show model files
	modelsDir.allowExt("obj");
	//modelsDir.allowExt("ma");
	//modelsDir.allowExt("mtl");
	//populate the directory object
	modelsDir.listDir();

	//go through and print out all the paths
	for (size_t i = 0; i < modelsDir.size(); i++) {
		std::cout << (modelsDir.getPath(i)) << "\n";
		//ofxAssimpModelLoader temp;
		models[modelsDir.getPath(i)].loadModel(modelsDir.getPath(i));
		models[modelsDir.getPath(i)].setScaleNormalization(false);
		meshes[modelsDir.getPath(i)] = (&models[modelsDir.getPath(i)])->getMesh(0);
	}
}

ResourceManager::~ResourceManager()
{
	for (auto const& x : images)
	{
		images[x.first].clear();
	}
	images.clear();

	for (auto const& x : sounds)
	{
		sounds[x.first].unload();
	}
	sounds.clear();

	for (auto const& x : sounds)
	{
		soundloops[x.first].unload();
	}
	soundloops.clear();

	for (auto const& x : sounds)
	{
		soundloops[x.first].unload();
	}
	soundloops.clear();

	for (auto const& x : models)
	{
		models[x.first].clear();
	}
	models.clear();

	for (auto const& x : meshes)
	{
		meshes[x.first].clear();
	}
	meshes.clear();
}

ofImage* ResourceManager::getImage(std::string path)
{
	return &images[path];
}

ofSoundPlayer* ResourceManager::getSound(std::string path)
{
	return &sounds[path];
}

ofSoundPlayer * ResourceManager::getSoundLoop(std::string path)
{
	return &soundloops[path];
}

void ResourceManager::playSoundLoop(std::string path)
{
	if (!soundloops[path].isPlaying())
	{
		soundloops[path].play();
	}
}

void ResourceManager::stopSoundLoop(std::string path)
{
	if (soundloops[path].isPlaying())
	{
		soundloops[path].stop();
	}
}

ofxAssimpModelLoader* ResourceManager::getModel(std::string path)
{
	return &models[path];
}

ofMesh* ResourceManager::getMesh(std::string path)
{
	return &meshes[path];
}

