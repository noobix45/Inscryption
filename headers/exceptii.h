#ifndef EXCEPTII_H
#define EXCEPTII_H

#include<stdexcept>

class GameError : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class FontError : public GameError
{
public:
    explicit FontError(const std::string& path);
};

class TextureError : public GameError
{
public:
    TextureError(const std::string& class_name, const std::string& path);
};

class SoundError : public GameError
{
    public:
    explicit SoundError(const std::string& path);
};

#endif //EXCEPTII_H
