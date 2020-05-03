// The button
// Handles a single button to act as a keyboard input

#include <Arduino.h>
#include <DigiKeyboard.h>

#define PIN_BUTTON 0
#define PIN_LED 1

// Uncomment to send a single keystroke
#define KEYSTROKE KEY_F // to pay respects

// Uncomment to to send a keystroke + modifier
// #define KEYSTROKE KEY_L
// #define KEYSTROKE_MOD MOD_GUI_LEFT

// Uncomment to send a string
// #define KEY_MESSAGE "github.com/Chris-Johnston/the-button"

#define DEBOUNCE_MS 50

unsigned long lastDebounceTime = 0;
int buttonState;
int lastButtonState = LOW;

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);

    // blink on startup
    for (int i = 0; i < 5; i++)
    {
      digitalWrite(PIN_LED, HIGH);
      delay(50);
      digitalWrite(PIN_LED, LOW);
      delay(50);
    }
}

void loop()
{
    int state = digitalRead(PIN_BUTTON);

    if (state)
    {
      digitalWrite(PIN_LED, HIGH);
    }
    else
    {
     analogWrite(PIN_LED, abs(255 * sin((millis() - lastDebounceTime) / 1000.0))); 
    }
    
    if (state != buttonState && (millis() - lastDebounceTime) > DEBOUNCE_MS)
    {
        buttonState = state;
        lastDebounceTime = millis();

        if (buttonState == HIGH)
        {
            digitalWrite(PIN_LED, HIGH);

            #ifdef KEYSTROKE
                #ifdef KEYSTROKE_MOD
                    DigiKeyboard.sendKeyPress(KEYSTROKE, KEYSTROKE_MOD);
                #else
                    DigiKeyboard.sendKeyPress(KEYSTROKE);
                #endif
            #endif

            #ifdef KEY_MESSAGE
            DigiKeyboard.write(KEY_MESSAGE);
            #endif
        }
        else
        {
            #ifdef KEYSTROKE
            // release
            DigiKeyboard.sendKeyPress(0);
            #endif
        }
    }
    DigiKeyboard.update();
}
