#include "individual.h"
#include <cstdlib>
using namespace std;
using namespace cv;

const int DEPTH = 256;
const int MINRADIUS = 5;
const int R_DIV = 3;

Gene::Gene(int w, int h)
{
	center.x = rand() % w;
	center.y = rand() % h;
	color = Scalar(rand() % DEPTH, rand() % DEPTH, rand() % DEPTH);
	radius = MINRADIUS + rand() % ((w < h ? w : h) / R_DIV - MINRADIUS);
	alpha = (1 + rand() % 10) / 10.0;
}

Individual::Individual(int w, int h, int chSize, int mutRate):
w(w), h(h), chSize(chSize), mutRate(mutRate)
{
	chromosome.resize(chSize);
	for(int i = 0; i < chSize; ++i)
	{
		chromosome[i] = Gene(w, h);
	}
	phenotype = Mat(h, w, CV_32FC3, Scalar(0, 0, 0));//initalize phenotype as CV_32FC3 Mat
}

void Individual::crossover(Individual & mate)
{
	int a = rand() % chSize;
	int b = rand() % chSize;
	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	for (int i = a; i <= b; ++i)
	{
		Gene temp = chromosome[i];
		chromosome[i] = mate.chromosome[i];
		mate.chromosome[i] = temp;
	}
}

void Individual::mutate()
{
	for (int i = 0; i < chSize; ++i)
	{
		if (rand() % 100 < mutRate)
		{
			chromosome[i] = Gene(w, h);
		}
	}
}

void Individual::expression()
{
	for (int i = 0; i < chSize; ++i)
	{
		Mat temp(h, w, CV_8UC3, Scalar(0, 0, 0)), a, b;//draw circles on CV_8UC3 Mat
		Mat Mask1(h, w, CV_32FC3, Scalar(1, 1, 1));
		Mat Mask2(h, w, CV_32FC3, Scalar(1, 1, 1));
		double alpha = chromosome[i].alpha;
		circle(temp, chromosome[i].center, chromosome[i].radius, chromosome[i].color, -1);
		circle(Mask1, chromosome[i].center, chromosome[i].radius, Scalar(alpha, alpha, alpha), -1);
		circle(Mask2, chromosome[i].center, chromosome[i].radius, Scalar(1 - alpha, 1 - alpha, 1 - alpha), -1);

		temp.convertTo(a, CV_32FC3);
		a = a.mul(Mask1);
		b = phenotype.mul(Mask2);
		phenotype = a + b;
	}
}