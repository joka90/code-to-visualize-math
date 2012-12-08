#include "MusicAnalyzer.h"

using namespace std;

/*
MusicAnalyzer::MusicAnalyzer()
:sf::SoundRecorder()
{

}
MusicAnalyzer::~MusicAnalyzer()
:sf::~SoundRecorder()
{

}*/

bool MusicAnalyzer::onProcessSamples(const sf::Int16* samples, std::size_t sampleCount)
{
	needData=true;
	if(needData)
	{
		sampelSize = (int)sampleCount;
		double *input;

		// allocate input arrays
		input = new double[sampelSize];

		for(int i = 0; i < sampelSize; i++)
		{
			input[i] = samples[i];
		}

		// allocate output arrays
		output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*sampelSize);

		// create plans
		fftw_plan plan;
		plan = fftw_plan_dft_r2c_1d(sampelSize, input, output,FFTW_ESTIMATE);



		// perform FORWARD fft
		fftw_execute(plan);


		// free memory
		fftw_destroy_plan(plan);

		fftw_free(input);

		vaildData=true;
	}
	return true;
}
void MusicAnalyzer::draw(sf::RenderWindow& canvas)
{
	if(vaildData)
	{
 		sf::VertexArray lines(sf::LinesStrip, sampelSize);
		int mostCommonValue[10];
		int mostCommonFreq[10];

		for(int i=20;i<sampelSize-500;i++)
		{
			int x = sqrt(pow(output[i][1],2)+pow(output[i][0],2));
			lines[i-20].position = sf::Vector2f(i/4-20, 600-x);
			for(int n=0;n<10;n++)
			{
				if(mostCommonValue[n]<x)
				{
					mostCommonFreq[n]=i-20;
					mostCommonValue[n]=x;
					break;
				}

			}
		}
		canvas.draw(lines);
		for(int n=0;n<10;n++)
		{
			cout << mostCommonFreq[n] << " " << mostCommonValue[n] << endl;
		}
		vaildData=false;
		fftw_free(output);
	}
}


/*void fft(int squareSize, PixelPacket* pixels, PixelPacket* outMag, PixelPacket* outPhase)
{
	fftw_plan planR, planG, planB;
	fftw_complex *inR, *inG, *inB, *outR, *outG, *outB;
	
	// allocate input arrays
	inR = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * squareSize * squareSize);
	
	// allocate output arrays
	outR = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * squareSize * squareSize);
	
	// create plans
	planR = fftw_plan_dft_2d(squareSize, squareSize, inR, outR, FFTW_FORWARD, FFTW_ESTIMATE);
	
	// assign values to real parts (values between 0 and MaxRGB)
	for(int i = 0; i < squareSize * squareSize; i++) {
		PixelPacket current = *(pixels + i);
		double red = current.red;
		
		// save as real numbers
		inR[i][0] = red;

	}
	
	// perform FORWARD fft
	fftw_execute(planR);
	
	// transform imaginary number to phase and magnitude and save to output
	for(int i = 0; i < squareSize * squareSize; i++) {
		// normalize values
		double realR = outR[i][0] / (double)(squareSize * squareSize);
		double imagR = outR[i][1] / (double)(squareSize * squareSize);
				
		
		// magnitude
		double magR = sqrt((realR * realR) + (imagR * imagR));
		
		// write to output
		(*(outMag + i)).red = magR;
		
		// std::complex for arg()
		complex<double> cR(realR, imagR);

		// phase
		double phaseR = arg(cR) + M_PI;
		
		// scale and write to output
		(*(outPhase + i)).red = (phaseR / (double)(2 * M_PI)) * MaxRGB;
	}
	

	
	// free memory
	fftw_destroy_plan(planR);

	fftw_free(inR); fftw_free(outR);

}*/
