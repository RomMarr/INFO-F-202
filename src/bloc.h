#ifdef _BLOC_H
#define _BLOC_H


class Bloc {
    int weight;
    string color;
public: 
    virtual Bloc(int weight, string color) 
    virtual void draw()
    virtual void setWeight(int weight)
    virtual void setColor(string color)
    virtual void move()
    //~Bloc()
}

class Target:public Bloc{
    int weight;
    string color;
public:
    Target(int weight, string color)
    void draw()
    void setWeight(int weight) 
    void setColor(string color) //override ?
    void move()
    //~Target()
}

class Wall:public Bloc{
    int weight;
    string color;
public:
    Wall(int weight, string color)
    void draw()
    void setWeight(int weight) 
    void setColor(string color) //override ?
    void move()
    //~Wall()
}

class Floor:public Bloc{
    int weight;
    string color;
public:
    Floor(int weight, string color)
    void draw()
    void setWeight(int weight) 
    void setColor(string color) //override ?
    void move()
    //~Floor()
}

class Box:public Bloc{
    int weight;
    string color;
public:
    Box(int weight, string color)
    void draw()
    void setWeight(int weight) 
    void setColor(string color) //override ?
    void move()
    //~Box()
}

#endif