#include <iostream>
using namespace std;

template < typename T >
T getMax(T* pT, size_t length);

int main() {
	int grade[10] = { 78, 44, 89, 55, 45, 75, 94, 74, 83, 65 };
	float height[10] = { 178.3, 164.6, 189.4, 155.8, 158.3, 175.0, 169.6, 174.2, 183.1, 165.9 };
	
	cout << "The best score is " << getMax(grade, sizeof(grade)/sizeof(int)) << endl;
	cout << "The maximum height is " << getMax(height, sizeof(height) / sizeof(float)) << endl;

	getchar();
	return 0;
}

template < typename T >
T getMax(T* pT, size_t length) {
	T max = pT[0];
	for (size_t i = 1; i < length; i++)
	{
		if (pT[i] > max)
			max = pT[i];
	}
	return max;
}