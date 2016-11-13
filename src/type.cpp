#include "type.h"

namespace NA{



    //顶点类构造函数实现
    Vertex::Vertex(){

        attribute = new VertexAttribute;
    } 

    Vertex::Vertex(double x_, double y_, double z_){ 
        attribute = new VertexAttribute;
        x = x_; 
        y = y_; 
        z = z_;
    }
    
    Vertex::~Vertex(){delete attribute;};

    Edge::~Edge(){
        delete attribute;
    }

    //面片类构造函数实现
    Face::Face(){
        attribute = new FaceAttribute;
        v = new vector<Vertex*>;
    }

    
    Face::Face(Vertex* v1_, Vertex* v2_, Vertex* v3_){
        v = new vector<Vertex*> ;
        v->push_back(v1_); 
        v->push_back(v2_); 
        v->push_back(v3_); 
    }

    Face::~Face(){
        delete v;
        delete attribute;
    }


}
