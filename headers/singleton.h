#ifndef SINGLETON_H
#define SINGLETON_H
//  singleton crtp

template <typename Derived>
class Singleton
{
protected:
    Singleton() = default;
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    static Derived& getInstance() {
        if constexpr (std::is_default_constructible_v<Derived>)
            if(!instance)
                instance = new DerivedInstance;
        return *instance;
    }
    // ~Singleton()
    // {
    //     if (instance)
    //     {
    //         delete instance;
    //         instance = nullptr;
    //     }
    // }
    template <typename... Args>
    static void init(Args&&... args) {
        if(!instance)
            instance = new DerivedInstance(std::forward<Args>(args)...);
    }
    static void destroyInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }
private:
    class DerivedInstance : public Derived
    {
    public:
        template <typename... Args>
        explicit DerivedInstance(Args&&... args) : Derived(std::forward<Args>(args)...) {}
    };
    static Derived* instance;
};
template<typename Derived>
Derived* Singleton<Derived>::instance = nullptr;

#endif //SINGLETON_H
