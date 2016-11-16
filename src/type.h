#ifndef __TYPE_H_
#define __TYPE_H_

#include"vecg.h"
#include <vector>
#include <map>
#include <stdlib.h>
using namespace std;



namespace NA{

     class VertexAttribute;
     class EdgeAttribute;
     class FaceAttribute;
     // class Mesh;
   
     //顶点类
     typedef vec3g<double> vec3;
     class Vertex : public vec3{
          
     public:
          Vertex();
          Vertex(double x_, double y_, double z_); 
          ~Vertex();

          void faceOrientation();

     public:

          // Mesh *mesh;
          VertexAttribute* attribute ;

      };


/****************************************/
    //边类
    class Edge{


    public:
         Edge():v1(NULL), v2(NULL){}
         Edge(Vertex* v1_, Vertex* v2_):v1(v1_),v2(v2_){}
         ~Edge();
    public:
       
         Vertex* v1;
         Vertex* v2;
         EdgeAttribute* attribute;
         // Mesh *mesh;
    private:
                  friend std::ostream& operator<<(std::ostream &os, const Edge &e){
              os << e.v1 << " " << e.v2 <<"\t"; return os;
         }
    };

/****************************************/
     //面片类
    class Face{

    public:
         Face();
         Face(Vertex* v1_, Vertex* v2_, Vertex* v3_);
         ~Face();

    public:
    
         vector<Vertex*>* v;
         FaceAttribute *attribute;
         // Mesh *mesh;

    public:

         void inline setValue(Vertex* v1_, Vertex* v2_, Vertex* v3_){ v = new vector<Vertex*> ; v->push_back(v1_);v->push_back(v2_); v->push_back(v3_);  }
         void setVertexNormal();
         void setVertexFlag();

         void setFaceNormal();

    private:
         //标准输出面片数据,顶点用id表示
         friend std::ostream& operator<<(std::ostream &os, const Face &f){
              os << *f.v->at(0) << " " << *f.v->at(1) << " " << *f.v->at(2) <<"\t"; return os;
         }
         
    };

/****************************************/
    //属性类
    class VertexAttribute{
         
    public:

    VertexAttribute():flag(-1), id(-1){}
         ~VertexAttribute(){delete faceIncident; delete normal;}

    public:
         vector<Face*> *faceIncident = new vector<Face*>;
         vec3g<double>* normal = new vec3g<double> ;
         int flag;
         int id;
         
         
    };

    class EdgeAttribute{

    public:
    EdgeAttribute():flag(-1), id(-1){}

    public:
         int flag;
         int id;

    };
    
    class FaceAttribute{

    public:
         FaceAttribute():flag(-1), id(-1){}
         ~FaceAttribute(){delete normal; delete normal_;  delete state;}
         void calculateNormal(){
              *normal_ = *normal;
              for(auto itera = state->begin(); itera != state->end(); itera++){
                   int i = *itera;
                   *normal_ = (*normal_)*i;
                   
             }
              
         }
    public:
         vec3g<double>* normal = new vec3g<double> ;
         vec3g<double>* normal_ = new vec3g<double> ;
         vector<int>* state = new vector<int>;
         int flag;
         int id;

    };



}
#endif
