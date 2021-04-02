#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <HID.h>
#include <string.h>
#include <Keyboard.h>

int ChipSelect = 5;

File payload;

void Line(String l);
void Press(String b);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  String file_name="";
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  // Switches are checked, file_name string is contructed
  if (digitalRead(6) == LOW){file_name += "1";} else {file_name += "0";}
  if (digitalRead(7) == LOW){file_name += "1";} else {file_name += "0";}
  if (digitalRead(8) == LOW){file_name += "1";} else {file_name += "0";}
  if (digitalRead(9) == LOW){file_name += "1";} else {file_name += "0";}
  Serial.println("file name is:"+ file_name);

  payload = SD.open(file_name);
  if(payload){
    Serial.print("payload started");
    Keyboard.begin();
    String line = "";
    while(payload.available()){
      char m = payload.read();
      if (m == '\n'){
        Line(line);
        line = "";
      }
      else if(m != 13){
        line += m;
      }
    }
    payload.close();

  }
  else{
    Serial.print("Error");
    Keyboard.end();
  }
  Serial.print("keystroke finish");
}

void loop() {
 // never loop a keystrok injection
}


void Line(String l){
  int space_1 = l.indexOf(" ");
  if (space_1 == -1){
    Press(l);
  }
  else if (l.substring(0,space_1) == "STRING"){
    Keyboard.print(l.substring(space_1 + 1));
  }
  else if (l.substring(0,space_1) == "DELAY"){
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if(l.substring(0,space_1) == "REM"){}
  else{
      String remain = l;
      while(remain.length() > 0){
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1){
          Press(remain);
          remain = "";
        }
        else{
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }

  Keyboard.releaseAll();
}

void Press(String b){
    if(b.length() == 1){
    char c = b[0];
    Keyboard.press(c);
    }
  else if (b.equals("ENTER")){
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL")){
    Keyboard.press(KEY_LEFT_CTRL);
  }
    else if (b.equals("SHIFT")){
    Keyboard.press(KEY_LEFT_SHIFT);
  }
    else if (b.equals("ALT")){
    Keyboard.press(KEY_LEFT_ALT);
  }
    else if (b.equals("GUI")){
    Keyboard.press(KEY_LEFT_GUI);
  }
    else if (b.equals("UP")){
    Keyboard.press(KEY_UP_ARROW);
  }
    else if (b.equals("DOWN")){
    Keyboard.press(KEY_DOWN_ARROW);
  }
    else if (b.equals("LEFT")){
    Keyboard.press(KEY_LEFT_ARROW);
  }
    else if (b.equals("RIGHT")){
    Keyboard.press(KEY_RIGHT_ARROW);
  }
    else if (b.equals("DELETE")){
    Keyboard.press(KEY_DELETE);
  }
    else if (b.equals("PAGEUP")){
    Keyboard.press(KEY_PAGE_UP);
  }
    else if (b.equals("PAGEDOWN")){
    Keyboard.press(KEY_PAGE_DOWN);
  }
    else if (b.equals("HOME")){
    Keyboard.press(KEY_HOME);
  }
    else if (b.equals("ESC")){
    Keyboard.press(KEY_ESC);
  }
    else if (b.equals("INSERT")){
    Keyboard.press(KEY_INSERT);
  }
    else if (b.equals("TAB")){
    Keyboard.press(KEY_TAB);
  }
    else if (b.equals("END")){
    Keyboard.press(KEY_END);
  }
    else if (b.equals("CAPSLOCK")){
    Keyboard.press(KEY_CAPS_LOCK);
  }
    else if (b.equals("F1")){
    Keyboard.press(KEY_F1);
  }
    else if (b.equals("F2")){
    Keyboard.press(KEY_F2);
  }
    else if (b.equals("F3")){
    Keyboard.press(KEY_F3);
  }
    else if (b.equals("F4")){
    Keyboard.press(KEY_F4);
  }
    else if (b.equals("F5")){
    Keyboard.press(KEY_F5);
  }
    else if (b.equals("F6")){
    Keyboard.press(KEY_F6);
  }
    else if (b.equals("F7")){
    Keyboard.press(KEY_F7);
  }
    else if (b.equals("F8")){
    Keyboard.press(KEY_F8);
  }
    else if (b.equals("F9")){
    Keyboard.press(KEY_F9);
  }
    else if (b.equals("F10")){
    Keyboard.press(KEY_F10);
  }
    else if (b.equals("F11")){
    Keyboard.press(KEY_F11);
  }
    else if (b.equals("F12")){
    Keyboard.press(KEY_F12);
  }
}