/*
*/
#ifdef Consequences1
/*
*/
class Composition {
  public:
    void Repair();
    void ComposeWithSimpleCompositor();
    void ComposeWithTeXCompositor();
    int _breakingStrategy;
};
const int SimpleStrategy = 1;
const int TeXStrategy = 2;
/*
*/
void Composition::Repair () {
    switch (_breakingStrategy) {
    case SimpleStrategy:
        ComposeWithSimpleCompositor();
        break;
    case TeXStrategy:
        ComposeWithTeXCompositor();
        break;
    // ...
    }
    // merge results with existing composition, if necessary
}
/*
*/
#endif
/*
*/
#ifdef Consequences2
class Compositor {
    public:
    void Compose();
};
class Composition {
  public:
    void Repair();
    Compositor* _compositor;
};
/*
*/
void Composition::Repair () {
    _compositor->Compose();
    // merge results with existing composition, if necessary
}
/*
*/
#endif
/*
*/
#ifdef Implementation
/*
*/
template <class AStrategy>
class Context {
    void Operation() { theStrategy.DoAlgorithm(); }
    // ...
private:
    AStrategy theStrategy;
};
/*
*/
class MyStrategy {
public:
    void DoAlgorithm();
};

Context<MyStrategy> aContext;
/*
*/
#endif
/*
*/
#ifdef SampleCode
#include "Geom.H"
/*
*/
class Compositor;
class Component;
/*
*/
class Composition {
public:
    Composition(Compositor*);
    void Repair();
private:
    Compositor* _compositor;
    Component* _components;    // the list of components
    int _componentCount;       // the number of components
    int _lineWidth;            // the Composition's line width
    int* _lineBreaks;          // the position of linebreaks
                               // in components
    int _lineCount;            // the number of lines
};
/*
*/
class Compositor {
public:
    virtual int Compose(
        Coord natural[], Coord stretch[], Coord shrink[],
        int componentCount, int lineWidth, int breaks[]
    ) = 0;
protected:
    Compositor();
};
/*
*/
Coord coords[] = {
    1,2,3
};
int b[] = {
    1,2,2
};
/*
*/
void Composition::Repair () {
    Coord* natural;
    Coord* stretchability;
    Coord* shrinkability;
    int componentCount;
    int* breaks;

    // prepare the arrays with the desired component sizes
    // ...
/*
*/
    // kills comiler warnings
    natural = coords;
    stretchability = coords;
    shrinkability = coords;
    componentCount = 1;
    breaks = b;
/*
*/
    // determine where the breaks are:
    int breakCount;
    breakCount = _compositor->Compose(
        natural, stretchability, shrinkability,
        componentCount, _lineWidth, breaks
    );
/*
*/
    // lay out components according to breaks
    // ...
}
/*
*/
class SimpleCompositor : public Compositor {
public:
    SimpleCompositor();

    virtual int Compose(
        Coord natural[], Coord stretch[], Coord shrink[],
        int componentCount, int lineWidth, int breaks[]
    );
    // ...
};
/*
*/
class TeXCompositor : public Compositor {
public:
    TeXCompositor();

    virtual int Compose(
        Coord natural[], Coord stretch[], Coord shrink[],
        int componentCount, int lineWidth, int breaks[]
    );
    // ...
};
/*
*/
class ArrayCompositor : public Compositor {
public:
    ArrayCompositor(int interval);

    virtual int Compose(
        Coord natural[], Coord stretch[], Coord shrink[],
        int componentCount, int lineWidth, int breaks[]
    );
    // ...
};
/*
*/
Composition* quick = new Composition(new SimpleCompositor);
Composition* slick = new Composition(new TeXCompositor);
Composition* iconic = new Composition(new ArrayCompositor(100));
/*
*/
#endif
/*
*/
