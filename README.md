# Problem Statement 4: Obstacle Avoidance Robot

<b>Group</b>: 55  
<b>Course</b>: Foundations of Design Practicum (FDP)  
<b>Institute</b>: IIT Mandi

Hello! I’m <b>Jigar Fufal</b>, an Electrical Engineering undergraduate ('28) at IIT Mandi. This repository contains the Source Code, PCB design, CAD, and project overview for our FDP Group 55 robot — a fully autonomous obstacle avoidance bot. The robot is designed to navigate an environment using real-time ultrasonic sensing and conditional logic to avoid collisions. This project was part of our semester-long foundation design course.

---

## <b>Hardware Components</b>

- <b>Ultrasonic Sensors</b> – Y401  
- <b>Motor Driver</b> – L298N  
- <b>Microcontroller</b> – Arduino Uno R3  
- <b>Power Regulation</b> – LM2596S Buck Converter  

---

## <b>Team Members</b>

- <b> Dhruv (B24242)</b>  
- <b> Jigar (B24244)</b>  
- <b> Pradeep (B24248)</b>  
- <b> Kush (B24252)</b>  
- <b> Kartik (B24253)</b>  

---

## **Code Logic**

The robot continually samples distance measurements from three ultrasonic sensors positioned at the front, left, and right. If the front path is unobstructed and both sides are sufficiently clear, the robot advances forward. In the presence of a frontal obstacle, the code evaluates side clearances to decide the optimal turning direction. This branching logic ensures the robot adapts to dynamic environments by selecting the most viable path at each moment. In the event of full enclosure (obstacles on all sides), it reverses briefly and performs a fixed right turn to escape. The structure is built in a modular form, making it easily extensible for further logic enhancements or sensor integration.

---

## <b>Code Structure and Working</b>

The obstacle avoidance robot’s control logic is organized into a modular Arduino program that continuously processes input from three ultrasonic sensors to make movement decisions. Initially, all motor and sensor pins are defined clearly to enhance code readability and flexibility. Distance measurements are obtained using a dedicated function that calculates distance from pulse durations, providing real-time environmental feedback.

Within the core <b>loop()</b> function, a sequence of prioritized <b>if</b> statements evaluates sensor data to determine the robot’s actions. When the front and both side sensors detect sufficient clearance, the robot advances forward. If the front sensor detects an obstacle, the robot stops momentarily and compares the side distances. It then executes a turn toward the side with more space—turning right if the right side is clearer, or left if the left side offers more room. When all directions are blocked, the robot performs a brief backward movement followed by a right turn to free itself.

This structured conditional logic ensures responsive, real-time obstacle avoidance, with modular motor control functions (<b>moveForward()</b>, <b>turnRight()</b>, <b>turnLeft()</b>, <b>moveBackward()</b>, <b>stopMotors()</b>) simplifying the implementation and future enhancements. The design leverages simple, deterministic conditions to maintain predictable and effective navigation behavior.

---

## <b>Final Thoughts</b>

This project gave us valuable experience in sensor integration, embedded systems, real-world debugging, and basic decision-making logic. The modular code structure combined with a custom PCB allowed efficient testing and iteration.
