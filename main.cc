/*
 * BBButton V 8.0  ,main.cc
 *
 * (C) 09-03-2005 Konstantinos Mantzaris <GODoal@hotmail.com>
 *     09-03-2005 Stathis <p00pie@sourceforge.net>
 *
 * This software is licensed under LGPL
 *
 * Part of this code is striped from wmNetscapeKiller
 * by Pierre-Olivier <pblumo@free.fr>
 *
 */

#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>

#include "bbbutton.h"
#include "bbbrc.h"

int main(int argc, char ** argv)
{

    char * pname = argv[0];
    vector <BBButton *> bbbuttons;

    Display         *display;
    Window          root;
    XEvent          event;
    int             screen;

    if( ( display = XOpenDisplay(NULL) ) == NULL )
    {
        cerr<<"Error: XOpenDisplay "<<endl;
        exit(1);
    }

    root = RootWindow(display, screen = DefaultScreen(display));

    BBBrc *rcParser = new BBBrc(&bbbuttons);
    if(argc == 1)
    {
        cout<<"Loading data from .bbbuttonrc ...\n";
	if (rcParser->configValid()) {
	    if ( rcParser->getButtonNumber() > rcParser->getMaxButtons() ) {
    		cout << "Error: The number of buttons to load do not comply with the\n"
            	     << "       maximum button limit specified in ~/.bbbuttonrc"<<endl;
		exit(1);
	    }
	}
	else exit(1);

        rcParser->createButtons(display);
    }
    else
    {
        cout<<"\n+-----------------------------------------------------------------+\n"
	<<"  "<<pname<<" v0.8 ,by Konstantinos Mantzaris (GODoal@hotmail.com)  \n"
	<<"  Available @ http://bbbutton.sourceforge.net/index.html\n"
        <<"\n"
        <<"  Usage : "<<pname<<"\n"
        <<"+-----------------------------------------------------------------+\n";
	exit(1);
    }

    int i;
    delete rcParser;

    while (1)
    {
	XNextEvent(display, &event);
    	for ( i = 0; i < bbbuttons.size(); i++ )
    	{
	    if ( event.xbutton.window == bbbuttons[i]->iconwin ) {
	            bbbuttons[i]->runEvents(&event);
    	    }
	}
    }
    exit(1);
}
