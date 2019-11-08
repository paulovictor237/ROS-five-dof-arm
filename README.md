# five_dof_robot_arm

> ligue o arduino ao computador
> alimente somente a garra com o próprio arduino
> alimente o resto braço robotico com uma fonte externa
> conecte o ground do arduino junto ao ground da fonte
> para rodar o programa digite os seguintes comandos nessa ordem

> roda o node prinpical
roscore
> cria os nodes subscrible do arduino
rosrun five_dof_arm_test arduino_node
> cria os nodes publishers do arduino
rosrun rosserial_python serial_node.py _port:=/dev/ttyACM0 _baud:=115200
> inicia o Rviz
roslaunch five_dof_arm_peve demo.launch use_gui:=true


> outras aplicações
rosrun five_dof_arm_test test_random_node 
rosrun five_dof_arm_test test_custom_node
rosrun five_dof_arm_test test_custom_node_2