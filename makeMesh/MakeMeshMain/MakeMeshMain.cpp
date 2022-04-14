#include <iostream>
#include "Point.hpp"
#include "Face.hpp"
#include "LabeledPoint.hpp"
#include "List.hpp"
#include "DynamicList.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"
//#include <filesystem>
int main(){

    Point point1(-1,1,0);
    Point point2(0,1,0);
    Point point3(1,0,0);
    Point point4(0,-1,0);
    Point point5(-1,0,0);
    Point* points[5] = {&point1, &point2, &point3, &point4, &point5};
    std::cout << "point1 is " << *points[0] << std:: endl;
    std::cout << "point2 is " << *points[1] << std:: endl;
    std::cout << "point3 is " << *points[2] << std:: endl;
    std::cout << "point4 is " << *points[3] << std:: endl;
    std::cout << "point5 is " << *points[4] << std:: endl;
    LabeledPoint labeledPoint1(1, point1);
    unsigned tempinds[4] = {1,2,3,4};
    List<unsigned> inds(4, tempinds);
    Face a(inds, points);
    std::cout << "face a center is " << a.center() << " face a area is " << a.area() << " normal vector is " << a.normalVector() << " face a is " << a << std::endl;
    Face b (1,2,3, points);
    std::cout << "face b center is " << b.center() << " face b area is " << b.area() << " normal vector is " << b.normalVector() << " face b is " << b << std::endl;
    Face c (0,2,3,4, points);
    std::cout << "face c center is " << c.center() << " face c area is " << c.area() << " normal vector is " << c.normalVector() << " face c is " << c << std::endl;    

    Face *faces[3];
    faces[0] = &a;
    faces[1] = &b;
    faces[2] = &c;
    
    std::cout << "face 1 center is " << faces[0]->center() << " face 1 area is " << faces[0]->area() << " normal vector is " << faces[0]->normalVector() << " face 1 is " << a << std::endl;


    Vector <double> vector1(point1, point2);
    Vector <double> vector2(3,4,5);
    std::cout << "Vector 2 is " << vector2 << std::endl;
    std::cout << "vector 1 is " << vector1 << std::endl;    

    std::cout << "Vector 2 is " << vector2 << std::endl;
    std::cout << "List type is " << inds.type() << " Point type is " << point1.type() << " LabeledPoint type is " << labeledPoint1.type() << std:: endl;
    std::cout << "Vector type is " << vector1.type() << " Face type is " << a.type() << std :: endl;
    point4 = point3;

    std::cout << "Vector1[0] is " << vector1[0] << std::endl;

    std::cout << "point4 now become " << point4 << std::endl;
    point3[0] = 100;
    std::cout << "point3 now is " << point4 << std::endl;
    std::cout << "point4 now is " << point4 << std::endl;
    std::cout << "vector1 is " << vector1 << " vector2 is " << vector2 << std::endl;
    std::cout << "+: " << (vector1 + vector2) << " -: " << (vector1 - vector2) <<  " *: " << (vector1 * vector2) << " &: " << (vector1 & vector2) << std::endl;
    
    DynamicList <unsigned> dynamicList1(List<unsigned>(3));
    std::cout << "dynamicList1 is " << dynamicList1 << std::endl;
    dynamicList1 = List<unsigned> (4);
    std::cout << "dynamicList1 is " << dynamicList1 << std::endl;
    dynamicList1.append(3);
    std::cout << "dynamicList1 is " << dynamicList1 << std::endl;
    
    unsigned** arr;

    arr = new unsigned*[5];

    for(unsigned i = 0; i < 5; i++){
        arr[i] = new unsigned[5];
        for (unsigned j = 1; j < 5; j++){
            arr[i][j] = 1;
            arr[i][i] = i+11;
        }
    }

    Matrix <unsigned> matrix1 (2,5);
    Matrix <unsigned> matrix2 (5,5, arr);
    Matrix <unsigned> matrix3 (5,5, arr);
    for(unsigned i = 0; i < 5; i++){
        for (unsigned j = 1; j < 5; j++){
            matrix3[i][j] = rand()%100;
        }
    }
    Matrix <unsigned> matrix4 (3,3);
    matrix4.setIdentity();
    std::cout << matrix1 [1];
    std::cout << arr[4][4] << std::endl;
    std::cout << "matrix1 is " << std:: endl << matrix1 << std::endl;
    std::cout << "matrix2 is " << std:: endl << matrix2 << std::endl;
    std::cout << "matrix3 is " << std:: endl << matrix3 << std::endl;
    std::cout << "matrix4 is " << std:: endl << matrix4 << std::endl;
    std::cout << "matrix1 is " << "square" << matrix1.ifSquare() << "identity" << matrix1.ifIdentity() << std::endl;
    std::cout << "matrix3 is " << "square" << matrix3.ifSquare() << "identity" << matrix3.ifIdentity() << std::endl;
    std::cout << "matrix4 is " << "square" << matrix4.ifSquare() << "identity" << matrix4.ifIdentity() << std::endl;
    
    std::cout << "matrix2 det() is " << matrix2.det() << std:: endl;
    std::cout << "matrix3 det() is " << matrix3.det() << std:: endl;
    std::cout << "matrix4 det() is " << matrix4.det() << std:: endl;

    std::cout << "matrix2 inverse() is " << matrix2.inverse() << std:: endl;
    std::cout << "matrix3 inverse() is " << matrix3.inverse() << std:: endl;
    std::cout << "matrix4 inverse() is " << matrix4.inverse() << std:: endl;

    std::cout << "matrix2 inverse() & matrix2 is " << (matrix2.inverse() & matrix2.toDouble()) << std:: endl;
    std::cout << "matrix3 inverse() & matrix3 is " << (matrix3.inverse() & matrix3.toDouble()) << std:: endl;
    std::cout << "matrix1 & matrix2 is " << (matrix1 & matrix2) << std:: endl;

    std::cout << "matrix2 + matrix2 is " << std:: endl << matrix2 + matrix2 << std::endl;
    std::cout << "matrix2 - matrix2 is " << std:: endl << matrix2 - matrix2 << std::endl;
    std::cout << "matrix2 * matrix2 is " << std:: endl << matrix2 * matrix2 << std::endl;    
    std::cout << "matrix1 & matrix2 is " << std:: endl << (matrix1 & matrix2) << std::endl;

    Mesh mesh (Point (0,0,0), Point (3,3,3), Vector <double> (1,1,1), "test");
    mesh.write();
    std :: cout << mesh;

    //std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl; 

    for(unsigned i = 0; i < 5; i++){
        delete arr[i];
        }
    delete arr;
}