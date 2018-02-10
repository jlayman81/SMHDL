/*	=============================================================================
	ImmunoSensor Class Source
	
	@version	0.1.1
	@author	JoshuaP
	========================================================================== */

#include "ImmunoSensor.h"

/* =============================================================================
	TO DO
	Well border does not show when the well is placed on top of a channel
	Large polygon waste pad has round edges, how to reproduce?
	WastePad on layer 4 doesn't render with gray fill
	Can't add light grey color object?
	More accurate string IDs for box components
	Review commented out blocks in ImmunoSensor.h for removal

	NOTE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	Try to minimize calculations in a method. In the draw method there is a lot
	of repeated calculations. Perform them once and save as a variable. This
	practice may not have much savings in a small scope, but can make a large
	difference in loops.
	<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	- JP
	
	========================================================================== */

/*	=============================================================================
	Default Constructor for ImmunoSensor Class
	
	@param 		none		nothing
	@return 	none		nothing
	========================================================================== */
ImmunoSensor::ImmunoSensor() : Device() {
	init();
}

/* =============================================================================
	Constructor for ImmunoSensor Class with a string id parameter

	@param    string  ID of the component
	@return   none    nothing
	========================================================================== */
ImmunoSensor::ImmunoSensor(string id) : Device(id) {
	init();
}

/* =============================================================================
	Constructor for ImmunoSensor Class with a substrate id parameter

	@param    substrate		ID of the substrate
	@return   none    		nothing
	========================================================================== */
ImmunoSensor::ImmunoSensor(Page* p) : Device(p) {
	init();
}

/* =============================================================================
	Constructor for ImmunoSensor Class with a string ID parameter and
	a substrate ID parameter

	@param    string     the id of the component
	@param    substrate  substrate id
	@return   none       nothing
	========================================================================== */
ImmunoSensor::ImmunoSensor(string id, Page* p) : Device(id, p) {
	init();
}


/*	=============================================================================
	Destructor for ImmunoSensor Class
	
	@param 		none		nothing
	@return 	none		nothing
	========================================================================== */
ImmunoSensor::~ImmunoSensor() {
	//
}

/* =============================================================================
	Initializer for ImmunoSensor Class
	
	@param    none	nothing
	@return   none	nothing
	========================================================================== */
int ImmunoSensor::init() {

	//Initialize
	setClassID("ImmunoSensor");
	Page* pg;

	// Refer to Fig. 3A @paper.
	// Base Page
	pg = new Page("01_Base");
	registry.registerPage(pg);

	// Signal Connector Page
	pg = new Page("02_Base");
	registry.registerPage(pg);

	// Signal Well Page
	pg = new Page("03_DelayChannel");
	registry.registerPage(pg);

	// Signal Well Page
	pg = new Page("04_ValveLayer");
	registry.registerPage(pg);

	// Signal Well Page
	pg = new Page("05_CunjugatePad");
	registry.registerPage(pg);

	// Signal Well Page
	pg = new Page("06_SamplePad");
	registry.registerPage(pg);

	// Signal Well Page
	pg = new Page("06_SamplePad2");
	registry.registerPage(pg);

	return 0;
}

/* =============================================================================
	Method for drawing the Device built from components and drawSignal()

	@param    none    nothing
	@return   int     status of method
	========================================================================== */
