#ifndef _LINE_STREAM__
#define _LINE_STREAM__

#include <iostream>
#include <sstream>

namespace NA {

    /**
     * 
     LineInputStream 对ASCII文件一行一行进行解析
     */
    class LineInputStream {
    public:
        LineInputStream(std::istream& in) : in_(in), line_in_(0) {   }
        ~LineInputStream() { delete line_in_ ; line_in_ = 0 ;  }
        //是否到达文件末尾
        bool eof() const { return in_.eof() ; }
        //是否到达一行的末尾
        bool eol() const { return line_in_ == 0 || line_in_->eof() ; }
        bool ok() const { return in_ != 0; }
        void get_line() { 
            in_.getline(buffer_, 65536) ; 
            delete line_in_ ; 
            line_in_ = new std::istringstream(buffer_) ;   
        }
        std::istream& line() { return *line_in_ ;    }
        const char *current_line() const { return buffer_;  }
        template <class T> LineInputStream& operator>>(T& param) { *line_in_ >> param; return *this;  }
    private:
        std::istream& in_ ;
        //istringstream对象可以绑定一行字符串, 然后以空格为分隔符将该行分割开来.
        std::istringstream* line_in_ ;
        char buffer_[65536] ;
    } ;

}

#endif
