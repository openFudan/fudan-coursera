#include "Geom.H"
#include <iostream.h>

#include "C++/MazeParts.H"

Door::Door (const Door& other) {
    _room1 = other._room1;
    _room2 = other._room2;
}

void Door::Initialize (Room* r1, Room* r2) {
    _room1 = r1;
    _room2 = r2;
}

Door* Door::Clone () const {
    return new Door(*this);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

BombedWall::BombedWall (const BombedWall& other) : Wall(other) {
    _bomb = other._bomb;
}

Wall* BombedWall::Clone () const {
    return new BombedWall(*this);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Factories
#include "C++/MazeFactories.H"
Maze* MazeFactory::MakeMaze() const
        { return new Maze; }
Wall* MazeFactory::MakeWall() const
        { return new Wall; }
Room* MazeFactory::MakeRoom(int n) const
        { return new Room(n); }
Door* MazeFactory::MakeDoor(Room* r1, Room* r2) const
        { return new Door(r1, r2); }

MazeFactory* MazeFactory::_instance = 0;

#ifdef Singleton
MazeFactory* MazeFactory::Instance () {
    if (_instance == 0) {
        _instance = new MazeFactory;
    }
    return _instance;
}

#else
int strcmp(const char*, const char*);
const char* getenv(const char*);

MazeFactory* MazeFactory::Instance () {
    if (_instance == 0) {
        const char* mazeStyle = getenv("MAZESTYLE");

        if (strcmp(mazeStyle, "bombed") == 0) {
            _instance = new BombedMazeFactory;
        } else if (strcmp(mazeStyle, "enchanted") == 0) {
            _instance = new EnchantedMazeFactory;

        // ... other possible subclasses

        } else {        // default
            _instance = new MazeFactory;
        }
    }
    return _instance;
}
#endif


Wall* BombedMazeFactory::MakeWall () const {
    return new BombedWall;
}
Room* BombedMazeFactory::MakeRoom (int n) const {
    return new RoomWithABomb(n);
}

Room* EnchantedMazeFactory::MakeRoom(int n)  const
        { return new EnchantedRoom(n, CastSpell()); }
Door* EnchantedMazeFactory::MakeDoor(Room* r1, Room* r2)  const
        { return new DoorNeedingSpell(r1, r2); }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class MazePrototypeFactory : public MazeFactory {
public:
    MazePrototypeFactory(Maze*, Wall*, Room*, Door*);

    virtual Maze* MakeMaze() const;
    virtual Room* MakeRoom(int) const;
    virtual Wall* MakeWall() const;
    virtual Door* MakeDoor(Room* r1, Room *r2) const;

private:
    Maze* _prototypeMaze;
    Room* _prototypeRoom;
    Wall* _prototypeWall;
    Door* _prototypeDoor;
};

MazePrototypeFactory::MazePrototypeFactory (Maze* m,
                                            Wall* w,
                                            Room* r,
                                            Door* d) {
   _prototypeMaze = m;
   _prototypeWall = w;
   _prototypeRoom = r;
   _prototypeDoor = d;
}

Room* MazePrototypeFactory::MakeRoom(int n) const {
    Room* room = _prototypeRoom->Clone();
    room->InitializeRoomNo(n);
    return room;
}

Maze* MazePrototypeFactory::MakeMaze() const {
    return _prototypeMaze->Clone();
}

Wall* MazePrototypeFactory::MakeWall() const {
    return _prototypeWall->Clone();
}

Door* MazePrototypeFactory::MakeDoor(Room* r1, Room *r2) const {
    Door* door = _prototypeDoor->Clone();
    door->Initialize(r1, r2);
    return door;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class MazeBuilder {
public:
    virtual void BuildMaze() {};
    virtual void BuildRoom(int) {};
    virtual void BuildDoor(int, int) {};

    virtual Maze* GetMaze() { return 0; }
//    virtual Maze* OrphanMaze() { return 0;}

protected:
    MazeBuilder();
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class StandardMazeBuilder  : public MazeBuilder {
public:
    StandardMazeBuilder();

    virtual void BuildMaze();
    virtual void BuildRoom(int);
    virtual void BuildDoor(int, int);

    virtual Maze* OrphanMaze();

private:
    Direction CommonWall(Room*, Room*);
    Maze* _currentMaze;
};

StandardMazeBuilder::StandardMazeBuilder () {
    _currentMaze = 0;
}

void StandardMazeBuilder::BuildMaze () {
    _currentMaze = new Maze;
}

Maze* StandardMazeBuilder::OrphanMaze () {
    Maze* maze =  _currentMaze;
    _currentMaze = 0;
    return maze;
}

void StandardMazeBuilder::BuildRoom (int n) {
    if (!_currentMaze->RoomNo(n)) {
        Room* room = new Room(n);
        _currentMaze->AddRoom(room);

        room->SetSide(North, new Wall);
        room->SetSide(South, new Wall);
        room->SetSide(East, new Wall);
        room->SetSide(West, new Wall);
    }
}

void StandardMazeBuilder::BuildDoor (int n1, int n2) {
    Room* r1 = _currentMaze->RoomNo(n1);
    Room* r2 = _currentMaze->RoomNo(n2);
    Door* d = new Door(r1, r2);
    r1->SetSide(CommonWall(r1,r2), d);
    r2->SetSide(CommonWall(r2,r1), d);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class EnchantedMazeBuilder : public MazeBuilder {
public:
    EnchantedMazeBuilder();

    virtual void BuildMaze();
    virtual void BuildRoom(int);
    virtual void BuildDoor(int, int);

    virtual Maze* OrphanMaze();
private:
    Maze* _enchantedMaze;
    Direction CommonWall(Room*, Room*);
};

class TwistyTurnyPassage : public Room {
public:
    TwistyTurnyPassage();
    virtual void Enter();
};

void EnchantedMazeBuilder::BuildDoor (int n1, int n2) {

    Room* r1 = _enchantedMaze->RoomNo(n1);
    Room* r2 = _enchantedMaze->RoomNo(n2);
    TwistyTurnyPassage* p = new TwistyTurnyPassage;
    Door* d1 = new Door(r1, p);
    Door* d2 = new Door(p, r2);
    r1->SetSide(CommonWall(r1,r2), d1);
    r2->SetSide(CommonWall(r2,r1), d2);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class CountingMazeBuilder : public MazeBuilder {
public:
    CountingMazeBuilder();

    virtual void BuildMaze();
    virtual void BuildRoom(int);
    virtual void BuildDoor(int, int);
    virtual void AddWall(int, Direction);

    void GetCounts(int&, int&) const;
private:
    int _doors;
    int _rooms;
};


CountingMazeBuilder::CountingMazeBuilder () {
    _rooms = _doors = 0;
}
void CountingMazeBuilder::BuildRoom (int) {
    _rooms++;
}
void CountingMazeBuilder::BuildDoor (int, int) {
    _doors++;
}
void CountingMazeBuilder::GetCounts (int& rooms, int& doors) const {
    rooms = _rooms;
    doors = _doors;
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include "C++/MazeGame.H"

class BombedMazeGame : public MazeGame {
public:
    BombedMazeGame();
    virtual Wall* MakeWall()  const
        { return new BombedWall; }
    virtual Room* MakeRoom(int n)  const
        { return new RoomWithABomb(n); }
};


class EnchantedMazeGame : public MazeGame {
public:
    EnchantedMazeGame();

    virtual Room* MakeRoom(int n)  const
        { return new EnchantedRoom(n, WeaveSpell()); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const 
        { return new DoorNeedingSpell(r1, r2); }

protected:
    Spell* WeaveSpell() const;
};


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Maze* MazeGame::CreateMaze() {
    Maze* aMaze = new Maze;
    Room* r1 = new Room(1);
    Room* r2 = new Room(2);
    Door *theDoor = new Door(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(North, new Wall);
    r1->SetSide(East, theDoor);
    r1->SetSide(South, new Wall);
    r1->SetSide(West, new Wall);
    r2->SetSide(North, new Wall);
    r2->SetSide(East, new Wall);
    r2->SetSide(South, new Wall);
    r2->SetSide(West, theDoor);

    return aMaze;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


Maze* MazeGame::CreateMaze (MazeBuilder& builder) {
    builder.BuildMaze();

    builder.BuildRoom(1);
    builder.BuildRoom(2);
    builder.BuildDoor(1, 2);

    return builder.GetMaze();
}

Maze* MazeGame::CreateComplexMaze (MazeBuilder& builder) {
    builder.BuildRoom(1);
    // ...
    builder.BuildRoom(1001);

    return builder.GetMaze();
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Maze* MazeGame::CreateMaze (MazeFactory& factory) {
    Maze* aMaze = factory.MakeMaze();
    Room* r1 = factory.MakeRoom(1);
    Room* r2 = factory.MakeRoom(2);
    Door* aDoor = factory.MakeDoor(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(North, factory.MakeWall());
    r1->SetSide(East, aDoor);
    r1->SetSide(South, factory.MakeWall());
    r1->SetSide(West, factory.MakeWall());
 
    r2->SetSide(North, factory.MakeWall());
    r2->SetSide(East, factory.MakeWall());
    r2->SetSide(South, factory.MakeWall());
    r2->SetSide(West, aDoor);

    return aMaze;
}

Maze* MazeGame::CreateSimpleMaze() {
    Maze* aMaze = MakeMaze();

    Room* r1 = MakeRoom(1);
    Room* r2 = MakeRoom(2);
    Door *theDoor = MakeDoor(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(North, MakeWall());
    r1->SetSide(East, theDoor);
    r1->SetSide(South, MakeWall());
    r1->SetSide(West, MakeWall());
    r2->SetSide(North, MakeWall());
    r2->SetSide(East, MakeWall());
    r2->SetSide(South, MakeWall());
    r2->SetSide(West, theDoor);

    return aMaze;
}

Maze* MazeGame::MakeMaze ()  const {
    return new Maze;
}
Room* MazeGame::MakeRoom (int n) const {
    return new Room(n);
}
Wall* MazeGame::MakeWall ()  const {
    return new Wall;
}
Door* MazeGame::MakeDoor (Room* r1, Room* r2) const {
    return new Door(r1, r2);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// The offsets below are bad, but it makes code appear ok in text
// Simply cut and paste

main() {
MazeGame game;
Maze* maze;

maze = game.CreateMaze();

// Prototype

MazePrototypeFactory prototypeFactory1( new Maze,
                                       new Wall, 
                                       new Room, 
                                       new Door );

maze = game.CreateMaze(prototypeFactory1);

MazePrototypeFactory prototypeFactory2(new Maze,
                                      new BombedWall,
                                      new RoomWithABomb,
                                      new Door);

maze = game.CreateMaze(prototypeFactory2);

// Builder
StandardMazeBuilder  sbuilder;
game.CreateMaze(sbuilder);

maze = sbuilder.GetMaze();

int rooms, doors;
CountingMazeBuilder cbuilder;
game.CreateMaze(cbuilder);
cbuilder.GetCounts(rooms, doors);
cout << "The maze has "
     << rooms << " rooms and "
     << doors << " doors rooms\n";
}


