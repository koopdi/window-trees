/*
 * CS 132 Tiles
 * This file contains a main that creates a GUI to display a multi-window
 * simulation. It uses your TileManager class to store all the windows and
 * calls its functions to alter the order and number of windows displayed.
 *
 * DO NOT MODIFY this provided file! Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * @author Allison Obourn
 * @version 2022/06/01 - 22wi 132 initial version
 */

#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gradiobutton.h"
#include "gtextfield.h"
#include "gthread.h"
#include "gwindow.h"
#include <iomanip>
#include <string>

#include "TileManager.h"

using namespace std;
using namespace sgl;

static const int TILE_COUNT     = 20;
static const int CONTROL_HEIGHT = 70;
static const int WINDOW_WIDTH   = 700;
static const int WINDOW_HEIGHT  = 500;
static const int MIN_SIZE       = 50;
static const int MAX_SIZE       = 150;

// prototypes for local functions - not accessible externally
Tile createTile();
void addInitialTiles(GWindow* window, TileManager* manager);
string buildColorString();
void createButtons(GWindow* window, TileManager* manager);
void createRadioButtons(GWindow*,
                        GRadioButton**,
                        GRadioButton**,
                        GRadioButton**,
                        GRadioButton**,
                        GRadioButton**);
GLabel* createLabels(GWindow* window);
void processMouseEvent(GEvent mouseEvent,
                       TileManager* manager,
                       GLabel* glMousePos,
                       GRadioButton* grbRaise,
                       GRadioButton* grbLower,
                       GRadioButton* grbRemove,
                       GRadioButton* grbRemoveAll,
                       GRadioButton* grbHighlight,
                       GWindow* window);

int main()
{
	TileManager* manager = new TileManager();
	GWindow* window      = new GWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

	window->setTitle("Window Manager");
	window->center();
	window->setExitOnClose(true);
	window->setBackground("White");
	window->clear();
	window->setColor("black");
	window->setRepaintImmediately(true);

	// adds a bottom row with two add buttons and a clear to the window
	createButtons(window, manager);

	// global pointers to the top row of radio buttons
	GRadioButton* grbHighlight;
	GRadioButton* grbRaise;
	GRadioButton* grbLower;
	GRadioButton* grbRemove;
	GRadioButton* grbRemoveAll;

	// forward declaration
	// adds the top row of radiobuttons
	createRadioButtons(window,
	                   &grbRaise,
	                   &grbLower,
	                   &grbRemove,
	                   &grbRemoveAll,
	                   &grbHighlight); //

	// adds the mouse position to the bottom right
	GLabel* glMousePos = createLabels(window);

	// sets the function to be called when the user clicks
	window->setMouseListener(
	    [manager,
	     glMousePos,
	     grbRaise,
	     grbLower,
	     grbRemove,
	     grbRemoveAll,
	     grbHighlight,
	     window](GEvent e)
	    {
		    processMouseEvent(e,
		                      manager,
		                      glMousePos,
		                      grbRaise,
		                      grbLower,
		                      grbRemove,
		                      grbRemoveAll,
		                      grbHighlight,
		                      window);
	    });
	window->setVisible(true);

	// adds tiles to the GUI
	addInitialTiles(window, manager);

	return 0;
}

// Takes a pointer to a GUI window and a pointer to a tile manager. Creates
// TILE_COUNT number of tiles of random sizes, positions and colors and adds
// them to the manager at the bottom of the z-ordering. Then, draws  all tiles
// on the GUI window.
void addInitialTiles(GWindow* window, TileManager* manager)
{
	for (int i = 0; i < TILE_COUNT; i++)
	{
		Tile t = createTile();
		manager->addBottom(t);
	}
	manager->drawAll(*window);
}

// Builds up a hexedecimal color string of random values and returns it
string buildColorString()
{
	string options = "0123456789ABCDEF";
	string color   = "#";
	for (int i = 0; i < 6; i++)
	{
		int index = rand() % 16;
		color += options[index];
	}
	return color;
}

