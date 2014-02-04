//
//  main.cpp
//  AimCalc
//
//  Created by Robbie Markwick on 1/20/14.
//  Copyright (c) 2014 Robbie Markwick. All rights reserved.
//

#include <iostream>
#include <math.h>
//g=9.8
//k=0.14917
const double k=0.14917;
const double g=9.8;
const double theta=M_PI/4;
const double targetHeight=2.57175;
const double releaseHeight=1.524;
const double margin=0.1;

int main(int argc, const char * argv[])
{
	while (true) {
		std::cout<<"Please enter your distance:\n";
		double x0;
		std::cin>>x0;
		double high=20,low=0;
		while (true) {
			double v0=(high+low)/2;
			double y=releaseHeight,vx=v0*cos(theta),vy=v0*sin(theta);
			for (double x=0; x<x0;) {
				vx-=(k*vx*vx)*0.01;
				vy-=(g+k*vy*fabs(vy))*0.01;
				double dx=vx*0.01;
				double dy=vy*0.01;
				if(dx+x>x0){
					double p=(x0-x)/dx;
					dx*=p;
					dy*=p;
				}
				x+=dx;
				y+=dy;
				if(y<releaseHeight)break;
			}
			if(y>targetHeight+margin){//To high
				high=v0;
				std::cout<<v0<<": HIGH\n";
			}
			else if(y<targetHeight-margin){//To low
				low=v0;
				std::cout<<v0<<": LOW\n";
			}
			else{//Good
				std::cout<<std::endl<<std::endl<<v0<<": PERFECT\n";
				break;
			}
		}
	}
	// insert code here...
    return 0;
}

