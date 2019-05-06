#include "ServiceLocator.h"

ServiceLocator::ServiceLocator() :
		textures_(nullptr), audio_(nullptr), fonts_(nullptr), random_(nullptr) {
}

ServiceLocator::~ServiceLocator() {
}

TexturesManager* ServiceLocator::getTextures() const {
	return textures_;
}

AudioManager* ServiceLocator::getAudios() const {
	return audio_;
}

void ServiceLocator::setTextures(TexturesManager* texturesManager) {
	textures_ = texturesManager;
}

void ServiceLocator::setAudios(AudioManager* audioManager) {
	audio_ = audioManager;
}

FontsManager* ServiceLocator::getFonts() const {
	return fonts_;
}

RandomNumberGenerator* ServiceLocator::getRandomGenerator() const {
	return random_;
}

void ServiceLocator::setFonts(FontsManager* fontsManager) {
	fonts_ = fontsManager;
}

void ServiceLocator::setRandomGenerator(
		RandomNumberGenerator* randomGenerator) {
	random_ = randomGenerator;
}
