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

#ifndef PART_SEMSHIELD_H
#define	PART_SEMSHIELD_H

#include<lxrad.h>
#include"part.h"
#include"../devices/io_74xx595_double.h"

class cpart_semshield:public part
{
   public:
      String GetName(void){return lxT("SEM shield");};
      cpart_semshield(unsigned x, unsigned y);
      ~cpart_semshield(void);
      void Draw(void);
      void PreProcess (void);
      void Process(void); 
      void PostProcess (void);
      String GetPictureFileName(void){return lxT("semshield.png");};
      String GetInputMapFile(void){return lxT("semshield_i.map");};
      String GetOutputMapFile(void){return lxT("semshield_o.map");};
      String GetPropertiesWindowFile(void){return lxT("semshield.lxrad");};
      void ConfigurePropertiesWindow(CPWindow *  wprop);
      void ReadPropertiesWindow(void);
      String WritePreferences(void);
      void ReadPreferences(String value);
      unsigned short get_in_id(char * name);
      unsigned short get_out_id(char * name);
   private:
      unsigned char input_pins[4];
      unsigned int lm[16]; //luminosidade media display
      unsigned int alm[16];
      long mcount;
      int JUMPSTEPS_;
      io_74xx595_double_t sr8;
      unsigned int _ret; 
};




#endif	/* PART_SEMSHIELD_H */

