#ifndef _TEST_H_
#define _TEST_H_


#include"vecg.h"
#include"type.h"

namespace NA{

     void test_vec3g();





}

void NA::test_vec3g(){

     
     //  typedef NA::vec3g<double> vec3;
    std::cout << "hello world" << std::endl;
   
    vertex p(2,3,4);
    vertex p1(1,2,3);
    vertex p2 ;
    p2.set(3,4,1);
    p2.normal.set(0,0,1);

    mesh mymesh;
    mymesh.vertex_list->push_back(p);
    mymesh.vertex_list->push_back(p1);
    mymesh.vertex_list->push_back(p2);

    std::cout << mymesh.vertex_list->at(1)  << std::endl;
    p.mesh_= &mymesh;
    vertex p_tmp = p.mesh_->vertex_list->at(1);

    std::cout << p_tmp  << std::endl;
    std::cout << p.mesh_->vertex_size()  << std::endl;

/*
    face face(10,23,3);    
    edge edge(200,232);
    std::cout << p.normal  << std::endl;
    std::cout << p.flag  << std::endl;
    std::cout << point << std::endl;
   std::cout << point[1] << std::endl;
    std::cout <<point*2 << std::endl;
    std::cout <<2*point << std::endl;
    std::cout <<dot(point, point1) << std::endl;
    std::cout << face << std::endl;
    std::cout << edge << std::endl;

*/

}

#endif
