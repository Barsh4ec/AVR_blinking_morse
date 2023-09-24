#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LED_R PD6
#define LED_G PD5
#define LED_B PD4

#define SET_PIN(port, pin) port &= ~(1<<(pin))  // Включити світодіод (common annode), для common cathode замість "&= ~" використати "|="
#define CLEAR_PIN(port, pin) port |= (1<<(pin)) // Виключити світодіод (common annode), для common cathode замість "|=" використати "&= ~"

static char* master[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

char* smorse(char *str) {
    int i;
    char *ele;
    int end = strlen(str);
    char *output = "";
    int totalSize = 0;


    for (i = 0; i < end; i++) {
        ele = master[(*str) - 97];
        totalSize += sizeof(ele) * sizeof(char);
        str++;
    }
    
    output = malloc(totalSize);
    str -= end;
    output[0] = '\0';

    for (i = 0; i < end; i++) {
        ele = master[(*str) - 97];
        strcat(output, ele);
        str++;
    }
    
    return output;
}   

void blink_short(void)
{
    SET_PIN(PORTD, LED_R);
    _delay_ms(200);
    CLEAR_PIN(PORTD, LED_R);
    _delay_ms(200);
    
}

void blink_long(void)
{
    SET_PIN(PORTD, LED_B);
    _delay_ms(400);
    CLEAR_PIN(PORTD, LED_B);
    _delay_ms(200);
}

int main(void)
{
    DDRD |= (1 << LED_R) | (1 << LED_G) | (1 << LED_B); 
    PORTD |= (1 << LED_R) | (1 << LED_G) | (1 << LED_B); 

    char *word = smorse("hello");
    size_t length = strlen(word);

    while (1) 
    {
        for (size_t i = 0; i < length; i++)
        {
            if (word[i] == '.'){
                blink_short();
            }
            if (word[i] == '-'){
                blink_long();
            }
        }
        _delay_ms(1000);
    }
    return 0;
}