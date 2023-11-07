void Motor7() {
  pulse7 = 0;
  if (Mot7On == 1)
  {
    if (pulse == 1)
    {
      if (Mot7WantedLength != Mot7ActualLength) {

        if (Mot7PulseCounter >= (StepSpeed / mot7PulseProcent) )
        {
          pulse7 = 1;
          Mot7PulseCounter = 0;

          if (Mot7Direction == 1)
          {
            Mot7ActualLength = Mot7ActualLength + 1;
          }
          else
          {
            Mot7ActualLength = Mot7ActualLength - 1;
          };
        };
      };

      Mot7PulseCounter = Mot7PulseCounter + 1;

      digitalWrite(oDir7, Mot7Direction);
      digitalWrite(oStep7, pulse7);
    };
  };
};
