/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2019-2020  Luis Claudio Gambôa Lopes

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

#ifndef PART_BUZZER_H
#define PART_BUZZER_H

#include<lxrad.h>
#include"part.h"

class cpart_Buzzer : public part {
public:

    String GetName(void) {
        return lxT("Buzzer");
    };
    cpart_Buzzer(unsigned x, unsigned y);
    ~cpart_Buzzer(void);
    void Draw(void);
    void PreProcess(void);
    void Process(void);
    void PostProcess(void);

    String GetPictureFileName(void) {
        return lxT("Buzzer.png");
    };

    String GetInputMapFile(void) {
        return lxT("Buzzer_i.map");
    };

    String GetOutputMapFile(void) {
        return lxT("Buzzer_o.map");
    };

    String GetPropertiesWindowFile(void) {
        return lxT("Buzzer.lxrad");
    };
    void ConfigurePropertiesWindow(CPWindow * wprop);
    void ReadPropertiesWindow(void);
    String WritePreferences(void);
    void ReadPreferences(String value);
    unsigned short get_in_id(char * name);
    unsigned short get_out_id(char * name);
private:
    void ChangeType(unsigned char tp);
    unsigned char input_pins[1];
    lxaudio buzzer;
    long int mcount;
    int JUMPSTEPS_;
    unsigned char type;
    unsigned int samplerate;
    short *buffer;
    unsigned int buffersize;
    unsigned int buffercount;
    unsigned int maxv;
    float in[3];
    float out[3]; 
};




#endif /* PART_BUZZER */

