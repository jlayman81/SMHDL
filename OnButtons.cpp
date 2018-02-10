/*  =============================================================================
    On Buttons Class Definition
    
    @version    1.0.0
    @author EL, JesseL
    ========================================================================== */

/* =============================================================================
	TO DO
	Add description for JSON functions,
	Review min/max checking in setSignalLength(),
	setSignalWidth(), and setWellRadii()
	========================================================================== */
#include "OnButtons.h"

using namespace std;

/* =============================================================================
	Default Constructor for OnButtons Class

	@param    none    nothing
	@return   none    nothing
	========================================================================== */
OnButtons::OnButtons() : Device() {
	init();
}

/* =============================================================================
	Constructor for OnButtons Class with a string id parameter

	@param    string  ID of the component
	@return   none    nothing
	========================================================================== */
OnButtons::OnButtons(string id) : Device(id) {
	init();
}

/* =============================================================================
	Constructor for OnButtons Class with a Page id parameter

	@param    Page*			ID of the Page
	@return   none    		nothing
	========================================================================== */
OnButtons::OnButtons(Page* p) : Device(p) {
	init();
}

/* =============================================================================
	Constructor for OnButtons Class with a string ID parameter and
	a Page ID parameter

	@param    string     the id of the component
	@param    Page*	  	Page id
	@return   none       nothing
	========================================================================== */
OnButtons::OnButtons(string id, Page* p) : Device(id, p) {
	init();
}

/* =============================================================================
	Destructor for OnButtons Class

	@param    none    nothing
	@return   none    nothing
	========================================================================== */
OnButtons::~OnButtons() {
   // Nothing
}

/* =============================================================================
	Initializer for OnButtons Class

	@param    none	nothing
	@return   none	nothing
	========================================================================== */
int OnButtons::init() {

   // Initialize
   setClassID("OnButtons");
   Page* p;

   // Base Page
   p = new Page("01_paper1");
   registry.registerPage(p);

   // Tape Page
   p = new Page("02_tape1");
   registry.registerPage(p);

   // Paper Page
   p = new Page("03_paper2");
   registry.registerPage(p);

   // Tape Page
   p = new Page("04_tape2");
   registry.registerPage(p);

   // Paper Page
   p = new Page("05_paper3");
   registry.registerPage(p);

   // Tape Page
   p = new Page("06_tape3");
   registry.registerPage(p);

   // Paper Page
   p = new Page("07_paper4");
   registry.registerPage(p);

   // Set component parameters

   setSignalLength(2*RESERVOIR_WIDTH);
   setSignalWidth(RESERVOIR_HEIGHT/2.0);
   setWellRadii(RESERVOIR_WIDTH/2.0);

   return 0;
}

/*	==========================================================================
	JSON import method for OnButtons Class

	@param 	   	string		s
	@return 	int			status of method
	========================================================================== */
