/*
*/
class Product {};

#ifdef Implementation1
class MyProduct : public Product {};
class YourProduct : public Product {};
class TheirProduct : public Product {};
typedef int ProductId;
const int MINE = 1;
const int YOURS = 2;
const int THEIRS = 2;
/*
*/
class Creator {
public:
    virtual Product* Create(ProductId);
};
/*
*/
Product* Creator::Create (ProductId id) {
    if (id == MINE)  return new MyProduct;
    if (id == YOURS) return new YourProduct;
    // repeat for remaining products...

    return 0;
}
/*
*/
class MyCreator : public Creator {
public:
    virtual Product* Create(ProductId);
};
/*
*/
Product* MyCreator::Create (ProductId id) {
    if (id == YOURS)  return new MyProduct;
    if (id == MINE)   return new YourProduct;
        // N.B.: switched YOURS and MINE

    if (id == THEIRS) return new TheirProduct;

    return Creator::Create(id); // called if all others fail
}
/*
*/
#endif
#ifdef Implementation2
/*
*/
class Creator {
public:
    Product* GetProduct();
protected:
    virtual Product* CreateProduct();
private:
    Product* _product;
};
/*
*/
Product* Creator::GetProduct () {
    if (_product == 0) {
        _product = CreateProduct();
    }
    return _product;
}
/*
*/
#endif
#ifdef Implementation3
/*
*/
class Creator {
public:
    virtual Product* CreateProduct() = 0;
};
/*
*/
template <class TheProduct>
class StandardCreator: public Creator {
public:
    virtual Product* CreateProduct();
};
/*
*/
template <class TheProduct>
Product* StandardCreator<TheProduct>::CreateProduct () {
    return new TheProduct;
}
/*
*/
class MyProduct : public Product {
public:
    MyProduct();
    // ...
};

StandardCreator<MyProduct> myCreator;
/*
*/
#endif
/*
*/
#include "C++/MazeParts.H"
/*
*/
class MazeGame {
public:
    Maze* CreateMaze();
/*
*/
// factory methods:
/*
*/
    virtual Maze* MakeMaze() const
        { return new Maze; }
    virtual Room* MakeRoom(int n) const
        { return new Room(n); }
    virtual Wall* MakeWall() const
        { return new Wall; }
    virtual Door* MakeDoor(Room* r1, Room* r2) const
        { return new Door(r1, r2); }
};
/*
*/
Maze* MazeGame::CreateMaze () {
    Maze* aMaze = MakeMaze();
/*
*/
    Room* r1 = MakeRoom(1);
    Room* r2 = MakeRoom(2);
    Door* theDoor = MakeDoor(r1, r2);
/*
*/
    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);
/*
*/
    r1->SetSide(North, MakeWall());
    r1->SetSide(East, theDoor);
    r1->SetSide(South, MakeWall());
    r1->SetSide(West, MakeWall());
/*
*/
    r2->SetSide(North, MakeWall());
    r2->SetSide(East, MakeWall());
    r2->SetSide(South, MakeWall());
    r2->SetSide(West, theDoor);
/*
*/
    return aMaze;
}
/*
*/
class BombedMazeGame : public MazeGame {
public:
    BombedMazeGame();
/*
*/
    virtual Wall* MakeWall() const
        { return new BombedWall; }
/*
*/
    virtual Room* MakeRoom(int n) const
        { return new RoomWithABomb(n); }
};
/*
*/
class EnchantedMazeGame : public MazeGame {
public:
    EnchantedMazeGame();
/*
*/
    virtual Room* MakeRoom(int n) const
        { return new EnchantedRoom(n, CastSpell()); }
/*
*/
    virtual Door* MakeDoor(Room* r1, Room* r2) const
        { return new DoorNeedingSpell(r1, r2); }
protected:
    Spell* CastSpell() const;
};
/*
*/
