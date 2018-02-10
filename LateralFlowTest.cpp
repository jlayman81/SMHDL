/* =============================================================================
	Lateral Flow Test Class Definition

	@version    0.1.6
	@author JL,JesseL
	========================================================================== */
    
/* =============================================================================
	TO DO
	Add support for setSignalSpace(), setSignalWidth(), setSignalLength()
	Add description for JSON functions,
	Remove or add support for setSpacing() and getSpacing().
	========================================================================== */

#include "LateralFlowTest.h"

using namespace std;

/* =============================================================================
	Default Constructor for LateralFlowTest Class

	@param  	none	nothing
	@return	none	nothing
	========================================================================== */
LateralFlowTest::LateralFlowTest() : Device() {
	init();
}

/* =============================================================================
	Default Constructor for LateralFlowTest Class with string ID passed in

	@param  	none	nothing
	@return	none	nothing
	========================================================================== */
LateralFlowTest::LateralFlowTest(string id) : Device(id) {
	init();
}

/* =============================================================================
	Default Constructor for LateralFlowTest Class with a page parameter

	@param    string  the id of the component
	@return   none    nothing
	========================================================================== */
LateralFlowTest::LateralFlowTest(Page* p) : Device(p) {
	init();
}

/* =============================================================================
	Default Constructor for LateralFlowTest Class with a string id, and a page parameter

	@param    string  the id of the component
	@return   none    nothing
	========================================================================== */
LateralFlowTest::LateralFlowTest(string id, Page* p) : Device(id, p) {
	init();
}

/* =============================================================================
	Default Destructor for LateralFlowTest Class

	@param    none    nothing
	@return   none    nothing
	========================================================================== */
LateralFlowTest::~LateralFlowTest() {
   // Nothing
}

/* =============================================================================
	Default initializer for LateralFlowTest Class

	@param    none    nothing
	@return   none    nothing
	========================================================================== */
int LateralFlowTest::init() {

   // Initialize
   setClassID("LateralFlowTest");
   Page* pg;


   // Base Page
   pg = new Page("01_paper1");
   registry.registerPage(pg);

   // Tape Page
   pg = new Page("02_tape1");
   registry.registerPage(pg);

   // Paper Page
   pg = new Page("03_paper2");
   registry.registerPage(pg);

   // Tape Page
   pg = new Page("04_tape2");
   registry.registerPage(pg);

   // Paper Page
   pg = new Page("05_paper3");
   registry.registerPage(pg);

   // Tape Page
   pg = new Page("06_tape3");
   registry.registerPage(pg);

   // Paper Page
   pg = new Page("07_paper4");
   registry.registerPage(pg);

   //setSignalSpacing(2.4);
   //setSpacing(3.0);

   return 0;
}

/* =============================================================================
	Method for drawing the device built from Components and Primitives

	@param    none    nothing
	@return   int     status of method
	========================================================================== */
