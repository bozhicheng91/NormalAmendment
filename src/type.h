
#ifndef __TYPE_H_
#define __TYPE_H_

#include"vecg.h"
#include <vector>
using namespace std;



namespace NA{

     class mesh;
     //顶点类
     typedef vec3g<double> Point;
     class vertex : public Point{
          
     public:
          vertex():flag(-1),id(-1){} 
     vertex(double x_, double y_, double z_):Point(x_,  y_,  z_),flag(-1),id(-1){} 

     public:

          int flag;
          int id;
          vec3g<double> normal;
          vector<int>normal_tag;
          vector<int>edges;
          vector<int>facets;
          mesh *mesh_;
     private:
          


     };


     //面片类
    class face{

    public:
         face():v1(-1), v2(-1), v3(-1), flag(-1), id(-1){}
         face(int v1_, int v2_, int v3_):v1(v1_),v2(v2_),v3(v3_), flag(-1), id(-1){}


    public:
         int v1, v2, v3;
         int flag;
         vector<int>edges;
         int id;
         mesh *mesh_;
    private:
         //标准输出面片数据,顶点用id表示
         friend std::ostream& operator<<(std::ostream &os, const face &f){
              os << f.v1 << " " << f.v2 << " " << f.v3 <<"\t"; return os;
         }
         
    };
          

    //边类
    class edge{


    public:
         edge():v1(-1), v2(-1), flag(-1), id(-1){}
         edge(int v1_, int v2_):v1(v1_),v2(v2_){}

    public:
         int v1, v2;
         int flag;
         vector<int>edges;
         int id;
         mesh *mesh_;
    private:
         //标准输出面片数据,顶点用id表示
         friend std::ostream& operator<<(std::ostream &os, const edge &e){
              os << e.v1 << " " << e.v2 <<"\t"; return os;
         }
    };

    //网格类
    class mesh{

    public: 
         int vertex_size(){return vertex_list->size();}
         int edge_size(){return edge_list->size();}
         int face_size(){return face_list->size();}


    public:
         vector<vertex> *vertex_list = new vector<vertex>;
         vector<face> * face_list = new vector<face>;
         vector<edge> * edge_list = new vector<edge>;
   
         
    };
    


}




#endif
