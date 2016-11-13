#ifndef __MESH_H_
#define __MESH_H_
#include <vector>
#include <fstream>
#include <map>
#include "vecg.h"
#include "line_stream.h"
#include "type.h"


using namespace std;
typedef map<string, int> Map ;


namespace NA{

/****************************************/
     //网格类
     class Mesh{
 
     public:
          Mesh(){}
          ~Mesh();

          int vertex_size(){return vertex_list->size();}
          int edge_size(){return edge_list->size();}
          int face_size(){return face_list->size();}
          Vertex* is_exist(const vec3* v);
          unsigned int STL_load(const std::string& filename);
          unsigned int OBJ_load(const std::string& filename);

     public:
          vector<Vertex*> *vertex_list = new vector<Vertex*>;
          vector<Face*> * face_list = new vector<Face*>;
          vector<Edge*> * edge_list = new vector<Edge*>;
               
          Map *vertexMap = new Map;
            
     };
    
          

}










#endif
