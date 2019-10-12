/*
*/
#ifdef Implementation1
/*
*/
class Singleton {
public:
    static Singleton* Instance();
protected:
    Singleton();
private:
    static Singleton* _instance;
};
/*
*/
Singleton* Singleton::_instance = 0;

Singleton* Singleton::Instance () {
    if (_instance == 0) {
        _instance = new Singleton;
    }
    return _instance;
}
/*
*/
#endif
/*
*/
#ifdef Implementation2
#include "List.H"
#include "stdlib.h"
class NameSingletonPair;

/*
*/
class Singleton {
public:
    static void Register(char* name, Singleton*);
    static Singleton* Instance();
protected:
    static Singleton* Lookup(const char* name);
private:
    static Singleton* _instance;
    static List<NameSingletonPair>* _registry;
};
/*
*/
Singleton* Singleton::Instance () {
    if (_instance == 0) {
        const char* singletonName = getenv("SINGLETON");
        // user or environment supplies this at startup

        _instance = Lookup(singletonName);
        // Lookup returns 0 if there's no such singleton
    }
    return _instance;
}
/*
*/
class MySingleton : public Singleton {
public:
    MySingleton();
};
/*
*/
MySingleton::MySingleton() {
    // ...
    Singleton::Register("MySingleton", this);
}
/*
*/
static MySingleton theSingleton;
/*
*/
#endif
/*
*/
#ifdef Singleton
/*
*/
class MazeFactory {
public:
    static MazeFactory* Instance();

    // existing interface goes here
protected:
    MazeFactory();
private:
    static MazeFactory* _instance;
};
/*
*/
MazeFactory* MazeFactory::_instance = 0;

MazeFactory* MazeFactory::Instance () {
    if (_instance == 0) {
        _instance = new MazeFactory;
    }
    return _instance;
}
/*
*/
#else
//MazeFactory* MazeFactory::_instance = 0;
#include "C++/MazeFactories.H"
#include "stdlib.h"
#include "strings.h"
/*
*/
MazeFactory* MazeFactory::Instance () {
    if (_instance == 0) {
        const char* mazeStyle = getenv("MAZESTYLE");
/*
*/
        if (strcmp(mazeStyle, "bombed") == 0) {
            _instance = new BombedMazeFactory;
/*
*/
        } else if (strcmp(mazeStyle, "enchanted") == 0) {
            _instance = new EnchantedMazeFactory;
/*
*/
        // ... other possible subclasses
/*
*/
        } else {        // default
            _instance = new MazeFactory;
        }
    }
    return _instance;
}
/*
*/
#endif
/*
*/
