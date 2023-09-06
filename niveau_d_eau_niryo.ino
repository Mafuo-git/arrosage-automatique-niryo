/*----------------- Guide arrosage automatique - Niryo -----------------*/

#define PIN_CAPTEUR A0      // Broche de l'Arduino à laquelle la broche du signal du capteur de niveau d'eau est reliée
#define LED 9               // Broche de l'Arduino à laquelle la LED est reliée.
#define COMMANDE 10         // Broche envoyant le même signal que la LED sauf que celle-ci est destiné au Ned 2
#define RETOUR 4           // Broche qui va recevoir la confirmation du Ned 2 une fois que la plante aura été arrosée

int value = 0;              // On initialise la variable à 0 avant de commencer
int ret = 0;               // Idem


void setup() {
  pinMode(LED, OUTPUT);     // On définit la LED comme une sortie car c'est l'Arduino qui 
                            // va lui envoyer des informations, pas l'inverse.

  pinMode(COMMANDE, OUTPUT); // Idem (ici la broche COMMANDE enverra les mêmes informations que dans la LED mais pour le Ned 2)
                            
  pinMode(RETOUR, INPUT);   // Ici, c'est le contraire, l'Arduino va recevoir des informations du Ned 2
                            
  Serial.begin(9600);       // Ici on définit simplement le paramétrage du moniteur série
}                           // (Attention : bien vérifier dans le moniteur série que le "baudrate" est mis sur 9600)

void loop() {
  
  value = analogRead(PIN_CAPTEUR);  // Ici on demande à l'Arduino de lire le niveau d'eau et de stocker la valeur dans la variable
  Serial.print("Valeur du capteur: "); // On fait un retour dans le moniteur série afin de connaitre la valeur du niveau
  Serial.println(value);               // d'eau dans le pot

  // Ici on va s'occuper de l'envoi conditionnel d'informations au Ned 2 en fonction du niveau d'eau mesuré

  ret = digitalRead(RETOUR);
  Serial.print("Valeur du retour: ");
  Serial.println(ret);

  if(value <= 310){                 // Si la valeur du niveau d'eau est inférieure à 310 (valeur arbitraire) alors on envoie
    digitalWrite(LED, HIGH);        // l'info à la LED et au Ned 2 pour arroser la plante (et on l'affiche dans le moniteur série)
    digitalWrite(COMMANDE, HIGH);
    Serial.println("J'ai soif\n");  // (le "\n" permet de faire un retour à la ligne dans le moniteur série

    
    if(ret == 1){                          // Si le robot à fini d'arroser la plante alors on dit à l'Arduino que la plante
      Serial.println("J'ai été arrosé !");    // a suffisament d'eau et on retourne dans notre boucle du début.
      value = 320;                           // De plus, on réinitialise les variables à des valeurs correspondant à notre
      ret = 0;                               // situation initiale mais en prenant en compte que la plante a été arrosée
      delay(3000);              // Ici on met un petit peu de délai pour que la terre du pot s'imprègne entièrement de l'eau versée
      }
    
    }
    
  else{
    digitalWrite(LED, LOW);          // Sinon, si le niveau d'eau est correct, on n'envoie pas d'ordre au Ned2 et on éteint la LED
    digitalWrite(COMMANDE, LOW);
    Serial.println("J'ai bien bu !\n");
  }
  

  delay(500);                      // On impose un délai d'une demi-seconde avant chaque nouvelle prise de mesure du niveau d'eau
}

/*------------ Réalisé par Mathéo Merlin ------------*/
