
#include <Arduino.h>


// init globale variabelen:
int blockx=0;
int blocky=0;
int blockz=0;
int steplength = 1;


//// beweeg:
//lineto(-40,30,0); // lijnrecht naar punt (-40,30), met snelheid 10 cm/sec
//circle(-10,0,2*pi/3,30); // cirkelvormig om middelpunt (-10,0) over een hoek van (2/3)*pi (tegen de klok in) met snelheid 30 cm/sec
//lineto(80,20,20); // lijnrecht naar punt (80,20) met snelheid 20 cm/sec
//circle(40,10,-pi,10); // cirkelvormig om middelpunt (40,10) over een hoek van -pi (=pi met klok mee) met snelheid 10 cm/sec

// Constanten
// alle maten voorlopig in mm

// gemeten stappen/mm ~250
float StepUnit =   250.0;

bool AutoMove = 0;
bool nextPos = 0;
int Autoteller = 0;

float phi = 3.141592653589 ;

int StepSpeed = 200;

int LengthBlockBottom = 118;
int WidthBlockBottom = 48;
int HighBlock = 41;

int LengthBlockTop = 68;
int WidthBlockTop = 78;

int LengthFrame = 320;
int WidhtFrame = 200;
int HighFrame = 280;

float DiaKatrol = 21.40;

float ActualMainX;
float ActualMainY;
float ActualMainZ;

float WantedMainX;
float WantedMainY;
float WantedMainZ;

float WantedRotX;
float ActualRotX;

float WantedRotY;
float ActualRotY;

float WantedRotZ;
float ActualRotZ;

long totalMove[8];
int motorNbr[8] = {1, 2, 3, 4, 5, 6, 7 , 8};;
String CommandFromPC = "";
bool Inpos = 1;
bool InposOld = 1;
long totalPulses = 0;
float Procent100;
bool CalibrationIsOn = true;
bool go = false;

struct Coordinate {
  float X;
  float Y;
  float Z;
} ;
struct Rotation {
  float X;
  float Y;
  float Z;
} ;
struct Coordinate ObjectCorner[9];

