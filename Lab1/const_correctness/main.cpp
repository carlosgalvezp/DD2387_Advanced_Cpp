int foo(int x) {return x;}
int fooc(const int x) {return x;}
int foorefc(const int & x) {return x;}
int fooref(int & x) {return x;}

int & rfoo(int x) {return x;}
//int & rfooc(const int x) {return x;}
//int & rfoorefc(const int & x) {return x;}
int & rfooref(int & x) {return x;}

const int & crfoo(int x) {return x;}
const int & crfooc(const int x) {return x;}
const int & crfoorefc(const int & x) {return x;}
const int & crfooref(int & x) {return x;}

int main() {
    int a = 1;
    const int* p1 = &a;
    int* const p2 = &a;

    p1 = 0;
    p2 = 0;
}

//struct A {
//    int m_x;

//    int foo(int x) {
//        m_x = 3;
//        return x;
//    }
//    int foo(int x) const {
//        m_x = 3;
//        return x;
//    }

//    // int fooc(const int x) {  o.s.v



//}; // by the way this semicolon important
