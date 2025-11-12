#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ezButton.h>
#include <pt.h>


static struct pt pt1, pt2;


const int BUTTON1_PIN = 6; // the number of the pushbutton pin
const int BUTTON2_PIN = 9;
const int LED1_PIN = 5; // the number of the LED pin
const int LED2_PIN = 12;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

ezButton button1(BUTTON1_PIN);  // create ezButton object that attach to pin 7;
ezButton button2(BUTTON2_PIN);  // create ezButton object that attach to pin 7;
// variables will change:
int led1_state = LOW;   // the current state of LED
int led2_state = LOW;   // the current state of LED


/*Simple display stopwatch program with stop, start, reset and lap buttons.*/

//including  liblary for disp

//setting up display INPUT pins

//setting hours, minutes, secound  and miliseconds to 0
int h1=0;     
int m1=0;     
int s1=0;
int h2=0;     
int m2=0;     
int s2=0;   

bool is_led_1_on = false;
bool is_led_2_on = false;


void stopwatch(){
  display.clearDisplay();    
  display.setCursor(34, 0);   //setting start point on display 
  display.print(h1);         //display hours
  display.print(":");      
  display.print(m1);         //display minutes
  display.print(":"); 
  display.print(s1);         //display seconds
  display.display();
  display.setCursor(34, 17);   //setting start point on display 
  display.print(h2);         //display hours
  display.print(":");      
  display.print(m2);         //display minutes
  display.print(":"); 
  display.print(s2);         //display seconds
  display.display();
  if (is_led_1_on){
    s1++;            
    
    if(s1 == 60)     //if state for counting up minutes
    { 
    s1 = 0; 
    m1++; 
    }

    if(m1 == 60)      //if state for counting up hours
    {  
    m1 = 00; 
    h1++;  
    }
  }
  else if (!is_led_1_on) {
    h1 = 0;     
    m1 = 0;     
    s1 = 0; 
  }
  if (is_led_2_on){
    s2++;            
    
    if(s2 == 60)     //if state for counting up minutes
    { 
    s2 = 0; 
    m2++; 
    }

    if(m2 == 60)      //if state for counting up hours
    {  
    m2 = 00; 
    h2++;  
    }
  }
  else if (!is_led_2_on) {
    h2 = 0;     
    m2 = 0;     
    s2 = 0; 
  }
}

static int protothread1(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) {
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis();
    stopwatch();
    
  }
  PT_END(pt);
}

void setup() {
  Serial.begin(9600);         // initialize serial

  Serial.println("OLED intialized");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  pinMode(LED1_PIN, OUTPUT);   // set arduino pin to output mode
  pinMode(LED2_PIN, OUTPUT);
  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  button1.loop(); // MUST call the loop() function first
  button2.loop();
  if(button1.isPressed()) {
    Serial.println("The button is pressed");

    // toggle state of LED
    led1_state = !led1_state;
    is_led_1_on = !is_led_1_on;

    // control LED arccoding to the toggleed sate
    digitalWrite(LED1_PIN, led1_state); 
  }

  if(button2.isPressed()) {
    Serial.println("The button is pressed");

    // toggle state of LED
    led2_state = !led2_state;
    is_led_2_on = !is_led_2_on;

    // control LED arccoding to the toggleed sate
    digitalWrite(LED2_PIN, led2_state); 
  }
  protothread1(&pt1, 1000);
}
