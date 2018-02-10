/*  =============================================================================
    Folding Card Class Definition
    
    @version    0.1.4
    @author RH, JesseL
    ========================================================================== */

#include "FoldingCard.h"

using namespace std;

/*  =============================================================================
    Default Constructor for FoldingCard Class
    
    @param  none        nothing
    @return     none        nothing
    ========================================================================== */
FoldingCard::FoldingCard() : Device() {
	init();
}

/*  =============================================================================
    Default Constructor for FoldingCard Class with string ID passed in
    
    @param  none        nothing
    @return     none        nothing
    ========================================================================== */
FoldingCard::FoldingCard(string id) : Device(id) {
    init();
}

/* =============================================================================
	Default Destructor for Raceway Class

	@param	none	nothing
	@return	none	nothing
	========================================================================== */
FoldingCard::~FoldingCard() {

}

/*	==========================================================================
	DESC
	
	@param 	null		nothing
	@return 	null		nothing
	========================================================================== */
int FoldingCard::init(){
	return setClassID("FoldingCard");
}

/*	==========================================================================
	DESC
	
	@param 	null		nothing
	@return 	null		nothing
	========================================================================== */
int FoldingCard::importParameters(string s) {
	if (s == "") return -1;
	int status = 0;
	return status;
}

/*	==========================================================================
	DESC
	
	@param 	null		nothing
	@return 	null		nothing
	========================================================================== */
string FoldingCard::exportParameters() {
	string results = "";
	return results;
}

/*  =============================================================================
    Per Compnent method for drawing the component built from the list of 
    Primitives
    
    @param  none        nothing
    @return     int     status of method
    ========================================================================== */
int FoldingCard::draw() {

	Component* fc = new Component;
	string layer0 = "source pads";
	string layer1 = "channels";
	
    fc->addLayer(layer0); // layer index 0
    fc->addLayer("channels"); // layer index 1
    
    // Volume-limited fluid source pad 1
    Circle* fsp1 = new Circle(3,7.5,1.0);
    fc->addPrimitive(layer0, fsp1);
    fsp1->setIndex(fc->getComponentSize());
    fsp1->setID("fsp1");

     // Volume-limited fluid source pad 2
    Circle* fsp2 = new Circle(14.414213,7.5,1.0);
    fc->addPrimitive(layer0, fsp2);
    fsp2->setIndex(fc->getComponentSize());
    fsp2->setID("fsp2");

    // Volume-limited fluid source pad 3
    Circle* fsp3 = new Circle(4.81839,3.11095,1.0);
    fc->addPrimitive(layer0, fsp3);
    fsp3->setIndex(fc->getComponentSize());
    fsp3->setID("fsp3");
 
    // Volume-limited fluid source pad 4
    Circle* fsp4 = new Circle(12.59661,3.11095,1.0);
    fc->addPrimitive(layer0, fsp4);
    fsp4->setIndex(fc->getComponentSize());
    fsp4->setID("fsp4");
     
    //center pentagon
    Polygon* pentagon = new Polygon();
    pentagon->addVertex(9.414213, 8);
    pentagon->addVertex(9.414213, 7);
    pentagon->addVertex(8.707107, 6.292894);
    pentagon->addVertex(8, 7);
    pentagon->addVertex(8, 8);
    fc->addPrimitive(layer1, pentagon);
    pentagon->setIndex(fc->getComponentSize());
    pentagon->setID("pentagon");  
 
    //first rectangle
    Polygon* rect1 = new Polygon();
    rect1->addVertex(8, 8);
    rect1->addVertex(8, 7);
    rect1->addVertex(4, 7);
    rect1->addVertex(4, 8);
    fc->addPrimitive(layer1, rect1);
    rect1->setIndex(fc->getComponentSize());
    rect1->setID("rect1");
     
    //second rectangle
    Polygon* rect2 = new Polygon();
    rect2->addVertex(8, 7);
    rect2->addVertex(8.707107, 6.292894);
    rect2->addVertex(5.878679, 3.464467);
    rect2->addVertex(5.171573, 4.171573);
    fc->addPrimitive(layer1, rect2);
    rect2->setIndex(fc->getComponentSize());
    rect2->setID("rect2");
 
    //third rectangle
    Polygon* rect3 = new Polygon();
    rect3->addVertex(12.242640, 4.171573);
    rect3->addVertex(11.535533, 3.464466);
    rect3->addVertex(8.707107, 6.292894);
    rect3->addVertex(9.414213, 7);
    fc->addPrimitive(layer1, rect3);
    rect3->setIndex(fc->getComponentSize());
    rect3->setID("rect3");

    //fourth rectangle
    Polygon* rect4 = new Polygon();
    rect4->addVertex(13.414213, 8);
    rect4->addVertex(13.414213, 7);
    rect4->addVertex(9.414213, 7);
    rect4->addVertex(9.414213, 8);
    fc->addPrimitive(layer1, rect4);
    rect4->setIndex(fc->getComponentSize());
    rect4->setID("rect4");    

    //fifth connecting rectangle
    Polygon* rect5 = new Polygon();
    rect5->addVertex(9.414213, 11);
    rect5->addVertex(9.414213, 8);
    rect5->addVertex(8, 8);
    rect5->addVertex(8, 11);
    fc->addPrimitive(layer1, rect5);
    rect5->setIndex(fc->getComponentSize());
    rect5->setID("rect5");

    //absorbent pad
    Polygon* abs_pad = new Polygon();
    abs_pad->addVertex(11.414213, 13);
    abs_pad->addVertex(11.414213, 11);
    abs_pad->addVertex(6, 11);
    abs_pad->addVertex(6, 13);
    fc->addPrimitive(layer1, abs_pad);
    abs_pad->setIndex(fc->getComponentSize());
    abs_pad->setID("abs_pad");

     return 0;
}

