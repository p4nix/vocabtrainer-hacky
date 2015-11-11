#include "fxlib.h"
#include "usefull.h"
#include "MonochromeLib.h"
#include "menu.h"

#define NUMVOCABELS 81

char latein[81][16] = {"limes",           "caligo",           "caecus",            "sidus",           "ullus",
                       "animal",          "astrum",           "caelestis",         "solum",           "piscis",
                       "unda",            "ferus",            "volucris",          "dominari",        "nasci",
                       "sive..sive",      "recens",           "nuper",             "miscere",         "pronus",
                       "os",              "erigere",          "modo",              "imago",           "induere",
                       "ignotus",         "convertere",       "figura",            "vacuus",          "praeda",
                       "extendere",       "stringere",        "vestigium",         "tergum",          "spargere",
                       "prex",            "finire",           "artus",             "haerere",         "remanere",
                       "dextera",         "complecti",        "osculum",           "munus",           "sitis",
                       "natus",           "blandus",          "procul",            "turbare",         "huc",
                       "illuc",           "evenire",          "proferre",          "super",           "lis",
                       "quamvis",         "collum",           "venter",            "interea",         "exilium",
                       "licet",           "possidere",        "ordo",              "rusticus",        "surgere",
                       "cera",            "avis",             "ignarus",           "tractare",        "lusus",
                       "impedire",        "instruere",        "volare",            "praeceptum",      "umerus",
                       "audax",           "cupido",           "vinculum",          "nudus",           "sepulcrum",
                       "sepelire"
};

char german[81][21] = {"Grenze, -wall",   "Finsternis/Rauch", "blind/dunkel",      "Stern/-bild",     "irgendeiner",
                       "Lebewesen/Tier",  "Stern/Gestirn",    "himmlisch/Goetter", "Boden/Land",      "Fisch",
                       "Welle/Gewaesser", "wild/wildes Tier", "Vogel",             "herrschen ueber", "geboren werden",
                       "sei es..,oder..", "neu/jung/frisch",  "neulich",           "mischen",         "vornuebergeneigt",
                       "Gesicht/Mund",    "aufrichten",       "gerade eben/nur",   "Bild/Bildnis",    "bekleiden",
                       "unbekannt",       "drehn/verwandeln", "Gestalt/Form",      "leer/frei",       "Beute",
                       "ausstrecken",     "ziehen/streifen",  "Spur/Fuss",         "Ruecken",         "ausstreuen",
                       "Bitte/Gebet",     "begrenzen/-enden", "Koerperteil",        "haften an",       "zurueckbleiben",
                       "rechte Hand",     "umfassen",         "Kuss",              "Amt/Aufgabe",     "Durst",
                       "Sohn/Tochter",    "schmeichlerisch",  "in der Ferne",      "Unruhe versetzn", "hierher",
                       "dahin/dorthin",   "sich ereignen",    "hervorbringen",     "ueber/oben",      "Streit/Prozess",
                       "auch wenn",       "Hals/Nacken",      "Bauch",             "inzwischen",      "Verbannung",
                       "auch wenn",       "besitzen",         "Ordnung/Stand",     "laendl./baurl.",  "aufstehen",
                       "Wachs/-tafel",    "Vogel",            "unwissend/-kundig", "behandeln",       "Spiel/Scherz",
                       "behindern",       "aufstellen",       "fliegen/ereilen",   "Anweisung/Lehre", "Schulter",
                       "mutig/kuehn",     "Begierde/Trieb",   "Fessel",            "nackt",           "Grab",
                       "begraben"

};

