#include"helper_functions.h"
#include<math.h>

double euclideanDistance(double x1, double x2, double y1, double y2)
{
	double Xdiff = (x2 - x1) * (x2 - x1);
	double Ydiff = (y2 - y1) * (y2 - y1);
	double distance = sqrt(Xdiff + Ydiff);
	return distance;
}
