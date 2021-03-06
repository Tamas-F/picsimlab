/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

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
#include"part_switchs.h"

/* outputs */
enum
{
 O_P1, O_P2, O_P3, O_P4, O_P5, O_P6, O_P7, O_P8, O_S1, O_S2, O_S3, O_S4, O_S5, O_S6, O_S7, O_S8
};

/* inputs */
enum
{
 I_S1, I_S2, I_S3, I_S4, I_S5, I_S6, I_S7, I_S8
};

cpart_switchs::cpart_switchs(unsigned x, unsigned y)
{
 X = x;
 Y = y;
 ReadMaps ();

 lxImage image;
 image.LoadFile (Window1.GetSharePath () + lxT ("parts/") + GetPictureFileName ());

 Bitmap = new lxBitmap (image, &Window5);
 image.Destroy ();

 canvas.Create (Window5.GetWWidget (), Bitmap);


 output_pins[0] = 0;
 output_pins[1] = 0;
 output_pins[2] = 0;
 output_pins[3] = 0;
 output_pins[4] = 0;
 output_pins[5] = 0;
 output_pins[6] = 0;
 output_pins[7] = 0;

 output_value[0] = 0;
 output_value[1] = 0;
 output_value[2] = 0;
 output_value[3] = 0;
 output_value[4] = 0;
 output_value[5] = 0;
 output_value[6] = 0;
 output_value[7] = 0;

 refresh = 0;

}

void
cpart_switchs::Reset(void)
{
 refresh = 0;

 //force pin update
 if (output_pins[0] > 0)Window5.SetPin (output_pins[0], !output_value[0]);
 if (output_pins[1] > 0)Window5.SetPin (output_pins[1], !output_value[1]);
 if (output_pins[2] > 0)Window5.SetPin (output_pins[2], !output_value[2]);
 if (output_pins[3] > 0)Window5.SetPin (output_pins[3], !output_value[3]);
 if (output_pins[4] > 0)Window5.SetPin (output_pins[4], !output_value[4]);
 if (output_pins[5] > 0)Window5.SetPin (output_pins[5], !output_value[5]);
 if (output_pins[6] > 0)Window5.SetPin (output_pins[6], !output_value[6]);
 if (output_pins[7] > 0)Window5.SetPin (output_pins[7], !output_value[7]);

 if (output_pins[0] > 0)Window5.SetPin (output_pins[0], output_value[0]);
 if (output_pins[1] > 0)Window5.SetPin (output_pins[1], output_value[1]);
 if (output_pins[2] > 0)Window5.SetPin (output_pins[2], output_value[2]);
 if (output_pins[3] > 0)Window5.SetPin (output_pins[3], output_value[3]);
 if (output_pins[4] > 0)Window5.SetPin (output_pins[4], output_value[4]);
 if (output_pins[5] > 0)Window5.SetPin (output_pins[5], output_value[5]);
 if (output_pins[6] > 0)Window5.SetPin (output_pins[6], output_value[6]);
 if (output_pins[7] > 0)Window5.SetPin (output_pins[7], output_value[7]);
}

cpart_switchs::~cpart_switchs(void)
{
 delete Bitmap;
 canvas.Destroy ();
}

void
cpart_switchs::Draw(void)
{

 int i;

 canvas.Init ();

 lxFont font (9, lxFONTFAMILY_TELETYPE, lxFONTSTYLE_NORMAL, lxFONTWEIGHT_BOLD);
 canvas.SetFont (font);

 for (i = 0; i < outputc; i++)
  {

   switch (output[i].id)
    {
    case O_P1:
    case O_P2:
    case O_P3:
    case O_P4:
    case O_P5:
    case O_P6:
    case O_P7:
    case O_P8:
     canvas.SetColor (49, 61, 99);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
     canvas.SetFgColor (255, 255, 255);
     if (output_pins[output[i].id - O_P1] == 0)
      canvas.Text ("NC", output[i].x1, output[i].y1);
     else
      canvas.Text (Window5.GetPinName (output_pins[output[i].id - O_P1]), output[i].x1, output[i].y1);
     break;
    case O_S1:
    case O_S2:
    case O_S3:
    case O_S4:
    case O_S5:
    case O_S6:
    case O_S7:
    case O_S8:

     canvas.SetColor (100, 100, 100);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
     canvas.SetColor (255, 255, 255);
     canvas.Rectangle (1, output[i].x1 + 2, output[i].y1 + 28 - 20 * output_value[output[i].id - O_S1], 18, 10);

     break;


    }


  };

 canvas.End ();

}

void
cpart_switchs::Process(void)
{

 if (refresh > 1000)
  {
   refresh = 0;

   if (output_pins[0] > 0)Window5.SetPin (output_pins[0], output_value[0]);
   if (output_pins[1] > 0)Window5.SetPin (output_pins[1], output_value[1]);
   if (output_pins[2] > 0)Window5.SetPin (output_pins[2], output_value[2]);
   if (output_pins[3] > 0)Window5.SetPin (output_pins[3], output_value[3]);
   if (output_pins[4] > 0)Window5.SetPin (output_pins[4], output_value[4]);
   if (output_pins[5] > 0)Window5.SetPin (output_pins[5], output_value[5]);
   if (output_pins[6] > 0)Window5.SetPin (output_pins[6], output_value[6]);
   if (output_pins[7] > 0)Window5.SetPin (output_pins[7], output_value[7]);

  }
 refresh++;
}

