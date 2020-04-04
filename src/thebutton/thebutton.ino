#include <Arduino.h>
#include <DigiKeyboard.h>

#define PIN_BUTTON 5
#define PIN_LED 0

#define KEYSTROKE KEY_F // to pay respects
#define DEBOUNCE_MS 50

unsigned long lastDebounceTime = 0;
int buttonState;
int lastButtonState = LOW;

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT);
}

void loop()
{
    DigiKeyboard.update();
    int state = digitalRead(PIN_BUTTON);

    if (state != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_MS)
    {
        if (state != buttonState)
        {
            buttonState = state;

            if (buttonState == HIGH)
            {
                DigiKeyboard.sendKeyPress(KEYSTROKE);
            }
            else
            {
                // release
                DigiKeyboard.sendKeyPress(0);
            }
            
        }
    }
}