int OnButtons::importParameters(string s) {

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
	SignalWidth 		= parameters["SignalWidth"];
	SignalLength 		= parameters["SignalLength"];
	SignalSpacing 		= parameters["SignalSpcaing"];
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
	JSON export method for OnButtons class

	@param 		null		nothing
	@return 	string		json serialized parameters
	========================================================================== */
string OnButtons::exportParameters() {

	// Build Object
	json::Object parameters;
	
	// Retrieve Base Class Parameters
	json::Value inputJSONvalue = json::Deserialize( Device::exportParameters() );
	parameters = inputJSONvalue.ToObject();

	// Add OnButtons parameters
	parameters["PageCount"] 		= (int) PageCount;
	parameters["Signals"] 			= (int) Signals;
	parameters["SignalWidth"] 		= SignalWidth;
	parameters["SignalLength"] 	= SignalLength;
	parameters["SignalSpacing"] 	= SignalSpacing;
	parameters["WellRadii"] 		= WellRadii;
	
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

/* =============================================================================
	Method for drawing the Device built from drawSignal and drawSignalVersion2

	@param    none    nothing
	@return   int     status of method
	========================================================================== */
int OnButtons::draw() {

	// Clear Component(s) if present
	while (getComponentCount() > 0) {
		deleteComponent(0);
	}

	// Initialize
	Component* box;
	Polygon* p;
	Page* pg;
	int status = 0;
	double reservoirX 	= getRegistrationX();
	double reservoirY 	= getRegistrationY();
	double signalSourceX = reservoirX + getSignalLength();
	double signalSourceY = 0.0;
	double signalSinkX 	= signalSourceX + getSignalLength();
	double signalSinkY 	= 0.0;
	// Used for calculations
	double offsetY = RESERVOIR_HEIGHT*getCount();


	// Specify Colors
	cb.setColor('A', 1.0); // Device Color: Black
	cw.setColor('A', 0.0); // Paper Color: White
	cg.setColor('A', 0.5); // Tape Color: Grey

	// Build the background
	for (unsigned i = 0; i < (registry.getPageCount() - 1); i++) {
	pg = registry.getPageAt(i);
		box = new Component("basePlate", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(0.0,getRegistrationY()-offsetY);
		p->addVertex(2*(getSignalLength()+RESERVOIR_WIDTH), getRegistrationY()-offsetY);
		p->addVertex(2*(getSignalLength()+RESERVOIR_WIDTH), getRegistrationY()+offsetY); // ur
		p->addVertex(0.0,getRegistrationY()+offsetY);// RESERVOIR_HEIGHT*getCount()); //ul
		p->addVertex(0.0, 0);
		p->setStrokeWidth(0.0); // no border

		// Determine Color
		if ( (i % 2) == 0 ) {
			p->setFill(cb); // Paper Layer, black background
			p->setStroke(cb);
		} else {
			p->setFill(cg); // Pape Layer, grey background
			p->setStroke(cg);
		}

	box->addPrimitive("baseplate", p);
	box->moveTo(getRegistrationX()-RESERVOIR_WIDTH, getRegistrationY()-offsetY);//calculate box location
	status += addComponent(box, pg);
	}
    setRegistrationY(getRegistrationY()+offsetY-2*RESERVOIR_HEIGHT);
	// While i is less than the total number of signals
	unsigned i =0;
	while(i<getCount()){

		/*
		 * Update the Y location of reservoir
		 * signal source and signal sink
		 */
		reservoirY 		= getRegistrationY();
		signalSourceY 	= getRegistrationY(); // Reservoir is the location for signal source
		signalSinkY   	= signalSourceY;

		/* Add signal
		 * drawSignal will change Y registration
		 * to make room for a new signal
		 */
		status += drawSignal(reservoirX, 	reservoirY,
									signalSourceX, signalSourceY,
									signalSinkX, 	signalSinkY);
		i++; // Count added button


		/* If i is still less than the total number of signals,
		 * draw another signal.  The reason why I call it again here is because
		 * the pattern alternates the button directions every two buttons
		 * This was a safe way to insure the pattern was maintained
		 */
		if(i<getCount()){

			// Update reservoir location
			reservoirY 	= getRegistrationY();
			signalSourceY = getRegistrationY();
			signalSinkY   = signalSourceY;

			// Add signal
			status += drawSignal(reservoirX, 	reservoirY,
										signalSourceX, signalSourceY,
										signalSinkX, 	signalSinkY);
			i++; // count added signal
		}

		/* Check to see if we still need more signals, if so,
		 * it is time to draw version two of the button
		 */
		if(i<getCount()){
			// Registration Y has changed, update signal location
			reservoirY 		= getRegistrationY();
			signalSourceY 	= getRegistrationY();
			signalSinkY   	= signalSourceY;

			/*
			 * Draw a round button using drawSignalR()
			 * Registration Y is updated by drawSignalR()
			 */
			status += drawSignalVersion2(reservoirX, 	reservoirY,
												  signalSourceX, signalSourceY,
												  signalSinkX, 	signalSinkY);
			i++; // Count added signal.
		}

		/*
		 * If we still need another signal, draw another
		 * round button this will complete the pattern
		 */
		if(i<getCount()){
			// Registration Y has changed, update signal location
			reservoirY 		= getRegistrationY();
			signalSourceY 	= getRegistrationY();
			signalSinkY   	= signalSourceY;


			// Add signal
			status += drawSignalVersion2(reservoirX, 	reservoirY,
												  signalSourceX, signalSourceY,
												  signalSinkX, 	signalSinkY);
		i++; // count added signal
		}
	}
	return status;
}

/* ============================================================================
	Draw a single square button, and update Y registration

	@param    double	reservoir location X
	@param    double	reservoir location Y
	@param    double	channel source location X
	@param    double	channel source location Y
	@param    double	channel sink location X
	@param    double	channel sink location Y
	@return   int         status of method
	========================================================================== */
int OnButtons::drawSignal(double resX, double resY,
							double srcX, double srcY,
							double sinkX, double sinkY) {
	int status = 0;
	Page* pg;
	Well* w;
	Channel* ch;
	Component* box;
	Polygon*  p;
	// Used to calculate registrationY after signal is drawn
	double regYUpdate = srcY-2*RESERVOIR_HEIGHT;

	// Calculate Box corners
	double ulX = -RESERVOIR_WIDTH/2.0;
	double ulY =  RESERVOIR_HEIGHT/2.0;
	double urX =  RESERVOIR_WIDTH/2.0;
	double urY =  RESERVOIR_HEIGHT/2.0;
	double llX = -RESERVOIR_WIDTH/2.0;
	double llY = -RESERVOIR_HEIGHT/2.0;
	double lrX =  RESERVOIR_WIDTH/2.0;
	double lrY = -RESERVOIR_HEIGHT/2.0;

	// Adjust parameters for reservoir height and signal count
	sinkY = sinkY-RESERVOIR_HEIGHT*getCount()+RESERVOIR_HEIGHT;
	srcY  = srcY-RESERVOIR_HEIGHT*getCount()+RESERVOIR_HEIGHT;
	resY  = resY-RESERVOIR_HEIGHT*(getCount())+RESERVOIR_HEIGHT;

	// Set up automatic naming
	string sourceNamePrefix = "source_";
	string sinkNamePrefix = "sink_";
	string sourceName = "";
	string sinkName = "";
	std::ostringstream oss;

	/*
	 * This loop iterates through each Page and adds the needed
	 * components/primitives to the device
	 */
	for (unsigned i = 0; i < (registry.getPageCount()-1); i++) {

		// Generate ID's
		pg = registry.getPageAt(i);
		oss << i;
		sourceName = sourceNamePrefix;
		sourceName += oss.str();
		sinkName = sinkNamePrefix;
		sinkName += oss.str();

		/*
		 * For this version of the button every
		 * layer gets the polygon reservoir
		 */
		box = new Component(sourceName, pg);// Reservoir
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(llX, llY); // ll
		p->addVertex(lrX, lrY); // lr
		p->addVertex(urX, urY); // ur
		p->addVertex(ulX, ulY); //ul
		p->setStrokeWidth(0.0);
		p->setFill(cw);
		box->addPrimitive(sourceName, p);

		// Location of bottom of background + offset to center
		box->moveTo(resX, resY);
		status += addComponent(box, pg);

		// Channel at layer 0
		if(i==0){
			ch = new Channel("Channel0", pg);
			ch->setHomeLayer(pg);
			ch->setSource(resX, resY);
			ch->setSink(srcX, srcY);
			ch->setWidth( getSignalWidth() );
			ch->setBorder(cb,0.0);
			ch->setFill(cw);
			ch->draw();
			status += addComponent(ch, pg);
		}

		/*
		 * At layer 0 these wells round off the channel
		 * At layer 1-4 they are the holes
		 */
		if (i<5){

			w = new Well(sourceName, pg);
			w->setRadius(WellRadii/2.0);
			w->setBorder(cw, 0.0);
			w->setFill(cw);
			w->draw();
			w->moveTo(srcX, srcY);
			status += addComponent(w, pg);
		}

		// Place sink wells
		if (i>3){
			w = new Well(sinkName, pg);
			w->setRadius(WellRadii/2.0);
			w->setBorder(cw, 0.0);
			w->setFill(cw);
			w->draw();
			w->moveTo(sinkX, srcY);
			status += addComponent(w, pg);
		}

		// Layer 5: Connector Channels
		pg = registry.getPageAt(4);
		ch = new Channel("Channel4", pg);
		ch->setHomeLayer(pg);
		ch->setSource(srcX, srcY);
		ch->setSink(sinkX, srcY);
		ch->setWidth( getSignalWidth() );
		ch->setBorder(cb,0.0);
		ch->setFill(cw);
		ch->draw();
		status += addComponent(ch, pg);

		// Layer 7: Buttons
		pg = registry.getPageAt(6);
		box = new Component(sourceName, pg);
		p = new Polygon();
		p->setID("polygonButton");
		p->addVertex(llX, llY); // ll
		p->addVertex(lrX, lrY); // lr
		p->addVertex(urX,urY); // ur
		p->addVertex(ulX, ulY); //ul
		p->setStrokeWidth(0.2);
		p->setFill(cb);
		p->setStroke(cg);
		box->addPrimitive(sourceName, p);
		box->moveTo(srcX, srcY);
		status += addComponent(box, pg);
	}

	// Update RegistrationY
	setRegistrationY(regYUpdate);

	return 0;
}

/* ============================================================================
	Draw a single round button, and update Y registration

	@param    double	reservoir location X
	@param    double	reservoir location Y
	@param    double	channel source location X
	@param    double	channel source location Y
	@param    double	channel sink location X
	@param    double	channel sink location Y
	@return   int         status of method
	========================================================================== */
int OnButtons::drawSignalVersion2(double resX, double resY,
							double srcX, double srcY,
							double sinkX, double sinkY) {
	// Initialize
	int status = 0;
	Page* pg;
	Well* w;
	Channel* ch;
	Component* box;
	Polygon*  p;

	// Used to calculate registrationY after signal is drawn
	double regYUpdate = srcY-2*RESERVOIR_HEIGHT;

	// Calculate Box corners
	double ulX = -RESERVOIR_WIDTH/2.0;
	double ulY =  RESERVOIR_HEIGHT/2.0;
	double urX =  RESERVOIR_WIDTH/2.0;
	double urY =  RESERVOIR_HEIGHT/2.0;
	double llX = -RESERVOIR_WIDTH/2.0;
	double llY = -RESERVOIR_HEIGHT/2.0;
	double lrX =  RESERVOIR_WIDTH/2.0;
	double lrY = -RESERVOIR_HEIGHT/2.0;

	// Adjust parameters for reservoir height and signal count
	sinkY = sinkY-RESERVOIR_HEIGHT*getCount()+RESERVOIR_HEIGHT;
	srcY  = srcY-RESERVOIR_HEIGHT*getCount()+RESERVOIR_HEIGHT;
	resY  = resY-RESERVOIR_HEIGHT*(getCount())+RESERVOIR_HEIGHT;

	// Set up automatic naming
	string sourceNamePrefix = "source_";
	string sinkNamePrefix = "sink_";
	string sourceName = "";
	string sinkName = "";
	std::ostringstream oss;

	/*
	 * This loop iterates through each Page and adds the needed
	 * components/primitives to the device
	 */
	for (unsigned i = 0; i < (registry.getPageCount()-1); i++) {

		// Generate ID's
		pg = registry.getPageAt(i);
		oss << i;
		sourceName = sourceNamePrefix;
		sourceName += oss.str();
		sinkName = sinkNamePrefix;
		sinkName += oss.str();

		// Place sink wells for all layers
		w = new Well(sinkName, pg);
		w->setRadius(WellRadii/2.0);
		w->setBorder(cw, 0.0);
		w->setFill(cw);
		w->draw();
		w->moveTo(sinkX, sinkY);
		status += addComponent(w, pg);

		// Add channel for layer 0
		if(i==0){
			ch = new Channel("Channel0", pg);
			ch->setHomeLayer(pg);
			ch->setSource(resX+getSignalLength(), resY);
			ch->setSink(srcX+getSignalLength(), srcY);
			ch->setWidth( getSignalWidth() );
			ch->setBorder(cb,0.0);
			ch->setFill(cw);
			ch->draw();
			status += addComponent(ch, pg);
		}

		/*
		 * Build round channel ends for layers 0 and 4
		 * Build source holes for layers 1 through 3
		 */
		if(i<5){
			w = new Well(sourceName, pg);
			w->setRadius(WellRadii/2.0);
			w->setBorder(cw, 0.0);
			w->setFill(cw);
			w->draw();
			w->moveTo(srcX, srcY);
			status += addComponent(w, pg);
		}

		// Build square reservoirs for layers 4 through 6
		if(i>3){
			box = new Component(sourceName,pg);
			p = new Polygon();
			p->setID("polygon");
			p->addVertex(llX, llY); // ll
			p->addVertex(lrX, lrY); // lr
			p->addVertex(urX, urY); // ur
			p->addVertex(ulX, ulY); //ul
			p->setStrokeWidth(0.0);
			p->setFill(cw);
			box->addPrimitive(sourceName, p);
			box->moveTo(resX, resY);
			status += addComponent(box, pg);
		}


		// Layer 5: Reservoir Channels
		pg = registry.getPageAt(4);
		ch = new Channel("Channel0", pg);
		ch->setHomeLayer(pg);
		ch->setSource(resX, resY);
		ch->setSink(srcX, srcY);
		ch->setWidth( getSignalWidth() );
		ch->setBorder(cb,0.0);
		ch->setFill(cw);
		ch->draw();
		status += addComponent(ch, pg);

		//layer 7: Round Buttons
		pg = registry.getPageAt(6);
		w = new Well(sourceName, pg);
		w->setRadius(WellRadii);
		w->setBorder(cw, 0.3);
		w->setFill(cb);
		w->draw();
		w->moveTo(srcX, srcY);
		status += addComponent(w, pg);
	}

	// Update Y registration
	setRegistrationY(regYUpdate);

	return 0;
}
/* ============================================================================
	Set the space between signals for the Titration Class

	@param    double      space between signals
	@return   int         status of method
	========================================================================== */
int OnButtons::setSignalSpacing(double s) {
	if (s < 0.0) return -1;
	SignalSpacing = s+getSignalWidth();
	return 0;
}
/* ============================================================================
	get the space between signals for the Titration Class

	@param    none    	  nothing
	@return   double      space between signals
	========================================================================== */
double OnButtons::getSignalSpacing() {
	return SignalSpacing;
}

/* ============================================================================
	Set Radius used for all wells

	@param    double	  radius
	@return   int         status of method
	========================================================================== */
int OnButtons::setWellRadii(double radius) {
	if(radius>RESERVOIR_WIDTH){
		WellRadii = RESERVOIR_WIDTH;
		return 0;
	}
	WellRadii = radius;
	return 0;
}

/* ============================================================================
	Get radius value used for all wells

	@param    none    	  nothing
	@return   double      WellRadii
	========================================================================== */
double OnButtons::getWellRadii() {
	return WellRadii;
}

/* ============================================================================
	Set the number of signals for the OnButtons device

	@param    unsigned    ID
	@return   int         status of method
	========================================================================== */
int OnButtons::setCount(unsigned count) {
	Signals = count;
	return 0;
}

/* ============================================================================
	Set the number of Pages for the OnButtons device

	@param    unsigned    number of Pages
	@return   int         status of method
	========================================================================== */
int OnButtons::setPageCount(unsigned count) {
	PageCount = count;
	return 0;
}

/* ============================================================================
	Set the value for signalWidth

	@param    double      width
	@return   int         status of method
	========================================================================== */
int OnButtons::setSignalWidth(double w) {
	if (w < 0.0) return -1;
	if (w>RESERVOIR_HEIGHT){
		SignalWidth = RESERVOIR_HEIGHT;
		return 0;
	}
	SignalWidth = w;
	return 0;
}

/* ============================================================================
	Set the length of the channels

	@param    double      channel length
	@return   int         status of method
	========================================================================== */
int OnButtons::setSignalLength(double l) {
	if (l < 0.0) return -1;
	SignalLength = l;
	return 0;
}

/* ============================================================================
	Get the number of signals

	@param    none    	  nothing
	@return   unsigned    number of signals
	========================================================================== */
unsigned OnButtons::getCount() {
	return Signals;
}

/* ============================================================================
	Get the number of Pages

	@param    none    	  nothing
	@return   unsigned    number of Pages
	========================================================================== */
unsigned OnButtons::getPageCount() {
	return PageCount;
}

/* ============================================================================
	Get width of channels

	@param    none   	  nothing
	@return   double      width of channels
	========================================================================== */
double OnButtons::getSignalWidth() {
	return SignalWidth;
}

/* ============================================================================
	Get length of channels

	@param    none   	  nothing
	@return   double      length of channel
	========================================================================== */
double OnButtons::getSignalLength() {
	return SignalLength;
}

