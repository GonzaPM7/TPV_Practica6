#pragma once

#include "TexturesManager.h"
#include "AudioManager.h"
#include "FontsManager.h"
#include "RandomNumberGenerator.h"

/*
 *
 */
class ServiceLocator {
public:
	ServiceLocator();
	virtual ~ServiceLocator();

	TexturesManager* getTextures() const;
	AudioManager* getAudios() const;
	FontsManager* getFonts() const;
	RandomNumberGenerator* getRandomGenerator() const;

	void setTextures(TexturesManager* texturesManager);
	void setAudios(AudioManager* audioManager);
	void setFonts(FontsManager* fontsManager);
	void setRandomGenerator(RandomNumberGenerator* randomGenerator);

private:

	TexturesManager* textures_;
	AudioManager* audio_;
	FontsManager* fonts_;
	RandomNumberGenerator* random_;
};

