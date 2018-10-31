# rosie-servo-controller
A servo gates controller for Rosie

## How to run
Run the following in different terminals:
**Starting service**
```
rosrun rosie_servo_controller rosie_servo_controller
```

**Running node**
```
rosrun rosie_servo_controller rosie_servo_controller
```

**Sending gate angle to servo controller**
```
rostopic pub /MoveGates rosie_servo_controller/GateAngles "header:
  seq: 0
  stamp:
    secs: 0
    nsecs: 0
  frame_id: ''
rightgate: 0
leftgate: 0"
```
where rightgate and leftgate are gate angles in degrees (0-180)

**KTH RAS Servo repo**

https://github.com/KTH-RAS/ras_servo_control
