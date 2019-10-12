/*
*/
#ifndef Foundation_H
#define Foundation_H
/*
*/
class ostream;
const long DEFAULT_LIST_CAPACITY = 200;
#ifndef defs_h
#define defs_h
/*
*/
typedef int bool;
const int true = 1;
const int false = 0;
/*
*/
#endif
/*
*/
template <class Item>
class List {
public:
    List(long size = DEFAULT_LIST_CAPACITY);
    List(List&);
    ~List();
    List& operator=(const List&);
/*
*/
    long Count() const;
    Item& Get(long index) const;
    Item& First() const;
    Item& Last() const;
    bool Includes(const Item&) const;
/*
*/
    void Append(const Item&);
    void Prepend(const Item&);
/*
*/
    void Remove(const Item&);
    void RemoveLast();
    void RemoveFirst();
    void RemoveAll();
/*
*/
    Item& Top() const;
    void Push(const Item&);
    Item& Pop();
};
/*
*/
template <class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item CurrentItem() const = 0;
protected:
    Iterator();
};
/*
*/
template <class Item>
class ListIterator : public Iterator<Item> {
public:
    ListIterator(const List<Item>* aList);
/*
*/
    virtual void First();
    virtual void Next();
    virtual bool IsDone() const;
    virtual Item CurrentItem() const;
};
/*
*/
typedef float Coord;
/*
*/
class ostream;
class istream;
/*
*/
class Point {
public:
    static const Point& Zero;	
/*
*/
    Point(Coord x = 0.0, Coord y = 0.0);
/*
*/
    Coord X() const;  void X(Coord x);
    Coord Y() const;  void Y(Coord y);
/*
*/
    friend Point& operator+(const Point&, const Point&);
    friend Point& operator-(const Point&, const Point&);
    friend Point& operator*(const Point&, const Point&);
    friend Point& operator/(const Point&, const Point&);
/*
*/
    Point& operator+=(const Point&);
    Point& operator-=(const Point&);
    Point& operator*=(const Point&);
    Point& operator/=(const Point&);
/*
*/
    Point operator-();
/*
*/
    friend bool operator==(const Point&, const Point&);
    friend bool operator!=(const Point&, const Point&);
/*
*/
    friend ostream& operator<<(ostream&, const Point&);
    friend istream& operator>>(istream&, Point&);
};
/*
*/
class Rect {
public:
    static const Rect& Zero;	
/*
*/
    Rect(Coord x, Coord y, Coord w, Coord h);
    Rect(const Point& origin, const Point& extent);
/*
*/
    Coord Width() const;   void Width(Coord);
    Coord Height() const;  void Height(Coord);
    Coord Left() const;    void Left(Coord);
    Coord Bottom() const;  void Bottom(Coord);
/*
*/
    Point& Origin() const; void Origin(const Point&);
    Point& Extent() const; void Extent(const Point&);
/*
*/
    void MoveTo(const Point&);
    void MoveBy(const Point&);
/*
*/
    bool IsEmpty() const;
    bool Contains(const Point&) const;
};
/*
*/
void dummy_found () {
Rect* tmp = new
/*
*/
Rect(Point(0, 0), Point(0, 0));
/*
*/
}
#endif
/*
*/
