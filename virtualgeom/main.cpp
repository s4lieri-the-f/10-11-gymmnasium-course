#include "geometry.hpp"

int main() {
    vector<Tetragon * > V;
    Point2D left_botom_Rec (0,0);
    Rectangle Rec (left_botom_Rec, 2.0, 3.0);
    Point2D first_Rh (0,0);
    Point2D second_Rh (sqrt(2)/2.0,sqrt(2)/2.0);
    Point2D third_Rh (1,0);
    Squar Sq(left_botom_Rec, 1);
    Rhombus Rh (first_Rh,second_Rh,third_Rh);
    Point2D A(23,5), B(-2,90), C(11,2), D(-3,-13);
    try {
        Tetragon T(A, B, C, D);
        V.push_back(&T);
    } catch (const PointExeption & e){
        cout << "the system says: " << e.exceptiondata << endl;
    }
    V.push_back(&Rec);
    V.push_back(&Rh);
    V.push_back(&Sq);
    for (const auto & x : V){
        cout<<x->Print()<<' '<< x->Square()<< ' '<<x-> Perimeter()<<endl;
    }
}
