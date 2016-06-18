#include <iostream>
#include <string>
#include <cmath>
using namespace std;

float linedis(float x, float y, float m, float c){
	//to get the distance of a point from a line y=m*x+c
	// assuming my pixels to be arranged on a grid, with each pixel of integer coordinates
	//and each pixel center with integer coordinates.Each center has integer coordinates
	float dist;
	
	dist=(m*(x)-(y)+c)/sqrt(1+m*m);
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
	int x,y,m,c;

	cin>>x>>y>>m>>c;

	cout<<linepass(x,y,m,c);

	return 0;
}