/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2019  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#ifndef PART_TEMPSYS_H
#define PART_TEMPSYS_H

#include<lxrad.h>
#include"part.h"

class cpart_tempsys : public part {
public:

    String GetName(void) {
        return lxT("Temperature System");
    };
    cpart_tempsys(unsigned x, unsigned y);
    ~cpart_tempsys(void);
    void Draw(void);
    void Process(void);

    String GetPictureFileName(void) {
        return lxT("TempSys.png");
    };

    String GetInputMapFile(void) {
        return lxT("TempSys_i.map");
    };

    String GetOutputMapFile(void) {
        return lxT("TempSys_o.map");
    };

    String GetPropertiesWindowFile(void) {
        return lxT("TempSys.lxrad");
    };
    void EvMouseButtonPress(uint button, uint x, uint y, uint state);
    void EvMouseButtonRelease(uint button, uint x, uint y, uint state);
    void EvMouseMove(uint button, uint x, uint y, uint state);
    void ConfigurePropertiesWindow(CPWindow * wprop);
    void ReadPropertiesWindow(void);
    String WritePreferences(void);
    void ReadPreferences(String value);
    unsigned short get_in_id(char * name);
    unsigned short get_out_id(char * name);
private:
    unsigned char input_pins[4];
    lxBitmap * vent[2];
    float temp[2];
    float ref;
    int vtc;
    int vt;
    int rpmstp;
    int rpmc;
};




#endif /* PART_TEMPSYS */

