#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "function.h"

#define DBG printf("%d\n",__LINE__);

static const double eps=1e-6;
static double g (double x)
{
  return cos (x*x);
} 
static double f (double x) 
{
  return exp(x*x);
}

int main (int argc, char **argv )
{
  double a,b, c;
  double first_result; 
  double *values=0;
  struct InitData initdata;
  int i;
  if (argc<2)
    {
      initdata.N=100;
    }
  else
    {
      sscanf (argv[1], "%d", &initdata.N);
    }
  initdata.f=exp;
  initdata.g=g;
  initdata.zero_value=0;
  values = (double *) malloc(initdata.N*sizeof(double));
  a=0;
  DBG;
  first_result=grIntegr(&initdata, a, values);
  DBG;
  b=1/(initdata.N);
  while(first_result*grIntegr(&initdata, b, values)>0) 
    {
      b*=-1.5;
    }
  c=(a+b)/2;
  while (fabs (grIntegr(&initdata, c, values))>eps)
    {
      if (grIntegr(&initdata,a,values)*grIntegr(&initdata,c,values)>0)
	{
	  a=c;
	}
      else b=c;
    }
  grIntegr(&initdata,c,values);
  for (i=0; i!=initdata.N; ++i)
    printf("%20.16lf\n",values[i]);
  free(values);
  return 0;
}
