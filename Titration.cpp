/*	=============================================================================
	Titration Class Source
	
	@version	0.1.2
	@author	JoshuaP, JesseL
	========================================================================== */

/* TODO - Collision detection?, better calculation for box->moveTO,
   check centerX calculation, check JSON comments
*/

#include "Titration.h"

using namespace std;

/*	=============================================================================
	Default Constructor for Titration Class
	
	@param 		none		nothing
	@return 	none		nothing
	========================================================================== */
Titration::Titration() : Device() {
	init();
}

/* =============================================================================
	Constructor for Titration Class with a string id parameter

	@param    string  ID of the component
	@return   none    nothing
	========================================================================== */
Titration::Titration(string id) : Device(id) {
	init();
}

/* =============================================================================
	Constructor for Titration Class with a Page id parameter

	@param    Page*			ID of the Page
	@return   none    		nothing
	========================================================================== */
Titration::Titration(Page* p) : Device(p) {
	init();
}

/* =============================================================================
	Constructor for Titration Class with a string ID parameter and
	a Page ID parameter

	@param    string     the id of the component
	@param    Page*  		Page id
	@return   none       nothing
	========================================================================== */
Titration::Titration(string id, Page* p) : Device(id, p) {
	init();
}

/* =============================================================================
	Destructor for Titration Class

	@param    none    nothing
	@return   none    nothing
	========================================================================== */
Titration::~Titration() {
	// nothing
}

/* =============================================================================
	Initializer for Titration Class

	@param    none	nothing
	@return   none	nothing
	========================================================================== */
int Titration::init() {

	// Initialize
	setClassID("Titration");
	Page* p;

	// Base Page
	p = new Page("01_Base");
	registry.registerPage(p);

	// Signal Connector Page
	p = new Page("02_Signal_Connect");
	registry.registerPage(p);

	// Signal Well Page
	p = new Page("03_Signal_Well");
	registry.registerPage(p);

	// Set default parameters
	setSignalLength(2*INLET_RADIUS);
	setSignalWidth(INLET_RADIUS);
	setWellRadii(INLET_RADIUS/2);
	setSignalSpacing(INLET_RADIUS/2);

	return 0;
}

/* =============================================================================
	Method for drawing the Device built from components and drawSignal()

	@param    none    nothing
	@return   int     status of method
	========================================================================== */
