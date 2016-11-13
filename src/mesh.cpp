#include "mesh.h"
#include <iostream>

namespace NA{


    Mesh::~Mesh(){

        for(auto itera = vertex_list->begin(); itera != vertex_list->end(); itera++){

            delete *itera;
        }

        for(auto iterb = edge_list->begin(); iterb != edge_list->end(); iterb++){

            delete *iterb;
        }

        for(auto iterc = face_list->begin(); iterc != face_list->end(); iterc++){

            delete *iterc;
        }

        vector<Vertex*>().swap(*vertex_list);
        vector<Edge*>().swap(*edge_list);
        vector<Face*>().swap(*face_list);

        delete vertex_list;
        delete edge_list;
        delete face_list;

        delete vertexMap;

    }

   
    /*判断点v是否已存在于顶点链表中, 若存在返回顶点指针, 否则返回 NULL*/
    Vertex* Mesh::is_exist(const vec3* v){
 

        double x = v->x;
        double y = v->y;
        double z = v->z;
        char buf_[1024];
        sprintf(buf_, "%lf%lf%lf", x,y,z );

        Map::iterator iter;
        iter = vertexMap->find(buf_);
        if(iter != vertexMap->end())
            {
                int id = iter->second;
                if (id-1 > vertex_list->size())
                    {
                        std::cout << "ERROR / IS_EXIST: data id is out range !! " << std::endl;
                        exit(0);
                    }
                Vertex* v = vertex_list->at(id-1);
                return v;
            }
        else 
            return NULL;

    }


    /*读入STL点云文件, 并解析点面间入射关系*/
    unsigned int Mesh::STL_load(const std::string& filename){
      
        std::cerr << "Mesh:STL file Loading " << filename << std::endl ;
        std::ifstream input(filename.c_str()) ;
        if(!input) {
            std::cerr << "could not open file." << std::endl ;
            return 0 ;
        }

        LineInputStream in(input) ;
     
        Face* face_;
        
        while(!in.eof()){

            in.get_line();
            std::string keyword ;
            in >> keyword;
           if(keyword == "facet"){
                std::string tmp;
                double x,y,z;
                in >> tmp >> x >> y >> z;
              
                face_ = new Face;
                face_->attribute->normal->setValue(x,y,z);
                face_list->push_back(face_);
                
                
                
           }else if(keyword == "vertex"){
               double x_,y_,z_;
               in >> x_ >> y_ >> z_;
               vec3 p_;
               p_.setValue(x_, y_, z_);
               Vertex *v_;
               if(!is_exist(&p_)){
                   v_ = new Vertex(x_, y_, z_);
                   vertex_list->push_back(v_);
                   char buf_[1024];
                   sprintf(buf_, "%lf%lf%lf", x_,y_,z_ );
                   vertexMap->insert(Map::value_type(buf_, vertex_size()));
                   v_->attribute->faceIncident->push_back(face_);
               }else{
                   v_ = is_exist(&p_);
                   v_->attribute->faceIncident->push_back(face_);
               }

               face_->v->push_back(v_);
                
           }else{
               continue;
           }
        }
    }
    
    /*读入OBJ点云文件, 并解析点面间入射关系*/
    unsigned int OBJ_load(const std::string& filename){
        
    }
  
  
}
