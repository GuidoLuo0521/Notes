#ifndef UNCOPYABLE_H
#define UNCOPYABLE_H
#include <QtCore>

#if false
class Uncopyable {
protected:
    Uncopyable() { };
    ~Uncopyable() { };

private:
    Uncopyable(const Uncopyable&) { };
    Uncopyable& operator = (const Uncopyable&);
};
#else
class Uncopyable {
protected:
    Uncopyable() { };
    ~Uncopyable() { };

private:
    Q_DISABLE_COPY(Uncopyable)
};


#endif

class Objcet : public Uncopyable
{

};

#endif // UNCOPYABLE_H
