#ifndef GA_H
#define GA_H
#include "individual.h"

class Ga
{
public:
	Ga(cv::Mat tar): targetImg(tar) {}
	double getFitness(const cv::Mat ind);
	void evolve(int popSize, int chSize, int max_gen);
	void dumpImg(cv::Mat src, int generation);
	cv::Mat targetImg;
};


#endif