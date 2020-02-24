/* -- Arduino Bluetooth Car - Luca

Itens utilillizados:
- Chassi RC Car Arduino. (Motores, rodas e suporte para pilhas incluso).
- Módulo HC-06 Bluetooth.
- Módulo Ponte H LN298N.
- Protoboard.
- Jumpers.
- Pilha 9V.
- 8 pilhas 1,5V.

App utilizado como controle no celular:
- ARDUINO CAR (ONE DAY OF CODE) - GOOGLE PLAY.

*/

#include <SoftwareSerial.h>

 SoftwareSerial mySerial(10, 11); // utilizando 10 e 11 como Serial 10-RX, 11-TX

 void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(7, OUTPUT); //Motor A +
  pinMode(6, OUTPUT); //Motor A +
  pinMode(5, OUTPUT); //Motor B +
  pinMode(4, OUTPUT); //Motor B -
  pinMode(9, OUTPUT); //Motor A Velocidade
  pinMode(3, OUTPUT); //Motor B Velocidade
 }

void loop() 
 if(mySerial.available()) {  
  
  int x; // x define o sentido anterior do carrinho (para virar para direita ou esquerda dependendo do sentido); frente x = 20; ré x = 30;
  char data= mySerial.read(); // leitura das informções do bluetooth;
  
  switch(data) {
    case 'F': //Frente
      analogWrite(9,255);
      analogWrite(3,255);
      digitalWrite (7, LOW);
      digitalWrite (6, HIGH);
      digitalWrite (5, LOW);
      digitalWrite (4, HIGH);
      x = 20; // x é definido como 20 para que o carrinho possa virar para direita e esquerda e continuar no sentido frente;
      break;
      
    case 'S': //Parar
      analogWrite(9,255);
      analogWrite(3,255);
      digitalWrite (7, LOW);
      digitalWrite (6, LOW);
      digitalWrite (5, LOW);
      digitalWrite (4, LOW);
      break;
      
    case 'E': //Esquerda
      switch (x) {
        case 20: // quando X = 20, para permanecer andando para frente, o pino 6 é ativado;
          analogWrite (3,125);
          analogWrite (9,125);
          digitalWrite (7, LOW);
          digitalWrite (6, HIGH);
          digitalWrite (5, LOW);
          digitalWrite (4, LOW);
          x = 20;
          break;
          
        case 30: //quando X = 30, para permanecer andando para trás (ré), o pino 5 é ativado;
          analogWrite (3,125);
          analogWrite (9,125);
          digitalWrite (7, LOW);
          digitalWrite (6, LOW);
          digitalWrite (5, HIGH);
          digitalWrite (4, LOW);
          break;
       }
      break;
      
    case 'D': //Direita
      switch (x){
        case 20: // quando X = 20, para permanecer andando para frente, o pino 4 é ativado;
        analogWrite (3,125);
        analogWrite (9,125);
        digitalWrite (5, LOW);
        digitalWrite (4, HIGH);
        digitalWrite (7, LOW);
        digitalWrite (6, LOW);
        x = 20;
        break;
        
      case 30: //quando X = 30, para permanecer andando para trás (ré), o pino 7 é ativado;
        analogWrite (3,125);
        analogWrite (9,125);
        digitalWrite (5, LOW);
        digitalWrite (4, LOW);
        digitalWrite (7, HIGH);
        digitalWrite (6, LOW);
        x = 30;
        break;
      }
    break;
    
    case 'R': 
      analogWrite(9,125);
      analogWrite(3,125);   
      digitalWrite (7, HIGH);
      digitalWrite (6,LOW);
      digitalWrite (5, HIGH);
      digitalWrite (4, LOW);
      x = 30; // x é definido como 30 para que o carrinho possa virar para direita e esquerda e continuar no sentido ré;
      break;
      
      default : break;
   }
      Serial.println(data); //receber os códigos vindos do bluetooth (data) ver se o x realmente é definido (x);
   }
   delay(50); //Delay anti-interferencia
}
