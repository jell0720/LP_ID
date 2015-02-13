#include "stdafx.h"
#include "histogram.h"
#include <opencv2\opencv.hpp>

using namespace cv;

Histogram::Histogram(){
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
}

void Histogram::setRange(float minValue, float maxValue){
	hranges[0] = minValue;
	hranges[1] = maxValue;
}

float Histogram::getMinValue(){
	return hranges[0];
}

float Histogram::getMaxValue(){
	return hranges[1];
}