int LateralFlowTest::draw() {

	// Clear Component(s) if present
	while (getComponentCount() > 0) deleteComponent(0);

	// Initialize
	int status = 0;
	Page* pg;
	Well *b1,*b2,*b3,*b4,*r1,*r2,*r3,*r4;
	Component* box,*cutout;
	Polygon* p,*p1;
	Channel* ch0,*ch1,*ch2,*ch3,*ch4;	
	double deviceWidth 	= 0.0;
	double deviceHeight 	= 0.0;

	// Specify Colors
	cb.setColor('A', 1.0); // Device Color: Black
	cw.setColor('A', 0.0); // Paper Color: White
	cg.setColor('A', 0.5); // Tape Color: Grey

	// Calculate Dimensions and location of Device Box
	deviceWidth  = getSpacing() + ( getCount() * ( getSignalWidth() + getSignalSpacing() ) );
	deviceHeight = getSpacing() + ( getCount() * ( getSignalWidth() + getSignalSpacing() ) );

	// Build base layers
	for (unsigned i = 0; i < (registry.getPageCount() - 1); i++) {
		pg = registry.getPageAt(i);
		//Background
		box = new Component("baseplate", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(0.0, 0.0); // ll
		p->addVertex(deviceWidth, 0.0); // lr
		p->addVertex(deviceWidth, deviceHeight); // ur
		p->addVertex(0.0, deviceHeight); //ul
		p->addVertex(0.0, 0.0);
		p->setStrokeWidth(0.0); // no border

		// Cut out
		if(i>0){
			cutout = new Component("cutout", pg);

			p1 = new Polygon();
			p1->setID("polygon cutout");
			p1->addVertex(0.0, 0.0); // ll
			p1->addVertex(6.5, 0.0); // lr
			p1->addVertex(6.5, 6.5); // ur
			p1->addVertex(0.0, 6.5); //ul
			p1->addVertex(0.0, 0.0);
			p1->setStrokeWidth(0.0); // no border
			p1->setFill(cw);

			cutout->addPrimitive("cutout", p1);
			cutout->move( ( box->getRegistrationX() - ReservoirRadius - getSpacing() ),
									( box->getRegistrationX() - ( 0.5 * deviceHeight ) ) );
			status += addComponent(cutout, pg);
			}

		// Determine Color
		if ( (i % 2) == 0 ) {
			p->setFill(cb); // paper Layer, black background
		} else {
			p->setFill(cg); // tape Layer, black background
		}

		box->addPrimitive("baseplate", p);
		box->move( ( box->getRegistrationX() - ReservoirRadius - getSpacing() ),
						( box->getRegistrationX() - ( 0.5 * deviceHeight ) ) );
		status += addComponent(box, pg);

		// Add input channels numbered clockwise starting from lower left
		if(i==0){
			ch0 = new Channel("inlet_0", pg);
			ch0->setHomeLayer(pg);
			ch0->setSource(-4.8, -7.8);
			ch0->setSink(getRegistrationX()+2, getRegistrationY()-2);
			ch0->setWidth(2.0);
			ch0->setBorder(cb,0.0);
			ch0->setFill(cw);
			ch0->draw();
			status += addComponent(ch0, pg);

			ch1 = new Channel("inlet_1", pg);
			ch1->setHomeLayer(pg);
			ch1->setSource(getRegistrationX()+2, getRegistrationY()-2);
			ch1->setSink(getRegistrationX()+0.5, getRegistrationY()+1);
			ch1->setWidth(1.6);
			ch1->setBorder(cb,0.0);
			ch1->setFill(cw);
			ch1->draw();
			status += addComponent(ch1, pg);

			ch2 = new Channel("inlet_2", pg);
			ch2->setHomeLayer(pg);
			ch2->setSource(getRegistrationX()+2, getRegistrationY()-2);
			ch2->setSink(getRegistrationX()+3.7, getRegistrationY()+1);
			ch2->setWidth(1.3);
			ch2->setBorder(cb,0.0);
			ch2->setFill(cw);
			ch2->draw();
			status += addComponent(ch2, pg);

			ch3 = new Channel("inlet_3", pg);
			ch3->setHomeLayer(pg);
			ch3->setSource(getRegistrationX()+2, getRegistrationY()-2);
			ch3->setSink(getRegistrationX()+5.5, getRegistrationY()-1.2);
			ch3->setWidth(1.3);
			ch3->setBorder(cb,0.0);
			ch3->setFill(cw);
			ch3->draw();
			status += addComponent(ch3, pg);

			ch4 = new Channel("inlet_4", pg);
			ch4->setHomeLayer(pg);
			ch4->setSource(getRegistrationX()+2, getRegistrationY()-2);
			ch4->setSink(getRegistrationX()+4.4, getRegistrationY()-4.4);
			ch4->setWidth(1.6);
			ch4->setBorder(cb,0.0);
			ch4->setFill(cw);
			ch4->draw();
			status += addComponent(ch4, pg);
		}

		// Add holes numbered clockwise starting from upper left
		if(i!=5){

			b1 = new Well("button_1", pg);
			b1->setRadius(.70);
			if(i!=6){
				b1->setBorder(cw, 0.0);
				b1->setFill(cw);
			}
			else {
				b1->setBorder(cw, 0.1);
				b1->setFill(cb);
			}
			b1->draw();
			b1->moveTo(getRegistrationX()+0.5, getRegistrationY()+1);
			status += addComponent(b1, pg);

			b2 = new Well("button_2", pg);
			b2->setRadius(.70);
			if(i!=6){
				b2->setBorder(cw, 0.0);
				b2->setFill(cw);
			}
			else {
				b2->setBorder(cw, 0.1);
				b2->setFill(cb);
			}
			b2->draw();
			b2->moveTo(getRegistrationX()+3.7, getRegistrationY()+1);
			status += addComponent(b2, pg);

			b3 = new Well("button_3", pg);
			b3->setRadius(.70);
			if(i!=6){
				b3->setBorder(cw, 0.0);
				b3->setFill(cw);
			}
			else {
				b3->setBorder(cw, 0.1);
				b3->setFill(cb);
			}
			b3->draw();
			b3->moveTo(getRegistrationX()+5.5, getRegistrationY()-1.2);
			status += addComponent(b3, pg);

			b4 = new Well("button_4", pg);
			b4->setRadius(.70);
			if(i!=6){
				b4->setBorder(cw, 0.0);
				b4->setFill(cw);
			}
			else {
				b4->setBorder(cw, 0.1);
				b4->setFill(cb);
			}
			b4->draw();
			b4->moveTo(getRegistrationX()+4.4, getRegistrationY()-4.4 );
			status += addComponent(b4, pg);

		}

		//Add outlet channels numbered clockwise from upper left
		if(i==4){
			ch1 = new Channel("outlet_1", pg);
			ch1->setHomeLayer(pg);
			ch1->setSource(getRegistrationX()+0.5, getRegistrationY()+1);
			ch1->setSink(getRegistrationX()+0.5, getRegistrationY()+4);
			ch1->setWidth(1.3);
			ch1->setBorder(cb,0.0);
			ch1->setFill(cw);
			ch1->draw();
			status += addComponent(ch1, pg);

			ch2 = new Channel("outlet_2", pg);
			ch2->setHomeLayer(pg);
			ch2->setSource(getRegistrationX()+3.7, getRegistrationY()+1);
			ch2->setSink(getRegistrationX()+5.5, getRegistrationY()+4);
			ch2->setWidth(1.3);
			ch2->setBorder(cb,0.0);
			ch2->setFill(cw);
			ch2->draw();
			status += addComponent(ch2, pg);

			ch3 = new Channel("outlet_3", pg);
			ch3->setHomeLayer(pg);
			ch3->setSource(getRegistrationX()+5.5, getRegistrationY()-1.2);
			ch3->setSink(getRegistrationX()+8.5, getRegistrationY());
			ch3->setWidth(1.3);
			ch3->setBorder(cb,0.0);
			ch3->setFill(cw);
			ch3->draw();
			status += addComponent(ch3, pg);

			ch4 = new Channel("outlet_4", pg);
			ch4->setHomeLayer(pg);
			ch4->setSource(getRegistrationX()+4.4, getRegistrationY()-4.4);
			ch4->setSink(getRegistrationX()+7.8, getRegistrationY()-4.4);
			ch4->setWidth(1.3);
			ch4->setBorder(cb,0.0);
			ch4->setFill(cw);
			ch4->draw();
			status += addComponent(ch4, pg);
		}

		// Add mixing reservoirs
		if(i>3){
			r1 = new Well("res_1", pg);
			r1->setRadius(1.2);
			r1->setBorder(cw, 0.0);
			r1->setFill(cw);
			r1->draw();
			r1->moveTo(getRegistrationX()+0.5, getRegistrationY()+4);
			status += addComponent(r1, pg);

			r2 = new Well("res_2", pg);
			r2->setRadius(1.2);
			r2->setBorder(cw, 0.0);
			r2->setFill(cw);
			r2->draw();
			r2->moveTo(getRegistrationX()+5.5, getRegistrationY()+4);
		    status += addComponent(r2, pg);

			r3 = new Well("res_3", pg);
			r3->setRadius(1.2);
			r3->setBorder(cw, 0.0);
			r3->setFill(cw);
			r3->draw();
			r3->moveTo(getRegistrationX()+8.5, getRegistrationY());
		    status += addComponent(r3, pg);

			r4 = new Well("res_4", pg);
			r4->setRadius(1.2);
			r4->setBorder(cw, 0.0);
			r4->setFill(cw);
			r4->draw();
			r4->moveTo(getRegistrationX()+7.8, getRegistrationY()-4.4);
		    status += addComponent(r4, pg);

		}

	}
	return status;
}

/*	==========================================================================
	DESC
	
	@param 		null		nothing
	@return 	null		nothing
	========================================================================== */
int LateralFlowTest::importParameters(string s) {
	
	// Null Check
	if (s == "") return -1;
	
	// Error Status
	int status = 0;
	
	// Build Object
	json::Object parameters;
	
	// Reconstitute JSON
	json::Value inputJSONvalue = json::Deserialize(s);
	parameters = inputJSONvalue.ToObject();
	
	// Set Base Class Parameters
	status += Device::importParameters(s);
	
	// Retrieve Values
	int signedInt = 0;
	signedInt 			= parameters["PageCount"];
	PageCount 			= (unsigned) signedInt;
	signedInt 			= parameters["Signals"];
	Signals 				= (unsigned) signedInt;
	Margin 				= parameters["Margin"];
	SignalSpacing 		= parameters["SignalSpacing"];
	SignalWidth 		= parameters["SignalWidth"];
	SignalLength 		= parameters["SignalLength"];
	ReservoirRadius 	= parameters["ReservoirRadius"];
	WellRadii 			= parameters["WellRadii"];
	
	// Temp Variables to hold color b/c set methods are overloaded and 
	// JSON cannot figure out the conversion of JSON Type to which value is needed
	double R, G, B, C, Y, M, K, A;
	
	// cb
	json::Object cbColor = parameters["cb"];
	bool jsonVisible;
	jsonVisible = (bool) cbColor["visible"];
	R = cbColor["R"];
	G = cbColor["G"];
	B = cbColor["B"];
	C = cbColor["C"];
	M = cbColor["M"];
	Y = cbColor["Y"];
	K = cbColor["K"];
	A = cbColor["A"];
	status += cb.setRGB(R,G,B);
	status += cb.setCMYK(C,M,Y,K);
	status += cb.setColor('A', A);
	status += cb.setVisible( jsonVisible );
	status += cb.setColorSpace( cbColor["ColorSpace"].ToString() );
	
	// cw
	json::Object cwColor = parameters["cw"];
	R = cwColor["R"];
	G = cwColor["G"];
	B = cwColor["B"];
	C = cwColor["C"];
	M = cwColor["M"];
	Y = cwColor["Y"];
	K = cwColor["K"];
	A = cwColor["A"];
	status += cw.setRGB(R,G,B);
	status += cw.setCMYK(C,M,Y,K);
	status += cw.setColor('A', A);
	status += cw.setVisible( jsonVisible );
	status += cw.setColorSpace( cwColor["ColorSpace"].ToString() );
	
	// cg
	json::Object cgColor = parameters["cg"];
	R = cgColor["R"];
	G = cgColor["G"];
	B = cgColor["B"];
	C = cgColor["C"];
	M = cgColor["M"];
	Y = cgColor["Y"];
	K = cgColor["K"];
	A = cgColor["A"];
	status += cg.setRGB(R,G,B);
	status += cg.setCMYK(C,M,Y,K);
	status += cg.setColor('A', A);
	status += cg.setVisible( jsonVisible );
	status += cg.setColorSpace( cgColor["ColorSpace"].ToString() );
	
	return status;
}

/*	==========================================================================
	DESC
	
	@param 	null		nothing
	@return 	null		nothing
	========================================================================== */
string LateralFlowTest::exportParameters() {

	// Build Object
	json::Object parameters;
	
	// Retrieve Base Class Parameters
	json::Value inputJSONvalue = json::Deserialize( Device::exportParameters() );
	parameters = inputJSONvalue.ToObject();

	// Add FluidicMultiplexer parameters	
	parameters["PageCount"] = (int) PageCount;
	parameters["Signals"] = (int) Signals;
	parameters["Margin"] = Margin;
	parameters["SignalSpacing"] = SignalSpacing;
	parameters["SignalWidth"] = SignalWidth;
	parameters["SignalLength"] = SignalLength;
	parameters["ReservoirRadius"] = ReservoirRadius;
	parameters["WellRadii"] = WellRadii;
	
	// cb Color
	json::Value cbColor = json::Deserialize( cb.exportParameters() );
	parameters["cb"] = cbColor.ToObject();
	
	// cw Color
	json::Value cwColor = json::Deserialize( cw.exportParameters() );
	parameters["cw"] = cwColor.ToObject();
	
	// cg Color
	json::Value cgColor = json::Deserialize( cg.exportParameters() );
	parameters["cg"] = cgColor.ToObject();

	return json::Serialize(parameters);
}

/* ============================================================================
	Set the number of signals for the LateralFlowTest device

	@param    unsigned    number of signals
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::setCount(unsigned count) {
	Signals = count;
	return 0;
}

/* ============================================================================
	Set the number of pages for the LateralFlowTest device

	@param    unsigned    number of pages
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::setPageCount(unsigned count) {
	PageCount = count;
	return 0;
}

/* ============================================================================
	Add an addtional signal to the LateralFlowTest device

	@param    none    	  nothing
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::addSignal() {
	Signals++;
	return 0;
}

/* ============================================================================
	Remove a signal from the LateralFlowTest device

	@param    none    	  nothing
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::deleteSignal() {

	Signals--;
	return 0;
}

/* ============================================================================
	DESC

	@param    double      space between signals
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::setSpacing(double s) {
	if (s < 0.0) return -1;
	Margin = s;
	return 0;
}

/* ============================================================================
	Set the distance between signals for the LateralFlowTest device

	@param    double   	  distance between signals
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::setSignalSpacing(double s) {
	if (s < 0.0) return -1;
	SignalSpacing = s;
	return 0;
}

/* ============================================================================
	Set the signal width for the LateralFlowTest device

	@param    double      signal width
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::setSignalWidth(double w) {
	if (w < 0.0) return -1;
	SignalWidth = w;
	return 0;
}

/* ============================================================================
	Set the signal length for the LateralFlowTest device

	@param    double      signal length
	@return   int         status of method
	========================================================================== */
int LateralFlowTest::setSignalLength(double l) {
	if (l < 0.0) return -1;
	SignalLength = l;
	return 0;
}

/* ============================================================================
	Get the number of signals for the LateralFlowTest device

	@param    none		  nothing
	@return   unsigned    number of signals
	========================================================================== */
unsigned LateralFlowTest::getCount() {
	return Signals;
}

/* ============================================================================
	Get the number of pages for the LateralFlowTest device

	@param    none		  nothing
	@return   int         status of method
	========================================================================== */
unsigned LateralFlowTest::getPageCount() {
	return PageCount;
}

/* ============================================================================
	DESC

	@param    unsigned    ID
	@return   int         status of method
	========================================================================== */
double LateralFlowTest::getSpacing() {
	return Margin;
}

/* ============================================================================
	Get the distance between signals for the LateralFlowTest device

	@param    none	 	  nothing
	@return   unsigned    distance between signals
	========================================================================== */
double LateralFlowTest::getSignalSpacing() {
	return SignalSpacing;
}

/* ============================================================================
	Get the signal width for the LateralFlowTest device

	@param    none		  nothing
	@return   unsigned    width of the signal
	========================================================================== */
double LateralFlowTest::getSignalWidth() {
	return SignalWidth;
}

/* ============================================================================
	Get the signal length for the LateralFlowTest device

	@param    none		  nothing
	@return   unsigned    length of the signal
	========================================================================== */
double LateralFlowTest::getSignalLength() {
	return SignalLength;
}
















