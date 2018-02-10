/*	=============================================================================
	ImmunoSensor Class Definition
	
	@paper: A New Paper-Based Platform Technology for Point-
of-Care Diagnostics
Roman Gerbers a , Wilke Foellscher a , Hong Chen b , Constantine Anagnostopoulos b ,
Mohammad Faghri c*
	@filename: c4lc00786g.pdf
	
	@version	0.1.1
	@author	JoshuaP, JesseL
	========================================================================== */

#ifndef IMMUNOSENSOR_H_
#define IMMUNOSENSOR_H_

#include "../app/App.h"				// App-Wide
#include "Device.h"					// For Base Class


using namespace std;

class ImmunoSensor : public Device {

	public:
		ImmunoSensor();
		ImmunoSensor(string);
		ImmunoSensor(Page*);
		ImmunoSensor(string, Page*);
		virtual ~ImmunoSensor();
		virtual int init();
		virtual int draw();
		virtual int importParameters(string);
		virtual string exportParameters();

		// Draw background
		int drawBackground(Color, Page*);

		// Draw channel
		int drawChannel(double, double, 	// sourceX,Y,sinkX,Y
							 double, double, 	//  width, color, Substrate
							 double, Color,	
							 Page*);
		// Draw holes/valves
		int drawHole(double, double, 		// Center X,Y,Radius, border, fill, substrate
						 double, 
						 Color, Color, 
						 Page*);
		// Draw waste pad
		int drawWastePad(Color, Color, 
							  double, Page*);    //  border, fill, substrate

		// Modifiers
		/*
		int setCount(unsigned);
		int setSubstrateCount(unsigned);
		int setSignalWidth(double);
		int setSignalLength(double);
		int setWellRadii(double);
		int setSignalSpacing(double);
								 
		// Retrievers
		unsigned getCount();
		unsigned getSubstrateCount();
		double getSignalWidth();
		double getSignalLength();
		double getSignalSpacing();
		double getWellRadii();
		*/
		
		// <<<<<<<<<<<<<<<<<<<<<<<<<  TO DO  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

		
		// <<<<<<<<<<<<<<<<<<<<<<<<<  TO DO  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	private:

		/*unsigned SubstrateCount	=   7;
		unsigned Signals 			=   0;
		double SignalWidth 		= 0.0;
		double SignalLength 		= 0.0;
		double SignalSpacing    = 0.0;

		double WellRadii 			= 0.0;
       */
		Color cb, cw, cg; // Color objects


};

#endif 
