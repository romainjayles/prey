import sys
import subprocess
import pygame
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

LOCAL_COMMAND = ["./../source/orientation_visualisation"]
REMOTE_COMMAND = ["ssh" ,"-t" ,"pi@raspberrypi.local", "./prey/build/source/orientation_visualisation"]

def print_help():
    print("Tool used to draw a 3D representation of the UAV")
    print("The first argument must be an integer representing the desired update value of both gyroscopes and accelerometers")
    print("The second argument is -l to launch the script with pre-recorded values or -r to launch on the raspberry-pi via ssh")
    print("Example : python 3D_visualisation.py 50 -r")

nodes = (
    (1, -0.2, -1),
    (1, 0.2, -1),
    (-1, 0.2, -1),
    (-1, -0.2, -1),
    (1, -0.2, 1),
    (1, 0.2, 1),
    (-1, -0.2, 1),
    (-1, 0.2, 1)
)

connections = (
    (0,1),
    (0,3),
    (0,4),
    (2,1),
    (2,3),
    (2,7),
    (6,3),
    (6,4),
    (6,7),
    (5,1),
    (5,4),
    (5,7)
)

try:
    frequency = int(sys.argv[1])
    if sys.argv[2]== '-r':
        print "Remote launch"
        COMMAND_LINE = REMOTE_COMMAND
    elif sys.argv[2]== '-l':
        print "Local launch"
        COMMAND_LINE = LOCAL_COMMAND
except:
    print_help()
    exit()

lines_buffer = []
actual_roll = 0
actual_pitch = 0
actual_yaw = 0

print "Launching the 3D representation of the position of the device"
print " * Update frequency set at " + str(frequency) + "ms"
print " * Warning experiment show that python is too slow for processing at frequencies bellow 30ms"
proc = subprocess.Popen(COMMAND_LINE + [str(frequency)], stdout=subprocess.PIPE)


def update_values():
    global actual_roll, actual_pitch, actual_yaw
    proc.stdout.flush()
    #stdout_lines = iter(proc.stdout.readline, "")
    stdout_line = proc.stdout.readline()

    if stdout_line[0:18] != 'TEST_ORIENTATION::':
        return

    stdout_line = stdout_line[18:]
    actual_roll_str, actual_pitch_str, actual_yaw_str = stdout_line.split(' ')
    actual_roll = float(actual_roll_str)
    actual_pitch = float(actual_pitch_str)
    actual_yaw = float(actual_yaw_str)

def Shape():
    glBegin(GL_LINES)
    for connection in connections:
        for node in connection:
            glVertex3fv(nodes[node])
    glEnd()


def main():
    pygame.init()
    display_size = (800,600)
    pygame.display.set_mode(display_size, DOUBLEBUF|OPENGL)

    gluPerspective(60, (display_size[0]/display_size[1]), 0.3, 40.0)
    glTranslatef(0.0,0.0, -5)

    while True:
        #rotate_x = 0
        #rotate_y = 0
        #rotate_z = 0
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            #if event.type == pygame.KEYDOWN:
            #    if event.key == pygame.K_LEFT:
            #        rotate_z = 1
            #    if event.key == pygame.K_RIGHT:
            #        rotate_z = -1
            #    if event.key == pygame.K_UP:
            #        rotate_x = -1
            #    if event.key == pygame.K_DOWN:
            #        rotate_x = 1
        glRotatef(-actual_pitch, 0, 0, 1)
        glRotatef(-actual_roll, 1, 0, 0)
        update_values()
        glRotatef(actual_roll, 1, 0, 0)
        glRotatef(actual_pitch, 0, 0, 1)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        Shape()
        pygame.display.flip()
        pygame.time.wait(frequency)


main()
