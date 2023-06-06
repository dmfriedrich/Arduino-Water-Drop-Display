# Arduino-Water-Drop-Display
Arduino code used to make concentric circles of LEDs resemble a water dropping into a pond.
Author: Derek Friedrich

***Summary***
This code is for use in the Arduino IDE, using the FastLED library imported through the IDE, as a way to make a concentric circle of LEDs appear to ripple out like a body of water being struck by a water droplet. My implementation needed a golden color and is set to a delay of 3 ms per hue change. Changing the hue value is based on the HSV color system, so changing the color should use the appropriate chart. It is coded to my expandable but the reliance on delay as a metric of slowing it down makes it ill-suited for purposes that utilize another element on the same board. The code works on an outside in system, assuming the first LED is on the outside ring and moving to the center.

***Adapting the code for different colors and sizes***
Setting Checkpoints - This is the most important change that will most likely have to be made depending on what LEDs are being used. Starting with the outmost ring, the checkpoints must be set to 1 over the amount of LEds in that ring, remembering that the first LED is 0. In my case the first LED is 0 and the last is 31, so the second checkpoint is 32. The final ring, in my case a single LED, requires an extra end checkpoint to be used so the array would be 1 larger than the amount of rings you have. Without correctly defined ring boundaries the pulse will look like a garbled mess.

Color - Adjust the hue variable near the top in accordance with HSV chart.

Number of Rings - Currently it is set for 6 rings. The easiest way to set this is to have the same size hues[] and rings[] array. This way you need only add or remove extra falses in the rings array. If this is not feasible, due to too many rings, you would have to swap between true and false the appropriate amount of times for how many hues you have, which would get messy and require much more understanding of whats happening than I assume anyone searching for a solution wants.

Upper/Lower Limits - Currently the limits are set to 20 and 200, although they could go from 1 to 254, its advisable to choose a number divisible by number of rings. In my case a range of 180 can be spread to 6 rings very easily.

Changing hues[] - The easiest implementation is to have as many hues as you have rings, evenly spread between upper and lower limit. If you want a shorter pulse distance or an uneven pulse you can mess with the spacing of the hues or have more rings start in the rising position (rings[] true position). I didn't need that for my project so any of that I have no advice for.

***Troubleshooting***
Did you import the FastLED library using the Arduino IDE?

Did you correctly add your checkpoints with an extra for the final ring?

Did you add the same amount of hues in the array as you have booleans in the rings array?

Are your LED rings wired from outside in?
