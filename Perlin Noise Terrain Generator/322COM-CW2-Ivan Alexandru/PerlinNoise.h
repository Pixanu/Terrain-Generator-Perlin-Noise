// Disclaimer: This code was not made by me 

// This class is a translation from java to C++ from the reference
// Java implementation of the improved perlin function
// The original java implementation is copyright 2002 Ken Perlin
// Check // (http://mrl.nyu.edu/~perlin/noise)

#ifndef PERLINNOISE_H
#define PERLINNOISE_H

//Optimisation - Extra method that generates a new permutation vector (not pressent in the original)
#include <vector>

class PerlinNoise
{
	// The permutation vector
	std::vector<int> p;
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for 2D images z can have any value
	double noise(double x, double y, double z);
private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};


#endif // !PERLINNOISE_H



