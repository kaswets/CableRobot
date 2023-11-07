void Motor6() {
  pulse6 = 0;
  if (Mot6On == 1)
  {
    if (pulse == 1)
    {
      if (Mot6WantedLength != Mot6ActualLength) {

        if (Mot6PulseCounter >= (StepSpeed / mot6PulseProcent) )
        {
          pulse6 = 1;
          Mot6PulseCounter = 0;

          if (Mot6Direction == 1)
          {
            Mot6ActualLength = Mot6ActualLength + 1;
          }
          else
          {
            Mot6ActualLength = Mot6ActualLength - 1;
          };
        };
      };

      Mot6PulseCounter = Mot6PulseCounter + 1;

      digitalWrite(oDir6, Mot6Direction);
      digitalWrite(oStep6, pulse6);
    };
  };
};
