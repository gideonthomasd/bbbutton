/*
 * BBButton V 8.0  ,bbbrc.h
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

#ifndef bbbrc_h
#define bbbrc_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#include "bbbutton.h"

class BBBrc
{

public :
    BBBrc(vector <BBButton *> *bbbuttons);
    ~BBBrc();

    vector<BBButton *> *aBBButton;

    void createButtons(Display* display);
    bool configValid(void);

    void setButtonNumber(void);
    int getMaxButtons(void) { return maxButtons; }
    int getButtonNumber(void){ return numButtons; }

protected :
    char * rcName;
    int lines;
    int maxButtons;
    int numButtons;
    char picPath[64];
    char picCMD[64];
    vector <string> holdAll;

    void sTrim(string& StringToModify);

};

#endif
