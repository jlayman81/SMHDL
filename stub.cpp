/*	=============================================================================
	Test routine
	
	@version	0.1.1
	@author	JesseL
	========================================================================== */
	
#include "app/App.h"
#include "library/Library.h"
#include "render/RenderEngines.h"

using namespace std;

int main() {


	//typedef std::vector<Component*> render_queue; // Polymorphic Vector
	//cout << "Instantiating Interface...";
	Interface interface;
	string menuInput;
	//unsigned netlistCount = 0;
	//cout << "done.\n";
	
	// Instantiate new Environment object
	//cout << "Instantiating Environment...";
	Environment env;
	env.setTemp(25.12);
	env.setPressure(132.145);
	//cout << "done.\n";
	
	// Instantiate new Substance object
	//cout << "Instantiating Substance...";
	Substance vinegar("1");
	vinegar.setName("Vinegar");
	vinegar.setSummary("Base acidity reagent");
	//cout << "done.\n";
	

	/*
	// Instantiate new Substrate object
	cout << "Instantiating Substrate...";
	Substrate paper("paper");
	paper.setName("Paper, 80# off white");
	paper.setSummary("The capillary action on this is off the hook, yo!");
	paper.scale.setConversion(in);
	paper.setDimensions(4.5,5.5,0.125);
	//cout << "done.\n";
	*/
	// Instantiate new Substrate object
	cout << "Instantiating Substrate...";
	Substrate paper1("paper1");
	paper1.setName("Paper, 80# off white");
	paper1.setSummary("The capillary action on this is off the hook, yo!");
	paper1.scale.setConversion(in);
	paper1.setDimensions(7.875, 4.875, 0.125);
	cout << "done.\n";
	
	// Instantiate new Page
	/*
	cout << "Instantiating Page...";
	Page page1("page_1");
	page1.setUnits(in);
	page1.setDimensions(7.875, 4.875);
	page1.setSubstrate(&paper1);
	cout << "done.\n";
	*/
	// Instantiate new Layout
	//cout << "Instantiating Layout...";
	Layout testLayout;
	testLayout.scale.setConversion(mm);
	testLayout.registry.setID("Layout");
	//cout << "done.\n";
	/**/
	
	
	cout << "Instantiating Page...\n";
	Page* pg = testLayout.registry.getCurrentPage();
	if (pg != NULL) {
		std::cout << TAB1 << "PAGE FOUND\n";
		pg->setUnits(in);
		pg->setDimensions(7.875, 4.875);
		pg->setSubstrate(&paper1);
	} else {
		std::cout << TAB1 << "PAGE NOT FOUND\n";
	}
	cout << "Instantiating Page...DONE\n";
	
	// Add paper to layout
	//cout << "Adding Substrate to Layout...";
//	testLayout.registry.registerPage(&page1);
	//testLayout.registry.registerLayer(layer_1);
	//cout << "Adding Substrate to Layout...DONE.\n";
	//cout << "done.\n";
	//cout << "Current substrate ID: " << testLayout.registry.getCurrentSubstrateID() << "\n";



	//cout << "Adding Registration Marks to Layout...\n";
	testLayout.addRegistrationMarks(6.35);
	//cout << "Adding Registration Marks to Layout...done.\n";


	/* Add Test Device
	cout << "Creating new Test Device...\n";

	Device* t = new Device();
	t->setID("Test Device");
	
	// Well
	Well* testWell;
	
	testWell = new Well("Source Test");
	testWell->setRadius(10.0);
	testWell->setBorder(1.0);
	testWell->draw();
	testWell->moveTo(100.0, 100.0);
	t->addComponent(testWell);
	
	testWell = new Well("Sink Test");
	testWell->setRadius(10.0);
	testWell->setBorder(1.0);
	testWell->draw();
	testWell->moveTo(150.0, 150.0);
	t->addComponent(testWell);
	
	// Test Component  - Added for testing
	Channel* TestComponent = new Channel();
	TestComponent->setID("Channel Test");
	TestComponent->setSource(0.0, 0.0);
	TestComponent->setSink(50.0, 50.0);
	TestComponent->setWidth(10.0);
	TestComponent->setBorder(2.0);
	TestComponent->draw();
	TestComponent->moveTo(100,100);
	//TestComponent->rotateBy(45);
	t->addComponent(TestComponent);
	//t->moveTo(0.0,0.0);
	
	
	
	cout << "Creating new Test Device...done\n";*/

	/* Add ImmunoSensor */
/*
	cout << "Creating ImmunoSensor...\n";
	ImmunoSensor* is = new ImmunoSensor("ImmunoSensor", testLayout.registry.getCurrentSubstrate());
	is->draw();
	is->moveTo(40.0,70.0);
	cout << "Creating ImmunoSensor...Done\n";
*/
	/* Add LateralFlowTest */
/*
	cout << "Creating LateralFlowTest...\n";
	LateralFlowTest* lft = new LateralFlowTest("LateralFlowTest", testLayout.registry.getCurrentSubstrate());
	lft->setCount(4); // Number of signals
	lft->draw();
	lft->moveTo(40.0,70.0);
	cout << "Creating LateralFlowTest...Done\n";
*/
	/* Add OnButtons */

/*	OnButtons* ob = new OnButtons("OnButton", testLayout.registry.getCurrentSubstrate());
	ob->setCount(5); // Number of signals
	ob->setSignalLength(15);
	ob->setSignalWidth(1);
	ob->draw();
	ob->moveTo(30.0,60);
*/
	/* Add Titration */

/*	Titration* t = new Titration("Titration", testLayout.registry.getCurrentSubstrate());
	t->setCount(5); // Number of signals
	//t->setSignalSpacing(10);
	//t->setWellRadii(5);
	//t->setSignalWidth(5);

	t->draw();
	t->moveTo(30,0);
*/

	/* Add FluidicMultiplexer */
	/*
	FluidicMultiplexer* fm = new FluidicMultiplexer("FmMUX", testLayout.registry.getCurrentSubstrate());
	fm->setCount(55); // Number of signals
	fm->draw();
	fm->moveTo(100.0,150.0); */

	//Add Bullseye
/*
	cout << "Creating Bullseye...\n";
	Bullseye* b = new Bullseye();
	b->setID("Bullseye Calibration Device");
	b->registry.registerSubstrate(testLayout.registry.getCurrentSubstrate());
	b->addLane(100.0, 0.0);
	b->addLane(100.0, 45.0);
	b->addLane(100.0, 90.0);
	b->draw();
	b->moveTo(50.0,150.0);
	cout << "Creating Bullseye...done\n";
*/
	//b->print();
	//b->draw();	 */

	// Add Raceway

	cout << "Creating Raceway...\n";
	Raceway* r = new Raceway("raceway_device");
	//r->registry.registerPage(testLayout.registry.getPageAt(0));
	//r->setID("Raceway Calibration Device");
	r->setLaneSpacing(5.0);
	r->setTickSpacing(10.0);
	r->setBorder(1.0);
	//r->setReservoir(25, 100, 0.1); // NOT USED ANYMORE - JP 20170914
	r->addLane(1, 100, 1.5);
	r->addLane(2, 100, 2);
	r->addLane(4, 100, 3);
	r->addLane(8, 100, 5);
	r->addLane(16, 100, 9);
	r->addLane(32, 100, 17);
	r->draw();
	r->moveTo(10, 10.0);
	r->print();
//	return 0;
	

	// Add Devices to Layout
	//testLayout.addDevice(b);
	testLayout.addDevice(r);
	//testLayout.registry.output();
	//testLayout.registry.deregisterLayer(DEFAULT_PAGE_NAME, DEFAULT_LAYER_NAME);
	//testLayout.registry.deregisterPage(DEFAULT_PAGE_NAME);
	//testLayout.deletePage(DEFAULT_PAGE_NAME);
	//testLayout.registry.output();
	
	//cout << "Number of Devices in Layout: |" << testLayout.getNetlistCount() << "|\n";
	//testLayout.print();
	//testLayout.output();
	
	//PDF output
	cout << "+======================== CREATING PDF ======================\n";
	PDF testOutput("RacewayTest_For Jesse","output/");
	testOutput.add(&testLayout);
	//lft.exportAsPDF("LFT","output/");
	
	// ADD COMPONENT TO LAYOUT
	//testOutput.add(&TestComponent);
	testOutput.save();
	// END PDF Ouput

	//return 0; // temporary halt

	/*
	// Main Menu Loop	
	while ( interface.getMenuOption() != "0") {
		interface.printMainMenu();
		cin >> menuInput;
		interface.setMenuOption(menuInput);
		netlistCount++;
	}
	
	// Instantiate new Well object
	Well well("2");
	well.setName("Well #1");
	well.setType("well");
	well.output();
	well.moveTo(0.0, 5.0);
	//well.rotateBy(90.0);
	well.output();
		
	// Add Components to netlist
	vector<Component*> netlist;
	netlist.push_back(&well);
	netlist.push_back(new Well("3"));
	netlist.push_back(new Well("4"));
	netlist.push_back(new RegPoint("5"));
	netlist.push_back(new FoldingCard("6"));
	netlist.push_back(new FluidicMultiplexer("7"));
	netlist[4]->setName("Ryan's card");
	netlist[4]->setType("folding card");
	netlist[5]->setName("Mux card");
	netlist[5]->setType("Fluidic Multiplexer");
	*/
	cout << "Done. \n";
	

	return 0;
}



