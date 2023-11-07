void Motor2() {
  pulse2 = 0;
  if (Mot2On == 1)
  {
    if (pulse == 1)
    {
      if (Mot2WantedLength != Mot2ActualLength) {

        if (Mot2PulseCounter >= (StepSpeed / mot2PulseProcent) )
        {
          pulse2 = 1;
          Mot2PulseCounter = 0;

          if (Mot2Direction == 1)
          {
            Mot2ActualLength = Mot2ActualLength + 1;
          }
          else
          {
            Mot2ActualLength = Mot2ActualLength - 1;
          };
        };
      };

      Mot2PulseCounter = Mot2PulseCounter + 1;

      digitalWrite(oDir2, Mot2Direction);
      digitalWrite(oStep2, pulse2);
    };
  };
};
