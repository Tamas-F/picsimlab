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

#include"../picsimlab1.h"
#include"../picsimlab4.h"
#include"../picsimlab5.h"
#include"part_semshield.h"
#include <stdio.h>
#include <cstring>

/* outputs */
enum
{
 O_A1, O_B1, O_C1, O_D1, O_E1, O_F1, O_G1, O_DP1,
 O_A2, O_B2, O_C2, O_D2, O_E2, O_F2, O_G2, O_DP2,
 O_RST, O_SCLK, O_LCLK, O_SER
};

const char pin_names[7][10] = {
 "GND",
 "/RST",
 "SCLK",
 "LCLK",
 "/OE",
 "SER",
 "VCC"
};

const char pin_values[7][10] = {
 "GND",
 {0},
 {1},
 {2},
 "GND",
 {3},
 "+5V"
};

cpart_semshield::cpart_semshield(unsigned x, unsigned y)
{
 X = x;
 Y = y;
 ReadMaps ();
 Bitmap = NULL;

 lxImage image;

 image.LoadFile (Window1.GetSharePath () + lxT ("parts/") + GetPictureFileName ());


 Bitmap = new lxBitmap (image, &Window5);
 image.Destroy ();
 canvas.Create (Window5.GetWWidget (), Bitmap);

 io_74xx595_double_init (&sr8);
 io_74xx595_double_rst (&sr8);

 input_pins[0] = 0;
 input_pins[1] = 0;
 input_pins[2] = 0;
 input_pins[3] = 0;

 memset (lm, 0, 16 * sizeof (unsigned int));
 memset (alm, 0, 16 * sizeof (unsigned int));

}

cpart_semshield::~cpart_semshield(void)
{
 delete Bitmap;
 canvas.Destroy ();
}

void
cpart_semshield::Draw(void)
{

 //int i;

 canvas.Init ();

 lxFont font (8, lxFONTFAMILY_TELETYPE, lxFONTSTYLE_NORMAL, lxFONTWEIGHT_BOLD);
 canvas.SetFont (font);
 for (size_t i = 0; i < outputc; i++)
 {
   if (output[i].id >= O_A1 && output[i].id <= O_DP2)
   {
     int idx = 0;
     switch (output[i].id)
     {
     case O_A1: idx = 15; break;
     case O_B1: idx = 14; break;
     case O_C1: idx = 13; break;
     case O_D1: idx = 8; break;
     case O_E1: idx = 9; break;
     case O_F1: idx = 10; break;
     case O_G1: idx = 11; break;
     case O_DP1: idx = 12; break;
     case O_A2: idx = 4; break;
     case O_B2: idx = 5; break;
     case O_C2: idx = 6; break;
     case O_D2: idx = 3; break;
     case O_E2: idx = 2; break;
     case O_F2: idx = 1; break;
     case O_G2: idx = 0; break;
     case O_DP2: idx = 7; break;
     }
     canvas.SetColor (0, lm[idx], 0);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
    }
    else if (output[i].id >= O_RST && output[i].id <= O_SER)
    {
     canvas.SetColor (49, 61, 99);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
     canvas.SetFgColor (255, 255, 255);
     std::string txt = "";
     switch (output[i].id)
     {
     case O_RST:
       txt += "RST  - ";
       break;
     case O_SCLK:
       txt += "SCLK - ";
       break;
     case O_LCLK:
       txt += "LCLK - ";
       break;
     case O_SER:
       txt += "SER  - ";
       break;
     }
     
     if (input_pins[output[i].id - O_RST] == 0)
       txt += "NC";
     else
       txt += Window5.GetPinName (input_pins[output[i].id - O_RST]);
      canvas.RotatedText (txt, output[i].x1, output[i].y2, 90.0);
    }
 }

 canvas.End ();

}

unsigned short
cpart_semshield::get_in_id(char * name)
{
 printf ("Erro input '%s' don't have a valid id! \n", name);
 return -1;
};

unsigned short
cpart_semshield::get_out_id(char * name)
{
 if (strcmp (name, "A1") == 0)return O_A1;
 if (strcmp (name, "B1") == 0)return O_B1;
 if (strcmp (name, "C1") == 0)return O_C1;
 if (strcmp (name, "D1") == 0)return O_D1;
 if (strcmp (name, "E1") == 0)return O_E1;
 if (strcmp (name, "F1") == 0)return O_F1;
 if (strcmp (name, "G1") == 0)return O_G1;
 if (strcmp (name, "DP1") == 0)return O_DP1;

 if (strcmp (name, "A2") == 0)return O_A2;
 if (strcmp (name, "B2") == 0)return O_B2;
 if (strcmp (name, "C2") == 0)return O_C2;
 if (strcmp (name, "D2") == 0)return O_D2;
 if (strcmp (name, "E2") == 0)return O_E2;
 if (strcmp (name, "F2") == 0)return O_F2;
 if (strcmp (name, "G2") == 0)return O_G2;
 if (strcmp (name, "DP2") == 0)return O_DP2;

 if (strcmp (name, "RST") == 0)return O_RST;
 if (strcmp (name, "SCLK") == 0)return O_SCLK;
 if (strcmp (name, "LCLK") == 0)return O_LCLK;
 if (strcmp (name, "SER") == 0)return O_SER;

 printf ("Erro output '%s' don't have a valid id! \n", name);
 return 1;
};