/*  =============================================================================
    Method for moving individual Primitives by ID
    
    @param  unsigned    ID
    @param  double       distance moved in the x-axis
    @param  double       distance moved in the y-axis
    @return     int     status of method
    ========================================================================== */
int FoldingCard::moveID(unsigned ID, double x, double y) {
   Component* fc = new Component;
   fc->findPrimitive(ID)->move(x, y); /* Call move function defined in Primitive class */
   return 0;
}

/*  =============================================================================
    Method for moving individual Primitives by alias
    
    @param string       alias
    @param  double       distance moved in the x-axis
    @param  double       distance moved in the y-axis
    @return     int     status of method
    ========================================================================== */
int FoldingCard::moveAlias(string alias, double x, double y) { 
	Component* fc = new Component;
	fc->findPrimitive(alias)->move(x, y); /* Call move function defined in Primitive class */
    return 0;
}

/*  =============================================================================
    Method for moving entire Component
    
    @param  double       distance moved in the x-axis
    @param  double       distance moved in the y-axis
    @return     int     status of method
    ========================================================================== 
int FoldingCard::moveBy(double x, double y) { 
    Device::moveBy(x,y); // Call moveBy function defined in Component class 
    return 0;
}*/

/*  =============================================================================
    Method for rotating individual Primitives by ID

    @param  unsigned    ID
    @param  double       angle in degrees to rotate by
    @return     int     status of method
    ========================================================================== */
int FoldingCard::rotateID(unsigned ID, double ang_deg) {

	// Init
	Polygon *p 		= NULL;
	Circle *c 		= NULL;
	Component* fc 	= NULL;

	// If primitive is a polygon 
	// Else if primitive is a circle 
	if ((p = dynamic_cast<Polygon*>(fc->findPrimitive(ID)))) { 
		return rotateHelperPoly(p, ang_deg);
	} else if ((c = dynamic_cast<Circle*>(fc->findPrimitive(ID)))) { 
		return rotateHelperCircle(c, ang_deg);
	}
	
	return -1;
}

/* =============================================================================
	Method for rotating individual Primitives by alias

	@param 		string      alias
	@param  		double      angle in degrees to rotate by
	@return     int     		status of method
	========================================================================== */
