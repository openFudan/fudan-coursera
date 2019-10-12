/*
*/
#include "Geom.H"
// Compilation Instructions
// With ClassAdapter defined and not defined
#define ClassAdapter 0
/*
*/
class Manipulator;
/*
*/
class Shape {
public:
    Shape();
    virtual void BoundingBox(
        Point& bottomLeft, Point& topRight
    ) const;
    virtual Manipulator* CreateManipulator() const;
};
/*
*/
class TextView {
public:
    TextView();
    void GetOrigin(Coord& x, Coord& y) const;
    void GetExtent(Coord& width, Coord& height) const;
    virtual bool IsEmpty() const;
};
/*
*/
#ifdef ClassAdapter
/*
*/
class TextShape : public Shape, private TextView {
public:
    TextShape();

    virtual void BoundingBox(
        Point& bottomLeft, Point& topRight
    ) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;
};
/*
*/
void TextShape::BoundingBox (
    Point& bottomLeft, Point& topRight
) const {
    Coord bottom, left, width, height;

    GetOrigin(bottom, left);
    GetExtent(width, height);
/*
*/
    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
}
/*
*/
bool TextShape::IsEmpty () const {
    return TextView::IsEmpty();
}
/*
*/
class Manipulator {
};
class TextManipulator : public Manipulator {
  public:
    TextManipulator(const TextShape*);
};
/*
*/
Manipulator* TextShape::CreateManipulator () const {
    return new TextManipulator(this);
}
/*
*/
#endif
#ifndef ClassAdapter
class TextView;
class Manipulator {
};
class TextManipulator : public Manipulator {
  public:
    TextManipulator();
};
/*
*/
class TextShape : public Shape {
public:
    TextShape(TextView*);

    virtual void BoundingBox(
        Point& bottomLeft, Point& topRight
    ) const;
    virtual bool IsEmpty() const;
    virtual Manipulator* CreateManipulator() const;
private:
    TextView* _text;
};
/*
*/
TextShape::TextShape (TextView* t) {
    _text = t;
}
/*
*/
void TextShape::BoundingBox (
    Point& bottomLeft, Point& topRight
) const {
    Coord bottom, left, width, height;

    _text->GetOrigin(bottom, left);
    _text->GetExtent(width, height);

    bottomLeft = Point(bottom, left);
    topRight = Point(bottom + height, left + width);
}
/*
*/
bool TextShape::IsEmpty () const {
    return _text->IsEmpty();
}
/*
*/
Manipulator* TextShape::CreateManipulator () const {
    return new TextManipulator(this);
}
/*
*/
#endif
/*
*/
