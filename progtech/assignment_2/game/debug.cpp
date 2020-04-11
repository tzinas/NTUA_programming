#include <iostream>

using namespace std;

class Person{
    public:
        virtual void doing(){
            cout << "living stuff" << endl;
        }
};

class Doctor: public Person{
    public:
        void doing(){
            cout << "doctor stuff" << endl;
        }
};

class Teacher: public Person{
    public:
        void doing(){
            cout << "teacher stuff" << endl;
        }
};

int main(){
    
    Person **p;
    p = new Person*[4];
    p[0] = new Person;
    p[1] = new Doctor;
    p[2] = new Teacher;

    p[0] -> doing();
    p[1] -> doing();
    p[2] -> doing();
    

    return 0;
}
