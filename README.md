# PID regulation
I have made this project during my first year at university when I was preparing a robot to participate in national robotics competition.
It is dedicated for the beginners in the field of robotics and regulation.
The regulation consists of adapting the voltage provided to the motors, in order to reach the desired robot speed.
To make the regulation successful, we have to get feedback on the motor speed. 
Encoders are the solution: they are a kind of sensors that returns in real-time, the motor angular position.

## How do encoders work?
An encoder is composed mainly of a perforated disk, an issure LED and a receiver photo-transistor. The disk is recessed to the motor shaft. When the rotor rotates, the disk rotates with the same speed. When rotating, at one time, it lets the receiver photo-transistor receive the signal, and at another time it prevents it from doing it. As a result, the encoder ouptut is a square signal.


This code is one of the first steps that I made to discover the regulation and PID process.
It is implemented on Arduino.
It uses interruption to count ticks and the SimpleTimer library to make a sampled treatment. 
![Analog_rotary-encoder_Pt1-opener](https://user-images.githubusercontent.com/53936812/159812461-fc2741ae-95c0-471f-a432-4e26b1523b82.gif)


## How can we explore the output signal?
To know about the motor's knimatics,we have to treat the encoder's output signal. 
Each encoder is characterized by its resolution N and an amplification ratio R. the resolution defines the number of the holes in the disk. 1 revolution corresponds to N holes. And the amplification ratio is defined by Vdisk = R * Vrotor.
Vdisk: the disk angular speed and Vrotor: the rotor angular speed.

To increase the precesion, we can reason on both edges. In this case, 1 revolution correspoonds to 2 * R * N edges.

The signal output:

![encoder output](https://user-images.githubusercontent.com/53936812/159940343-ccfed2a5-32ab-4f9e-9935-35c7712fb35e.png)

The detection of each edge is managed by interruption.

To do so, we configure the interruption ins the ``` void setup() ```

```   attachInterrupt(digitalPinToInterrupt(2), ReagirGauche, CHANGE); ```

The number ``` 2 ``` represents the ``` PIN 2 ``` that supports interruption.

It is to know that the ``` ReagirGauche ``` is a function that calculates the number of edges. 

The ``` ReagirGauche ``` definition:

``` 
void ReagirGauche() 
{  
    comptG++;            
} 
```

The right motor's encoder is managed by the ``` PIN 3 ```, and the ``` ReagirDroite ``` manages the iinterruption on that pin.



