#include <iostream>
#include <omp.h>
using namespace std;


void transpose(int *dst, int *src, int dim)
{
  const int blocksize = 8;
  int i, j, x, y;

#pragma omp parallel for private(j, x, y) collapse (3)
  for (i = 0; i < dim; i += blocksize)
    {
      for (j = 0; j < dim; j += blocksize)
        {
	  for (x = i; (x < dim && x < i+blocksize); x++)
            {
	      for (y = j; (y < dim && y < j+blocksize); y++)
			dst[y*dim + x] = src[x*dim + y];
            }
        }
    }
}



int main()
{
  /*  
    int a[2][2] = {{4, 5},
                   {7, 8}};
    int b[2][2];
    transpose(*b, *a, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
	cout << b[i][j] << " ";
        cout << endl;
    }
  */

  
  int a[10][10] =  {{1,2,3,4,5,6,7,8,9,10},
		    {11,12,13,14,15,16,17,18,19,20},
		    {21,22,23,24,25,26,27,28,29,30},
		    {31,32,33,34,35,36,37,38,39,40}};
  int b[10][10];
  transpose(*b, *a, 10);

  for (int i = 0; i < 10; i++)
    {
      for (int j = 0; j < 10; j++)
	cout << b[i][j] << " ";
      cout << endl;
    }
  
}
