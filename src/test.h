#ifndef _TEST_H_
#define _TEST_H_


#include"mesh.h"
#include"type.h"
#include <map>
#include <string>


namespace NA{

     void test_vec3g();

     void test_map();
     
     void test_fileload();



}

void NA::test_vec3g(){

     /*
     //  typedef NA::vec3g<double> vec3;
    std::cout << "hello world" << std::endl;
   
    Vertex p(2,3,4);
    Vertex p1(1,2,3);
    Vertex p2 ;
    p2.setValue(3,4,1);

    p2.attribute->id = 5;
    std::cout << p2.attribute->id << std::endl;
    
    Mesh mymesh;
    mymesh.vertex_list->push_back(&p);
    mymesh.vertex_list->push_back(&p1);
    mymesh.vertex_list->push_back(&p2);

    std::cout << mymesh.vertex_list->at(1)  << std::endl;
    // p.mesh= &mymesh;
    //  Vertex *p_tmp = p.mesh->vertex_list->at(1);

    // std::cout << *p_tmp  << std::endl;
    //std::cout << p.mesh->vertex_size()  << std::endl;

    Face* f = new Face;
    f->setValue(&p, &p1, &p2);
    
    std::cout << *f << std::endl;
     */


}

void NA::test_map(){

     Vertex *p1 = new Vertex;
     p1->setValue(1,2,3);
     Vertex *p2 = new Vertex;
     p2->setValue(2,2,3);
     Vertex *p3 = new Vertex;
     p3->setValue(3,2,3);
    

     Mesh mymesh;
     mymesh.vertex_list->push_back(p1);
     mymesh.vertex_list->push_back(p2);
     mymesh.vertex_list->push_back(p3);

     std::map<string, int> mymap;

     vector<Vertex*> *vl = mymesh.vertex_list;
     
     int num = 0;
     
     for(auto itera = vl->begin(); itera != vl->end(); itera++)
     {
          Vertex *v = *itera;
          double x = v->x;
          double y = v->y;
          double z = v->z;

          char buf_x[1024];

          sprintf(buf_x, "%lf%lf%lf", x,y,z );
          mymesh.vertexMap->insert(Map::value_type(buf_x,num+1));
          
          num++;
     }
     
     double x_ = 3; double y_ = 2; double z_ = 3;
     char buf_y[1024];
     sprintf(buf_y, "%lf%lf%lf", x_,y_,z_ );

     vec3 v_(3,2,3);
     Vertex *v = mymesh.is_exist(&v_);

     
     cout << *v << endl;
    

}


void NA::test_fileload()
{

     string filename = "../data/rabbit.stl";
     NA::Mesh mesh;
     mesh.STL_load(filename);
     
     vector<Face*>* f_ = mesh.vertex_list->at(2)->attribute->faceIncident;

     for(auto iter = f_->begin(); iter != f_->end(); iter++){

          std::cout << **iter << std::endl;

     }
     
    
 
}

  


#endif