int FoldingCard::rotateAlias(string alias, double ang_deg) {

	// Init
	Polygon *p 		= NULL;
	Circle *c 		= NULL;
	Component* fc 	= NULL;

	// If primitive is a polygon 
	// Else if primitive is a circle 
	if ((p = dynamic_cast<Polygon*>(fc->findPrimitive(alias)))) { 
		rotateHelperPoly(p, ang_deg);
	} else if ((c = dynamic_cast<Circle*>(fc->findPrimitive(alias)))) { 
		rotateHelperCircle(c, ang_deg);
	}
	return 0;
}

/* =============================================================================
	Method for rotating entire Component

	@param 	double   angle in degrees to rotate by
	@return  int     	status of method
	========================================================================== */
int FoldingCard::rotateBy(double ang_deg) {

	smhdl::coords oldCenter = getCenterAll();

	// Call rotate function defined in device class 
	Device::rotateBy(ang_deg);

	// Get center of component 
	smhdl::coords newCenter = getCenterAll();

	/// Calculate distance between original center and new center
	double deltaX = oldCenter.x - newCenter.x;
	double deltaY = oldCenter.y - newCenter.y;

	// Translate back to original center
	move(deltaX, deltaY);        

	return 0;
}

/* =============================================================================
	Method for scaling individual Primitives by ID

	Dynamic Casts are necessary in order to determine what type of Primitive 
	we are scaling. --There should be a better way?

	Primitives

	@param  		unsigned    ID
	@param  		double   	factor to scale by
	@return    	int     		status of method
	========================================================================== */
int FoldingCard::scaleID(unsigned ID, double scaleFactor) {

	// If scaleFactor is 0 -- error 
	if (!scaleFactor) return -1;

	// Init
	Polygon *p 		= NULL;
	Circle *c 		= NULL;
	Component* fc 	= NULL;

	// If primitive is a polygon
	// Else if primitive is a circle
	if ( ( p = dynamic_cast<Polygon*>( fc->findPrimitive(ID) ) ) ) { 
		return scaleHelperPoly(p, scaleFactor);
	} else if ((c = dynamic_cast<Circle*>(fc->findPrimitive(ID)))) { 
		return scaleHelperCircle(c, scaleFactor);
	} 

	// Neither circle or polygon - Error
	return -1;
}

/* =============================================================================
	Method for scaling individual Primitives by alias

	Dynamic Casts are necessary in order to determine what type of Primitive 
	we are scaling. --There should be a better way?

	Primitives

	@param  	str      alias
	@param  	dbl   	factor to scale by
	@return  int     	status of method
	========================================================================== */
int FoldingCard::scaleAlias(string alias, double scaleFactor) {

	// If scaleFactor is 0 -- error
	if (!scaleFactor) return -1;

	// Init
	Polygon *p 		= NULL;
	Circle *c 		= NULL;
	Component* fc 	= NULL;

	// If primitive is a polygon
	// Else if primitive is a circle
	if ( ( p = dynamic_cast<Polygon*>( fc->findPrimitive(alias) ) ) ) { 
		return scaleHelperPoly(p, scaleFactor);	
	} else if ( ( c = dynamic_cast<Circle*>( fc->findPrimitive(alias) ) ) ) {
		return scaleHelperCircle(c, scaleFactor); 
	} 

	return -1; // Neither circle or polygon - Error
}


/*  =============================================================================
    Method for scaling entire component

    Dynamic Casts are necessary in order to determine what type of Primitive 
    we are scaling. --There should be a better way?
    
    @param  double   factor to scale by
    @return     int     status of method
    ========================================================================== */
