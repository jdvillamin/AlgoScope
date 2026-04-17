#include <stdio.h>
#include <math.h>

double roundoff(double num, int n);

int main() {
	int n;
	double x1, y1, x2, y2, x3, y3;
	double a, b, c;
	double A, B, C, S;
	double px, py, r;

	scanf("%d", &n);
	while (n--) {
		scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);
		a = pow(x2 - x1, 2) + pow (y2 - y1, 2);
		b = pow(x3 - x1, 2) + pow (y3 - y1, 2);
		c = pow(x3 - x2, 2) + pow (y3 - y2, 2);
		A = a * (b + c - a);
		B = b * (c + a - b);
		C = c * (a + b - c);
		S = A + B + C;
		px = (A * x1 + B * x2 + C * x3) / S;
		py = (A * y1 + B * y2 + C * y3) / S;
		a = sqrt(a);
		b = sqrt(b);
		c = sqrt(c);
		r = a*b*c / sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c));
		roundoff(px, 4);
		roundoff(py, 4);
		roundoff(r, 4);
		printf("%.3f %.3f %.3f\n", px, py, r);
	}

	return 0;
}

double roundoff(double num, int n) {
	num *= pow(10, n+1);
	num += (num >= 0)? 0.5 : -0.5;
	num = (int)num * pow(10, -n-1);

	return num;
}