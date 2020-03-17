/*
 * BBButton V 8.0  ,bbbutton.h
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

#ifndef bbbutton_h
#define bbbutton_h

#include <iostream>
#include <fstream>
#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/xpm.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>

using namespace std;

class BBButton
{

public :
    BBButton(Display* display, char* Image, char* Command);
    ~BBButton();

    void runEvents(XEvent* e);

    void BPressed(void);
    void BReleased(void);

    Window iconwin;

protected :
    char xpmPath[64];
    char procCMD[64];

private:
    Display	*display;
    Pixmap	XPM;
    GC		gc;

    char ** xpm_data;

};

#endif

