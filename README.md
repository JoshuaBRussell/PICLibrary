# PICLibrary


There are multiple goals have for this project. The main two are 1. to supplement my embedded knowledge and 2. to practice implementing controls projects. By working on this project I am able to:

1. Gain experience implementing a microcontroller from the "ground up." (I've always had "helper" code provided to get things going, whether it be from professors or the manufacturer)

2. Practice writing code (and properly) in C. Along with this I want to use unit testing to help ensure my code is more reliable.

3. Add to my controls theory theoretical knowledge. Although I learned a lot from my Controls Theory course, it was obvious there was a lot missing. 

4. Add to my controls theory practical knowledge. Doing things in theory is one thing and doing them in the real world is another. I wanted to learn about what methods there are to implement a controls algorithm, and what things to look out for. 


By writing a peripheral library, while trying to write a PID motor control algorithm, I can combine all the goals into one project.  

I am using the dsPIC33EP128GP502 microcontroller. 

**With this being said, the main goal for all of this is to _learn_** The code is likely to change often, and will probably have sections of poorly written code...*initially*. 


**Update (07/02/18):**

PIDExample.c shows how to set up a working PID controller that is able to control the speed of a DC motor. The code needs refactoring and test code needs to be wrapped around everything along with some other misc. changes. After those changes are in effect, other performance improving code will be added. 

