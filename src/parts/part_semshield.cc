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

// enum
// {
//  O_P1, O_P2, O_P3, O_P4, O_P5, O_P6, O_P7, O_P8, O_P9, O_P10, O_P11, O_P12,
//  O_P13, O_P14, O_P15, O_P16, O_IC
// };

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

//  output_pins[0] = Window5.RegisterIOpin (lxT ("QA"));
//  output_pins[1] = Window5.RegisterIOpin (lxT ("QB"));
//  output_pins[2] = Window5.RegisterIOpin (lxT ("QC"));
//  output_pins[3] = Window5.RegisterIOpin (lxT ("QD"));
//  output_pins[4] = Window5.RegisterIOpin (lxT ("QE"));
//  output_pins[5] = Window5.RegisterIOpin (lxT ("QF"));
//  output_pins[6] = Window5.RegisterIOpin (lxT ("QG"));
//  output_pins[7] = Window5.RegisterIOpin (lxT ("QH"));
//  output_pins[8] = Window5.RegisterIOpin (lxT ("SOUT"));

 //mcount = 0;
 memset (lm, 0, 16 * sizeof (unsigned int));
 memset (alm, 0, 16 * sizeof (unsigned int));
 //memset (output_pins_alm, 0, 9 * sizeof (unsigned long));

}

cpart_semshield::~cpart_semshield(void)
{
 //for (int i = 0; i < 9; i++)
  //Window5.UnregisterIOpin (output_pins[i]);
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
      //canvas.RotatedText ("NC", output[i].x1, output[i].y2, 90.0);
     else
       txt += Window5.GetPinName (input_pins[output[i].id - O_RST]);
      //canvas.RotatedText (Window5.GetPinName (input_pins[output[i].id - O_P1]), output[i].x1, output[i].y2, 90.0);
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

//  if (output_pins[0] != outp)
//   {

//    for (int i = 0; i < 9; i++)
//     Window5.UnregisterIOpin (output_pins[i]);

//    output_pins[0] = Window5.RegisterIOpin (lxT ("QA"), outp++);
//    output_pins[1] = Window5.RegisterIOpin (lxT ("QB"), outp++);
//    output_pins[2] = Window5.RegisterIOpin (lxT ("QC"), outp++);
//    output_pins[3] = Window5.RegisterIOpin (lxT ("QD"), outp++);
//    output_pins[4] = Window5.RegisterIOpin (lxT ("QE"), outp++);
//    output_pins[5] = Window5.RegisterIOpin (lxT ("QF"), outp++);
//    output_pins[6] = Window5.RegisterIOpin (lxT ("QG"), outp++);
//    output_pins[7] = Window5.RegisterIOpin (lxT ("QH"), outp++);
//    output_pins[8] = Window5.RegisterIOpin (lxT ("SOUT"), outp++);
//   }


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
  //  else if (pinv >= 4)
  //   {
  //    if (output_pins[pinv - 4] == 0)
  //     value = "          NC";
  //    else
  //     value = lxT ("          ") + itoa (output_pins[pinv - 4]); // + lxT (" ") + Window5.GetPinName (output_pins[pinv - 4]);
  //   }


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

//  if (_ret != ret)
//   {
//    Window5.WritePin (output_pins[0], (ret & 0x01) != 0);
//    Window5.WritePin (output_pins[1], (ret & 0x02) != 0);
//    Window5.WritePin (output_pins[2], (ret & 0x04) != 0);
//    Window5.WritePin (output_pins[3], (ret & 0x08) != 0);
//    Window5.WritePin (output_pins[4], (ret & 0x10) != 0);
//    Window5.WritePin (output_pins[5], (ret & 0x20) != 0);
//    Window5.WritePin (output_pins[6], (ret & 0x40) != 0);
//    Window5.WritePin (output_pins[7], (ret & 0x80) != 0);
//    Window5.WritePin (output_pins[8], (ret & 0x100) != 0);
//   }
 _ret = ret;
//  for (int i = 15; i >= 0; i--)
//  {
//    printf("%d", (1 << i) & ret ? 1 : 0);
//  }
//  printf("\n");
 
 mcount++;
  if (mcount >= JUMPSTEPS_)
   {
     for (int i = 0; i < 16; i++)
     {
       if (_ret & (1 << i))
       {
         alm[i]++;
       }
     }
     
//    if (ppins[output_pins[0]].value)output_pins_alm[0]++;
//    if (ppins[output_pins[1]].value)output_pins_alm[1]++;
//    if (ppins[output_pins[2]].value)output_pins_alm[2]++;
//    if (ppins[output_pins[3]].value)output_pins_alm[3]++;
//    if (ppins[output_pins[4]].value)output_pins_alm[4]++;
//    if (ppins[output_pins[5]].value)output_pins_alm[5]++;
//    if (ppins[output_pins[6]].value)output_pins_alm[6]++;
//    if (ppins[output_pins[7]].value)output_pins_alm[7]++;

//    if (ppins[output_pins[8]].value)output_pins_alm[8]++;

    mcount = -1;
   }


}

void
cpart_semshield::PostProcess(void)
{
 long int NSTEPJ = Window1.GetNSTEPJ ();
//  const picpin * ppins = Window5.GetPinsValues ();
 for (size_t i = 0; i < 16; i++)
 {
    lm[i] = (int) ((255.0 * alm[i]) / NSTEPJ);
    if (lm[i] > 255)lm[i] = 255;
 }
 
//  Window5.WritePinA (output_pins[0], (ppins[output_pins[0] - 1].oavalue + ((output_pins_alm[0]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[1], (ppins[output_pins[1] - 1].oavalue + ((output_pins_alm[1]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[2], (ppins[output_pins[2] - 1].oavalue + ((output_pins_alm[2]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[3], (ppins[output_pins[3] - 1].oavalue + ((output_pins_alm[3]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[4], (ppins[output_pins[4] - 1].oavalue + ((output_pins_alm[4]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[5], (ppins[output_pins[5] - 1].oavalue + ((output_pins_alm[5]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[6], (ppins[output_pins[6] - 1].oavalue + ((output_pins_alm[6]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[7], (ppins[output_pins[7] - 1].oavalue + ((output_pins_alm[7]*255.0) / NSTEPJ)) / 2);
//  Window5.WritePinA (output_pins[8], (ppins[output_pins[8] - 1].oavalue + ((output_pins_alm[8]*255.0) / NSTEPJ)) / 2);

}