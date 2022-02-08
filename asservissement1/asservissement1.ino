#include<SimpleTimer.h>

//moteur droit
const uint8_t mot_avd = 4;
const uint8_t mot_ard = 12;
const uint8_t mot_vitd = 10;

//moteur gauche
const uint8_t mot_avg = 7;
const uint8_t mot_arg = 8;
const uint8_t mot_vitg = 9;

//codeur
const uint8_t canalGauche   = 2;  
const uint8_t canalDroite   = 3; 

uint32_t comptD = 0;
uint32_t comptG = 0;
uint32_t precComptG = 0;
uint32_t precComptD = 0;
uint32_t erreurG = 0;
uint32_t erreurD = 0;
uint32_t integralErreurG = 0;
uint32_t integralErreurD = 0;
uint32_t nouvelleCommandeG = 0;
uint32_t nouvelleCommandeD = 0;
float vitesseReelleG = 0.0;
float vitesseReelleD = 0.0;
float vitSD=80;
float vitSG=80;


SimpleTimer timer;

/* These constants are to be set and confirmed experimmentally */
const float kpg=2.13;
const float kpd=1.18;
const float kig=0.01;
const float kid=0.009;

void ReagirGauche();
void ReagirDroite();
void asservissement();

void setup() {
  Serial.begin(9600); 
  
  comptD=0;
  comptG=0;
  vitSD=0;
  vitSG=0;

  timer.setInterval(20, asservissement);
  
  pinMode(canalGauche, INPUT);  
  pinMode(canalDroite, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), ReagirGauche, RISING);
  attachInterrupt(digitalPinToInterrupt(3), ReagirDroite, RISING);
}

void loop() {
  while (comptD<290)
  {
    timer.run();
    analogWrite(mot_vitd, vitSD);
    digitalWrite(mot_avd, HIGH);
    digitalWrite(mot_ard, LOW);

    analogWrite(mot_vitg, vitSG);
    digitalWrite(mot_avg, HIGH);
    digitalWrite(mot_arg, LOW);

    Serial.println(comptD);
  }
  
    digitalWrite(mot_avd, LOW);
    digitalWrite(mot_ard, LOW);
    digitalWrite(mot_avg, LOW);
    digitalWrite(mot_arg, LOW);
}

void ReagirGauche()
{  
  if(digitalRead(canalGauche) == HIGH)
  {
    comptG++;        
  }     
}

void ReagirDroite()
{     
  if(digitalRead(canalDroite) == HIGH)
  {
    comptD ++;
  }
}

void asservissement()
{
  vitesseReelleG = (comptG - precComptG)/0.02;
  vitesseReelleD = (comptD - precComptD)/0.02;
  precComptG = comptG;
  precComptD = comptD;
  erreurG = 2500 - vitesseReelleG;        /* the target here is 2500 ticks per second for the left motor */
  erreurD = 2500 - vitesseReelleD;        /* the target here is 2500 ticks per second for the right motor */
  integralErreurG += erreurG;
  integralErreurD += erreurD;
  nouvelleCommandeG = kpg*erreurG + kig*integralErreurG;
  nouvelleCommandeD = kpd*erreurD + kid*integralErreurD;

  if (nouvelleCommandeG > 0 && nouvelleCommandeG <= 255)
  {
    vitSG = nouvelleCommandeG;
  }
  else if (nouvelleCommandeG < 0)
  {
    vitSG = 0;
  } else if (nouvelleCommandeG > 255)
  {
    vitSG = 255;
  }
  
  if (nouvelleCommandeD > 0 && nouvelleCommandeD <= 255)
  {
    vitSD = nouvelleCommandeD;
  }
  else if (nouvelleCommandeD < 0)
  {
    vitSD = 0;
  } else if (nouvelleCommandeD > 255)
  {
    vitSD = 255;
  }
  
}
