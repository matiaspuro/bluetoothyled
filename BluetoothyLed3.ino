/*
 *  Author: Jose Antonio Luceño Castilla
 *  Date  : Septempber 2013
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <SoftwareSerial.h>
#include "IRremote3.h"
//VCC va conectado a 5V
#define RxD 11
#define TxD 10
#define RST 5 // Encendido del Modulo
#define KEY 4

#define LED 13

//PARA EL ONOFF
#define GND2 8
#define ONOFF 6
//PARA EL ONOFF

SoftwareSerial BTSerial(TxD, RxD);
byte pinEstado = 0;
IRsend irsend;
String lectura = "";

unsigned int S_pup[68]={4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};


void setup()
{
  
  pinMode(LED, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(KEY, OUTPUT);

  //PARA EL ONOFF  
  pinMode(GND2, OUTPUT);
  pinMode(ONOFF, OUTPUT);
  digitalWrite(GND2, LOW);
  digitalWrite(ONOFF, HIGH);
  //PARA EL ONOFF
  
  // Estado inicial
  digitalWrite(LED, LOW);
  digitalWrite(RST, LOW);
  // Modo Comunicacion
  digitalWrite(KEY, LOW); 
   
  // Encendemos el modulo.
  digitalWrite(RST, HIGH);
  
  // Configuracion del puerto serie por software
  // para comunicar con el modulo HC-05
  BTSerial.begin(9600);
  BTSerial.flush();
  delay(500);
  
  // Configuramos el puerto serie de Arduino para Debug
  Serial.begin(115200);
  Serial.println("Readyyyy BT y led 2");


}

void loop()
{
/*
    if (Serial.available())
    {
      char c = Serial.read();
      BTSerial.write(c);
      Serial.println(c);
    }
*/
  
  // Esperamos a recibir datos.
  
  while(BTSerial.available() > 0)
  {
    char inChar = BTSerial.read();
    //BTSerial.flush();
    
    //Serial.println(inChar);
    lectura += inChar;
    
    if (inChar == ';')
    {
      lectura += '\0';
      Serial.println("AA");
//      Serial.println("lectura: " + lectura);
     // Serial.println("A");
      IrSendCode(lectura);
      //IrSendCode("68-38-4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650;");
      
   //   Serial.println("B");
      lectura = "";
      inChar == '\0';
      //BTSerial.flush();
    }
    
    if(inChar == 'L')
    {
      Serial.println("lectura: L");
      Serial.println("sizeof (S_pup): ");
      Serial.println(sizeof (S_pup));
      //irsend.sendRaw(S_pup, sizeof(S_pup), 38);
      irsend.sendRaw(S_pup, 68, 38);
    }
  /*
  if (BTSerial.available())
  {   
    // La funcion read() devuelve un caracter 
    
    char command = BTSerial.read();
    BTSerial.flush();
    lectura += command;
   // Serial.println(command);
    
    // En caso de que el caracter recibido sea "L" cambiamos
    // El estado del LED
    if (command == 'L')
    {
      Serial.println("Toggle LED");
      toggle(ONOFF); 
    }   
    
   Serial.println(lectura);
   // if (command == ';')
   // {
   //   Serial.println(lectura);
   //   lectura = "";
   // }   
  }
*/
  }
}

void toggle(int pinNum) {
  // Establece el pin del LED usando la variable pinEstado:
  digitalWrite(pinNum, pinEstado); 
  // si el pinEstado = 0, lo establece a 1, y vice versa:
  pinEstado = !pinEstado;
}


void IrSendCode(String value)
{
  Serial.println("value= " + value);
   // Serial.println("IrSendCode");
  
    String longitud;
    String frecuencia;
    String valor;
    int i = 0;
    unsigned int codigoIR[500] = {};
    
    //unsigned int codigoIR[longitud];
    
   // Serial.print("value:" + value);
    longitud = value.substring(0, value.indexOf('-'));
    value = value.substring(value.indexOf('-')+1);
    //Serial.println("longitud:" + longitud);
    Serial.println("valuel:" + value);
 
    frecuencia = value.substring(0, value.indexOf('-'));
    value = value.substring(value.indexOf('-')+1);
    Serial.println("frecuencia:" + frecuencia);
  //  Serial.println("valuef:" + value);
    //String valor;
  
    while(value.indexOf(',') != -1)
    {
        valor = value.substring(0, value.indexOf(','));
        value = value.substring(value.indexOf(',')+1);
        codigoIR[i] = valor.toInt();
        i++;
    }
    //toma el ultimo valor
    codigoIR[i] = value.toInt();
  /*
    Serial.print("codigoIR0:");
    Serial.print(codigoIR[0]);
    Serial.print("codigoIR1:");
    Serial.print(codigoIR[1]);
    */
    //valor = value.substring(0, value.indexOf(','));
    //unsigned int codigoIR[] = {4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};
    /**/
    
  
   // Serial.print("longitud:" + longitud);
   // Serial.println("C"); 
   // Serial.println("frecuencia:" + frecuencia);
   // Serial.println("D");
    
  //  irsend.sendRaw(codigoIR,longitud.toInt(),frecuencia.toInt());
  // irsend.sendRaw(codigoIR, sizeof(S_pup), 38);
    irsend.sendRaw(S_pup, longitud.toInt(),38);
  Serial.println("SENDRAW");
  
}