int FoldingCard::scaleBy(double scaleFactor) {

	// If scaleFactor is 0 -- error
	if (!scaleFactor) return -1;

	// Init
	Primitive* pr = NULL;
	Polygon *poly = NULL;
	Circle *c 	  = NULL;
	Component* fc = NULL;
	string layerKey = "";

	// Get center of entire component
	smhdl::coords center = getCenterAll();

	// Translate to global center for scaling
	double deltaX = getRegistrationX() - center.x;
	double deltaY = getRegistrationY() - center.y; 
	move(deltaX, deltaY);

	// Gets the sum of all x coordinates and the sum of all y coordinates for all the vertices 
	for (unsigned l = 0; l < fc->getComponentLayerCount(); l++) {
	
		if (fc != NULL) layerKey = fc->getLayerKey(l);

	  	for (unsigned p = 0; p < fc->getPrimitivesCount( layerKey ); p++) {

	  		pr = fc->getPrimitiveAt(layerKey, p);
	  		
	  		if (pr->getType() == 3) { // CIRCLE
	  		
	  			c = dynamic_cast<Circle*>(pr);
	  			
				// Scale circle
				c->setCenter(c->getCenterX() * scaleFactor, c->getCenterY() * scaleFactor);
				c->setRadius(c->getRadius() * scaleFactor); // Scale radius
	  		} else if (pr->getType() == 4) { // POLYGON
	  		
	  			poly = dynamic_cast<Polygon*>(pr);
	  			
	  			// Scale polygon 
				for (unsigned v = 0; v < poly->getVertexCount(); ++v) {
					poly->setVertexX(v, poly->getVertexX(v) * scaleFactor); // Scale x-coordinate
					poly->setVertexY(v, poly->getVertexY(v) * scaleFactor); // Scale y-coordinate
				}    
	  		} else {
				cout << "Error!" << endl;
				return -1;
	  		}
	  }
	}

    // Translate back to original center
    move(-deltaX, -deltaY);

    return 0;
}

/*  =============================================================================
    Helper function to rotate a polygon
    
    @param  Polygon*        polygon to rotate
    @param  double   factor to rotate by
    @return     int     status of method
    ========================================================================== */
int FoldingCard::rotateHelperPoly(Polygon* p, double ang_deg) {

    // Get old center so we can translate back to original position after rotating
    smhdl::coords oldCenter = getCenterPoly(p);

    // Rotate
    p->rotate(ang_deg);

    // Get center of polygon 
    smhdl::coords newCenter = getCenterPoly(p);

    // Calculate distance between original center and new center 
    double deltaX = oldCenter.x - newCenter.x;
    double deltaY = oldCenter.y - newCenter.y;

    // Translate back to original center 
    p->move(deltaX, deltaY);        

    return 0;
}


/*  =============================================================================
    Helper function to rotate a circle
    
    @param  Circle*        circle to rotate
    @param  double   angle to rotate
    @return     int     status of method
    ========================================================================== */
int FoldingCard::rotateHelperCircle(Circle* c, double ang_deg) {
    /* Get old center so we can translate back to original position after rotating */
    smhdl::coords oldCenter;
    oldCenter.x = c->getCenterX();
    oldCenter.y = c->getCenterY();

    /* Rotate */
    c->rotate(ang_deg);

    smhdl::coords newCenter;
    newCenter.x = c->getCenterX();
    newCenter.y = c->getCenterY();

    /* Calculate distance between original center and new center */
    double deltaX = oldCenter.x - newCenter.x;
    double deltaY = oldCenter.y - newCenter.y;

    /* Translate back to original center */
    c->move(deltaX, deltaY);        

    return 0;
}

/*  =============================================================================
    Helper function to scale a polygon
    
    @param  Polygon*        polygon to scale
    @param  smhdl::coords     global center
    @param  double   factor to scale by
    @return     int     status of method
    ========================================================================== */
int FoldingCard::scaleHelperPoly(Polygon* p, double scaleFactor) {
    /* Get center of polygon */
    smhdl::coords center = getCenterPoly(p); 

    /* Translate to global center for scaling */
    double deltaX = getRegistrationX() - center.x;
    double deltaY = getRegistrationY() - center.y; 
    p->move(deltaX, deltaY);

    /* Scale all vertices */
    for (unsigned i = 0; i < p->getVertexCount(); ++i) {
        p->setVertexX(i, p->getVertexX(i) * scaleFactor); /* Scale x-coordinate */
        p->setVertexY(i, p->getVertexY(i) * scaleFactor); /* Scale y-coordinate */
    }    

    /* Translate back to original center */
    p->move(-deltaX, -deltaY);

    /* TODO?: Adjust component to fix overlaps from scaling */

    return 0;
}

