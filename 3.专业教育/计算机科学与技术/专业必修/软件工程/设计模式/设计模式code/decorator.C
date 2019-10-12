/*
*/
class VisualComponent;
class Window {
  public:
    void SetContents (VisualComponent* contents);
};
/*
*/
class VisualComponent {
public:
    VisualComponent();

    virtual void Draw();
    virtual void Resize();
    // ...
};
/*
*/
class Decorator : public VisualComponent {
public:
    Decorator(VisualComponent*);
/*
*/
    virtual void Draw();
    virtual void Resize();
    // ...
private:
    VisualComponent* _component;
};
/*
*/
void Decorator::Draw () {
    _component->Draw();
}

void Decorator::Resize () {
    _component->Resize();
}
/*
*/
class BorderDecorator : public Decorator {
public:
    BorderDecorator(VisualComponent*, int borderWidth);

    virtual void Draw();
private:
    void DrawBorder(int);
private:
    int _width;
};
/*
*/
void BorderDecorator::Draw () {
    Decorator::Draw();
    DrawBorder(_width);
}
/*
*/
void Window::SetContents (VisualComponent* contents) {
    // ...
}
/*
*/
class ScrollDecorator : public Decorator {
public:
    ScrollDecorator(VisualComponent*);
};

class TextView : public VisualComponent {
};
main () {
/*
*/
Window* window = new Window;
TextView* textView = new TextView;
/*
*/
window->SetContents(textView);
/*
*/
window->SetContents(
    new BorderDecorator(
        new ScrollDecorator(textView), 1
    )
);
/*
*/
}
/*
*/
class Stream {
  public:
    virtual void PutInt(int);
    virtual void PutString(const char*);
};

class StreamDecorator : public Stream {
  public:
    StreamDecorator(Stream*);
  private:
    Stream* _component;
};

class CompressingStream : public StreamDecorator {
  public:
    CompressingStream(Stream*);
};

class ASCII7Stream : public Stream {
  public:
    ASCII7Stream(Stream*);
};
class FileStream : public Stream {
  public:
    FileStream(const char*);
};

void dummy() {

/*
*/
Stream* aStream = new CompressingStream(
    new ASCII7Stream(
         new FileStream("aFileName")
    )
);
aStream->PutInt(12);
aStream->PutString("aString");
/*
*/
}
/*
*/
