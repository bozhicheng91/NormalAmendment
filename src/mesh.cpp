#include "mesh.h"
#include <iostream>
#include <algorithm>

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


    /*输出STL文件*/
    unsigned int Mesh::STL_write(const std::string& filename){

        std::ofstream out(filename.c_str()) ;
        if(!out) {
            std::cerr << "could not open file." << std::endl ;         
            return 0 ;
        }

        out << "soild mesh"<< std::endl;
        for(auto iter = face_list->begin(); iter != face_list->end(); iter++){
        
            Face* f = *iter;
            out << "facet normal " << *f->attribute->normal_ << std::endl;
            out << "outer loop " << std::endl;
            out << "vertex " << *f->v->at(0)<< std::endl;
            out << "vertex " << *f->v->at(1)<< std::endl;
            out << "vertex " << *f->v->at(2)<< std::endl;
            out << "endloop" << std::endl;
            out << "endfacet" << std::endl;
        }
        out << "endsoild mesh" << std::endl;

    }


    void Mesh::traverse_mesh(Vertex* vertex){

        vector<Vertex*> vlist_;
        vlist_.push_back(vertex);
        vector<Vertex*> vlist_tmp;
        
        while(vlist_.size() > 0){

            // std::cout << "the loop " << loop << " date is " << std::endl;
            for(auto itera = vlist_.begin(); itera != vlist_.end(); itera++ ){
                Vertex* v_ = *itera;
                vector<Face*> *flist_incident = v_->attribute->faceIncident;

                v_->faceOrientation();
                v_->attribute->flag = 1;
                for(auto iterb = flist_incident->begin(); iterb != flist_incident->end(); iterb++){
                    Face* f_ = *iterb;
                    f_->setVertexNormal();
                    //f_->setVertexFlag();
                    f_->attribute->flag = 1;
                    
                }
                
                for(auto iterb_ = flist_incident->begin(); iterb_ != flist_incident->end(); iterb_++){
                    Face* f1_ = *iterb_;
                    int i = 0;
                    for(; i < 3; i++){
                        Vertex* f1_v = f1_->v->at(i%3);
                        if((f1_v != v_)&&(f1_v->attribute->flag != 1))
                            vlist_tmp.push_back(f1_v);
                    }
                }
                
            }
            
            //删除传播环中的重复点
            sort(vlist_tmp.begin(), vlist_tmp.end());
            vlist_tmp.erase(unique(vlist_tmp.begin(), vlist_tmp.end()), vlist_tmp.end());
        
            for(auto iterc = vlist_tmp.begin(); iterc != vlist_tmp.end(); iterc++){
                Vertex* v_tmp = *iterc;
                v_tmp->attribute->flag = 1;                            //  std::cout << *v_tmp << std::endl;
            }
        
            //更新波前环
            vlist_.swap(vlist_tmp);
            vector<Vertex*>().swap(vlist_tmp);

            // std::cout << vlist_.size() << std::endl;

        }
    }

  
  
}
