void Motor4() {
  pulse4 = 0;
  if (Mot4On == 1)
  {
    if (pulse == 1)
    {
      if (Mot4WantedLength != Mot4ActualLength) {

        if (Mot4PulseCounter >= (StepSpeed / mot4PulseProcent) )
        {
          pulse4 = 1;
          Mot4PulseCounter = 0;

          if (Mot4Direction == 1)
          {
            Mot4ActualLength = Mot4ActualLength + 1;
          }
          else
          {
            Mot4ActualLength = Mot4ActualLength - 1;
          };
        };
      };

      Mot4PulseCounter = Mot4PulseCounter + 1;

      digitalWrite(oDir4, Mot4Direction);
      digitalWrite(oStep4, pulse4);
    };
  };
};
