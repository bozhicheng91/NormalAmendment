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

    void Vertex:: faceOrientation(){
        
        vector<Face*> *flist = attribute->faceIncident;
        for(auto itera = flist->begin(); itera != flist->end(); itera++){
            Face* f = *itera;
            if(f->attribute->flag == 1)
                continue;
            double ret = dot(*this->attribute->normal, *f->attribute->normal);
            // std::cout << ret << std::endl;
            if(ret <= 0)
                f->attribute->state->push_back(-1);
            else
                f->attribute->state->push_back(1);
                
            
        }
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

    void Face::setVertexNormal(){

        setFaceNormal();
       *v->at(0)->attribute->normal =  *v->at(1)->attribute->normal = *v->at(2)->attribute->normal = *attribute->normal_;
    }

    void Face::setVertexFlag(){
        
        v->at(0)->attribute->flag =  v->at(1)->attribute->flag = v->at(2)->attribute->flag = 1;
    }


    void Face::setFaceNormal(){
        
        *attribute->normal_ = *attribute->normal;
        for(auto itera = attribute->state->begin(); itera != attribute->state->end(); itera++){
            int i = *itera;
            *attribute->normal_ = (*attribute->normal_)*i;
            if(i < 0)
                swap(v->at(0), v->at(1));
            
        }
    }
}
