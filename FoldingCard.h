/*	=============================================================================
	Folding Card Class Definition
	
	@paper: Dissolvable fluidic time delays for programming multi-
				step assays in instrument-free paper diagnostics3
				Cite this: Lab Chip, 2013, 13, 2840
				Barry Lutz,* Tinny Liang, Elain Fu, Sujatha Ramachandran, Peter Kauffman
				and Paul Yager
	@filename: 13 C3LC50178G.pdf
	
	@version	0.1.4
	@author	RH, JesseL
	========================================================================== */

#ifndef FOLDINGCARD_H_
#define FOLDINGCARD_H_

#include "../app/App.h"				// App-Wide
#include "Device.h"					// For Base Class

using namespace std;

class FoldingCard : public Device {
	public:
		FoldingCard();
		FoldingCard(string);
		virtual ~FoldingCard();
		virtual int init();
		virtual int draw();
		virtual int importParameters(string);
		virtual string exportParameters();

		int moveID(unsigned, double, double);
		int moveAlias(string, double, double);
		//int moveBy(double, double);

		int rotateID(unsigned, double);
		int rotateAlias(string, double);
		int rotateBy(double);

		int scaleID(unsigned, double); 
		int scaleAlias(string, double);
		int scaleBy(double);

		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  TO DO
		int scaleWidthID(unsigned, double);
		int scaleWidthAlias(unsigned, double);
		int scaleLengthID(unsigned, double);
		int scaleLengthAlias(unsigned, double);

		//void printAll();
		// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  TO DO


	private:
		int scaleHelperPoly(Polygon*, double);
		int scaleHelperCircle(Circle*, double);

      int refreshPoly(Polygon *p, smhdl::coords, double, double);

		int rotateHelperPoly(Polygon*, double);
		int rotateHelperCircle(Circle*, double);

		smhdl::coords getCenterPoly(Polygon*);
		smhdl::coords getCenterAll();
};

#endif 