struct Coordinate NewPosition[20] = {{0, 0, 30},
  {0, 0, 0},
  {0, 0, -30},
  {0, 0, 0},
  {0, 30, 0},
  {0, 0, 0},
  {0, -30, 0},
  {0, 0, 0},
  {30, 0, 0},
  {0, 0, 0},
  { -30, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};
struct Rotation NewRotation[20] =   {{0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {45, 0, 0},
  {0, 0, 0},
  { -45, 0, 0},
  {0, 0, 0},
  {0, 30, 0},
  {0, 0, 0},
  {0, -30, 0},
  {0, 0, 0}
};

#define oDir1 0
#define oStep1 1
#define oDir2 2
#define oStep2 3
#define oDir3 4
#define oStep3 5
#define oDir4 6
#define oStep4 7
#define oDir5 9
#define oStep5 8
#define oDir6 11
#define oStep6 10
#define oDir7 13
#define oStep7 12
#define oDir8 15
#define oStep8 14

//----------------------------------------------------------------------------------------------
bool Mot1On = 0;
bool Mot1Direction = 0;
long Mot1WantedLength;
long Mot1ActualLength;
int mot1PulseProcent;
int Mot1PulseCounter;
bool pulse1 = 0;
//----------------------------------------------------------------------------------------------
bool Mot2On = 0;
bool Mot2Direction = 0;
long Mot2WantedLength;
long Mot2ActualLength;
int mot2PulseProcent;
int Mot2PulseCounter;
bool pulse2 = 0;
//----------------------------------------------------------------------------------------------
bool Mot3On = 0;
bool Mot3Direction = 0;
long Mot3WantedLength;
long Mot3ActualLength;
int mot3PulseProcent;
int Mot3PulseCounter;
bool pulse3 = 0;
//----------------------------------------------------------------------------------------------
bool Mot4On = 0;
bool Mot4Direction = 0;
long Mot4WantedLength;
long Mot4ActualLength;
int mot4PulseProcent;
int Mot4PulseCounter;
bool pulse4 = 0;
//----------------------------------------------------------------------------------------------
bool Mot5On = 0;
bool Mot5Direction = 0;
long Mot5WantedLength;
long Mot5ActualLength;
int mot5PulseProcent;
int Mot5PulseCounter;
bool pulse5 = 0;
//----------------------------------------------------------------------------------------------
bool Mot6On = 0;
bool Mot6Direction = 0;
long Mot6WantedLength;
long Mot6ActualLength;
int mot6PulseProcent;
int Mot6PulseCounter;
bool pulse6 = 0;
//----------------------------------------------------------------------------------------------
bool Mot7On = 0;
bool Mot7Direction = 0;
long Mot7WantedLength;
long Mot7ActualLength;
int mot7PulseProcent;
int Mot7PulseCounter;
bool pulse7 = 0;
//----------------------------------------------------------------------------------------------
bool Mot8On = 0;
bool Mot8Direction = 0;
long Mot8WantedLength;
long Mot8ActualLength;
int mot8PulseProcent;
int Mot8PulseCounter;
bool pulse8 = 0;
//----------------------------------------------------------------------------------------------

int incomingByte = 0;

bool pulse = 0;

void setup() {

  pinMode(oDir1, OUTPUT);
  pinMode(oStep1, OUTPUT);

  pinMode(oDir2, OUTPUT);
  pinMode(oStep2, OUTPUT);

  pinMode(oDir3, OUTPUT);
  pinMode(oStep3, OUTPUT);

  pinMode(oDir4, OUTPUT);
  pinMode(oStep4, OUTPUT);

  pinMode(oDir5, OUTPUT);
  pinMode(oStep5, OUTPUT);

  pinMode(oDir6, OUTPUT);
  pinMode(oStep6, OUTPUT);

  pinMode(oDir7, OUTPUT);
  pinMode(oStep7, OUTPUT);

  pinMode(oDir8, OUTPUT);
  pinMode(oStep8, OUTPUT);

  //Setup Array by start programma 
  ObjectCorner[1].X =   ActualMainX - (LengthBlockBottom / 2.0);
  ObjectCorner[1].Y =   ActualMainY - (WidthBlockBottom / 2.0);
  ObjectCorner[1].Z =   ActualMainZ - (HighBlock / 2.0);

  Mot1ActualLength = Mot1(ObjectCorner[1].X, ObjectCorner[1].Y, ObjectCorner[1].Z);
  Mot1WantedLength = Mot1ActualLength;

  ObjectCorner[2].X =   ActualMainX - (LengthBlockBottom / 2.0);
  ObjectCorner[2].Y =   ActualMainY + (WidthBlockBottom / 2.0);
  ObjectCorner[2].Z =   ActualMainZ - (HighBlock / 2.0);

  Mot2ActualLength = Mot2(ObjectCorner[2].X, ObjectCorner[2].Y, ObjectCorner[2].Z);
  Mot2WantedLength = Mot2ActualLength;

  ObjectCorner[3].X =   ActualMainX + (LengthBlockBottom / 2.0);
  ObjectCorner[3].Y =   ActualMainY - (WidthBlockBottom / 2.0);
  ObjectCorner[3].Z =   ActualMainZ - (HighBlock / 2.0);

  Mot3ActualLength = Mot3(ObjectCorner[3].X, ObjectCorner[3].Y, ObjectCorner[3].Z);
  Mot3WantedLength = Mot3ActualLength;

  ObjectCorner[4].X =   ActualMainX + (LengthBlockBottom / 2.0);
  ObjectCorner[4].Y =   ActualMainY + (WidthBlockBottom / 2.0);
  ObjectCorner[4].Z =   ActualMainZ - (HighBlock / 2.0);

  Mot4ActualLength = Mot4(ObjectCorner[4].X, ObjectCorner[4].Y, ObjectCorner[4].Z);
  Mot4WantedLength = Mot4ActualLength;

  ObjectCorner[5].X =   ActualMainX - (LengthBlockBottom / 2.0);
  ObjectCorner[5].Y =   ActualMainY - (WidthBlockBottom / 2.0);
  ObjectCorner[5].Z =   ActualMainZ + (HighBlock / 2.0);

  Mot5ActualLength = Mot5(ObjectCorner[5].X, ObjectCorner[5].Y, ObjectCorner[5].Z);
  Mot5WantedLength = Mot5ActualLength;

  ObjectCorner[6].X =   ActualMainX - (LengthBlockBottom / 2.0);
  ObjectCorner[6].Y =   ActualMainY + (WidthBlockBottom / 2.0);
  ObjectCorner[6].Z =   ActualMainZ + (HighBlock / 2.0);

  Mot6ActualLength = Mot6(ObjectCorner[6].X, ObjectCorner[6].Y, ObjectCorner[6].Z);
  Mot6WantedLength = Mot6ActualLength;

  ObjectCorner[7].X =   ActualMainX + (LengthBlockBottom / 2.0);
  ObjectCorner[7].Y =   ActualMainY - (WidthBlockBottom / 2.0);
  ObjectCorner[7].Z =   ActualMainZ + (HighBlock / 2.0);

  Mot7ActualLength = Mot7(ObjectCorner[7].X, ObjectCorner[7].Y, ObjectCorner[7].Z);
  Mot7WantedLength = Mot7ActualLength;


  ObjectCorner[8].X =   ActualMainX + (LengthBlockBottom / 2.0);
  ObjectCorner[8].Y =   ActualMainY + (WidthBlockBottom / 2.0);
  ObjectCorner[8].Z =   ActualMainZ + (HighBlock / 2.0);

  Mot8ActualLength = Mot8(ObjectCorner[8].X, ObjectCorner[8].Y, ObjectCorner[8].Z);
  Mot8WantedLength = Mot8ActualLength;

  Serial.begin(11520);

  while (!Serial.available());

  Serial.println("Communication Active");
}

void loop() {

  if (Serial.available()) {
    char c = Serial.read();
    //Serial.println(c) ;
    if (c == '\n')
    {
      parseCommand(CommandFromPC);
      CommandFromPC = "";
    }
    else
    {
      CommandFromPC += c;
    }
  }

  //=====================================================================================================
  // pulsjes maken
  pulse = pulse xor 1;            // pulse inverteren

  //=====================================================================================================
  if (Inpos == 1) {

    if (WantedRotX != ActualRotX) {
      // object draaien om x-as
      for (int j = 1; j < 9; j++) {
        matrixRotX(ObjectCorner[j].X, ObjectCorner[j].Y , ObjectCorner[j].Z , ActualRotX - WantedRotX , j);
      };
      go = 1;
    };
    if (WantedRotY != ActualRotY) {
      // object draaien om Y-as
      for (int j = 1; j < 9; j++) {
        matrixRotY(ObjectCorner[j].X, ObjectCorner[j].Y , ObjectCorner[j].Z , ActualRotY - WantedRotY , j);
      };
      go = 1;
    };
    if (WantedRotZ != ActualRotZ) {
      // object draaien om Z-as
      for (int j = 1; j < 9; j++) {
        matrixRotZ(ObjectCorner[j].X, ObjectCorner[j].Y , ObjectCorner[j].Z , ActualRotZ - WantedRotZ , j);
      };
      go = 1;
    };
    if ( WantedMainX != ActualMainX or WantedMainY != ActualMainY or WantedMainZ != ActualMainZ ) {
      // hoekpunten door de matrix halen, aan de hand van de main coordinaten
      for (int j = 1; j < 9; j++) {
        //        SerialUSB.print("Hoek nr : ");
        //        SerialUSB.print(j);
        //        SerialUSB.print(" ");
        matrixTrans(ObjectCorner[j].X, ObjectCorner[j].Y , ObjectCorner[j].Z , (ActualMainX - WantedMainX) , (ActualMainY - WantedMainY), -(ActualMainZ - WantedMainZ) , j);
      };
      go = 1;
    };

    if (go == 1) {
      Inpos = 0;
      go = 0;
      Mot1WantedLength = Mot1(ObjectCorner[1].X, ObjectCorner[1].Y, ObjectCorner[1].Z);
      Mot2WantedLength = Mot2(ObjectCorner[2].X, ObjectCorner[2].Y, ObjectCorner[2].Z);
      Mot3WantedLength = Mot3(ObjectCorner[3].X, ObjectCorner[3].Y, ObjectCorner[3].Z);
      Mot4WantedLength = Mot4(ObjectCorner[4].X, ObjectCorner[4].Y, ObjectCorner[4].Z);

      Mot5WantedLength = Mot5(ObjectCorner[5].X, ObjectCorner[5].Y, ObjectCorner[5].Z);
      Mot6WantedLength = Mot6(ObjectCorner[6].X, ObjectCorner[6].Y, ObjectCorner[6].Z);
      Mot7WantedLength = Mot7(ObjectCorner[7].X, ObjectCorner[7].Y, ObjectCorner[7].Z);
      Mot8WantedLength = Mot8(ObjectCorner[8].X, ObjectCorner[8].Y, ObjectCorner[8].Z);

      // langste verplaatsing zoeken

      totalMove[0] = abs(Mot1WantedLength - Mot1ActualLength);
      totalMove[1] = abs(Mot2WantedLength - Mot2ActualLength);
      totalMove[2] = abs(Mot3WantedLength - Mot3ActualLength);
      totalMove[3] = abs(Mot4WantedLength - Mot4ActualLength);

      totalMove[4] = abs(Mot5WantedLength - Mot5ActualLength);
      totalMove[5] = abs(Mot6WantedLength - Mot6ActualLength);
      totalMove[6] = abs(Mot7WantedLength - Mot7ActualLength);
      totalMove[7] = abs(Mot8WantedLength - Mot8ActualLength);

      long storeTemp;
      int storeNbr;
      bool tmpSwapped;
again :
      tmpSwapped = false;
      for (int i = 0; i < 7; i++) {
        if (totalMove[i] < totalMove[i + 1]) {

          storeTemp = totalMove[i + 1];
          totalMove[i + 1] = totalMove[i];
          totalMove[i] = storeTemp;

          storeNbr = motorNbr[i + 1];
          motorNbr[i + 1] = motorNbr[i];
          motorNbr[i] = storeNbr;

          tmpSwapped = true;
        }
      }
      if (tmpSwapped == 1) {
        goto again;
      }

      Procent100 = 100.0 / totalMove[0];
      Serial.print("Procent100 :");
      Serial.println(Procent100);

      for (int i = 0; i < 8; i++) {
        if (motorNbr[i] == 1) {
          mot1PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 2) {
          mot2PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 3) {
          mot3PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 4) {
          mot4PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 5) {
          mot5PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 6) {
          mot6PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 7) {
          mot7PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
        if (motorNbr[i] == 8)
        {
          mot8PulseProcent = (Procent100 * totalMove[i]) + 0.5;
        }
      }

      for (int i = 0; i < 8; i++) {
        Serial.print("Motornr :");
        Serial.print(motorNbr[i]);
        Serial.print(" totalMove:");
        Serial.println(totalMove[i]);
      }
      Mot1Direction = 0;
      if (Mot1WantedLength > Mot1ActualLength) {
        Mot1Direction = 1;
      }
      Mot2Direction = 0;
      if (Mot2WantedLength > Mot2ActualLength) {
        Mot2Direction = 1;
      }
      Mot3Direction = 0;
      if (Mot3WantedLength > Mot3ActualLength) {
        Mot3Direction = 1;
      }
      Mot4Direction = 0;
      if (Mot4WantedLength > Mot4ActualLength) {
        Mot4Direction = 1;
      }
      Mot5Direction = 0;
      if (Mot5WantedLength > Mot5ActualLength) {
        Mot5Direction = 1;
      }
      Mot6Direction = 0;
      if (Mot6WantedLength > Mot6ActualLength) {
        Mot6Direction = 1;
      }
      Mot7Direction = 0;
      if (Mot7WantedLength > Mot7ActualLength) {
        Mot7Direction = 1;
      }
      Mot8Direction = 0;
      if (Mot8WantedLength > Mot8ActualLength) {
        Mot8Direction = 1;
      }
      Serial.println(" ----------");
      Serial.print("richting : ");
      Serial.print(Mot1Direction );
      Serial.print(" Procent : ");
      Serial.println(mot1PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot2Direction );
      Serial.print(" Procent : ");
      Serial.println(mot2PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot3Direction );
      Serial.print(" Procent : ");
      Serial.println(mot3PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot4Direction );
      Serial.print(" Procent : ");
      Serial.println(mot4PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot6Direction );
      Serial.print(" Procent : ");
      Serial.println(mot5PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot6Direction );
      Serial.print(" Procent : ");
      Serial.println(mot6PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot7Direction );
      Serial.print(" Procent : ");
      Serial.println(mot7PulseProcent);

      Serial.print("richting : ");
      Serial.print(Mot8Direction );
      Serial.print(" Procent : ");
      Serial.println(mot8PulseProcent);
    }
  }

  //=====================================================================================================
  // positie bereikt

  if (Mot1WantedLength == Mot1ActualLength and
      Mot2WantedLength == Mot2ActualLength and
      Mot3WantedLength == Mot3ActualLength and
      Mot4WantedLength == Mot4ActualLength and
      Mot5WantedLength == Mot5ActualLength and
      Mot6WantedLength == Mot6ActualLength and
      Mot7WantedLength == Mot7ActualLength and
      Mot8WantedLength == Mot8ActualLength)
  {
    ActualMainX = WantedMainX;
    ActualMainY = WantedMainY;
    ActualMainZ = WantedMainZ;

    ActualRotX = WantedRotX;
    ActualRotY = WantedRotY;
    ActualRotZ = WantedRotZ;

delay(100);

    Inpos = 1;
    Mot1PulseCounter = 0;
    Mot2PulseCounter = 0;
    Mot3PulseCounter = 0;
    Mot4PulseCounter = 0;
    Mot5PulseCounter = 0;
    Mot6PulseCounter = 0;
    Mot7PulseCounter = 0;
    Mot8PulseCounter = 0;
  };


  //  //------------------------------------------------------------------------------------
  //  // motors aan sturen
  //
  if (Inpos == 0) {
    Motor1();
    Motor2();
    Motor3();
    Motor4();
    //
    Motor5();
    Motor6();
    Motor7();
    Motor8();
  };

  if (Inpos > InposOld) {
    Serial.println("InPosition");
    Serial.print("Main :");
    Serial.print(ActualMainX);
    Serial.print(" , ");
    Serial.print(ActualMainY);
    Serial.print(" , ");
    Serial.println(ActualMainZ);
    nextPos = 1;
  };
  if (Inpos < InposOld) {
    Serial.println("Moving");
  };

  InposOld = Inpos;

  if (AutoMove == 1) {
    if (nextPos == 1) {
      nextPos = 0;
      WantedMainX = NewPosition[Autoteller].X;
      WantedMainY = NewPosition[Autoteller].Y;
      WantedMainZ = NewPosition[Autoteller].Z;

      WantedRotX = NewRotation[Autoteller].X;
      WantedRotY = NewRotation[Autoteller].Y;
      WantedRotZ = NewRotation[Autoteller].Z;

      Autoteller = Autoteller + 1;
      if (Autoteller > 19) {
        Autoteller = 0;
      }
    }
  }
};

//==========================================================================================
void reversepulse() {
  pulse = pulse xor 1;            // pulse inverteren

}