/*  =============================================================================
    Helper function to scale a circle
    
    @param  Circle*        circle to scale
    @param  smhdl::coords     global center
    @param  double   factor to scale by
    @return     int     status of method
    ========================================================================== */
int FoldingCard::scaleHelperCircle(Circle* c, double scaleFactor) {
    /* Translate to global center for scaling */
    double deltaX = getRegistrationX() - c->getCenterX();
    double deltaY = getRegistrationY() - c->getCenterY(); 
    c->move(deltaX, deltaY);

    /* Scale all vertices */
    c->setCenter(c->getCenterX() * scaleFactor, c->getCenterY() * scaleFactor);
    c->setRadius(c->getRadius() * scaleFactor); /* Scale radius */

    /* Translate back to original center */
    c->move(-deltaX, -deltaY);

    /* TODO?: Adjust component to fix overlaps from scaling */

    return 0;
}

/*  =============================================================================
    Helper function to reposition componenet after scaling a primitive
    
    @param  Polygon*      polygon that was scaled 
    @return     int     status of method
    ========================================================================== */
// int FoldingCard::refreshPoly(Polygon *q, smhdl::coords qCenter, double diffX, double diffY) {

// }

/* TODO? */
int scaleWidthID(unsigned ID, double scaleFactor) {
	return 0;
}
/* TODO? */
int scaleWidthAlias(string alias, double scaleFactor) {
	return 0;
}
/* TODO? */
int scaleLengthID(unsigned ID, double scaleFactor) {
	return 0;
}
/* TODO? */
int scaleLengthAlias(string alias, double scaleFactor) {
	return 0;
}


/*  =============================================================================
    Determines center of polygon
    
    @param  Polygon*        polygon to find center of
    @return     smhdl::coords    center of poloygon
    ========================================================================== */
smhdl::coords FoldingCard::getCenterPoly(Polygon* p) {
    smhdl::coords center;

    double x, y;
    x = y = 0.0;
    unsigned count = 0;

    /* Sum polygon vertices */
    for (unsigned i = 0; i < p->getVertexCount(); ++i) { 
        x += p->getVertexX(i);
        y += p->getVertexY(i);
        ++count;
    }

    /* Divide sums by number of vertices to get center */
    center.x = x / count;
    center.y = y / count;

    return center;
}

/*  =============================================================================
    Determines center of component
    
    @param  none        nothing
    @return     smhdl::coords    center of component
    ========================================================================== */
smhdl::coords FoldingCard::getCenterAll() {
	
	// Initialize
	smhdl::coords center;
	double x = 0.0;
	double y = 0.0;
	unsigned count = 0;
	Primitive* pr 	= NULL;
	Polygon *poly 	= NULL;
	Circle *c 		= NULL;
	Component *fc 	= NULL;
	string layerKey = "";

	// Gets the sum of all x coordinates and the sum of all y coordinates for all the vertices 
	for (unsigned l = 0; l < fc->getComponentLayerCount(); l++) {
		
		layerKey = fc->getLayerKey(l);

	  	for (unsigned p = 0; p < fc->getPrimitivesCount( layerKey ); p++) {

	  		pr = fc->getPrimitiveAt(layerKey, p);
	  		
	  		if (pr->getType() == 3) { // CIRCLE
	  			c = dynamic_cast<Circle*>(pr);
				x += c->getCenterX();
				y += c->getCenterY();
				++count;
	  		} else if (pr->getType() == 4) { // POLYGON
	  			poly = dynamic_cast<Polygon*>(pr);
	  			for (unsigned v = 0; v < poly->getVertexCount(); ++v) { // Sum all polygon vertices 
					x += poly->getVertexX(v);
					y += poly->getVertexY(v);
					++count;
				}
	  		} else {
				cout << "Error: getCenterAll()" << endl;
				exit(1);
	  		}
	  }
	}
    
	// Divide sums by number of vertices to get center 
	center.x = x / count;
	center.y = y / count;

	return center;
}
