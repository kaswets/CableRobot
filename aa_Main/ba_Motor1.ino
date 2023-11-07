void Motor1() {
  pulse1 = 0;
  if (Mot1On == 1)
  {
    if (pulse == 1)
    {
      if (Mot1WantedLength != Mot1ActualLength) {

        if (Mot1PulseCounter >= (StepSpeed / mot1PulseProcent) )
        {
          pulse1 = 1;
          Mot1PulseCounter = 0;

          if (Mot1Direction == 1)
          {
            Mot1ActualLength = Mot1ActualLength + 1;
          }
          else
          {
            Mot1ActualLength = Mot1ActualLength - 1;
          };
        };
      };

      Mot1PulseCounter = Mot1PulseCounter + 1;

      digitalWrite(oDir1, Mot1Direction);
      digitalWrite(oStep1, pulse1);
    };
  };
};