String
cpart_semshield::WritePreferences(void)
{
 char prefs[256];

 sprintf (prefs, "%hhu,%hhu,%hhu,%hhu", input_pins[0], input_pins[1], input_pins[2], input_pins[3]);

 return prefs;
}

void
cpart_semshield::ReadPreferences(String value)
{
 unsigned char outp;
 sscanf (value.c_str (), "%hhu,%hhu,%hhu,%hhu", &input_pins[0], &input_pins[1], &input_pins[2], &input_pins[3]);
 Reset ();
}

CPWindow * WProp_semshield;

void
cpart_semshield::ConfigurePropertiesWindow(CPWindow * wprop)
{
 String Items = Window5.GetPinsNames ();
 String spin;
 WProp_semshield = wprop;

 for (int i = 0; i < 7; i++)
  {
   String value = "";

   int pinv = pin_values[i][0];
   if (pinv > 4)
    {
     value = lxT ("          ") + String (pin_values[i]);
    }

   ((CLabel*) WProp_semshield->GetChildByName ("label" + itoa (i + 1)))->SetText (itoa (i + 1) + lxT ("-") + pin_names[i] + value);
  }


 ((CCombo*) WProp_semshield->GetChildByName ("combo1"))->SetItems (Items);
 if (input_pins[0] == 0)
  ((CCombo*) WProp_semshield->GetChildByName ("combo1"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[0]);
   ((CCombo*) WProp_semshield->GetChildByName ("combo1"))->SetText (itoa (input_pins[0]) + "  " + spin);
  }

 ((CCombo*) WProp_semshield->GetChildByName ("combo2"))->SetItems (Items);
 if (input_pins[1] == 0)
  ((CCombo*) WProp_semshield->GetChildByName ("combo2"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[1]);
   ((CCombo*) WProp_semshield->GetChildByName ("combo2"))->SetText (itoa (input_pins[1]) + "  " + spin);
  }

 ((CCombo*) WProp_semshield->GetChildByName ("combo3"))->SetItems (Items);
 if (input_pins[2] == 0)
  ((CCombo*) WProp_semshield->GetChildByName ("combo3"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[2]);
   ((CCombo*) WProp_semshield->GetChildByName ("combo3"))->SetText (itoa (input_pins[2]) + "  " + spin);
  }


 ((CCombo*) WProp_semshield->GetChildByName ("combo4"))->SetItems (Items);
 if (input_pins[3] == 0)
  ((CCombo*) WProp_semshield->GetChildByName ("combo4"))->SetText ("0  NC");
 else
  {

   spin = Window5.GetPinName (input_pins[3]);
   ((CCombo*) WProp_semshield->GetChildByName ("combo4"))->SetText (itoa (input_pins[3]) + "  " + spin);
  }



 ((CButton*) WProp_semshield->GetChildByName ("button1"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
 ((CButton*) WProp_semshield->GetChildByName ("button1"))->SetTag (1);

 ((CButton*) WProp_semshield->GetChildByName ("button2"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
}

void
cpart_semshield::ReadPropertiesWindow(void)
{

 input_pins[0] = atoi (((CCombo*) WProp_semshield->GetChildByName ("combo1"))->GetText ());
 input_pins[1] = atoi (((CCombo*) WProp_semshield->GetChildByName ("combo2"))->GetText ());
 input_pins[2] = atoi (((CCombo*) WProp_semshield->GetChildByName ("combo3"))->GetText ());
 input_pins[3] = atoi (((CCombo*) WProp_semshield->GetChildByName ("combo4"))->GetText ());
}

void
cpart_semshield::PreProcess(void)
{
 memset (alm, 0, 16 * sizeof (unsigned int));

 JUMPSTEPS_ = Window1.GetJUMPSTEPS ();
 mcount = JUMPSTEPS_;
}

void
cpart_semshield::Process(void)
{
 const picpin * ppins = Window5.GetPinsValues ();

 unsigned int ret;

 ret = io_74xx595_double_io (&sr8, ppins[input_pins[3] - 1].value, ppins[input_pins[1] - 1].value, ppins[input_pins[2] - 1].value, ppins[input_pins[0] - 1].value);
 
 mcount++;
  if (mcount >= JUMPSTEPS_)
   {
     for (int i = 0; i < 16; i++)
     {
       if (!(ret & (1 << i)))
       {
         alm[i]++;
       }
     }

    mcount = -1;
   }


}

void
cpart_semshield::PostProcess(void)
{
 long int NSTEPJ = Window1.GetNSTEPJ ();
 for (size_t i = 0; i < 16; i++)
 {
    lm[i] = (int) ((255.0 * alm[i]) / NSTEPJ);
    if (lm[i] > 255)lm[i] = 255;
 }
}