void Motor5() {
  pulse5 = 0;
  if (Mot5On == 1)
  {
    if (pulse == 1)
    {
      if (Mot5WantedLength != Mot5ActualLength) {

        if (Mot5PulseCounter >= (StepSpeed / mot5PulseProcent) )
        {
          pulse5 = 1;
          Mot5PulseCounter = 0;

          if (Mot5Direction == 1)
          {
            Mot5ActualLength = Mot5ActualLength + 1;
          }
          else
          {
            Mot5ActualLength = Mot5ActualLength - 1;
          };
        };
      };

      Mot5PulseCounter = Mot5PulseCounter + 1;

      digitalWrite(oDir5, Mot5Direction);
      digitalWrite(oStep5, pulse5);
    };
  };
};
