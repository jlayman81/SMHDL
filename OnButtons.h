/* =============================================================================
	On Buttons Class Definition

	@paper: 	Programmable Diagnostic Devices Made from Paper and Tape
				Andres W. Martinez, Scott T. Phillips, Zhihong Nie, Chao-Min Cheng, 
				Emanuel Carrilho, Benjamin J. Wiley and George M. Whitesides

	@filename: 11 Programmable Diagnostic Devices Made from Paper and Tape.pdf

	@version    0.1.0
	@author EL, JesseL
	========================================================================== */

#ifndef ONBUTTONS_H_
#define ONBUTTONS_H_

#include "../app/App.h"				// App-Wide
#include "Device.h"					// For Base Class

using namespace std;

// RESERVOIR_HEIGHT = RESERVOIR WIDTH
#define RESERVOIR_HEIGHT  5.0
#define RESERVOIR_WIDTH   5.0


class OnButtons : public Device {

	public:
		 OnButtons();
		 OnButtons(string);
		 OnButtons(Page*);
		 OnButtons(string, Page*);
		~OnButtons();
		virtual int init();
		virtual int draw();
		virtual int importParameters(string);
		virtual string exportParameters();

		// Draw signal with polygon button on layer 7
		int drawSignal(double, double, 			// Reservoir location
							double, double, 	// Sources
							double, double);

		// Draw signal with round button on layer 7 see reference paper
		int drawSignalVersion2(double, double, 		// Reservoir location
							double, double, 		// Sources
							double, double);

		// Modifiers
		int setCount(unsigned);
		int setPageCount(unsigned);
		int setSignalWidth(double);
		int setSignalLength(double);
		int setSignalSpacing(double);
		int setWellRadii(double);
		
		// Retrievers
		unsigned getCount();
		unsigned getPageCount();
		double getSignalWidth();
		double getSignalLength();
		double getSignalSpacing();
		double getWellRadii();

	private:
		unsigned PageCount	= 7;
		unsigned Signals 		= 0;
		double SignalWidth 	= 0.0;
		double SignalLength 	= 0.0;
		double WellRadii 		= 0.0;
		double SignalSpacing	= 0.0;
		Color cb, cw, cg; // Color objects
};

#endif






