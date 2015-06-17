#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <opencv2/opencv.hpp>
#include <vector>

struct Gene
{
	cv::Point center;
	int radius;
	cv::Scalar color;
	double alpha;
	Gene(int w, int h);
	Gene(){};
};

class Individual
{
public:
	Individual(int w, int h, int chSize, int mutRate = 10);
	void crossover(Individual & mate);
	void mutate();
	void expression(); //draw all circles onto phenotype
	cv::Mat phenotype; //a CV_32FC3 Mat, convert to CV_8UC3 when expression
private:
	std::vector<Gene> chromosome;
	int chSize;
	int w, h;
	int mutRate;
};

#endif