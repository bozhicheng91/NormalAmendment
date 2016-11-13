#ifndef __VECG_H_
#define __VECG_H_

#include <iostream>
#include <cfloat>

namespace NA{

     template<class T>
          struct vec3g{
                             
               typedef vec3g<T> thisclass;
               
              
               vec3g():x(0),y(0),z(0){}
               vec3g(T x_in, T y_in, T z_in):x(x_in), y(y_in), z(z_in){}
             
               /*主要运算符重载*/
               template<class T1>
               friend std::ostream& operator<<(std::ostream &os, const vec3g<T1> &v){ os << v.x << " " << v.y << " " << v.z <<"\t"; return os;}

               template<class T1>
               friend std::istream& operator>>(std::istream &is, const vec3g<T1> &v){return is >> v.x >> v.y >> v.z;}


               inline thisclass operator+ (const thisclass& v) const {return thisclass(x+v.x, y+v.y, z+v.z); }
               inline thisclass operator- (const thisclass& v) const {return thisclass(x-v.x, y-v.y, z-v.z); }

               template <class T2> 
               inline thisclass operator* (T2 s) const {return thisclass(x*T(s), y*T(s), z*T(s)); }
               template <class T2> 
               friend inline thisclass operator* (T2 s, thisclass& v){return thisclass(v.x*T(s), v.y*T(s), v.z*T(s));}

               template <class T2> inline thisclass operator/ (T2 s) const {return thisclass(x/T(s), y/T(s), z/T(s)); }

   
               inline thisclass operator- () const {return thisclass(-x, -y, -z);}
             


               inline T& operator[](int idx) {
                    switch(idx) {
                    case 0: return x ; break ;
                    case 1: return y ; break ;
                    case 2: return z ; break ;
                    }
                    return x ;
               }

               inline const T& operator[](int idx) const {
                    switch(idx) {
                    case 0: return x ; break ;
                    case 1: return y ; break ;
                    case 2: return z ; break ;
                    }
                    return x ;
               }
        

               void inline setValue(T x_in, T y_in, T z_in){ x= x_in; y = y_in; z = z_in;}

               //成员数据
               T x;
               T y;
               T z;


          };

 

     //定义点成
     template <class T> inline T dot(const vec3g<T>& v1, const vec3g<T>& v2) {  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;  }

     //定义差乘
     template <class T> inline  vec3g<T> cross(const vec3g<T>& v1, const vec3g<T>& v2) {
          return vec3g<T>(
               v1.y*v2.z - v1.z*v2.y,
               v1.z*v2.x - v1.x*v2.z,
               v1.x*v2.y - v1.y*v2.x
               ) ;
     }


}







#endif

