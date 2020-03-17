/*
 * BBButton V 8.0  ,bbbutton.cc
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

#include "bbbutton.h"

BBButton :: BBButton( Display* display, char* Image, char* Command )
: display(display)
{
    XWMHints    wmHints;
    XSizeHints  sizeHints;
    XClassHint  classHint;
    Pixmap	pixmask;

    int screen DefaultScreen(display);
    long event_mask = ButtonPressMask|ExposureMask|ButtonReleaseMask;
    
    Window root = RootWindow(display, screen);
    long fgcolor = BlackPixel(display, screen);
    long bgcolor = WhitePixel(display, screen);
    this->gc = XDefaultGC(display, screen);

    strncpy(xpmPath, Image, sizeof(xpmPath));
    strncpy(procCMD, Command, sizeof(procCMD));

    sizeHints.x = 0;
    sizeHints.y = 0;
    sizeHints.width = 64;
    sizeHints.height = 64;

    int depth = 1;

    iconwin = XCreateSimpleWindow(display, root, sizeHints.x,
                                  sizeHints.y,
                                  sizeHints.width,
                                  sizeHints.height,
                                  depth, fgcolor, bgcolor);

    Window parentWindow = XCreateSimpleWindow(display, root, sizeHints.x,
                                       sizeHints.y,
                                       sizeHints.width,
                                       sizeHints.height,
                                       depth, fgcolor, bgcolor);

    sizeHints.flags = USSize | USPosition;
    XSetWMNormalHints(display, parentWindow, &sizeHints);

    wmHints.initial_state = WithdrawnState;
    wmHints.icon_window = iconwin;
    wmHints.icon_x = sizeHints.x;
    wmHints.icon_y = sizeHints.y;
    wmHints.window_group = parentWindow;
    wmHints.flags = StateHint|IconWindowHint|IconPositionHint|WindowGroupHint;
    XSetWMHints(display, parentWindow, &wmHints);

    XpmReadFileToPixmap(display, root, Image, &XPM, &pixmask, NULL);
    XShapeCombineMask(display, iconwin, ShapeBounding, 8, 8, pixmask, ShapeSet);

    XSelectInput(display, iconwin, event_mask);
    XMapWindow(display, parentWindow);
}

BBButton::~BBButton()
{
}

void BBButton :: BPressed()
{
    XCopyArea(display, XPM, iconwin, gc,0,0,48,48,9,9);
    system(procCMD);
}

void BBButton :: BReleased()
{
    XCopyArea(display, XPM, iconwin, gc,0,0,48,48,8,8);
}

void BBButton :: runEvents(XEvent *e)
{

    switch(e->type)
    {

    case Expose:
        //cout << "Released Button" << endl;
        BReleased();
        break;

    case ButtonPress:
        switch(e->xbutton.button )
        {
        case 1: //left click
            //cout << "Left Click" << endl;
            BPressed();
            break;
        case 3: //right click
            //cout << "Right Click" << endl;
            break;
        default:
            break;
        }
        break;

    case MotionNotify:
        BReleased();
	break;
    case ButtonRelease:
    	BReleased();
	break;

    }
}


