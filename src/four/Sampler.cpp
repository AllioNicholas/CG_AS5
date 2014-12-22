#include "Sampler.h"

#include <cassert>

Sampler::Sampler(int nSamples) :
	m_nSamples(nSamples)
{}

Sampler* Sampler::constructSampler(Args::SamplePatternType t, int numsamples)
{
	if( t == Args::Pattern_Uniform ) {
		return new UniformSampler(numsamples);
	} else if ( t == Args::Pattern_Regular ) {
		return new RegularSampler(numsamples);
	} else if ( t == Args::Pattern_Jittered ) {
		return new JitteredSampler(numsamples);
	} else {
		assert(false && "Bad sampler type");
		return nullptr;
	}
}

UniformSampler::UniformSampler(int nSamples) :    
	Sampler(nSamples)
{}

Vec2f UniformSampler::getSamplePosition(int i) {
	// make the compiler shut up by referencing the variable
	(void)i;	
	// YOUR CODE HERE (R9)
	// Return a uniformly distributed random 2-vector within the unit square [0,1]^2
	Vec2f rnd;
	rnd.x = (float)(rand()) / (float)(RAND_MAX);
	rnd.y = (float)(rand()) / (float)(RAND_MAX);

	return rnd;
}

RegularSampler::RegularSampler(int nSamples) :
	Sampler(nSamples)
{
	// test that it's a perfect square
	int dim = (int)sqrtf(float(nSamples));
	assert(nSamples == dim * dim);
	m_dim = dim;
}

Vec2f RegularSampler::getSamplePosition(int n) {
	// YOUR CODE HERE (R9)
	// Return a sample through the center of the Nth subpixel.
	// The starter code only supports one sample per pixel.
	Vec2f samp = Vec2f(0.5f, 0.5f);
	if (m_dim > 1) {
		samp.x = (float)(n%m_dim) / (m_dim - 1);
		samp.y = (float)(n / m_dim) / (m_dim - 1);
	}
	return samp;
}

JitteredSampler::JitteredSampler(int nSamples) :
	Sampler(nSamples)
{
	// test that it's a perfect square
	int dim = (int)sqrtf(float(nSamples));
	assert(nSamples == dim * dim);
	m_dim = dim;
}

Vec2f JitteredSampler::getSamplePosition(int n) {
	// YOUR CODE HERE (R9)
	// Return a randomly generated sample through Nth subpixel.
	Vec2f samp = Vec2f(0.5f, 0.5f);
	float rand_x = (float)(rand()) / (float)(RAND_MAX) / m_dim;
	float rand_y = (float)(rand()) / (float)(RAND_MAX) / m_dim;
	if (m_dim > 1) {
		samp.x = (float)(n%m_dim) / (m_dim)+rand_x;
		samp.y = (float)(n / m_dim) / (m_dim)+rand_y;
	}
	return samp;
}

