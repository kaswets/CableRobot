long Mot1(int X, int Y, int Z) {
  // z,y,z uit rekenen van uit main x,y,z
  // x,y,z van hoek 1
  long result;

  float XCorner1 = -(LengthFrame / 2);
  float yCorner1 = -(WidhtFrame / 2);
  float zCorner1 = (HighFrame / 2);

  float Mot1LengthX = XCorner1 - X ;
  float Mot1lengthY = yCorner1 - Y ;
  float Mot1lengthZ = zCorner1 - Z ;

  float DB = Pythagoras(Mot1lengthY, Mot1LengthX, Mot1lengthZ );

  float BP = DB - (DiaKatrol / 2);
  float MP = zCorner1 - Z;

  float BM = Pythagoras(MP, BP, 0 );

  float BK = Pythagoras(BM , (DiaKatrol / 2), 0);

  float hoekKLM = phi - asin(BK / BM) - asin(BP / BM);

  float KL = (DiaKatrol / 2) * hoekKLM;

  float Mot1Length = BK + KL;

  Serial.print("Lengt Motor 1 :");
  Serial.print(Mot1Length);
  Serial.print("mm, total Steps :");
  Serial.println(Mot1Length * StepUnit);

  result = ((Mot1Length * StepUnit) + 0.5);
  return result;
};
