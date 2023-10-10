# Homework Assignments OHA 2023

# Control Module to regulate flow of sea water during purification
Building a control module that will regulate the flow of sea water for [Acraea](https://codeberg.org/LibreWater/Acraea-Prototype)
Acraea is an open source small scale solar desalination and water purifier prototype.

This module is necessary to maximise the outflow of potable water with fluctuating input solar power. The challenges we face are:
1. Regulate flow of input sea water as the amount of solar power changes during the day.
    i. Too much sea water input for the energy input: there will be no evaporation, just lukewarm sea water coming back out - and no fresh water.
    ii. Too little sea water input for the energy input will lead to dry spots and a thick salt crust will form all over the evaporation surfaces, reducing performance and ultimately quality.
2. Use low cost electronic components that are widely and easily available. (This is an early list, suggestions are welcome)
    i. Micro-controller [ESP32](https://nl.mouser.com/ProductDetail/Espressif-Systems/ESP32-DevKitC-32E?qs=GedFDFLaBXFpgD0kAZWDrQ%3D%3D&mgh=1&gclid=CjwKCAjwvfmoBhAwEiwAG2tqzKyGMrlCJj6loXDFPuatXf5MClWCINW2yCYJrGlP4VWNI27dlKA7LxoC8AgQAvD_BwE)
    ii. Heating pads [Thermo Silicon self adhesive pads](https://www.conrad.de/de/p/thermo-tech-silikon-heizfolie-selbstklebend-24-v-dc-24-v-ac-200-w-schutzart-ipx7-l-x-b-200-mm-x-100-mm-1594219.html)
    iii. Temprature [sensors](https://www.adafruit.com/product/3290) and [amplifiers](https://www.adafruit.com/product/3328)
    

## List of all components required and their purpose
1. Micro-controller [ESP32](https://nl.mouser.com/ProductDetail/Espressif-Systems/ESP32-DevKitC-32E?qs=GedFDFLaBXFpgD0kAZWDrQ%3D%3D&mgh=1&gclid=CjwKCAjwvfmoBhAwEiwAG2tqzKyGMrlCJj6loXDFPuatXf5MClWCINW2yCYJrGlP4VWNI27dlKA7LxoC8AgQAvD_BwE): The brain of the controller. Shall interface with various sensors and run the algorithm.  Count 1
2. Heating pads [Thermo Silicon self adhesive pads](https://www.conrad.de/de/p/thermo-tech-silikon-heizfolie-selbstklebend-24-v-dc-24-v-ac-200-w-schutzart-ipx7-l-x-b-200-mm-x-100-mm-1594219.html): To add heat to the system for boiling water. Already available alongwith the Acraea prototype. Count 3.
3. Temprature [sensors](https://www.adafruit.com/product/3290) and [amplifiers](https://www.adafruit.com/product/3328). Count 3
4. Power Supply [24V 600 watt](http://www.meanwell.nl/products/Meanwell-HRP-600-24---PSU-enclosed-24V27A__HRP-600-24.aspx): To power the thermo silicon pads. A bench power supply is preferable over this. Count 1.
5. Moisture sensor [Resistive](https://www.kiwi-electronics.com/en/grove-moisture-sensor-1913): Determine the moisture in the wicks during operation. Count 4.
6. Moisture Sensor [Capacitive](https://wiki.seeedstudio.com/Grove-Capacitive_Moisture_Sensor-Corrosion-Resistant/): Same as 5. Has a different working principle which trades accuracy for longevity. Count 4.
7. [Relay](https://www.kiwi-electronics.com/nl/4-kanaals-5v-relais-module-1330?country=NL&utm_term=1330&gclid=CjwKCAjwvfmoBhAwEiwAG2tqzDw9EwRN7TIkzKhoL92BZartT4O03Z28l3axM0jAtKEZsk0Wux2PZxoCo2IQAvD_BwE): For control input. Turn on/ off the water pump. Can also be used to control the thermo pads during development.
8. Logic Level [converter](https://www.kiwi-electronics.com/en/4-channel-i2c-safe-bi-directional-logic-level-converter-bss138-837?search=level): For controlling the relay from ESP32
9. Water Pump: TBD

### Steady State Analysis
(Back of the envelop calculations done at 1 AM)


---
# Week 0

## Exercise 1: Choose your project

My favorite challenge is: [Solar Desalination - Process control with ESP32](https://docs.google.com/document/d/1hjMLiujZHO4uaf1BWmtY5O3Y-EC3x7oOxGmgZHRAPNE/edit)


# Week 1


## Exercise 1: Go through the OSHWA definition
- Read the definitions and principles: [OSHWA definitions](https://www.oshwa.org/definition/)
- Share in the chat which principles you find useful in this document that you think can improve your current practices and why.

## Exercise 2: Learn from open source projects
- Pick at least one of the many influential projects in open source hardware and get familiar with its history. (There is a list bellow, for example you can pick one software project and one hardware project to compare similarities and differences.)

->  I have chosen to read about RepRap and Prusa 3D printers

- Think about the concepts and ideas we provided in this lessons, were you able to spot some of these characteristics in the project you selected? 

-> I find that RepRap has been very well documented with detailed instructions about it's mechanical and software design. This literature is freely available on their wiki page.
-> RepRap has a lot of variants that the community has developed. These variants with various specialities are also available along with the original design!

## Excercise 3 (Optional): Find an open source project related to your domain
Find out if there are open source projects out there related to your project. You can start with the [open hardware observatory](https://en.oho.wiki/index.php?title=Special%3ARunQuery%2FprojectSearch&pfRunQueryFormName=projectSearch&ProjektSearch%5Bcontains_pdf_drawings%5D=yes&ProjektSearch%5Bsubcat%5D=Bending+machine) where there are lots of open hardware projects.

# Week 2
## Excercise 1: Start sharing your documentation
- Write a simple introduction to your project assuming that the audience is new to the topic and not familiarized with it. 
- Make it in a format that can be easily edited, presented, and shared online. 
    - If you are just getting started, we recommend starting with Markdown and hackmd as a platform to present, share and get feedback.
    - This will make it easy for the mentors to comment and help you out)
- Alternatively, if you have already a git repository or documentation published in a platform of your preference feel free to reuse that and avoid repeating yourself.
## Excercise 2: See how others do it
- Find an open source project, this can be one that you found last week, and see how they did their documentation, it can be handy to make an overview or to write down what you liked and what you did not like.
- You can do the following:
    - Reflect on how open it is and how easy it is to get started with it.
    - Reflect back on your documentation to see if you can improve it based on looking at other projects.


## Excercise 3: Make a plan for the future
- Make a checklist of what your documentation should look like by the end of the program.
- Assess if it is too much for your current status or is a good match.