#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

//take line y=mx+c.
// extend it to a all its pixels lying on the line.

float linedis(float x, float y, float m, float c){
	//to get the distance of a point from a line y=m*x+c
	// assuming my pixels to be arranged on a grid, with each pixel of integer coordinates
	//and each pixel center with integer coordinates.Each center has integer coordinates
	float dist;
	
	dist=abs((m*x-y+c)/sqrt(1+m*m));
	return dist;
	
}

bool linepass(float x, float y, float m, float c){
	//to check if the pixel lies on the line or not, 
	//if line passes through any part of pixel then yes.
	if(linedis(x,y,m,c)<0.707) return 1;
	else return 0;
	//cout<<linedis(x,y,m,c);
}



int main(){

	int image[51][51]={};
	//memset(&image,0,sizeof(image));
	float m,c,c1,c2;
	c1=0;c2=0;
	cin>>m;//>>c;

	//This is the line extension part.11 lines
	while (linedis(0,0,m,c1)<=36 &&  linedis(0,0,m,c2)<=36){
		for(int i=-25;i<=25;i+=1){
			int y=(m*(i)+c1);
			int y1=y,y2=y;
			 if(y<26 && y>-26) image[i+25][y+25]=linepass(i,y,m,c1);
			 while(linepass(i,y1,m,c1)!=0 && linepass(i,y2,m,c1)!=0 && y1<26 && y1>-26 && y2<26 && y2>-26){
			 	image[i+25][y1+25]=linepass(i,y1,m,c1);
			 	image[i+25][y2+25]=linepass(i,y2,m,c1);
			 	y1++;
			 	y2--;
			 }
		}
		for(int i=-25;i<=25;i+=1){
			int y=(m*(i)+c2);
			int y1=y,y2=y;
			 if(y<26 && y>-26) image[i+25][y+25]=linepass(i,y,m,c2);
			 while(linepass(i,y1,m,c2)!=0 && linepass(i,y2,m,c2)!=0 && y1<26 && y1>-26 && y2<26 && y2>-26){
			 	image[i+25][y1+25]=linepass(i,y1,m,c2);
			 	image[i+25][y2+25]=linepass(i,y2,m,c2);
			 	y1++;
			 	y2--;
			 }
		}
		c1+=sqrt(1+m*m);
		c2-=sqrt(1+m*m);
	}





//Outputting the array
	for(int i=0;i<51;i++){
		for(int j=0;j<51;j++){
			cout<<image[50-j][i];//<<linedis(i-25,j-25,m,c);//<<"\t";
		}
		cout<<"\n";
	}

	ofstream a_file ( "output.txt" );
		for(int i=0;i<51;i++){
			for(int j=0;j<51;j++){
				a_file<<image[50-j][i]<<"\t";//<<linedis(i-25,j-25,m,c);//<<"\t";
			}
			a_file<<"\n"; // Outputs to output.txt through a_file in all instances
		}
	  a_file.close();// Close the file stream explicitly







	return 0;
}