// Creates and returns a Tile with a random size between the min and max
// specified and at a random position entirely within the window. It also gives
// each Tile a random color.
Tile createTile()
{
	int width    = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
	int height   = rand() % (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
	int x        = rand() % (WINDOW_WIDTH - width);
	int y        = rand() % (WINDOW_HEIGHT - CONTROL_HEIGHT - height);
	string color = buildColorString();
	Tile info    = Tile(x, y, width, height, color);
	return info;
}

// Initializes three buttons and adds hotkey combinations to select them
void createButtons(GWindow* window, TileManager* manager)
{
	GButton* gbAddFront = new GButton("Add Top");
	gbAddFront->setClickListener(
	    [manager, window]()
	    {
		    Tile t = createTile();
		    manager->addTop(t);
		    t.draw(*window);
		    // manager->drawAll(*window);
	    });
	gbAddFront->setAccelerator("ctrl F");
	window->addToRegion(gbAddFront, "South");

	GButton* gbAddBack = new GButton("Add Bottom");
	gbAddBack->setClickListener(
	    [manager, window]()
	    {
		    Tile t = createTile();
		    manager->addBottom(t);
		    manager->drawAll(*window);
	    });
	gbAddBack->setAccelerator("ctrl B");
	window->addToRegion(gbAddBack, "South");

	GButton* gbClear = new GButton("Clear");
	gbClear->setClickListener(
	    [manager, window]()
	    {
		    window->clear();
		    manager->clear();
	    });
	window->addToRegion(gbClear, "South");
}

// takes the gui window, a string name of what this radio button will be,
// a string representing the hotkey and a pointer to a radio button variable.
// Creates a new radio button with the passed in text and hotkey and sets the
// radio button variable to store it.
void createSingleRadio(GWindow* window,
                       std::string text,
                       std::string key,
                       GRadioButton** nameOut)
{
	GRadioButton* button = new GRadioButton(text);
	button->setActionCommand(text);
	button->setAccelerator("ctrl " + key);
	window->addToRegion(button, "North");
	*nameOut = button;
}

// Initializes the radio buttons and sets hotkey combinations to select them.
// It initializes the highlight button to be selected.
void createRadioButtons(GWindow* window,
                        GRadioButton** grbRaise,
                        GRadioButton** grbLower,
                        GRadioButton** grbRemove,
                        GRadioButton** grbRemoveAll,
                        GRadioButton** grbHighlight)
{
	createSingleRadio(window, "highlight", "H", grbHighlight);
	(*grbHighlight)->setSelected(true);

	createSingleRadio(window, "raise", "R", grbRaise);
	createSingleRadio(window, "lower", "L", grbLower);
	createSingleRadio(window, "remove", "M", grbRemove);
	createSingleRadio(window, "removeAll", "V", grbRemoveAll);
}

// Initializes a label, sets its width and adds it to the passed gui window.
GLabel* createLabels(GWindow* window)
{
	GLabel* glMousePos = new GLabel("(x=___, y=___)");
	glMousePos->setWidth(150.0);
	window->addToRegion(glMousePos, "South");
	return glMousePos;
}

// This function runs when any mouse event occurs. It gets passed an event
// parameter from which we can access the x, y position of the event. Prints the
// current x, y location of the mouse to the label on the gui. Then calls the
// appropriate student function if it has been set.
void processMouseEvent(GEvent mouseEvent,
                       TileManager* manager,
                       GLabel* glMousePos,
                       GRadioButton* grbRaise,
                       GRadioButton* grbLower,
                       GRadioButton* grbRemove,
                       GRadioButton* grbRemoveAll,
                       GRadioButton* grbHighlight,
                       GWindow* window)
{
	int x = mouseEvent.getX();
	int y = mouseEvent.getY();
	glMousePos->setLabel("(x = " + std::to_string(x) +
	                     ", y = " + std::to_string(y) + ")");
	int type = mouseEvent.getEventType();
	if (type == MOUSE_PRESSED)
	{
		if (grbHighlight->isSelected())
		{
			manager->highlight(x, y, *window);
		}
		else
		{
			if (grbRaise->isSelected())
			{
				manager->raise(x, y);
				manager->drawDirty(*window);
			}
			else if (grbLower->isSelected())
			{
				manager->lower(x, y);
				manager->drawDirty(*window);
				// window->clear();
				// manager->drawAll(*window);
			}
			else if (grbRemove->isSelected())
			{
				manager->remove(x, y);
				window->clear();
				manager->drawAll(*window);
			}
			else if (grbRemoveAll->isSelected())
			{
				manager->removeAll(x, y);
				window->clear();
				manager->drawAll(*window);
			}
		}
	}
}
