#include <avr/io.h>

// Function declaration (prototype)
uint16_t calculate(uint8_t,uint8_t);

int main(void)
{
    uint8_t a = 156;
    uint8_t b = 14;
    uint16_t c;

    // Function call
    c = calculate(a, b);

    while (1)
    {
    }
    return 0;
}

// Function definition (body)
...      calculate(uint8_t x, uint8_t y)
{
    uint16_t result;    // result = x^2 + 2xy + y^2

    result = x*x;
    result = result + 2*x*y;
    result = result + y*y;
    
    return result;
}
