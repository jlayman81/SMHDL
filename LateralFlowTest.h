/*	=============================================================================
	Lateral Flow Test Class Definition
	
	@paper: 	Programmable Diagnostic Devices Made from Paper and Tape
				Andres W. Martinez, Scott T. Phillips, Zhihong Nie, Chao-Min Cheng, 
				Emanuel Carrilho, Benjamin J. Wiley and George M. Whitesides

	@filename: 11 Programmable Diagnostic Devices Made from Paper and Tape.pdf
	
	@version	0.1.4
	@author	JL,JesseL
	========================================================================== */

#ifndef LATERALFLOWTEST_H_
#define LATERALFLOWTEST_H_

#include "../app/App.h"				// App-Wide
#include "Device.h"					// For Base Class

using namespace std;

class LateralFlowTest : public Device {

	public:
		LateralFlowTest();
		LateralFlowTest(string);
		LateralFlowTest(Page*);
		LateralFlowTest(string, Page*);
		~LateralFlowTest();
		virtual int init();
		virtual int draw();
		virtual int importParameters(string);
		virtual string exportParameters();

		// Modifiers
		int drawSignal(double, double, 		// Reservoir location
							double, double, 		// Sources
							double, double); 		// Sinks
		int setCount(unsigned);
		int setPageCount(unsigned);
		int addSignal();
		int deleteSignal();
		int setSpacing(double);
		int setSignalWidth(double);
		int setSignalLength(double);
		int setSignalSpacing(double);

		// Retrievers
		unsigned getCount();
		unsigned getPageCount();
		double getSpacing();
		double getSignalWidth();
		double getSignalLength();
		double getSignalSpacing();


	private:
		unsigned PageCount		= 7;
		unsigned Signals 			= 0;
		double Margin 				= 3.0;
		double SignalSpacing 	= 2.4;
		double SignalWidth 		= 0.9;
		double SignalLength 		= 6.0;
		double ReservoirRadius 	= 1.5;
		double WellRadii 			= 0.6;

		Color cb, cw, cg;  // Color objects

		// PROBABLY WILL KILL
		int findMaxAndMins(double, double, double&, double&, double&, double&);

};

#endif



