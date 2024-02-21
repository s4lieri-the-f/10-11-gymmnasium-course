#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class PrintInterface
{
public:
    virtual std::string Print() const = 0;
};

class Point2D
{
public:
    double x, y;
    Point2D(double new_x = 0.0, double new_y = 0.0) : x(new_x), y(new_y){};
    bool operator==(const Point2D &A);
    bool operator<(const Point2D &A);
    friend ostream &operator<<(ostream &out, const Point2D &A);
};

class PointExeption : public std::exception
{
public:
    std::string exceptiondata;
    PointExeption(const char *e) : exceptiondata(e){};
};

class Tetragon : public PrintInterface
{
public:
    Point2D A, B, C, D;
    Tetragon(Point2D a, Point2D b, Point2D c, Point2D d) : A(a), B(b), C(c), D(d)
    {
        if ((a.x == b.x && a.y == b.y) || (c.x == b.x && c.y == b.y) || (c.x == d.x && c.y == d.y) || (a.x == d.x && a.y == d.y))
            throw PointExeption("ur gay");
    };
    Tetragon(Point2D a, Point2D b, Point2D c, bool isrhombus);
    virtual double Square() const;
    virtual double Perimeter() const;
    std::string Print() const override { return "tetragon"; };
};

class Rectangle : virtual public Tetragon
{
public:
    double short_side_, long_side_;
    Rectangle(Point2D start, double a, double b) : Tetragon(start, Point2D(start.x + a, start.y), Point2D(start.x + a, start.y + a), Point2D(start.x + a, start.y + a))
    {
        short_side_ = min(a, b);
        long_side_ = max(a, b);
    };
    double Square() const override { return short_side_ * long_side_; };
    double Perimeter() const override { return 2 * (short_side_ + long_side_); };
    std::string Print() const override { return "rec"; };
};

class Rhombus : virtual public Tetragon
{
public:
    double side_;
    Rhombus(Point2D A, Point2D B, Point2D C);
    double Square() const override;
    double Perimeter() const override { return side_ * 4; };
    std::string Print() const override { return "rhombus"; };
};

class Squar : public Rhombus, public Rectangle
{
    ;

public:
    Squar(Point2D A, double len) : Rhombus(A, Point2D(A.x + len, A.y), Point2D(A.x + len, A.y + len)), Rectangle(A, len, len),
                                   Tetragon(A, Point2D(A.x + len, A.y), Point2D(A.x + len, A.y + len), Point2D(A.x, A.y + len)) {}
    double Square() const override
    {
        return pow(side_, 2);
    }
    double Perimeter() const override
    {
        return 4 * side_;
    }
    std::string Print() const override { return "square"; };
};

bool Point2D::operator==(const Point2D &A)
{
    double d = sqrt(pow((x - A.x), 2) + pow((y - A.y), 2));
    if (d == 0)
        return true;
    else
        return false;
}

ostream &operator<<(ostream &out, const Point2D &A)
{
    out << fixed << setprecision(5) << "(" << A.x << "; " << A.y << ")";
    return out;
}

Rhombus::Rhombus(Point2D a, Point2D b, Point2D c) : Tetragon(a, b, c, true)
{
    side_ = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

double Tetragon::Square() const
{
    Point2D AC(C.x - A.x, C.y - A.y), BD(D.x - B.x, D.y - B.y);
    double scal = AC.x * BD.x + AC.y * BD.y;
    double ACl = sqrt(pow(AC.x, 2) + pow(AC.y, 2));
    double BDl = sqrt(pow(BD.x, 2) + pow(BD.y, 2));
    double alpha = scal / (ACl * BDl);
    return (ACl * BDl * sqrt(1 - pow(alpha, 2))) / 2.0;
}

double Rhombus::Square() const
{
    Point2D AC(C.x - A.x, C.y - A.y), BD(D.x - B.x, D.y - B.y);
    double ACl = sqrt(pow(AC.x, 2) + pow(AC.y, 2));
    double BDl = sqrt(pow(BD.x, 2) + pow(BD.y, 2));
    return (ACl * BDl) / 2;
}

Tetragon::Tetragon(Point2D a, Point2D b, Point2D c, bool isrhombus) : A(a), B(b), D(c)
{
    Point2D M((D.x + B.x) / 2, (D.y + B.y) / 2);
    Point2D d((M.x * 2 - A.x), (M.y * 2 - A.y));
    C = d;
}

double Tetragon::Perimeter() const
{
    Point2D AB(B.x - A.x, B.y - A.y);
    Point2D BC(C.x - B.x, C.y - B.y);
    Point2D CD(D.x - C.x, D.y - C.y);
    Point2D DA(A.x - D.x, A.y - D.y);

    double square = sqrt(pow(AB.x, 2) + pow(AB.y, 2)) + sqrt(pow(BC.x, 2) + pow(BC.y, 2)) + sqrt(pow(CD.x, 2) + pow(CD.y, 2)) + sqrt(pow(DA.x, 2) + pow(DA.y, 2));
    return square;
}