int Titration::draw() {
	
	
	//Initialize objects
	int status = 0;
	Well* w;
	Channel* c;
	Component* box;
	Polygon* p;
	Page* pg;

	// Offset Y calculations according to device parameters
	double offsetY = getSignalSpacing()*getCount()+getWellRadii()+INLET_RADIUS/2.0;

	// Center of device
	double centerX = 2*INLET_RADIUS+getWellRadii()+getSignalLength()+getSignalWidth();

	// Instantiate variables used by drawSignal()
	double signalSourceX = centerX;
	double signalSourceY = 0.0;
	double reservoirX =  centerX - getSignalLength();
	double reservoirY = 0.0;
	double signalSinkY = 0.0;
	double signalSinkX = reservoirX;

	// Specify Colors
	cb.setColor('A', 1.0); // Device Color: Black
	cw.setColor('A', 0.0); // Paper Color: White
	cg.setColor('A', 0.5); // Tape Color: Grey

	// Calculate background corners
	double uY = getRegistrationY()+offsetY+2*INLET_RADIUS;
	double rX = getRegistrationX()+2*getWellRadii()+getSignalLength()+getSignalWidth()+3*INLET_RADIUS;


	//Build Base Layer
	pg = registry.getPage("01_Base");

	// Build the background
	box = new Component("basePlate", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX(),getRegistrationY()); // ll
	p->addVertex(rX,getRegistrationY()); // lr
	p->addVertex(rX,uY); // ur
	p->addVertex(getRegistrationX(),uY); //ul
	p->setStrokeWidth(0.0); // no border
	p->setFill(cb); // Base layer, black background
	box->addPrimitive("basePlate", p);
	box->moveTo(getRegistrationX()+2*INLET_RADIUS,getRegistrationY()+offsetY);
	status += addComponent(box, pg);

	w = new Well("Inlet_Well", pg);
	w->setRadius(INLET_RADIUS);
	w->setBorder(cb, 0.2);
	w->setFill(cw);
	w->draw();
	w->moveTo(centerX,getRegistrationY()+offsetY+1.5*INLET_RADIUS);
	status += addComponent(w, pg);

	c = new Channel("01_Base_Channel", pg);
	c->setHomeLayer(pg);
	c->setSource(centerX, getRegistrationY());
	c->setSink(centerX, getRegistrationY()+getCount()*getSignalSpacing()+getSignalWidth()/2.0);
	c->setWidth( getSignalWidth() );
	c->setBorder(cb,0.0);
	c->setFill(cw);
	c->draw();
	status += addComponent(c, pg);

	// Build base layer 2, Signal_Connect
	pg = registry.getPage("02_Signal_Connect");

	// Build the background
	box = new Component("basePlate", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX(),getRegistrationY()); // ll
	p->addVertex(rX,getRegistrationY()); // lr
	p->addVertex(rX,uY); // ur
	p->addVertex(getRegistrationX(),uY); //ul
	p->setStrokeWidth(0.0); // no border
	p->setFill(cg); // Base layer, black background
	box->addPrimitive("basePlate", p);
	box->moveTo(getRegistrationX()+2*INLET_RADIUS,getRegistrationY()+offsetY);//calculate box location
	status += addComponent(box, pg);

	// Inlet Well
	w = new Well("Inlet_Well", pg);
	w->setRadius(INLET_RADIUS);
	w->setBorder(cw, 0.0);
	w->setFill(cw);
	w->draw();
	w->moveTo(centerX,getRegistrationY()+offsetY+1.5*INLET_RADIUS);
	status += addComponent(w, pg);

	// Channel
	c = new Channel("01_Base_Channel", pg);
	c->setHomeLayer(pg);
	c->setSource(centerX, getRegistrationY()+offsetY+1.5*INLET_RADIUS);
	c->setSink(centerX, uY+getCount()*getSignalSpacing()+getSignalWidth()/2.0);
	c->setWidth(getSignalWidth());
	c->setBorder(cb,0.0);
	c->setFill(cw);
	c->draw();
	status += addComponent(c, pg);

	// Build base layer 3 Signal_Well
	pg = registry.getPage("03_Signal_Well");

	// Build the background
	box = new Component("basePlate", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX(),getRegistrationY()); // ll
	p->addVertex(rX,getRegistrationY()); // lr
	p->addVertex(rX,uY); // ur
	p->addVertex(getRegistrationX(),uY); //ul
	p->setStrokeWidth(0.0); // no border
	p->setFill(cb); // Base layer, black background
	box->addPrimitive("basePlate", p);
	box->moveTo(getRegistrationX()+2*INLET_RADIUS,getRegistrationY()+offsetY);//calculate box location
	status += addComponent(box, pg);

	// Inlet Well
	w = new Well("Inlet_Well", pg);
	w->setRadius(INLET_RADIUS);
	w->setBorder(cw, 0.0);
	w->setFill(cw);
	w->draw();
	w->moveTo(centerX,getRegistrationY()+offsetY+1.5*INLET_RADIUS);
	status += addComponent(w, pg);

	// Iterate through number of signals and call draw signal
	unsigned i = 0;
	while(i<getCount()){

		// Update Y values for drawSignal()
		signalSourceY = getRegistrationY()+offsetY+INLET_RADIUS;
		reservoirY 	  = getRegistrationY()+offsetY+2*INLET_RADIUS+getSignalSpacing();
		signalSinkY   = reservoirY;

		status +=drawSignal(reservoirX, 	reservoirY,
								signalSourceX, signalSourceY,
									signalSinkX, 	signalSinkY);
		i++;  // Count drawn signal
	}

	return status;
}

/* ============================================================================
	Draw a single test site, and update Y registration

	@param    double	reservoir location X
	@param    double	reservoir location Y
	@param    double	channel source location X
	@param    double	channel source location Y
	@param    double	channel sink location X
	@param    double	channel sink location Y
	@return   int       status of method
	========================================================================== */
int Titration::drawSignal(double resX, double resY,
							double srcX, double srcY,
							double sinkX, double sinkY) {
	// Initialize
	int status = 0;
	Page* pg;
	Well* w;
	Channel* c;

	// Add Components to Signal_Connect layer
	pg = registry.getPage("02_Signal_Connect");

	// Signal Well
	w = new Well("Test_Well", pg);
	w->setRadius(getWellRadii());
	w->setBorder(cb, 0.0);
	w->setFill(cw);
	w->draw();
	w->moveTo(resX, resY);
	status += addComponent(w, pg);

	// Channel
	c = new Channel("Signal_Channel", pg);
	c->setHomeLayer(pg);
	c->setSource(srcX+getSignalWidth()/2.0, resY);
	c->setSink(resX, resY);
	c->setWidth( getSignalWidth() );
	c->setBorder(cb,0.0);
	c->setFill(cw);
	c->draw();
	status += addComponent(c, pg);

	// Add Components to Signal_Well layer
	pg = registry.getPage("03_Signal_Well");

	// Signal Well
	w = new Well("Test_Well", pg);
	w->setRadius(getWellRadii());
	w->setBorder(cb, 0.0);
	w->setFill(cw);
	w->draw();
	w->moveTo(resX, resY);
	status += addComponent(w, pg);

	// Update registration Y
	setRegistrationY(getRegistrationY()+ getSignalSpacing());

	return status;
}
/* ============================================================================
	Set the space between signals for the Titration Class

	@param    double      space between signals
	@return   int         status of method
	========================================================================== */
