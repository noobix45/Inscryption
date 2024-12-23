#include "exceptii.h"
#include <string>
#include <iostream>

Font_error::Font_error(const std::string &path): Exceptie("Unable to load Font: " + path) {}

Texture_error::Texture_error(const std::string& class_name,const std::string &path):
Exceptie(class_name + " Unable to load texture at: "+ path) {}

Sound_error::Sound_error(const std::string &path): Exceptie("Unable to load sound at: " + path) {}
