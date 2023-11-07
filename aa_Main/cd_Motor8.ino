void Motor8() {
  pulse8 = 0;
  if (Mot8On == 1)
  {
    if (pulse == 1)
    {
      if (Mot8WantedLength != Mot8ActualLength) {

        if (Mot8PulseCounter >= (StepSpeed / mot8PulseProcent) )
        {
          pulse8 = 1;
          Mot8PulseCounter = 0;

          if (Mot8Direction == 1)
          {
            Mot8ActualLength = Mot8ActualLength + 1;
          }
          else
          {
            Mot8ActualLength = Mot8ActualLength - 1;
          };
        };
      };

      Mot8PulseCounter = Mot8PulseCounter + 1;

      digitalWrite(oDir8, Mot8Direction);
      digitalWrite(oStep8, pulse8);
    };
  };
};