int ImmunoSensor::draw() {

	//Initialize
	int status = 0;
	double channelSourceX 	= 0;
	double channelSourceY 	= 0;
	double channelSinkX  	= 0;
	double channelSinkY 	= 0;
	Page* pg;
	Component* box, *el;
	Polygon* p;
	Channel* c;
	Ellipse* e;

	// Set channel widths
	double chWidth	 		= 2.5;
	double chWideWidth		= 4.0;


	// Specify Colors
	cb.setColor('A', 1.0); // Color: Black
	cw.setColor('A', 0.0); // Color: White
	cg.setColor('A', 0.5); // Color: Grey

	// Dimensions for white background from Fig. 3C @paper
	double uY = 36; // Device height

	// Set well and valve radius
	double wellRadius = 1.25;
	
	//Build Base Layer
	pg = registry.getPage("01_Base");
	status += drawBackground(cg,pg);
	
	//Build Base Layer 2
	pg = registry.getPage("02_Base");

	// Build the white background
	status += drawBackground(cw,pg);

	// Add Waste pad per Fig 3A @paper
	status += drawWastePad(cb,cw,0.2, pg);

	//Build Delay Channel Layer
	pg = registry.getPage("03_DelayChannel");
	cg.setColor('A', 0.15); // Color:  Light Grey

	// Build the background
	status += drawBackground(cb, pg);

	// Add Waste pad per Fig 3A @paper
	status += drawWastePad(cb,cg,0.0, pg);

	// Add Delay Channels, dimensions from Fig. 6 @paper
	channelSourceX = getRegistrationX() + 11.5;
	channelSourceY = getRegistrationY() + ( 15.5 - ( uY / 2.0 ) );
	channelSinkX   = channelSourceX + 5.6;
	channelSinkY   = channelSourceY;

	// Add first wide channel
	status += drawChannel(channelSourceX, channelSourceY,
								 channelSinkX, channelSourceY, chWideWidth, cg, pg);

	status += drawChannel(channelSinkX - 2, channelSourceY,
								 channelSinkX - 2, (channelSinkY + 9.0), chWidth, cg, pg);

	// Wells 1 and 2 numbered left to right, bottom to top @paper
	// Add well 1
	// change fill to grey when outline works
	status += drawHole(channelSourceX, channelSinkY, wellRadius, cb, cb, pg);

	//update channelSource/sink
	channelSourceY = channelSinkY+9.0;

	// Add well 2
	status += drawHole(channelSinkX, channelSinkY, wellRadius, cb, cb, pg);

	// Add connector channels to the next two wells
	status += drawChannel(channelSinkX-2.0, channelSourceY,
			channelSinkX-2.0-6.0, channelSourceY, chWidth, cg, pg);

	// Update sink
	channelSinkY = channelSourceY-4.5;
	channelSinkX = channelSourceX -2.4;

	status += drawChannel(channelSinkX, channelSourceY+1,
								channelSinkX, channelSinkY+1, chWidth, cg, pg);

	// Add second wide channel on the device
	status += drawChannel(channelSinkX-3.0, channelSinkY,
			channelSinkX+2.0, channelSinkY, chWideWidth, cg, pg);

	// Add wells 3 and 4
	status += drawHole(channelSinkX-3.0, channelSinkY, wellRadius, cb, cb, pg);
	status += drawHole(channelSourceX, channelSinkY, wellRadius, cb, cb, pg);

	// Update source/sink
	channelSinkY = channelSourceY + 4.5;
	channelSinkX = channelSinkX - 2.8;
	channelSourceY = channelSourceY + 1;

	// Add connector channels to last hole
	status += drawChannel(channelSinkX+2.8, channelSourceY,
								 channelSinkX, channelSourceY, chWidth, cg, pg);
	status += drawChannel(channelSinkX, channelSourceY,
								channelSinkX, channelSinkY, chWidth, cg, pg);
	status += drawChannel(channelSinkX, channelSinkY,
							channelSinkX + 4.8, channelSinkY, chWidth, cg, pg);
	status += drawChannel(channelSourceX, channelSinkY,
								 channelSourceX, channelSinkY, chWideWidth, cg, pg);
	// Add well 5
	status += drawHole(channelSourceX, channelSinkY, wellRadius, cb, cb, pg);

	// Build valve layer
	pg = registry.getPage("04_ValveLayer");
	cg.setColor('A', 0.5); // Color: Grey
	
	// Reset location variables
	channelSourceY = getRegistrationY()+15.5-uY/2.0;
	channelSinkX   = channelSourceX + 5.6;
	channelSinkY   = channelSourceY;

	// Draw background and waste pad
	status += drawBackground(cw,pg);
	status += drawWastePad(cg,cg,0.0,pg);

	// Add valves (wells) numbered left to right, bottom to top

	// Add well 1
	// change fill to grey when outline works
	status += drawHole(channelSourceX, channelSinkY, wellRadius, cb, cb, pg);

	// Add well 2
	status += drawHole(channelSinkX, channelSinkY, wellRadius, cb, cb, pg);

	//update sink
	channelSinkX = channelSinkX-2.0-6.0-3.0;
	channelSinkY = channelSinkY+4.5;

	// Add wells 3,4, and 5
	status += drawHole(channelSinkX, channelSinkY, wellRadius, cb, cb, pg);
	status += drawHole(channelSourceX, channelSinkY, wellRadius, cb, cb, pg);
	status += drawHole(channelSourceX, channelSinkY + 9, wellRadius, cb, cb, pg);

	// Build conjugate pad layer
	pg = registry.getPage("05_CunjugatePad");

	// Reset location variables
	channelSinkX   = channelSourceX + 5.6;
	channelSinkY   = channelSourceY;

	// Add white box Fig. 3A @ paper
	box = new Component("BasePlate", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX()+9.0,channelSinkY-1); // ll
	p->addVertex(getRegistrationX()+14,channelSinkY-1); // lr
	p->addVertex(getRegistrationX()+14,channelSourceY-13); // ur
	p->addVertex(getRegistrationX()+9.0,channelSourceY-13); //ul
	p->setStrokeWidth(0.2); // black border
	p->setFill(cg); // Base layer, white background
	box->addPrimitive("BasePlate", p);
	box->moveTo(getRegistrationX(),getRegistrationY()+8);
	status += addComponent(box, pg);

	// Black line that coincides with the top of the waste pad
	box = new Component("BasePlate", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX()+9.0,getRegistrationY()-5.5); // ll
	p->addVertex(getRegistrationX()+14,getRegistrationY()-5.5); // lr
	p->addVertex(getRegistrationX()+14,getRegistrationY()-5.0); // ur
	p->addVertex(getRegistrationX()+9.0,getRegistrationY()-5.0); //ul
	p->setStrokeWidth(0.0); // black border
	p->setFill(cb); // Base layer, white background
	box->addPrimitive("BasePlate", p);
	box->moveTo(getRegistrationX(),getRegistrationY()-0.5);
	status += addComponent(box, pg);

	// Add conjugate pad
	box = new Component("BasePlate", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX()+9.0,getRegistrationY()); // ll
	p->addVertex(getRegistrationX()+14,getRegistrationY()); // lr
	p->addVertex(getRegistrationX()+14,getRegistrationY()+7); // ur
	p->addVertex(getRegistrationX()+9.0,getRegistrationY()+7); //ul
	p->setStrokeWidth(0.0); // black border
	p->setFill(cg); // Base layer, white background
	box->addPrimitive("BasePlate", p);
	box->moveTo(getRegistrationX(),getRegistrationY()+8);
	status += addComponent(box, pg);

	// Add Well 1
	status += drawHole(channelSourceX, channelSinkY, wellRadius, cb, cb, pg);
	
	// Add Well 4
	status += drawHole(channelSourceX, channelSinkY+4.5, wellRadius, cb, cb, pg);


	// Build SamplePad Layer
	pg = registry.getPage("06_SamplePad");
	
	// Reset location variables
	channelSourceX = getRegistrationX()+11.5;
	channelSourceY = getRegistrationY()+15.5-uY/2.0;
	channelSinkX = channelSourceX + 5.6;
	channelSinkY = channelSourceY;

	cg.setColor('A', 0.15); // Color:  Light Grey

	status += drawBackground(cb, pg);
	
	status += drawWastePad(cg,cg,0.0, pg);
	status += drawChannel(channelSourceX, getRegistrationY()-6,
			channelSourceX, getRegistrationY()+12, 5.0, cg, pg);


	// Add white cross-sectional strips
	c = new Channel("strip",pg);
	c->setWidth(2.0);
	c->setFill(cw);
	c->setSource(getRegistrationX()+8.5, getRegistrationY()-4);
	c->setSink(getRegistrationX()+14.5, getRegistrationY()-4);
	c->draw();
	status += addComponent(c,pg);

	c = new Channel("strip",pg);
	c->setWidth(2.0);
	c->setFill(cw);
	c->setSource(getRegistrationX()+9, getRegistrationY()+6.25);
	c->setSink(getRegistrationX()+14,getRegistrationY()+6.25);
	c->draw();
	status += addComponent(c,pg);

	// Add wells

	// Add well 2
	status += drawHole(channelSinkX, channelSinkY,wellRadius+0.25,cg,cg,pg);

	// Update channel location values
	channelSourceX = channelSinkX-2.0-6.0;
	channelSourceY = channelSinkY+9.0;

	// Add wells 3 and 5
	status += drawHole(channelSourceX-3.0, channelSourceY-4.5,wellRadius+0.25,cg,cg,pg);
	status += drawHole(getRegistrationX()+11.5,channelSourceY+3,wellRadius,cb,cb,pg);

	// Add ellipses and connection channels
	el = new Component("ellipse", pg);
	e = new Ellipse(getRegistrationX()+45.75,channelSourceY+71.5,3.5,8);
	e->setStrokeWidth(0.0);
	e->setFill(cg);
	el->addPrimitive("ellipse",e);
	status += addComponent(el, pg);
	status += drawChannel(channelSourceX-3.0, channelSourceY-4.5,
			channelSourceX-3.25, channelSourceY-2,1.75,cg,pg);

	el = new Component("ellipse", pg);
	e = new Ellipse(getRegistrationX()+57.5,channelSourceY+67,3.5,8);
	e->setStrokeWidth(0.0);
	e->setFill(cg);
	el->addPrimitive("ellipse",e);
	status += addComponent(el, pg);
	status += drawChannel(channelSinkX, channelSinkY,
			channelSinkX+0.25, channelSinkY+2.5,1.75,cg,pg);

	return status;
}

