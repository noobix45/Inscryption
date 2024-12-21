#ifndef EXCEPTII_H
#define EXCEPTII_H

#include<stdexcept>

class Exceptie : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

class Font_error : public Exceptie
{
public:
    explicit Font_error(const std::string& path);
};

class Texture_error : public Exceptie
{
public:
    Texture_error(const std::string& class_name, const std::string& path);
};

#endif //EXCEPTII_H
