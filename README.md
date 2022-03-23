# PID regulation
I have made this project during my first year at university when I was preparing a robot to participate in national robotics competition.
It is dedicated for the beginners in the field of robotics and regulation.
The regulation consists of adapting the voltage provided to the motors, in order to reach the desired robot speed.
To make the regulation successful, we have to get feedback on the motor speed. 
Encoders are the solution: they are a kind of sensors that returns in real-time, the motor angular position.

## How do encoders work?

 

This code is one of the first steps that I made to discover the regulation and PID process.
It is implemented on Arduino.
It uses interruption to count ticks and the SimpleTimer library to make a sampled treatment. 