/* =============================================================================
	Method for drawing base polygons including the polygon background pattern
	for the ImmunoSensor device

	@param    Color   		fill color
	@param 	  Page*	Page
	@return   int     		status of method
	========================================================================== */
int ImmunoSensor::drawBackground(Color fillColor, Page* pg){
	int status = 0;
	Component* box;
	Polygon* p;

	// Dimensions for white background from Fig. 3C @paper
	double rX = 23; // Device width
	double uY = 36; // Device height
	// Build the white background
		box = new Component("BasePlate", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(getRegistrationX(),getRegistrationY()); // ll
		p->addVertex(rX,getRegistrationY()); // lr
		p->addVertex(rX,uY); // ur
		p->addVertex(getRegistrationX(),uY); //ul
		p->setStrokeWidth(0.1); // black border
		p->setFill(cw); // Base layer, white background
		box->addPrimitive("BasePlate", p);
		box->moveTo(getRegistrationX(),getRegistrationY()-uY/2.0);
		status += addComponent(box, pg);

		// Build the block pattern.
		// Dimensions estimated from Fig. 6 @paper
		// Pattern is built from one tall polygon
		// and 3 wide polygons
		box = new Component("TallBox", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(getRegistrationX()+2.0,getRegistrationY()+1.0); // ll Fig. 6 @paper
		p->addVertex(rX-2.0,getRegistrationY()+1.0); // lr
		p->addVertex(rX-2.0,uY-1.0); // ur
		p->addVertex(getRegistrationX()+2.0,uY-1.0); //ul
		p->setStrokeWidth(0.0); // no border
		p->setFill(fillColor); // Base pattern, grey background
		box->addPrimitive("TallBox", p);
		box->moveTo(getRegistrationX(),getRegistrationY()-uY/2.0);
		status += addComponent(box, pg);

		// Build 3 wide boxes
		box = new Component("WideBox", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(getRegistrationX()+1.0,getRegistrationY()+3.0); // ll Fig. 6 @paper
		p->addVertex(rX-1.0,getRegistrationY()+3.0); // lr
		p->addVertex(rX-1.0,uY-25.0); // ur
		p->addVertex(getRegistrationX()+1.0,uY-25.0); //ul
		p->setStrokeWidth(0.0); // no border
		p->setFill(fillColor); // Base pattern, black background
		box->addPrimitive("TallBox", p);
		box->moveTo(getRegistrationX(),getRegistrationY()-uY/2.0);
		status += addComponent(box, pg);

		box = new Component("WideBox", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(getRegistrationX()+1.0,getRegistrationY()+14.0); // ll Fig. 6 @paper
		p->addVertex(rX-1.0,getRegistrationY()+14.0); // lr
		p->addVertex(rX-1.0,uY-14.0); // ur
		p->addVertex(getRegistrationX()+1.0,uY-14.0); //ul
		p->setStrokeWidth(0.0); // no border
		p->setFill(fillColor); // Base pattern, black background
		box->addPrimitive("TallBox", p);
		box->moveTo(getRegistrationX(),getRegistrationY()-uY/2.0);
		status += addComponent(box, pg);

		box = new Component("WideBox", pg);
		p = new Polygon();
		p->setID("polygon");
		p->addVertex(getRegistrationX()+1.0,getRegistrationY()+25.0); // ll Fig. 6 @paper
		p->addVertex(rX-1.0,getRegistrationY()+25.0); // lr
		p->addVertex(rX-1.0,uY-3.0); // ur
		p->addVertex(getRegistrationX()+1.0,uY-3.0); //ul
		p->setStrokeWidth(0.0); // no border
		p->setFill(fillColor); // Base pattern, black background
		box->addPrimitive("TallBox", p);
		box->moveTo(getRegistrationX(),getRegistrationY()-uY/2.0);
		status += addComponent(box, pg);



	return status;
}

/* =============================================================================
	Method for drawing channels with rounded edges for the ImmunoSensor device

	@param    double  		Channel source X
	@param    double  		Channel source Y
	@param    double  		Channel sink X
	@param    double  		Channel sink Y
	@param    double  		Channel width
	@param    Color   		Fill color
	@param    Substrate*	Substrate
	@return   int     		status of method
	========================================================================== */
int ImmunoSensor::drawChannel(double sourceX, double sourceY, double sinkX,
								double sinkY, double width,
									Color fillColor, Page* pg){
	// Initialize
	int status = 0;
	Channel* c;
	Well* w;

	// Draw channel
	c = new Channel("DelayChannel",pg);
	c->setWidth(width);
	c->setFill(fillColor);
	c->setSource(sourceX, sourceY);
	c->setSink(sinkX,sinkY);
	c->draw();
	status += addComponent(c,pg);

	// Add round edges
	w = new Well("RoundCorners",pg);
	w->setRadius(width/2.0);
	w->setBorder(fillColor, 0.0);
	w->setFill(fillColor);
	w->draw();
	w->moveTo(sourceX,sourceY);
	status += addComponent(w, pg);

	w = new Well("RoundCorners",pg);
	w->setRadius(width/2.0);
	w->setBorder(fillColor, 0.0);
	w->setFill(fillColor);
	w->draw();
	w->moveTo(sinkX,sinkY);
	status += addComponent(w, pg);

	return status;
}

/* =============================================================================
	Method for drawing holes and valves for ImmunoSensor class

	@param    double  		center X
	@param    double  		center Y
	@param    double  		radius
	@param    Color   		border
	@param    Color   		fill
	@param    Page*  			PAage
	@return   int     		status of method
	========================================================================== */
int ImmunoSensor::drawHole(double centerX, double centerY, 
									double radius, //centerX,Y, radius
									Color lineColor, Color fillColor, 
									Page* pg){ // border, fill, Page
	int status = 0;
	Well* w;
	w = new Well("Hole", pg);
	w->setRadius(radius);
	w->setFill(fillColor);
	w->setBorder(lineColor, 0.1);
	w->draw();
	w->moveTo(centerX, centerY);
	status += addComponent(w, pg);

	return status;
}

/* =============================================================================
	Method for drawing the large waste pad for ImmunoSensor class
	FIG. 3A @paper

	@param    Color   		border
	@param    Color   		fill
	@param    double  		strokeWidth
	@param    Page*			Page
	@return   int     		status of method
	========================================================================== */
int ImmunoSensor::drawWastePad(Color borderColor, Color fillColor, 
										 double strokeWidth, Page* pg){
	int status = 0;
	double rX = 23; // Device width
	double uY = 36; // Device height
	Component* box;
	Polygon* p;
	box = new Component("WastePad", pg);
	p = new Polygon();
	p->setID("polygon");
	p->addVertex(getRegistrationX()+3.0,getRegistrationY()+2.8); // ll
	p->addVertex(rX-3.0,getRegistrationY()+2.8); // lr
	p->addVertex(rX-3.0,getRegistrationY()+12.3); // ur
	p->addVertex(getRegistrationX()+3.0,getRegistrationY()+12.3); //ul
	p->setStrokeWidth(strokeWidth); // black border
	p->setFill(fillColor); // Base layer, white background
	box->addPrimitive("WastePad", p);
	box->moveTo(getRegistrationX(),getRegistrationY()-uY/2.0);
	status += addComponent(box, pg);
	return status;
}

/*	==========================================================================
	JSON import method for ImmunoSensor class

	@param 	   	string		s
	@return 	int			status of method
	========================================================================== */
int ImmunoSensor::importParameters(string s) {

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
	JSON export method for ImmunoSensor class

	@param 		null		nothing
	@return 	string		json serialized parameters
	========================================================================== */
string ImmunoSensor::exportParameters() {

	// Build Object
	json::Object parameters;

	// Retrieve Base Class Parameters
	json::Value inputJSONvalue = json::Deserialize( Device::exportParameters() );
	parameters = inputJSONvalue.ToObject();

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
