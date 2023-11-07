long Pythagoras(long X, long Y, long Z) {

  long TmpXkwadraat = X * X;
  long TmpYKwadraat = Y * Y;
  long TmpZKwadraat = Z * Z;
  
  float result;

  result = sqrt(TmpXkwadraat + TmpYKwadraat + TmpZKwadraat);
  return result;

};
