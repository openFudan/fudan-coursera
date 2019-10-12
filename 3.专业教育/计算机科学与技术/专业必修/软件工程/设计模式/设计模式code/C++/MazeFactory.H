#ifndef MazeFactory_H
#define MazeFactory_H
class Maze;
class Room;
class Wall;
class Door;

class MazeFactory {
public:
    MazeFactory();

#ifndef Singleton
    static MazeFactory* Instance();
#else
    static MazeFactory* Instance();
#endif
    virtual Maze* MakeMaze() const;
    virtual Wall* MakeWall() const;
    virtual Room* MakeRoom(int n) const;
    virtual Door* MakeDoor(Room* r1, Room* r2) const;
protected:
    static MazeFactory* _instance;
};

#endif
