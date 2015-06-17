#include "ga.h"
#include <algorithm>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
using namespace cv;

struct Fitness
{
	int ind;
	double fitness;
	Fitness(){}
	Fitness(int i, int f): ind(i), fitness(f){}
	bool operator < (const Fitness & a) const{
		return fitness < a.fitness;
	}
};

double Ga::getFitness(const Mat ind)
{
	Mat tar, dif;
	targetImg.convertTo(tar, CV_32FC3);
	absdiff(tar, ind, dif);
	Scalar dif_total = cv::sum(dif);
	return dif_total[0] + dif_total[1] + dif_total[2];
}

void Ga::evolve(int popSize, int chSize, int max_gen)
{
	vector<Individual> population;
	for(int i = 0; i < popSize; ++i)
	{
		Individual temp(targetImg.cols, targetImg.rows, chSize);
		population.push_back(temp);
	}

	ofstream outfile("E:\\class\\gaMonaLisa\\gaMonaLisa\\fitness.txt", ios::out);
	outfile << std::fixed;
	vector<Fitness> score(popSize);
	for (int i = 0; i < max_gen; ++i)
	{
		cout << "generation " << i << "..." << endl;
		for (int j = 0; j < popSize; ++j)
		{
			population[j].expression();
			score[j].ind = j;
			score[j].fitness = getFitness(population[j].phenotype);
		}
		sort(score.begin(), score.end());
		
		cout << "best fitness: " << score[0].fitness << endl;
		outfile << i << " " << score[0].fitness << endl;
		if (i % 50 == 0)
		{
			dumpImg(population[score[0].ind].phenotype, i);
		}

		//select best half of the population and duplicate them
		for (int j = popSize / 2; j < popSize; ++j)
		{
			population[score[j].ind] = population[score[j - popSize / 2].ind];
		}
		vector<int> mateInd(popSize);
		for (int j = 0; j < popSize; ++j)
			mateInd[j] = j;
		random_shuffle(mateInd.begin(), mateInd.end());
		for (int j = 0; j < popSize; ++j)
		{
			int mate = mateInd[j];
			population[j].crossover(population[mate]);
			population[j].mutate();
			population[mate].mutate();
		}
	}
	outfile.close();
}

void Ga::dumpImg(Mat src, int generation)
{
	Mat b;
	src.convertTo(b, CV_8UC3);
	string name = "E:\\class\\gaMonaLisa\\gaMonaLisa\\generation";
	name += to_string(static_cast<long long>(generation)) + ".png";
	imwrite(name, b);
}