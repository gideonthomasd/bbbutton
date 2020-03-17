/*
 * BBButton V 8.0  ,bbbrc.cc
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

#include "bbbrc.h"

BBBrc::BBBrc(vector <BBButton *> *bbbuttons)
: aBBButton(bbbuttons)
{
    char *homedir  = getenv("HOME");
    rcName = new char[strlen(homedir) + 32];
    sprintf(rcName, "%s/.bbbuttonrc", homedir);
}

BBBrc::~BBBrc()
{
}

void BBBrc::sTrim(string& StringToModify)
{
    if(StringToModify.empty())
        return;

    int startIndex = StringToModify.find_first_not_of(" ");
    int endIndex = StringToModify.find_last_not_of(" ");
    string tempString = StringToModify;
    StringToModify.erase();

    StringToModify = tempString.substr(startIndex, (endIndex-startIndex+ 1) );
}


bool BBBrc::configValid(void)
{
    char lBuffer[64];
    int count=0;
    char sHold[3][64];
    string tmpStr;

    ifstream fin(rcName, ios::in);
    if(!fin)
    {
        cout<<"Unable to open .bbbuttonrc for reading.\n";
        exit(1);
    }
    while(!fin.eof())
    {
        fin.getline(lBuffer, 64);
        if(fin.peek() == '[')
        {
            fin.ignore(1);
            fin.getline(lBuffer, 64, ']');
            if (strcmp(lBuffer, "BUTTON_NO") == 0)
                strncpy(sHold[0], lBuffer, 64);
            count++;
            if (strcmp(lBuffer, "LOAD") == 0)
                strncpy(sHold[2], lBuffer, 64);
            count++;
        }
        // If the first Header in the INI is [BUTTON_NO] and
        // [LOAD] has not yet been discovered, and we have never been in
        // here before
        if (strcmp(sHold[0], "BUTTON_NO") == 0 && strcmp(sHold[2], "LOAD") != 0 &&
                strcmp(sHold[1], "MaxButtons") !=0 )
        {
            fin.getline(lBuffer, 64, '=');
            fin.ignore(1024, '\040'); // Remove leading spaces
            tmpStr = lBuffer;
            sTrim(tmpStr);           // Remove trailing spaces
            // If the string exists then get the value
            if ((tmpStr.compare(0,11,"\nMaxButtons")) == 0)
            {
                fin.getline(lBuffer, 64, '\n');
                istringstream fullString(lBuffer);
                fullString>>maxButtons;
                strncpy(sHold[1], "MaxButtons", 64);
                count++;
                break;
            }
        }
    }
    fin.close();
    if(count != 3 )
    {
        cout<<"Error: The configuration file is misconfigured"<<endl;
        return false;
    }
    else
    {
	setButtonNumber();	
        return true;
    }
}

void BBBrc::setButtonNumber()
{
    int count = 0, startFlag=0;
    char lBuffer[64];

    ifstream fin(rcName,ios::in);
    if(!fin){
        cout<<"Unable to open .bbbuttonrc for reading.\n";
        exit(1) ;
    }
    while(!fin.eof()) {
        if (startFlag ==0) {
            if(fin.peek() == '[') {
                fin.ignore(1);
                fin.getline(lBuffer, 64, ']');
                if (strcmp(lBuffer, "LOAD") == 0)
                    startFlag = 1;
            }
            else fin.ignore(1024, '\n');
        }
        else {
            if( fin.peek() == '#' || fin.peek() == '\0' || fin.peek() == '\n') {
                fin.ignore(1024, '\n');
            }
            else {
                if(!fin.eof()) {
                    count++;
                    fin.getline(picPath,64,'\040');
                    fin.getline(picCMD,64,'\n');
		    string sAmper(picCMD);
		    sAmper.append(" &");
		    holdAll.push_back(picPath);
                    holdAll.push_back(sAmper);
                }
            }

        }
    }
    fin.close();
    numButtons = count;
}

void BBBrc::createButtons(Display* display)
{    
	for( int i = 0; i < holdAll.size() - 1; i+=2 ) {
		aBBButton->push_back(new BBButton(display, 
					(char *) holdAll[i].c_str(), 
					(char *) holdAll[i+1].c_str()));
	}
}
