#include <iostream>

using namespace std;

class matrix
{
public:
    int h;
    int w;
    long long int **m = nullptr;

    matrix(int height, int width) ///CONSTRUCTOR
    {
        h = height;
        w = width;
        m = new long long int*[h];
        for (int i = 0; i < h; i++)
        {
            m[i] = new long long int[w];
            for (int j = 0; j < w; j++)
                m[i][j] = 0;
        }
    }

    matrix(const matrix& b) ///COPY CONSTRUCTOR
    {
        h=b.h;
        w=b.w;
        m = new long long int*[h];
        for (int i = 0; i < h; i++)
        {
            m[i] = new long long int[w];
            for (int j = 0; j < w; j++)
                m[i][j] = b.m[i][j];
        }
    }

    matrix(const matrix& b, int y1, int x1, int y2, int x2) ///COPY CONTRUCTOR OF FRAGMENT
    {
      if (y1>y2 || y1>b.h || y2>b.h || x1>x2 || x1>b.w || x2>b.w || y1<1 || y2<1 || x1<1 || x2<1)
      {
        h=1; w=1; m=new long long int*[1]; m[0]=new long long int[1]; m[0][0]=0;
        return;
      }
      h=y2-y1+1;
      w=x2-x1+1;
      m = new long long int*[h];
        for (int i = 0; i < h; i++)
        {
            m[i] = new long long int[w];
            for (int j = 0; j < w; j++)
                m[i][j] = b.m[i+y1-1][j+x1-1];
        }
    }

    ~matrix() ///DESTRUCTOR
    {
        for (int i = 0; i < h; i++)
            delete[] m[i];
        delete[] m;
    }

    matrix& operator=(const matrix& b) ///OVERLOADED ASSIGNMENT
    {
        h = b.h; w = b.w;
        m = new long long int*[h];
        for (int i = 0; i < h; i++)
        {
            m[i] = new long long int[w];
            for (int j = 0; j < w; j++)
                m[i][j] = b.m[i][j];
        }
    }

    matrix operator*(const matrix& b) ///OVERLOADED MULTIPLICATION
    {
        if (w != b.h)
            return matrix(1, 1);
        matrix res(h, b.w);
        for (int i = 0; i < h; i++)
            for (int j = 0; j < b.w; j++)
                for (int k = 0; k < w; k++)
                    res.m[i][j]+=m[i][k]*b.m[k][j];
        return res;
    }

    matrix operator^(const int& b) ///OVERLOADED EXPONENTIATION - !!!MUST BE PUT IN PARENTHESES ()!!!
    {
        if (w != h)
            return matrix(1, 1);

        if (b == 1)
            return *this;

        matrix res(w, w);
        if (b == 0)
        {
            for (int i = 0; i < w; i++)
                res.m[i][i]=1;
            return res;
        }

        res = (*this)^(b/2);
        return res*res*((*this)^(b%2));
    }

    friend istream& operator>>(istream& os, matrix& b) ///OVERLOADED CIN
    {
        for (int i = 0; i < b.h; i++)
            for (int j = 0; j < b.w; j++)
                os >> b.m[i][j];
    }

    friend ostream& operator<<(ostream& os, const matrix& b) ///OVERLOADED COUT
    {
        for (int i = 0; i < b.h; i++)
        {
            for (int j = 0; j < b.w; j++)
                os << b.m[i][j] << " ";
            os << "\n";
        }
        return os;
    }
};

int main()
{
    ///EXAMPLE USE
    matrix fib(2, 2); ///specify height and width.
    fib.m[0][0] = 0; fib.m[0][1] = 1; fib.m[1][0] = 1; fib.m[1][1] = 1; ///fill "m" member.
    int n;
    cin >> n;
    cout << (fib^n) << "\n"; ///fib^n returns a matrix. cout << matrix prints the "m" member on screen.

    int a, b;
    cin >> a >> b; ///read dimensions of new matrix
    matrix Mat(a, b);
    cin >> Mat; ///read matrix
    cout << "\n" << Mat; ///print matrix
    cout << "\n" << Mat*Mat; ///prints the squared matrix if possible. Otherwise prints the 1x1 matrix {0}.
    cout << "\n" << (Mat^7); ///prints the cubed matrix if possible. Otherwise prints the 1x1 matrix {0}.
}
