#ifndef MusicAnalyzer_H
#define MusicAnalyzer_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fftw3.h>
#include <math.h>
#include <complex>

class MusicAnalyzer : public sf::SoundRecorder
{
public:
	//MusicAnalyzer();
	//~MusicAnalyzer();
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
void draw(sf::RenderWindow& canvas);

	bool needData;
	bool vaildData;
	fftw_complex *output;
	int sampelSize;


};

#endif
