#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#define N 10000
#define NULL 0
const int MAX1=710;
const int MAX2=710;
const int MAX3=710;
const int MAX4=710;
const int MAX5=710;
/******* Continuous object function in (x,y) co-ordinate system *********/
float cont_obj_func_xy (float ic,float jc,int x1,int y1,int x2,int y2,int q11,int q12,int q21,int q22)
{
return
(((((x2-ic)*(y2-jc))/((x2-x1)*(y2-y1)))*q11)+((((ic-x1)*(y2-jc))/((x2-x1)*(y2-y1)))*q21)+((((x2-ic)*(jc-y1))/((x2-
x1)*(y2-y1)))*q12)+((((ic-x1)*(jc-y1))/((x2-x1)*(y2-y1)))*q22));
}
/**************************************************************/
/******* Continuous object function in (r,s) co-ordinate system ******************/
float cont_obj_func_rs (float r,float s,float phi,int xp1,int yp1,int xp2, int yp2,int e11, int e12, int e21,int e22)
{
return
(((((xp2-((r*(cos(phi)))-(s*(sin(phi)))))*(yp2-((r*(sin(phi)))+(s*(cos(phi))))))/((xp2-xp1)*(yp2-
yp1)))*e11)+((((((r*(cos(phi)))-(s*(sin(phi))))-xp1)*(yp2-((r*(sin(phi)))+(s*(cos(phi))))))/((xp2-xp1)*(yp2-
yp1)))*e21)+((((xp2-((r*(cos(phi)))-(s*(sin(phi)))))*(((r*(sin(phi)))+(s*(cos(phi))))-yp1))/((xp2-xp1)*(yp2-
yp1)))*e12)+((((((r*(cos(phi)))-(s*(sin(phi))))-xp1)*(((r*(sin(phi)))+(s*(cos(phi))))-yp1))/((xp2-xp1)*(yp2-yp1)))*e22));
}
/***********************************************************************/
int main()
{
int i,j,n,x008,y008,l,m,k,q,ip1_,ip2_,jp1_,jp2_,f11_,f12_,f21_,f22_,sa,x_im_min,y_im_min,x_im_max,y_im_max,q111,nn;
float *ar1,*ar2[MAX1],*ar6,*ar7;
float *ar3[MAX2][MAX3],*ar4[MAX4],*ar5[MAX5];
float
x007,y007,x0007,y0007,r007,fy,r_min,r_max,del_r,l1,s_min,s_max,xx_,yy_,sum,v,r_,x_min,x_max,y_min,y_max,r1,r2,r3,
r4,p1,p2,p3,i8,j8,l11,q11;
const float PII=3.1415926535;
printf("Enter value of n to create required matrix of order n, you have to enter odd number ");
scanf("%d",&n);
printf("Enter the number of angular views you need, please enter even number:");
scanf("%d",&m);
printf("If highest number of sample point in one projection less than m and if del_r is other than 1 then you have to change
line 60 and 76\n");
printf("Enter the delta r value");scanf("%f",&del_r);
x_min=0;
y_min=0;
x_max=(n-1);
y_max=(n-1);
/****** Defining range of the image grid in (x,y) co-ordinate ********/
x_im_min=-(n-1)/(2);
x_im_max=(n-1)/(2);
y_im_min=-(n-1)/(2);
y_im_max=(n-1)/(2);
/**********************************************************/
nn=n*(1.414213562)+1;
/***** Defining pointer for object ******/
ar1=(float*)calloc(((n)*(n)),sizeof(float));
if(ar1==NULL)
{
printf("No space available for ar1");
exit(1);
}
/**********************************/
/**** Defining pointer for image grid ***************/
ar6=(float*)calloc(((2*x_im_max)*(2*y_im_max)),sizeof(float));
if(ar6==NULL)
{
printf("No space available for ar6");
exit(1);
}
/*********************************************/
/*****Defining pointer for sonogram ******************************/
ar7=(float*)calloc(((nn)*(nn)),sizeof(float));
if(ar7==NULL)
{
printf("No space available for ar7");
exit(1);
}
/*********************************************************/
std::ofstream file1_;
file1_.open("dat301021.txt");for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{
/**** For point source object *****/
/*p1=((i-150)*(i-150))+((j-150)*(j-150))-(10*10);*/
/******************************/
/**** For elliptic object ******/
p1=(((i-200)*(i-200))+(((j-200)*(j-200))*(125*125)/(170*170)))-(125*125);
p2=(((i-150)*(i-150)+(j-150)*(j-150))-(35*35));
/*************************/
/*p3=(((i-250)*(i-250)+(j-250)*(j-250))-(30*30));*/
/**** For circular object *****/
/* p1=((i-50)*(i-50))+((j-50)*(j-50))-(40*40);
p2=((i-40)*(i-40))+((j-40)*(j-40))-(20*20);*/
/*************************/
if(p1<=0)
{
/*if(p3<=0)
{
ar1[i*n+j]=24;
/* file1_ << ar1[i*n+j];*/
/*}*/
if(p2<0)
{
ar1[i*n+j]=20;
file1_ << ar1[i*n+j];
}
else
{
ar1[i*n+j]=10;
file1_ << ar1[i*n+j];
}
}
else
{
ar1[i*n+j]=0;
/*printf("%d",ar1[i*n+j]);*/
file1_ << ar1[i*n+j];
}
/*printf(",");*/file1_ <<",";
}
/*printf("\n");*/
file1_ <<"\n";
}
file1_.close();
/*free(ar1);*/
std::ofstream file_;
file_.open("dat301022.txt");
for (k=0;k<m;k++)
{
fy=(((k)*PII)/(m));
///LOOP FOR ANGULAR VIEW STARTS HERE.....................
r1=x_max*(sin(fy));
r2=(cos(fy))*x_max;
r3=0;
r4=(cos(fy-(PII/2)))*(y_max+(x_max/(tan(fy))));
/******* Calculation of r_min and r_max ************/
if(fy<((PII)/2))
{
if(fy<((PII)/4))
{
if(fy==0.0)
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}
}
else
{
if(fy==((PII)/2))
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=(x_max)*(cos(fy));r_max=(y_max)*(sin(fy));
}
}
/**************************************************************************/
/***** Depending on r_min and r_max we calculate length of projection profile ******************************/
l1=((r_max-r_min)/(del_r));
l=l1+1;
l11=l;
/***********************************************************************************************/
/***** Defining array of pointers for storing #include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include <iostream>
#include <fstream>
#define N 10000
#define NULL 0
const int MAX1=710;
const int MAX2=710;
const int MAX3=710;
const int MAX4=710;
const int MAX5=710;
/******* Continuous object function in (x,y) co-ordinate system *********/
float cont_obj_func_xy (float ic,float jc,int x1,int y1,int x2,int y2,int q11,int q12,int q21,int q22)
{
return
(((((x2-ic)*(y2-jc))/((x2-x1)*(y2-y1)))*q11)+((((ic-x1)*(y2-jc))/((x2-x1)*(y2-y1)))*q21)+((((x2-ic)*(jc-y1))/((x2-
x1)*(y2-y1)))*q12)+((((ic-x1)*(jc-y1))/((x2-x1)*(y2-y1)))*q22));
}
/**************************************************************/
/******* Continuous object function in (r,s) co-ordinate system ******************/
float cont_obj_func_rs (float r,float s,float phi,int xp1,int yp1,int xp2, int yp2,int e11, int e12, int e21,int e22)
{
return
(((((xp2-((r*(cos(phi)))-(s*(sin(phi)))))*(yp2-((r*(sin(phi)))+(s*(cos(phi))))))/((xp2-xp1)*(yp2-
yp1)))*e11)+((((((r*(cos(phi)))-(s*(sin(phi))))-xp1)*(yp2-((r*(sin(phi)))+(s*(cos(phi))))))/((xp2-xp1)*(yp2-
yp1)))*e21)+((((xp2-((r*(cos(phi)))-(s*(sin(phi)))))*(((r*(sin(phi)))+(s*(cos(phi))))-yp1))/((xp2-xp1)*(yp2-
yp1)))*e12)+((((((r*(cos(phi)))-(s*(sin(phi))))-xp1)*(((r*(sin(phi)))+(s*(cos(phi))))-yp1))/((xp2-xp1)*(yp2-yp1)))*e22));
}
/***********************************************************************/
int main()
{
int i,j,n,x008,y008,l,m,k,q,ip1_,ip2_,jp1_,jp2_,f11_,f12_,f21_,f22_,sa,x_im_min,y_im_min,x_im_max,y_im_max,q111,nn;
float *ar1,*ar2[MAX1],*ar6,*ar7;
float *ar3[MAX2][MAX3],*ar4[MAX4],*ar5[MAX5];
float
x007,y007,x0007,y0007,r007,fy,r_min,r_max,del_r,l1,s_min,s_max,xx_,yy_,sum,v,r_,x_min,x_max,y_min,y_max,r1,r2,r3,
r4,p1,p2,p3,i8,j8,l11,q11;
const float PII=3.1415926535;
printf("Enter value of n to create required matrix of order n, you have to enter odd number ");
scanf("%d",&n);
printf("Enter the number of angular views you need, please enter even number:");
scanf("%d",&m);
printf("If highest number of sample point in one projection less than m and if del_r is other than 1 then you have to change
line 60 and 76\n");
printf("Enter the delta r value");scanf("%f",&del_r);
x_min=0;
y_min=0;
x_max=(n-1);
y_max=(n-1);
/****** Defining range of the image grid in (x,y) co-ordinate ********/
x_im_min=-(n-1)/(2);
x_im_max=(n-1)/(2);
y_im_min=-(n-1)/(2);
y_im_max=(n-1)/(2);
/**********************************************************/
nn=n*(1.414213562)+1;
/***** Defining pointer for object ******/
ar1=(float*)calloc(((n)*(n)),sizeof(float));
if(ar1==NULL)
{
printf("No space available for ar1");
exit(1);
}
/**********************************/
/**** Defining pointer for image grid ***************/
ar6=(float*)calloc(((2*x_im_max)*(2*y_im_max)),sizeof(float));
if(ar6==NULL)
{
printf("No space available for ar6");
exit(1);
}
/*********************************************/
/*****Defining pointer for sonogram ******************************/
ar7=(float*)calloc(((nn)*(nn)),sizeof(float));
if(ar7==NULL)
{
printf("No space available for ar7");
exit(1);
}
/*********************************************************/
std::ofstream file1_;
file1_.open("dat301021.txt");for(i=0;i<n;i++)
{
for(j=0;j<n;j++)
{
/**** For point source object *****/
/*p1=((i-150)*(i-150))+((j-150)*(j-150))-(10*10);*/
/******************************/
/**** For elliptic object ******/
p1=(((i-200)*(i-200))+(((j-200)*(j-200))*(125*125)/(170*170)))-(125*125);
p2=(((i-150)*(i-150)+(j-150)*(j-150))-(35*35));
/*************************/
/*p3=(((i-250)*(i-250)+(j-250)*(j-250))-(30*30));*/
/**** For circular object *****/
/* p1=((i-50)*(i-50))+((j-50)*(j-50))-(40*40);
p2=((i-40)*(i-40))+((j-40)*(j-40))-(20*20);*/
/*************************/
if(p1<=0)
{
/*if(p3<=0)
{
ar1[i*n+j]=24;
/* file1_ << ar1[i*n+j];*/
/*}*/
if(p2<0)
{
ar1[i*n+j]=20;
file1_ << ar1[i*n+j];
}
else
{
ar1[i*n+j]=10;
file1_ << ar1[i*n+j];
}
}
else
{
ar1[i*n+j]=0;
/*printf("%d",ar1[i*n+j]);*/
file1_ << ar1[i*n+j];
}
/*printf(",");*/file1_ <<",";
}
/*printf("\n");*/
file1_ <<"\n";
}
file1_.close();
/*free(ar1);*/
std::ofstream file_;
file_.open("dat301022.txt");
for (k=0;k<m;k++)
{
fy=(((k)*PII)/(m));
///LOOP FOR ANGULAR VIEW STARTS HERE.....................
r1=x_max*(sin(fy));
r2=(cos(fy))*x_max;
r3=0;
r4=(cos(fy-(PII/2)))*(y_max+(x_max/(tan(fy))));
/******* Calculation of r_min and r_max ************/
if(fy<((PII)/2))
{
if(fy<((PII)/4))
{
if(fy==0.0)
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}
}
else
{
if(fy==((PII)/2))
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=(x_max)*(cos(fy));r_max=(y_max)*(sin(fy));
}
}
/**************************************************************************/
/***** Depending on r_min and r_max we calculate length of projection profile ******************************/
l1=((r_max-r_min)/(del_r));
l=l1+1;
l11=l;
/***********************************************************************************************/
/***** Defining array of pointers for storing projection profile data *********/
ar2[k]=(float*)calloc((l),sizeof(float));
if(ar2[k]==NULL)
{
printf("No space available for ar2");
exit(1);
}
/*****************************************************************/
/********** Defining array of pointers for storing filtered projection profile data *********/
ar5[k]=(float*)calloc((l),sizeof(float));
if(ar2[k]==NULL)
{
printf("No space available for ar5");
exit(1);
}
/****************************************************************************/
/***** Coefficient matrix for Fourier transformation **************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar3[i][j]=(float*)calloc((2),sizeof(float));
if(ar3[i][j]==NULL)
{
printf("No space available for ar3");
exit(1);
}
}
}
/**********************************************************/
/************ Defining coefficient matrix ************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++){
/*i8=(-l11/2)+((l11)/(l11-1))*i;*/
i8=(-l11/2)+((l11)/(l11-1))*i;
ar3[i][j][0]=cos(2*(PII/l)*i8*j);
ar3[i][j][1]=-sin(2*(PII/l)*i8*j);
///REAL PART...........................................
///COMPLEX PART...................................
}
}
/**********************************************************************************/
for(q=0;q<l;q++)
{
///R LOOP STARTS HERE..................................................
r_=(r_min+((q)*del_r));
/******* Depending r_min and r_max we calculate integration limits s_min and s_max here ********************/
if(fy==0)
{
s_min=x_min;
s_max=x_max;
}
else if(fy<=((PII)/4))
{
if(r_<=r1)
{
s_min=-r_*(tan(fy));
s_max=r_/(tan(fy));
}
else if(r_>=r2)
{
s_min=((r_*(cos(fy)))-x_max)/(sin(fy));
s_max=(y_max-r_*(sin(fy)))/(cos(fy));
}
else
{
s_min=-r_*tan(fy);
s_max=(y_max-r_*sin(fy))/(cos(fy));
}
}
else if(fy>(PII/4))
{
if(fy<(PII))
{
if(fy<=(3*PII/4))
{
if(fy<(PII/2))
{if(r_<=r2)
{
s_min=(y_min-r_*sin(fy))/(cos(fy));
s_max=((r_-x_min*cos(fy)-r_*sin(fy)*sin(fy))/(sin(fy)*cos(fy)));
}
else if(r_>=r1)
{
s_min=-((x_max-r_*cos(fy))/(sin(fy)));
s_max=(x_max-r_*sin(fy))/(cos(fy));
}
else
{
s_min=-((x_max-r_*cos(fy))/(sin(fy)));
s_max=r_/(tan(fy));
}
}
else
{
if(fy==PII/2)
{
s_min=-x_max;
s_max=-x_min;
}
else if(r_<=r3)
{
s_min=-(x_max/(cos(fy-(PII/2))))-((r_)/((sin(fy-PII/2))*(cos(fy-PII/2))))+((r_)/(tan(fy-
PII/2)));
s_max=r_/(tan(fy-(PII/2)));
}
else if(r_>=r4)
{
s_max=r_/(tan(fy));
s_min=((x_max-r_*sin(fy))/(cos(fy)));
}
else
{
s_min=-((x_max-r_*cos(fy))/((cos(fy))*(tan(fy))));
s_max=-r_*(tan(fy-(PII/2)));
}
}
}
else
{
if(r_<=r4)
{
s_min=-(1/(sin(PII-fy)))*(y_max+((r_)/(cos(PII-fy))))+r_*tan(PII-fy);
s_max=r_*(tan(PII-(fy)));
}
else if((r_-r3)>=0)
{
s_max=-r_*(tan(fy-(PII/2)));s_min=-((r_/(tan(fy-(PII/2))))+((y_max-(r_/(cos(fy-(PII/2)))))/(cos(PII-fy))));
}
else
{
s_min=((x_max-r_*sin(fy))/(cos(fy)));
s_max=-r_*tan(fy);
}
}
}
}
else
{
s_min=0;
s_max=0;
}
/*************************************************************************************************/
/******* Integration is done here ************/
sum=0;
for(v=s_min;v<=s_max;v+=0.1)
{
xx_=r_*(cos(fy))-v*(sin(fy));
yy_=r_*(sin(fy))+v*(cos(fy));
ip1_=xx_;
if(ip1_==(n-1))
{ip2_=ip1_-1;}
else
{ip2_=ip1_+1;}
jp1_=yy_;
if(jp1_==(n-1))
{jp2_=jp1_-1;}
else
{jp2_=jp1_+1;}
f11_=ar1[ip1_*n+jp1_];
f12_=ar1[ip1_*n+jp2_];
f21_=ar1[ip2_*n+jp1_];
f22_=ar1[ip2_*n+jp2_];
sum=sum+(cont_obj_func_rs (r_,v,fy,ip1_,jp1_,ip2_,jp2_,f11_,f12_,f21_,f22_))*0.1; ///INTEGRATION STEP=0.1...
}
ar2[k][q]=sum;
q11=(nn/2)+q-(l1/2);
q111=q11;
ar7[k*nn+q111]=ar2[k][q];
///STORING DATA FOR PRINTING SINOGRAM........................................................
/********** Coefficients in Fourier space ***************/
ar4[q]=(float*)calloc((2),sizeof(float));
if(ar4[q]==NULL)
{printf("No space available for ar4");
exit(1);
}
/*************************************************/
}
/******* Calculating real and imaginary part of Fourier spectrum amplitudes ****************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar4[i][0]=ar4[i][0]+(ar3[i][j][0])*(ar2[k][j]);
}
}
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar4[i][1]=ar4[i][1]+(ar3[i][j][1])*(ar2[k][j]);
}
}
/*********************************** Filtering ****************************************************/
for(i=0;i<l;i++)
{
ar4[i][0]=((ar4[i][0])*(fabs(i-l1/2)/(l1/2)));
///RAMP
/*ar4[i][0]=((ar4[i][0])*(l1/PII)*(sin((fabs(i-l1/2))*(PII/l1))));*/
///SHEPP-LOGAN
/*ar4[i][0]=((ar4[i][0])*(1/l1)*(fabs(i-l1/2))*(1+cos((PII*(i-l1/2))/(l1/2))));*/ ///HANN
}
for(i=0;i<l;i++)
{
ar4[i][1]=((ar4[i][1])*(fabs(i-l1/2)/(l1/2)));
///RAMP
/*ar4[i][1]=((ar4[i][1])*(l1/PII)*(sin((fabs(i-l1/2))*(PII/l1))));*/
///SHEPP-LOGAN
/*ar4[i][1]=((ar4[i][1])*(1/l1)*(fabs(i-l1/2))*(1+cos((PII*(i-l1/2))/(l1/2))));*/ ///HANN
}
/*********************Redefining coefficient matrix for inverse DFT **********************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
/*j8=(-l11/2)+((l11)/(l11-1))*j;*/
j8=(-l11/2)+((l11)/(l11-1))*j;
ar3[i][j][1]=sin(2*(PII/l)*i*j8);
ar3[i][j][0]=cos(2*(PII/l)*i*j8);
}
}
/*********** Filtered projection profile data set ***************/for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar5[k][i]=ar5[k][i]+((ar3[i][j][0])*(ar4[j][0]))-((ar3[i][j][1])*(ar4[j][1])); ///ONLY REAL PART TAKEN........
}
ar5[k][i]=((ar5[k][i])/(l));
}
/********* Freeing memory used by ar3 inside the loop ************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
free(ar3[i][j]);
}
}
/********* Freeing memory used by ar4 inside the loop *************/
for(i=0;i<l;i++)
{
free(ar4[i]);
}
}
/********************************BACKPROJECTION************************************************/
for (k=0;k<m;k++)
{
fy=(((k)*PII)/(m));
if(fy<((PII)/2))
{
if(fy<((PII)/4))
{
if(fy==0.0)
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}}
else
{
if(fy==((PII)/2))
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=(x_max)*(cos(fy));
r_max=(y_max)*(sin(fy));
}
}
l1=((r_max-r_min)/(del_r));
l=l1+1;
for(q=0;q<l;q++)
{
r_=(r_min+((q)*del_r));
r007=r_-((r_max+r_min)/2);
x007=r007*cos(fy);
y007=r007*sin(fy);
///MID-POINT DETECTION.........................................................................................
/// TRANFORMATION TO RECTANGULAR CO-ORDINATE.......................................
/*******************************Storing data in image grid ************************************/
if (fy==0)
{
for(i=0;i<(2*y_im_max);i++)
{
y007=y_im_min+(i);
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
///WHEN SIMPLE BACKPROJECTION
OUTPUT NEEDED REPALCE ALL ar5s BY ar2...........................................................................................................................................
}
}
if(fy==(PII/2))
{
for(i=0;i<(2*x_im_max);i++)
{
x007=x_im_min+(i);
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}else
{
if(fy<(3*PII/4))
{
if(fy<(PII/4))
{
x0007=r007*cos(fy);
y0007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007+(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
x007=r007*cos(fy);
y007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007-(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
}
else
{
x0007=r007*cos(fy);
y0007=r007*sin(fy);
for(i=0;i<(x_im_max);i++)
{
x007=x0007+(i);
y007=((x0007-x007)/(tan(fy)))+y0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
x007=r007*cos(fy);
y007=r007*sin(fy);
for(i=0;i<(x_im_max);i++)
{
x007=x0007-(i);
y007=((x0007-x007)/(tan(fy)))+y0007;if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
}
}
else
{
x0007=r007*cos(fy);
y0007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007+(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
x007=r007*cos(fy);
y007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007-(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
}
}
} /// END OF R LOOP
} /// END OF ANGLE LOOP
/*************Matching dimensionality of the image with object and printing image output *******************/
for(i=0;i<(2*x_im_max);i++)
{
for(j=0;j<(2*y_im_max);j++)
{
ar6[i*(2*x_im_max)+j]=((ar6[i*(2*x_im_max)+j])/m);
file_ << ar6[i*(2*x_im_max)+j];
file_ << ",";
}
file_<<"\n";
}
/**********************************************************************************************//********** Printing sonogram data set ****************/
/*
for(i=0;i<nn;i++)
{
for(j=0;j<nn;j++)
{
file_ << ar7[i*nn+j];
file_ << ",";
}
file_ << "\n";
}
*/
/************************************************/
file_.close();
free(ar1);
for(i=0;i<m;i++)
{
free(ar2[i]);
free(ar5[i]);
}
free(ar6);
free(ar7);
}projection profile data *********/
ar2[k]=(float*)calloc((l),sizeof(float));
if(ar2[k]==NULL)
{
printf("No space available for ar2");
exit(1);
}
/*****************************************************************/
/********** Defining array of pointers for storing filtered projection profile data *********/
ar5[k]=(float*)calloc((l),sizeof(float));
if(ar2[k]==NULL)
{
printf("No space available for ar5");
exit(1);
}
/****************************************************************************/
/***** Coefficient matrix for Fourier transformation **************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar3[i][j]=(float*)calloc((2),sizeof(float));
if(ar3[i][j]==NULL)
{
printf("No space available for ar3");
exit(1);
}
}
}
/**********************************************************/
/************ Defining coefficient matrix ************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++){
/*i8=(-l11/2)+((l11)/(l11-1))*i;*/
i8=(-l11/2)+((l11)/(l11-1))*i;
ar3[i][j][0]=cos(2*(PII/l)*i8*j);
ar3[i][j][1]=-sin(2*(PII/l)*i8*j);
///REAL PART...........................................
///COMPLEX PART...................................
}
}
/**********************************************************************************/
for(q=0;q<l;q++)
{
///R LOOP STARTS HERE..................................................
r_=(r_min+((q)*del_r));
/******* Depending r_min and r_max we calculate integration limits s_min and s_max here ********************/
if(fy==0)
{
s_min=x_min;
s_max=x_max;
}
else if(fy<=((PII)/4))
{
if(r_<=r1)
{
s_min=-r_*(tan(fy));
s_max=r_/(tan(fy));
}
else if(r_>=r2)
{
s_min=((r_*(cos(fy)))-x_max)/(sin(fy));
s_max=(y_max-r_*(sin(fy)))/(cos(fy));
}
else
{
s_min=-r_*tan(fy);
s_max=(y_max-r_*sin(fy))/(cos(fy));
}
}
else if(fy>(PII/4))
{
if(fy<(PII))
{
if(fy<=(3*PII/4))
{
if(fy<(PII/2))
{if(r_<=r2)
{
s_min=(y_min-r_*sin(fy))/(cos(fy));
s_max=((r_-x_min*cos(fy)-r_*sin(fy)*sin(fy))/(sin(fy)*cos(fy)));
}
else if(r_>=r1)
{
s_min=-((x_max-r_*cos(fy))/(sin(fy)));
s_max=(x_max-r_*sin(fy))/(cos(fy));
}
else
{
s_min=-((x_max-r_*cos(fy))/(sin(fy)));
s_max=r_/(tan(fy));
}
}
else
{
if(fy==PII/2)
{
s_min=-x_max;
s_max=-x_min;
}
else if(r_<=r3)
{
s_min=-(x_max/(cos(fy-(PII/2))))-((r_)/((sin(fy-PII/2))*(cos(fy-PII/2))))+((r_)/(tan(fy-
PII/2)));
s_max=r_/(tan(fy-(PII/2)));
}
else if(r_>=r4)
{
s_max=r_/(tan(fy));
s_min=((x_max-r_*sin(fy))/(cos(fy)));
}
else
{
s_min=-((x_max-r_*cos(fy))/((cos(fy))*(tan(fy))));
s_max=-r_*(tan(fy-(PII/2)));
}
}
}
else
{
if(r_<=r4)
{
s_min=-(1/(sin(PII-fy)))*(y_max+((r_)/(cos(PII-fy))))+r_*tan(PII-fy);
s_max=r_*(tan(PII-(fy)));
}
else if((r_-r3)>=0)
{
s_max=-r_*(tan(fy-(PII/2)));s_min=-((r_/(tan(fy-(PII/2))))+((y_max-(r_/(cos(fy-(PII/2)))))/(cos(PII-fy))));
}
else
{
s_min=((x_max-r_*sin(fy))/(cos(fy)));
s_max=-r_*tan(fy);
}
}
}
}
else
{
s_min=0;
s_max=0;
}
/*************************************************************************************************/
/******* Integration is done here ************/
sum=0;
for(v=s_min;v<=s_max;v+=0.1)
{
xx_=r_*(cos(fy))-v*(sin(fy));
yy_=r_*(sin(fy))+v*(cos(fy));
ip1_=xx_;
if(ip1_==(n-1))
{ip2_=ip1_-1;}
else
{ip2_=ip1_+1;}
jp1_=yy_;
if(jp1_==(n-1))
{jp2_=jp1_-1;}
else
{jp2_=jp1_+1;}
f11_=ar1[ip1_*n+jp1_];
f12_=ar1[ip1_*n+jp2_];
f21_=ar1[ip2_*n+jp1_];
f22_=ar1[ip2_*n+jp2_];
sum=sum+(cont_obj_func_rs (r_,v,fy,ip1_,jp1_,ip2_,jp2_,f11_,f12_,f21_,f22_))*0.1; ///INTEGRATION STEP=0.1...
}
ar2[k][q]=sum;
q11=(nn/2)+q-(l1/2);
q111=q11;
ar7[k*nn+q111]=ar2[k][q];
///STORING DATA FOR PRINTING SINOGRAM........................................................
/********** Coefficients in Fourier space ***************/
ar4[q]=(float*)calloc((2),sizeof(float));
if(ar4[q]==NULL)
{printf("No space available for ar4");
exit(1);
}
/*************************************************/
}
/******* Calculating real and imaginary part of Fourier spectrum amplitudes ****************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar4[i][0]=ar4[i][0]+(ar3[i][j][0])*(ar2[k][j]);
}
}
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar4[i][1]=ar4[i][1]+(ar3[i][j][1])*(ar2[k][j]);
}
}
/*********************************** Filtering ****************************************************/
for(i=0;i<l;i++)
{
ar4[i][0]=((ar4[i][0])*(fabs(i-l1/2)/(l1/2)));
///RAMP
/*ar4[i][0]=((ar4[i][0])*(l1/PII)*(sin((fabs(i-l1/2))*(PII/l1))));*/
///SHEPP-LOGAN
/*ar4[i][0]=((ar4[i][0])*(1/l1)*(fabs(i-l1/2))*(1+cos((PII*(i-l1/2))/(l1/2))));*/ ///HANN
}
for(i=0;i<l;i++)
{
ar4[i][1]=((ar4[i][1])*(fabs(i-l1/2)/(l1/2)));
///RAMP
/*ar4[i][1]=((ar4[i][1])*(l1/PII)*(sin((fabs(i-l1/2))*(PII/l1))));*/
///SHEPP-LOGAN
/*ar4[i][1]=((ar4[i][1])*(1/l1)*(fabs(i-l1/2))*(1+cos((PII*(i-l1/2))/(l1/2))));*/ ///HANN
}
/*********************Redefining coefficient matrix for inverse DFT **********************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
/*j8=(-l11/2)+((l11)/(l11-1))*j;*/
j8=(-l11/2)+((l11)/(l11-1))*j;
ar3[i][j][1]=sin(2*(PII/l)*i*j8);
ar3[i][j][0]=cos(2*(PII/l)*i*j8);
}
}
/*********** Filtered projection profile data set ***************/for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
ar5[k][i]=ar5[k][i]+((ar3[i][j][0])*(ar4[j][0]))-((ar3[i][j][1])*(ar4[j][1])); ///ONLY REAL PART TAKEN........
}
ar5[k][i]=((ar5[k][i])/(l));
}
/********* Freeing memory used by ar3 inside the loop ************/
for(i=0;i<l;i++)
{
for(j=0;j<l;j++)
{
free(ar3[i][j]);
}
}
/********* Freeing memory used by ar4 inside the loop *************/
for(i=0;i<l;i++)
{
free(ar4[i]);
}
}
/********************************BACKPROJECTION************************************************/
for (k=0;k<m;k++)
{
fy=(((k)*PII)/(m));
if(fy<((PII)/2))
{
if(fy<((PII)/4))
{
if(fy==0.0)
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}
}
else
{
r_min=0.0;
r_max=((sin(fy))*y_max)+((cos(fy))*x_max);
}}
else
{
if(fy==((PII)/2))
{
r_min=0.0;
r_max=x_max;
}
else
{
r_min=(x_max)*(cos(fy));
r_max=(y_max)*(sin(fy));
}
}
l1=((r_max-r_min)/(del_r));
l=l1+1;
for(q=0;q<l;q++)
{
r_=(r_min+((q)*del_r));
r007=r_-((r_max+r_min)/2);
x007=r007*cos(fy);
y007=r007*sin(fy);
///MID-POINT DETECTION.........................................................................................
/// TRANFORMATION TO RECTANGULAR CO-ORDINATE.......................................
/*******************************Storing data in image grid ************************************/
if (fy==0)
{
for(i=0;i<(2*y_im_max);i++)
{
y007=y_im_min+(i);
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
///WHEN SIMPLE BACKPROJECTION
OUTPUT NEEDED REPALCE ALL ar5s BY ar2...........................................................................................................................................
}
}
if(fy==(PII/2))
{
for(i=0;i<(2*x_im_max);i++)
{
x007=x_im_min+(i);
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}else
{
if(fy<(3*PII/4))
{
if(fy<(PII/4))
{
x0007=r007*cos(fy);
y0007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007+(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
x007=r007*cos(fy);
y007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007-(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
}
else
{
x0007=r007*cos(fy);
y0007=r007*sin(fy);
for(i=0;i<(x_im_max);i++)
{
x007=x0007+(i);
y007=((x0007-x007)/(tan(fy)))+y0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
x007=r007*cos(fy);
y007=r007*sin(fy);
for(i=0;i<(x_im_max);i++)
{
x007=x0007-(i);
y007=((x0007-x007)/(tan(fy)))+y0007;if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
}
}
else
{
x0007=r007*cos(fy);
y0007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007+(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
x007=r007*cos(fy);
y007=r007*sin(fy);
for(i=0;i<(y_im_max);i++)
{
y007=y0007-(i);
x007=(y0007-y007)*(tan(fy))+x0007;
if(x007>x_im_max)
{
break;
}
else if(x007<x_im_min)
{
break;
}
else if(y007>y_im_max)
{
break;
}
else if(y007<y_im_min)
{
break;
}
else
{
x008=x007+(x_im_max);
y008=y007+(y_im_max);
ar6[x008*2*x_im_max+y008]=ar6[x008*2*x_im_max+y008]+ar5[k][q];
}
}
}
}
} /// END OF R LOOP
} /// END OF ANGLE LOOP
/*************Matching dimensionality of the image with object and printing image output *******************/
for(i=0;i<(2*x_im_max);i++)
{
for(j=0;j<(2*y_im_max);j++)
{
ar6[i*(2*x_im_max)+j]=((ar6[i*(2*x_im_max)+j])/m);
file_ << ar6[i*(2*x_im_max)+j];
file_ << ",";
}
file_<<"\n";
}
/**********************************************************************************************//********** Printing sonogram data set ****************/
/*
for(i=0;i<nn;i++)
{
for(j=0;j<nn;j++)
{
file_ << ar7[i*nn+j];
file_ << ",";
}
file_ << "\n";
}
*/
/************************************************/
file_.close();
free(ar1);
for(i=0;i<m;i++)
{
free(ar2[i]);
free(ar5[i]);
}
free(ar6);
free(ar7);
}