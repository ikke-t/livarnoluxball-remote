/*
 * LivarnoLuxBall.ino commands led ball sold in LIDL 2017.
 */
// prepare with Infra-Red libraries
#include <IRLibSendBase.h>
#include <IRLib_P01_NEC.h>
#include <IRLibCombo.h>
IRsend mySender;

// IR remote command codes
const unsigned long CMD_BRIGHTER = 0xF700FFul;
const unsigned long CMD_DIMMER   = 0xF7807Ful;
const unsigned long CMD_OFF      = 0xF740BFul;
const unsigned long CMD_ON       = 0xF7C03Ful;
const unsigned long CMD_FLASH    = 0xF7D02Ful;
const unsigned long CMD_STROBE   = 0xF7F00Ful;
const unsigned long CMD_FADE     = 0xF7C837ul;
const unsigned long CMD_SMOOTH   = 0xF7E817ul;
const unsigned long CMD_RED      = 0xF720DFul;
const unsigned long CMD_RED1     = 0xF710EFul;
const unsigned long CMD_RED2     = 0xF730CFul;
const unsigned long CMD_RED3     = 0xF708F7ul;
const unsigned long CMD_RED4     = 0xF728D7ul;
const unsigned long CMD_GREEN    = 0xF7A05Ful;
const unsigned long CMD_GREEN1   = 0xF7906Ful;
const unsigned long CMD_GREEN2   = 0xF7B04Ful;
const unsigned long CMD_GREEN3   = 0xF78877ul;
const unsigned long CMD_GREEN4   = 0xF7A857ul;
const unsigned long CMD_BLUE1    = 0xF7609Ful;
const unsigned long CMD_BLUE     = 0xF750AFul;
const unsigned long CMD_BLUE2    = 0xF7708Ful;
const unsigned long CMD_BLUE3    = 0xF748B7ul;
const unsigned long CMD_BLUE4    = 0xF76897ul;

/* The command is 0xF7 + below code + code inverted
brighter  = B00000; dimmer    = B10000; off       = B01000; on        = B11000;
flash     = B11010; strobe    = B11110; fade      = B11001; smooth    = B11101;
red       = B00100; red1      = B00010; red2      = B00110; red3      = B00001;
red4      = B00101; green     = B10100; green1    = B10010; green2    = B10110;
green3    = B10001; green4    = B10101; blue      = B01100; blue1     = B01010;
blue2     = B01110; blue3     = B01001; blue4     = B01101;
*/

// Prepare radio with NRF24L01+
#define MY_RADIO_NRF24
#define MY_BAUD_RATE 9600
//#define MY_NODE_ID AUTO
#define MY_NODE_ID 7
#include <SPI.h>
#include <MySensors.h>
#define IR_PIN 3
#define IR_ID 1

// Initialize motion message
MyMessage msg_ir(IR_ID, V_IR_SEND);

// Status LED
#define LED_PIN 6

void setup() {
  Serial.begin(MY_BAUD_RATE);
  pinMode(IR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Serial.println(F("Init done"));
  for (int i=0; i<3; i++) {
    digitalWrite(LED_PIN, HIGH);
    wait(100);
    digitalWrite(LED_PIN, LOW);
    wait(100);
  }
}

void presentation()  {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Topi's controller", "1.0");
  // Register all sensors to gw (they will be created as child devices)
  present(IR_ID, S_IR);
}

void loop()
{
}

void send_ircode(uint32_t ircode)
{
  char code_in_hex[9];
  for (int i=0; i<3;i++) {
      digitalWrite(LED_PIN, HIGH);
      mySender.send(NEC, ircode);
      wait(100);
      digitalWrite(LED_PIN, LOW);
      wait(100);
  }
  sprintf(code_in_hex, "%lX\n", ircode);
  Serial.print(F("Sent signal: "));
  Serial.println(code_in_hex);
}

void ack_ir_to_controller(uint32_t ircode)
{
	send(msg_ir.set(ircode));
}

void receive(const MyMessage &message)
{
  uint32_t ircode;
  char code_in_hex[9];

  Serial.print( "Received something of type: " );
  Serial.println( message.type );

	if (message.type == V_IR_SEND) {
		Serial.println( "V_IR_SEND command received..." );

		ircode = atol( message.data );
    //ircode = message.data;
    switch (ircode) {
      case CMD_BRIGHTER:
      case CMD_DIMMER:
      case CMD_OFF:
      case CMD_ON:
      case CMD_FLASH:
      case CMD_STROBE:
      case CMD_FADE:
      case CMD_SMOOTH:
      case CMD_RED:
      case CMD_RED1:
      case CMD_RED2:
      case CMD_RED3:
      case CMD_RED4:
      case CMD_GREEN:
      case CMD_GREEN1:
      case CMD_GREEN2:
      case CMD_GREEN3:
      case CMD_GREEN4:
      case CMD_BLUE1:
      case CMD_BLUE:
      case CMD_BLUE2:
      case CMD_BLUE3:
      case CMD_BLUE4:
      {
        sprintf(code_in_hex, "%lX\n", ircode);
        Serial.print( "V_IR_SEND code received: ");
        Serial.println( code_in_hex );
        ack_ir_to_controller(ircode);
        send_ircode(ircode);
        break;
      }
      default:
      {
        Serial.print( "V_IR_SEND data invalid: " );
        Serial.print( message.data );
        Serial.print( ", ircode: " );
        Serial.println( ircode );
			  return;
		   }
    }
  }
}