void
cpart_switchs::EvMouseButtonPress(uint button, uint x, uint y, uint state)
{
 int i;

 for (i = 0; i < inputc; i++)
  {
   if (((input[i].x1 <= x)&&(input[i].x2 >= x))&&((input[i].y1 <= y)&&(input[i].y2 >= y)))
    {

     switch (input[i].id)
      {
      case I_S1: output_value[0] ^= 1;
       break;
      case I_S2: output_value[1] ^= 1;
       break;
      case I_S3: output_value[2] ^= 1;
       break;
      case I_S4: output_value[3] ^= 1;
       break;
      case I_S5: output_value[4] ^= 1;
       break;
      case I_S6: output_value[5] ^= 1;
       break;
      case I_S7: output_value[6] ^= 1;
       break;
      case I_S8: output_value[7] ^= 1;
       break;
      }
    }
  }
};

unsigned short
cpart_switchs::get_in_id(char * name)
{

 if (strcmp (name, "S1") == 0)return I_S1;
 if (strcmp (name, "S2") == 0)return I_S2;
 if (strcmp (name, "S3") == 0)return I_S3;
 if (strcmp (name, "S4") == 0)return I_S4;
 if (strcmp (name, "S5") == 0)return I_S5;
 if (strcmp (name, "S6") == 0)return I_S6;
 if (strcmp (name, "S7") == 0)return I_S7;
 if (strcmp (name, "S8") == 0)return I_S8;

 printf ("Erro input '%s' don't have a valid id! \n", name);
 return -1;
};

unsigned short
cpart_switchs::get_out_id(char * name)
{

 if (strcmp (name, "P1") == 0)return O_P1;
 if (strcmp (name, "P2") == 0)return O_P2;
 if (strcmp (name, "P3") == 0)return O_P3;
 if (strcmp (name, "P4") == 0)return O_P4;
 if (strcmp (name, "P5") == 0)return O_P5;
 if (strcmp (name, "P6") == 0)return O_P6;
 if (strcmp (name, "P7") == 0)return O_P7;
 if (strcmp (name, "P8") == 0)return O_P8;

 if (strcmp (name, "S1") == 0)return O_S1;
 if (strcmp (name, "S2") == 0)return O_S2;
 if (strcmp (name, "S3") == 0)return O_S3;
 if (strcmp (name, "S4") == 0)return O_S4;
 if (strcmp (name, "S5") == 0)return O_S5;
 if (strcmp (name, "S6") == 0)return O_S6;
 if (strcmp (name, "S7") == 0)return O_S7;
 if (strcmp (name, "S8") == 0)return O_S8;

 printf ("Erro output '%s' don't have a valid id! \n", name);
 return 1;
};

String
cpart_switchs::WritePreferences(void)
{
 char prefs[256];

 sprintf (prefs, "%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu",
          output_pins[0], output_pins[1], output_pins[2], output_pins[3], output_pins[4], output_pins[5], output_pins[6], output_pins[7],
          output_value[0], output_value[1], output_value[2], output_value[3], output_value[4], output_value[5], output_value[6], output_value[7]);

 return prefs;
};

void
cpart_switchs::ReadPreferences(String value)
{
 sscanf (value.c_str (), "%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu",
         &output_pins[0], &output_pins[1], &output_pins[2], &output_pins[3], &output_pins[4], &output_pins[5], &output_pins[6], &output_pins[7],
         &output_value[0], &output_value[1], &output_value[2], &output_value[3], &output_value[4], &output_value[5], &output_value[6], &output_value[7]);
};

CPWindow * WProp_switchs;

void
cpart_switchs::ConfigurePropertiesWindow(CPWindow * wprop)
{
 String Items = Window5.GetPinsNames ();
 String spin;
 WProp_switchs = wprop;

 ((CCombo*) WProp_switchs->GetChildByName ("combo1"))->SetItems (Items);
 if (output_pins[0] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo1"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[0]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo1"))->SetText (itoa (output_pins[0]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo2"))->SetItems (Items);
 if (output_pins[1] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo2"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[1]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo2"))->SetText (itoa (output_pins[1]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo3"))->SetItems (Items);
 if (output_pins[2] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo3"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[2]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo3"))->SetText (itoa (output_pins[2]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo4"))->SetItems (Items);
 if (output_pins[3] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo4"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[3]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo4"))->SetText (itoa (output_pins[3]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo5"))->SetItems (Items);
 if (output_pins[4] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo5"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[4]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo5"))->SetText (itoa (output_pins[4]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo6"))->SetItems (Items);
 if (output_pins[5] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo6"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[5]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo6"))->SetText (itoa (output_pins[5]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo7"))->SetItems (Items);
 if (output_pins[6] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo7"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[6]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo7"))->SetText (itoa (output_pins[6]) + "  " + spin);
  }

 ((CCombo*) WProp_switchs->GetChildByName ("combo8"))->SetItems (Items);
 if (output_pins[7] == 0)
  ((CCombo*) WProp_switchs->GetChildByName ("combo8"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (output_pins[7]);
   ((CCombo*) WProp_switchs->GetChildByName ("combo8"))->SetText (itoa (output_pins[7]) + "  " + spin);
  }


 ((CButton*) WProp_switchs->GetChildByName ("button1"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
 ((CButton*) WProp_switchs->GetChildByName ("button1"))->SetTag (1);

 ((CButton*) WProp_switchs->GetChildByName ("button2"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
}

void
cpart_switchs::ReadPropertiesWindow(void)
{

 output_pins[0] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo1"))->GetText ());
 output_pins[1] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo2"))->GetText ());
 output_pins[2] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo3"))->GetText ());
 output_pins[3] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo4"))->GetText ());
 output_pins[4] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo5"))->GetText ());
 output_pins[5] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo6"))->GetText ());
 output_pins[6] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo7"))->GetText ());
 output_pins[7] = atoi (((CCombo*) WProp_switchs->GetChildByName ("combo8"))->GetText ());
}

