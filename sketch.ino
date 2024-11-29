#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "RoboEyes.h"
roboEyes roboEyes;

unsigned long eventTimer = 0;
int currentEvent = 0;
bool eventWasPlayed = false;

enum CustomEmotion {
  CUSTOM_NEUTRAL,
  CUSTOM_HAPPY,
  CUSTOM_TIRED,
  CUSTOM_CONFUSED,
  CUSTOM_ANGRY
};

CustomEmotion currentEmotion = CUSTOM_NEUTRAL;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  roboEyes.setAutoblinker(ON, 3, 2);
  roboEyes.setIdleMode(ON, 2, 2);
  roboEyes.setWidth(36, 36);
  roboEyes.setHeight(36, 36);
  roboEyes.setBorderradius(10, 10);
  roboEyes.setPosition(DEFAULT);
  roboEyes.setCuriosity(ON);

  roboEyes.close();  // Start with closed eyes
  eventTimer = millis();
}

void loop() {
  roboEyes.update();
  
  unsigned long currentTime = millis();
  
  // Event sequence
  switch (currentEvent) {
    case 0:
      if (currentTime >= eventTimer + 2000 && !eventWasPlayed) {
        roboEyes.open();
        nextEvent();
      }
      break;
    case 1:
      if (currentTime >= eventTimer + 2000 && !eventWasPlayed) {
        performRandomAction();
        nextEvent();
      }
      break;
    case 2:
      if (currentTime >= eventTimer + 2000 && !eventWasPlayed) {
        roboEyes.setMood(DEFAULT);
        nextEvent();
      }
      break;
  }
}

void nextEvent() {
  eventWasPlayed = true;
  currentEvent = (currentEvent + 1) % 3;
  eventTimer = millis();
  eventWasPlayed = false;
}

void performRandomAction() {
  int action = random(100);
  
  if (action < 15) {
    roboEyes.blink();
  } else if (action < 30) {
    roboEyes.setMood(DEFAULT);
    roboEyes.anim_confused();
  } else if (action < 45) {
    roboEyes.setMood(HAPPY);
    roboEyes.anim_laugh();
  } else if (action < 60) {
    changeEmotion();
  } else if (action < 75) {
    moveCuriously();
  } else if (action < 90) {
    roboEyes.setMood(TIRED);
  } else {
    roboEyes.setMood(ANGRY);
    roboEyes.setPosition(S);
  }
}

void changeEmotion() {
  currentEmotion = static_cast<CustomEmotion>(random(7));
  
  switch (currentEmotion) {
    case CUSTOM_NEUTRAL:
      roboEyes.setMood(DEFAULT);
      break;
    case CUSTOM_HAPPY:
      roboEyes.setMood(HAPPY);
      break;
    case CUSTOM_TIRED:
      roboEyes.setMood(TIRED);
      break;
    case CUSTOM_CONFUSED:
      roboEyes.setMood(DEFAULT);
      roboEyes.anim_confused();
      break;
    case CUSTOM_ANGRY:
      roboEyes.setMood(ANGRY);
      roboEyes.setPosition(S);
      break;
  }
}

void moveCuriously() {
  int direction = random(8);
  switch (direction) {
    case 0: roboEyes.setPosition(N); break;
    case 1: roboEyes.setPosition(NE); break;
    case 2: roboEyes.setPosition(E); break;
    case 3: roboEyes.setPosition(SE); break;
    case 4: roboEyes.setPosition(S); break;
    case 5: roboEyes.setPosition(SW); break;
    case 6: roboEyes.setPosition(W); break;
    case 7: roboEyes.setPosition(NW); break;
  }
}