int Titration::setSignalSpacing(double s) {
	if (s < 0.0) return -1;
	SignalSpacing = s+getSignalWidth();
	return 0;
}
/* ============================================================================
	get the space between signals for the Titration Class

	@param    none    	  nothing
	@return   double      space between signals
	========================================================================== */
double Titration::getSignalSpacing() {
	return SignalSpacing;
}
/* ============================================================================
	Set Radius used for all wells

	@param    double	  radius
	@return   int         status of method
	========================================================================== */
int Titration::setWellRadii(double radius) {
	WellRadii = radius;
	return 0;
}

/* ============================================================================
	Get radius value used for all wells

	@param    none    	  nothing
	@return   double      WellRadii
	========================================================================== */
double Titration::getWellRadii() {
	return WellRadii;
}

/* ============================================================================
	Set the number of signals for the Titration device

	@param    unsigned    ID
	@return   int         status of method
	========================================================================== */
int Titration::setCount(unsigned count) {
	Signals = count;
	return 0;
}

/* ============================================================================
	Set the number of Pages for the Titration device

	@param    unsigned    number of Pages
	@return   int         status of method
	========================================================================== */
int Titration::setPageCount(unsigned count) {
	PageCount = count;
	return 0;
}

/* ============================================================================
	Set the value for signalWidth

	@param    double      width
	@return   int         status of method
	========================================================================== */
int Titration::setSignalWidth(double w) {
	if (w < 0.0) return -1;
	SignalWidth = w;
	return 0;
}

/* ============================================================================
	Set the length of the signals

	@param    double      channel length
	@return   int         status of method
	========================================================================== */
int Titration::setSignalLength(double l) {
	if (l < 0.0) return -1;
	SignalLength = l;
	return 0;
}

/* ============================================================================
	Get the number of signals

	@param    none    	  nothing
	@return   unsigned    number of signals
	========================================================================== */
unsigned Titration::getCount() {
	return Signals;
}

/* ============================================================================
	Get the number of Pages

	@param    none    	  nothing
	@return   unsigned    number of Pages
	========================================================================== */
unsigned Titration::getPageCount() {
	return PageCount;
}

/* ============================================================================
	Get width of signals

	@param    none   	  nothing
	@return   double      width of channels
	========================================================================== */
double Titration::getSignalWidth() {
	return SignalWidth;
}

/* ============================================================================
	Get length of signals

	@param    none   	  nothing
	@return   double      length of channel
	========================================================================== */
double Titration::getSignalLength() {
	return SignalLength;
}

/*	==========================================================================
	JSON import method for Titration Class

	@param 	   	string		s
	@return 	int			status of method
	========================================================================== */
int Titration::importParameters(string s) {

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
	signedInt 		= parameters["PageCount"];
	PageCount 		= (unsigned) signedInt;
	signedInt 		= parameters["Signals"];
	Signals 			= (unsigned) signedInt;
	SignalSpacing  = parameters["SignalSpacing"];
	SignalWidth 	= parameters["SignalWidth"];
	SignalLength 	= parameters["SignalLength"];
	WellRadii 		= parameters["WellRadii"];

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
	jsonVisible = (bool) cwColor["visible"];
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
	status += cw.setVisible( jsonVisible);
	status += cw.setColorSpace( cwColor["ColorSpace"].ToString() );

	// cg
	json::Object cgColor = parameters["cg"];
	jsonVisible = (bool) cgColor["visible"];
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
	JSON export method for Titration class

	@param 		null		nothing
	@return 	string		json serialized parameters
	========================================================================== */
string Titration::exportParameters() {

	// Build Object
	json::Object parameters;

	// Retrieve Base Class Parameters
	json::Value inputJSONvalue = json::Deserialize( Device::exportParameters() );
	parameters = inputJSONvalue.ToObject();

	// Add Titration parameters
	parameters["PageCount"] 		= (int) PageCount;
	parameters["Signals"] 		 	= (int) Signals;
	parameters["SignalWidth"]    	= SignalWidth;
	parameters["SignalSpacing"]	= SignalSpacing;
	parameters["SignalLength"]   	= SignalLength;
	parameters["WellRadii"] 	 	= WellRadii;

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




