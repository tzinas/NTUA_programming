#include <iostream>  
  
#define MAXN 100005  
  
using namespace std;  
  
template <typename T>  
class stack {  
    public:  
        stack (int size) {  
            sz = size;
            A = new T[sz];
            end = 0;  
        }  
        stack (const stack &s) {  
            A = new T[s.sz];
            sz = s.sz;
            for(int i=0; i<s.end; i++){  
                A[i] = s.A[i];  
            }  
            end = s.end;  
        }  
        ~stack (){
            delete [] A;
        }  
        const stack & operator = (const stack &s) {  
            delete [] A;
            A = new T[s.sz];
            sz = s.sz;
            for(int i=0; i<s.end; i++){  
                A[i] = s.A[i];  
            }  
            end = s.end;  
            return *this;  
        }  
  
        bool empty () {  
            return end == 0;  
        }  
        void push (const T &x) {  
            A[end++] = x;   
        }  
        T pop () {  
            return A[--end];  
        }  
        int size () {  
            return end;  
        }  
  
        friend ostream & operator << (ostream &out, const stack &s) {  
            out << "[";  
            if(s.end != 0){  
                for(int i=0; i < s.end - 1; i++){  
                    out << s.A[i] << ", ";  
                }  
                out << s.A[s.end - 1];  
            }  
            out << "]";  
            return out;  
        }  
  
    private:  
        int sz;
        T *A;  
        int end;  
};
