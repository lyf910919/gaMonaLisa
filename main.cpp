#include "individual.h"
#include "ga.h"
#include <ctime>
using namespace std;
using namespace cv;

int main()
{
	srand(time(NULL));
	Mat img = imread("E:\\class\\gaMonaLisa\\gaMonaLisa\\target.png", IMREAD_COLOR);
	Ga g(img);
	g.evolve(20, 50, 500000);
	//Individual a(img.cols, img.rows, 50);
	//Ga g(img);
	//while(true)
	//{
	//	a.expression();
	//	Mat b;
	//	a.phenotype.convertTo(b, CV_8UC3);
	//	cout << g.getFitness(a.phenotype) << endl;
	//	imshow("rand", b);
	//	waitKey();
	//	a.mutate();
	//}
	return 0;
}