#ifndef USERDATA_H
#define USERDATA_H

	typedef struct RGBcolor{
		unsigned int R;
		unsigned int G;
		unsigned int B;
	}RGB;

	typedef struct Map{
		double x0;
		double y0;
		double xf;
		double yf;
	}cMapp;

	typedef struct userDataType{
		int type;
		double lStart;
		double lEnd;
		double lConstant;
		double leftAngle;
		double rightAngle;
		struct userDataType *Flags;
		int order;
		Map CMap;
		RGBcolor pColor;
	}userData;

#endif