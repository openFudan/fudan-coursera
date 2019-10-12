/*
*/
// Copilation Instructions
// #define Implementation | Consequences | SampleCode
#include "Foundation.H"
#include <iostream.h>
/*
*/
#ifdef Consequences
/*
*/
#ifndef Foundation_H
/*
*/
template <class Item>
class Iterator {
    // ...
    Item CurrentItem() const;
};
/*
*/
#endif
/*
*/
class MyType;
class YourType;
/*
*/
class Visitor {
public:
    // ...
    void VisitMyType(MyType*);
    void VisitYourType(YourType*);
};
/*
*/
#endif
/*
*/
#ifdef Implementation
class ElementA;
class ElementB;
/*
*/
class Visitor {
public:
    virtual void VisitElementA(ElementA*);
    virtual void VisitElementB(ElementB*);

    // and so on for other concrete elements
protected:
    Visitor();
};
/*
*/
class Element {
public:
    virtual ~Element();
    virtual void Accept(Visitor&) = 0;
protected:
    Element();
};
/*
*/
class ElementA : public Element {
public:
    ElementA();
    virtual void Accept(Visitor& v) { v.VisitElementA(this); }
};
/*
*/
class ElementB : public Element {
public:
    ElementB();
    virtual void Accept(Visitor& v) { v.VisitElementB(this); }
};
/*
*/
class CompositeElement : public Element {
public:
    virtual void Accept(Visitor&);
private:
    List<Element*>* _children;
};
/*
*/
void CompositeElement::Accept (Visitor& v) {
    ListIterator<Element*> i(_children);

    for (i.First(); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Accept(v);
    }
    v.VisitCompositeElement(this);
}
/*
*/
#endif Implementation
/*
*/
#ifdef SampleCode
typedef int Watt;
typedef int Currency;
typedef int Power;
class EquipmentVisitor;
class Equipment;
class Card;
class Bus;
class Chassis;
class FloppyDisk;
class Inventory {
  public:
    void Accumulate(Equipment*);
};
/*
*/
class Equipment {
public:
    virtual ~Equipment();

    const char* Name() { return _name; }
/*
*/
    virtual Watt Power();
    virtual Currency NetPrice();
    virtual Currency DiscountPrice();
/*
*/
    virtual void Accept(EquipmentVisitor&);
protected:
    Equipment(const char*);
private:
    const char* _name;
};
/*
*/
class EquipmentVisitor {
public:
    virtual ~EquipmentVisitor();

    virtual void VisitFloppyDisk(FloppyDisk*);
    virtual void VisitCard(Card*);
    virtual void VisitChassis(Chassis*);
    virtual void VisitBus(Bus*);

    // and so on for other concrete subclasses of Equipment
protected:
    EquipmentVisitor();
};
/*
*/
class FloppyDisk : public Equipment {
  public:
    virtual void Accept(EquipmentVisitor&);
};
/*
*/
void FloppyDisk::Accept (EquipmentVisitor& visitor) {
   visitor.VisitFloppyDisk(this);
}
/*
*/
class CompositeEquipment : public Equipment {
  public:
    virtual void Accept(EquipmentVisitor&);
};

class Chassis : public CompositeEquipment {
  public:
    virtual void Accept(EquipmentVisitor&);
    List<Equipment*>* _parts;
};
/*
*/
void Chassis::Accept (EquipmentVisitor& visitor) {
    for (
        ListIterator<Equipment*> i(_parts);
        !i.IsDone();
        i.Next()
    ) {
        i.CurrentItem()->Accept(visitor);
    }
    visitor.VisitChassis(this);
}
/*
*/
class PricingVisitor : public EquipmentVisitor {
public:
    PricingVisitor();

    Currency& GetTotalPrice();
/*
*/
    virtual void VisitFloppyDisk(FloppyDisk*);
    virtual void VisitCard(Card*);
    virtual void VisitChassis(Chassis*);
    virtual void VisitBus(Bus*);
    // ...
private:
    Currency _total;
};
/*
*/
void PricingVisitor::VisitFloppyDisk (FloppyDisk* e) {
    _total += e->NetPrice();
}
/*
*/
void PricingVisitor::VisitChassis (Chassis* e) {
    _total += e->DiscountPrice();
}
/*
*/
class InventoryVisitor : public EquipmentVisitor {
public:
    InventoryVisitor();

    Inventory& GetInventory();
/*
*/
    virtual void VisitFloppyDisk(FloppyDisk*);
    virtual void VisitCard(Card*);
    virtual void VisitChassis(Chassis*);
    virtual void VisitBus(Bus*);
    // ...
/*
*/
private:
    Inventory _inventory;
};
/*
*/
void InventoryVisitor::VisitFloppyDisk (FloppyDisk* e) {
    _inventory.Accumulate(e);
}
/*
*/
void InventoryVisitor::VisitChassis (Chassis* e) {
    _inventory.Accumulate(e);
}
/*
*/
ostream&  operator<<(ostream&, const Inventory&);
void dummy() {
/*
*/
Equipment* component;
InventoryVisitor visitor;

component->Accept(visitor);
cout << "Inventory "
     << component->Name()
     << visitor.GetInventory();
/*
*/
}
/*
*/
#endif
/*
*/