int AddIn_main(int isAppli, unsigned short OptionNum)
{
  short vokabelSkill[81];
  unsigned int key = 0;
  int initRand = 0;
  char i = 0;
  char chosenvoc = 0;
  char chosennum = 0;
  int smallest;
  int Rand[6];
  char input;
  int richtig = 0;
  int falsch = 0;
  int c;
  int mode = 1;

  for(i = 0; i < NUMVOCABELS; i++){
    vokabelSkill[i] = 0;
  }

  readFile("LEARN","YAY",(unsigned char*)vokabelSkill);


  locate(1,1);
  Print((unsigned const char*)"rand() seeden... [EXE]");
  Bdisp_PutDisp_DD();

  while(!key_down(K_EXE)){
    initRand++;
    if(initRand > 1000) initRand = 0;
  }
  Sleep(1000);
  Bdisp_AllClr_DDVRAM();




  while(1 && mode != 3){
    mode = 0;
    c = 0;
    richtig = 0;
    falsch = 0;
    ML_bmp_or(menu, 0, 0, 128, 64);
    Bdisp_PutDisp_DD();

    while(mode == 0){
      GetKey(&key);
      if(key == KEY_CTRL_F1) mode = 1;
      if(key == KEY_CTRL_F2) mode = 2;
      if(key == KEY_CTRL_F3) mode = 3;
    }
    ML_clear_vram();



    while((mode != 3) && ((mode == 1 && c < 20) || (mode == 2 && c < NUMVOCABELS))){
      if(mode == 1){
        smallest = vokabelSkill[0];
        for(i = 0; i < NUMVOCABELS; i++){
          if(smallest > vokabelSkill[i]){smallest = vokabelSkill[i]; chosenvoc = i;}
          if((smallest == vokabelSkill[i]) && !((rand() + initRand)%5)){smallest = vokabelSkill[i]; chosenvoc = i;}
        }
      }

      if(mode == 2){
        chosenvoc = c%NUMVOCABELS;
      }
      chosennum = (rand() + initRand)%6;

      for(i = 0; i < 6; i++){
        Rand[i] = (rand() + initRand)%NUMVOCABELS;
        while(Rand[i-1] == Rand[i] || Rand[i] == chosenvoc)
          Rand[i] = (rand() + initRand)%NUMVOCABELS;
      }

      Rand[chosennum] = chosenvoc;

      locate(1,1);
      Print((unsigned char*)latein[chosenvoc]);

      for(i = 0; i < 6; i++){
        //if(i == chosennum){
       //   PrintMini(0, 10+i*8, (unsigned char*)german[chosenvoc], MINI_OVER);
        //} else {
          PrintMini(0, 10+i*8, (unsigned char*)german[Rand[i]], MINI_OVER);
       // }
      }
      GetKey(&key);
      Bdisp_AllClr_DDVRAM();

      switch(key){
        case KEY_CTRL_F1: input = 0; break;
        case KEY_CTRL_F2: input = 1; break;
        case KEY_CTRL_F3: input = 2; break;
        case KEY_CTRL_F4: input = 3; break;
        case KEY_CTRL_F5: input = 4; break;
        case KEY_CTRL_F6: input = 5; break;
        case KEY_CTRL_EXIT: goto end; break;
        default: input = 7;
      }

      if(input == chosennum){
        locate(1,1);
        Print((unsigned char*)"Richtig!");
        vokabelSkill[chosenvoc]++;
        richtig++;
      } else {
        locate(1,1);
        Print((unsigned char*)"Falsch!");
        locate(1,2);
        Print((unsigned char*)german[chosenvoc]);
        falsch++;
      }

      for(i = 0; i < 6; i++){
        Rand[i] = NUMVOCABELS+1;
      }
      GetKey(&key);
      Bdisp_AllClr_DDVRAM();
      c++;
    }

    end:
    if(mode != 3){
      writeFile("LEARN","YAY",(unsigned char*)vokabelSkill,NUMVOCABELS*2);
      PrintV(0,0,richtig); PrintMini(60,0,"richtig!",MINI_OVER);
      PrintV(0,20,falsch); PrintMini(60,20,"falsch!",MINI_OVER);
      Bdisp_PutDisp_DD();
      GetKey(&key);
      ML_clear_vram();
    }
  }





  return 1;
}




#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP


int InitializeSystem(int isAppli, unsigned short OptionNum)
{
  return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

