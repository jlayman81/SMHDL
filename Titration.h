/*	=============================================================================
	Titration Class Definition
	
	@paper: Two-ply channels for faster wicking in paper-
				based microfluidic devices†
				Conor K. Camplisson,‡ a Kevin M. Schilling,‡ a William L. Pedrotti, a Howard A. Stone b
				and Andres W. Martinez* a
	@filename: c5lc01115a.pdf
	
	@version	0.1.1
	@author	JoshuaP, JesseL
	========================================================================== */
	
#ifndef TITRATION_H_
#define TITRATION_H_

#include "../app/App.h"				// App-Wide
#include "Device.h"					// For Base Class

using namespace std;

#define INLET_RADIUS 5.0

class Titration : public Device {

	public:
		Titration();
		Titration(string);
		Titration(Page*);
		Titration(string, Page*);
		virtual ~Titration();
		virtual int init();
		virtual int draw();
		virtual int importParameters(string);
		virtual string exportParameters();

		// Draw signal
		int drawSignal(double, double, 			// Reservoir location
								double, double, 	// Sources
								double, double);
		// Modifiers
		int setCount(unsigned);
		int setPageCount(unsigned);
		int setSignalWidth(double);
		int setSignalLength(double);
		int setWellRadii(double);
		int setSignalSpacing(double);
								 
		// Retrievers
		unsigned getCount();
		unsigned getPageCount();
		double getSignalWidth();
		double getSignalLength();
		double getSignalSpacing();
		double getWellRadii();

		
		// <<<<<<<<<<<<<<<<<<<<<<<<<  TO DO  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		
		// <<<<<<<<<<<<<<<<<<<<<<<<<  TO DO  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	private:
		unsigned PageCount 	= 7;
		unsigned Signals 			= 0;
		double SignalWidth 			= 0.0;
		double SignalLength 		= 0.0;
		double SignalSpacing        = 0.0;
		double WellRadii 			= 0.0;
		Color cb, cw, cg; // Color objects

};

#endif 
