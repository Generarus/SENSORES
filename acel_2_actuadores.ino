
#include <EspMQTTClient.h>
#include <ESP32Servo.h>

EspMQTTClient client(
  "P_Capstone", // nombre de la red
  "PCapstone1", // contraseña
  "192.168.0.102",  // dirección del broker
  "",   // omitir
  "",   // omitir
  "nodo_MPU6050" // nombre del cliente
);

Servo myservo;
int servoPin = 12;
int edo_act;

void onConnectionEstablished() {

  client.subscribe("capstone/actuador_agua", [] (const String &payload)  {
    Serial.println(payload);
    if((payload.equals("true"))&&(edo_act==0))
    {
      Serial.println("entra true");
      edo_act=1;
      myservo.write(0);
    }
    if((payload.equals("false"))&&(edo_act==1))
    {
      Serial.println("entra false");
      edo_act=0;
      myservo.write(180);
    }
  });
}

void onMessageReceived(const String& topic, const String& message) {
  Serial.println(topic + ": " + message);
  
}

void setup()
{

   ESP32PWM::allocateTimer(0);
   ESP32PWM::allocateTimer(1);
   ESP32PWM::allocateTimer(2);
   ESP32PWM::allocateTimer(3);
   myservo.setPeriodHertz(50);    // standard 50 hz servo
   myservo.attach(servoPin, 1000, 2000); 
   myservo.write(0);
   delay(1000);
   myservo.write(180);
   delay(1000);
   myservo.write(0);
   edo_act=1;
   Serial.begin(115200);
}
void loop()
{
   client.loop();
}
   
   
