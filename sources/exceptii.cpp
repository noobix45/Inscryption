#include "exceptii.h"
#include <string>
#include <iostream>

FontError::FontError(const std::string &path): GameError("Unable to load Font: " + path) {}

TextureError::TextureError(const std::string& class_name,const std::string &path):
GameError(class_name + " Unable to load texture at: "+ path) {}

SoundError::SoundError(const std::string &path): GameError("Unable to load sound at: " + path) {}