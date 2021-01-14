# Purchase information

Arduino nano with RF24 modules: 
https://www.amazon.com/gp/product/B07RDJYTZC/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1

Load cell Information: 
https://www.alibaba.com/product-detail/Customized-force-sensor-weighing-load-cell_62421576576.html?spm=a2756.order-detail-ta-ta-b.0.0.576b2fc2CQ4TRL

Circuit connection for load cell: 
https://www.amazon.com/Amplifier-Breakout-Converter-Raspberry-Microcontroller/dp/B07MTYT95R/ref=sr_1_1_sspa crid=3UR91DFIQGUP&dchild=1&keywords=load+cell+hx711&qid=1595537213&sprefix=load+cell+HX%2Caps%2C138&sr=8-1 spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEySU1SNDJQVkpXQkxGJmVuY3J5cHRlZElkPUEwMjc3NDA4MUxLMFMwNVhCNFRIVCZlbmNyeXB0ZWRBZElkPUEwMTIyMDUyUENOQVdZWks0UUZIJndpZGdldE5hbWU9c3BfYX mJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==

Wireless module:
https://www.amazon.com/Arduino-NRF24L01-2-4GHz-Wireless-Transceiver/dp/B07GZ17ZWS/ref=sr_1_4?dchild=1&keywords=wireless+module+nrf24&qid=1610654638&sr=8-4



# How to read Arduino’s data through ROS

## 1.Use rosserial_arduino to connect ROS and Arduino:
How to use rosserial_arduino can be seen in:
http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

## 2. Define your own data type in rosserial_arduino:

In our project, we use Arduino to control four force sensors, whose date type are float32. 

(1)In order to read the sensor’s data, first, we need to create our own data type ‘Sensor.msg’ in ‘～/catkin_ws/src/my_package/msg/’ and write the code below into ‘Sensor.msg’ :

![image](https://github.com/RLee-xy/Force-sensing-shoes-for-Nao/blob/main/docs/figures/figure1.jpg)
 
If you do not have a ‘my_package’ file, you can create one, following the instructions in :

http://wiki.ros.org/ROS/Tutorials/CreatingPackage 

and:

http://wiki.ros.org/ROS/Tutorials/BuildingPackages

(2) Second, we need to modify the ‘Cmakelist.txt’ and ‘package.xml’ files in ‘my_package’, in order to using the ‘Sensor.msg’.

You can follow the instructions in:

http://wiki.ros.org/ROS/Tutorials/CreatingMsgAndSrv 

After modifying, ‘Cmakelist.txt’ and ‘package.xml’ files should be look like this:

Then we go back to ‘～/catkin_ws/’ and run ‘catkin_make’. After compiling, you can find a ‘Sensor.h’ file in ‘～/catkin_ws/devel/include/my_package/’. You can test your msg file by running:

‘rosmsg show my_package/Sensor’

(3) After creating our own data type file, we need to rebuild the ‘ros_lib’ library for Arduino IDE, just follow the instructions here:

http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup

You should be able to see ‘Sensor.h’ file in ‘～/Arduino/libraries/ros_lib/my_package/’

## 3.Next, we need develop code for rosserial_arduino:

Code is developed as follows:

![image](https://github.com/RLee-xy/Force-sensing-shoes-for-Nao/blob/main/docs/figures/figure3.png)

Notice that the Baud rate for rosserial_python serial_node.py /dev/ttyACM0 is 57600, so we need to set our print rate in Arduino to be 57600: ‘Serial.begin(57600);’

## 4.Test:

(1) Let’s upload the code to Arduino by running:

‘rosrun rosserial_python serial_node.py /dev/ttyACM0’ (Do not forget to run ‘roscore’ first)

(2) Then we shall be able to see our topic ‘Sensor’ and read sensors’ date through ROS by running:
rostopic list
rostopic echo sensor
