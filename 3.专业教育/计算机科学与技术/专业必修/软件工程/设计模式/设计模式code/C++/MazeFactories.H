#ifndef BombedMazeFactory_H
#define BombedMazeFactory_H
#include "MazeFactory.H"

class BombedMazeFactory : public MazeFactory {
public:
    BombedMazeFactory();
    virtual Wall* MakeWall() const;
    virtual Room* MakeRoom(int n) const;
};
#endif
#ifndef EnchantedMazeFactory_H
#define EnchantedMazeFactory_H
#include "MazeFactory.H"
class Spell;
class EnchantedMazeFactory : public MazeFactory {
public:
    EnchantedMazeFactory();

    virtual Room* MakeRoom(int n)  const;
    virtual Door* MakeDoor(Room* r1, Room* r2) const;

protected:
    Spell* CastSpell() const;
};
#endif
