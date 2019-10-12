#ifndef MazeGame_H
#define MazeGame_H

class Maze;
class Wall;
class Door;
class Room;

class MazeFactory;
class MazeBuilder;

class MazeGame {
  public:
    Maze* CreateMaze();
    
    Maze* CreateSimpleMaze();
    Maze* CreateMaze(MazeFactory&);
    Maze* CreateMaze(MazeBuilder&);
    
    Maze* CreateComplexMaze (MazeBuilder& builder);
    
// factory methods
    
    virtual Maze* MakeMaze()  const;
    virtual Room* MakeRoom(int n) const;
    virtual Wall* MakeWall()  const;
    virtual Door* MakeDoor(Room* r1, Room* r2) const;
};
#endif
