#pragma once

#include <opencv2\opencv.hpp>

using namespace cv;

class Histogram {

private:
	int histSize[1];
	float hranges[2];
	const float* ranges[1];
	int channels[1];

public:
	Histogram();
	void setRange(float minValue, float maxValue);
	float getMinValue();
	float getMaxValue();

	// Sets the number of bins in histogram.
	// By default it is 256.
	void setNBins(int nbins) {

		histSize[0] = nbins;
	}

	// Gets the number of bins in histogram.
	int getNBins() {

		return histSize[0];
	}

	// Computes the 1D histogram.
	cv::MatND getHistogram(const cv::Mat &image) {

		cv::MatND hist;

		// Compute histogram
		cv::calcHist(&image,
			1,			// histogram of 1 image only
			channels,	// the channel used
			cv::Mat(),	// no mask is used
			hist,		// the resulting histogram
			1,			// it is a 1D histogram
			histSize,	// number of bins
			ranges		// pixel value range
			);

		return hist;
	}

	// Computes the 1D histogram and returns an image of it.
	cv::Mat getHistogramImage(const cv::Mat &image){

		// Compute histogram first
		cv::MatND hist = getHistogram(image);

		// Get min and max bin values
		double maxVal = 0;
		double minVal = 0;
		cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

		// Image on which to display histogram
		cv::Mat histImg(histSize[0], histSize[0], CV_8U, cv::Scalar(255));

		// set highest point at 90% of nbins
		int hpt = static_cast<int>(0.9*histSize[0]);

		// Draw vertical line for each bin 
		for (int h = 0; h < histSize[0]; h++) {

			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			cv::line(histImg, cv::Point(h, histSize[0]), cv::Point(h, histSize[0] - intensity), cv::Scalar::all(0));
		}

		return histImg;
	}

	// Equalizes the source image.
	Mat equalize(const Mat &image) {

		Mat result;
		equalizeHist(image, result);

		return result;
	}
};

