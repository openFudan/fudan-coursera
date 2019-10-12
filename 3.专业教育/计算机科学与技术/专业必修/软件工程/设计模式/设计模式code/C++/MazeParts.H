#ifndef MazeParts_H
#define MazeParts_H

#include "defs.H"

enum Direction { North, East, South, West };
#ifndef MapSite_H
#define MapSite_H

class MapSite {
public:
    virtual void Enter() = 0;
};

#endif
#ifndef _H
#define _H

class Room : public MapSite {
public:
    Room(int = 0);
    Room(const Room&);

    virtual Room* Clone() const;
    void InitializeRoomNo(int);

    MapSite* GetSide(Direction);
    void SetSide(Direction, MapSite*);

    virtual void Enter();
private:
    MapSite* _sides[4];
    int _roomNumber;
};
#endif
#ifndef Wall_H
#define Wall_H

class Wall : public MapSite {
public:

    Wall();
    Wall(const Wall&);
    virtual Wall* Clone() const;
    virtual void Enter();
};
#endif
#ifndef Door_H
#define Door_H

class Door : public MapSite {
public:
    Door(Room* = 0, Room* = 0);
    Door(const Room&);

    virtual Door* Clone() const;
    void Initialize(Room*, Room*);
    
    virtual void Enter();
    Room* OtherSideFrom(Room*);
private:
    Room* _room1;
    Room* _room2;
    bool _isOpen;
};
#endif
#ifndef Maze_H
#define Maze_H

class Maze {
public:
    Maze();
    Maze(const Maze&);
    Room* RoomNo(int);
    void AddRoom(Room*);

    virtual Maze* Clone() const;
private:
    // ...
};
#endif
#ifndef BombedWall_H
#define BombedWall_H

class BombedWall : public Wall {
public:
    BombedWall(bool bombed = false);
    BombedWall(const BombedWall&);

    virtual Wall* Clone() const;
    void Intialize(bool);

    virtual void Enter();
private:
    bool _bomb;
};
#endif
#ifndef RoomWithABomb_H
#define RoomWithABomb_H

class RoomWithABomb: public Room {
public:
    RoomWithABomb(int = 0, bool bombed = false);
    RoomWithABomb(const RoomWithABomb&);
    bool HasBomb();
private:
    bool _bomb;
};

#endif
#ifndef EnchantedRoom_H
#define EnchantedRoom_H

class Spell;

class EnchantedRoom : public Room {
public:
    EnchantedRoom(int, Spell* = 0);
    EnchantedRoom(const EnchantedRoom&);
    bool HasSpell();
    Spell PickUpSpell();
private:
    Spell* _spell;
};

#endif
#ifndef DoorNeedingSpell_H
#define DoorNeedingSpell_H

class  DoorNeedingSpell : public Door {
public:
    DoorNeedingSpell(Room*, Room*);
    DoorNeedingSpell(const DoorNeedingSpell&);
    bool TrySpell(Spell);
};
#endif


#endif
