#ifndef SINGLETON_H
#define SINGLETON_H
//  singleton crtp

template <typename Derived>
class Singleton
{
protected:
    Singleton() =default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static Derived& getInstance()
    {
        static DerivedInstance instance;
        return instance;
    }
    static void initialize(sf::RenderWindow& window,const sf::Font& font,int player_id)
    {
            static DerivedInstance instance(window,font,player_id);
    }

private:
    class DerivedInstance : public Derived
    {
    public:
        DerivedInstance() = default; //pentru fontmanager
        DerivedInstance(sf::RenderWindow& window,const sf::Font& font,int player_id) // pentru end screen
            : Derived{window,font,player_id} {}
    };
};

#endif //SINGLETON_H
