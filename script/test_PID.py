import sys
import subprocess
import pygame
from pygame.locals import *



LOCAL_COMMAND = ["./../source/test_PID"]
REMOTE_COMMAND = ["ssh" ,"-t" ,"pi@raspberrypi.local", "./prey/build/source/test_PID"]

def print_help():
    print("Tool used to display the motor output given by the PID controller")
    print("The first argument must be an integer representing the desired update value of both gyroscopes and accelerometers and from the flight controller")
    print("The second argument is -l to launch the script with pre-recorded values or -r to launch on the raspberry-pi via ssh")
    print("Example : python test_PID.py 50 -r")

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
x_m_out = 0
x_p_out = 0
y_m_out = 0
y_p_out = 0
maximum_value = 0

DISPLAY_LENGHT = 600
DISPLAY_HEIGHT = 600

display_size = (DISPLAY_LENGHT,DISPLAY_HEIGHT)
screen = pygame.display.set_mode(display_size)

#The center of the edge of the quadcopter
center_x_m = (int(DISPLAY_LENGHT/2+(DISPLAY_HEIGHT/2)*(3.0/4)), int(DISPLAY_HEIGHT/2))
center_x_p = (int(DISPLAY_LENGHT/2-(DISPLAY_HEIGHT/2)*(3.0/4)), int(DISPLAY_HEIGHT/2))
center_y_m = (int(DISPLAY_LENGHT/2), int(DISPLAY_HEIGHT/2+(DISPLAY_LENGHT/2)*(3.0/4)))
center_y_p = (int(DISPLAY_LENGHT/2), int(DISPLAY_HEIGHT/2-(DISPLAY_LENGHT/2)*(3.0/4)))

print "Launching the 3D representation of the position of the device"
print " * For now the script has to be launch from the /script directory"
print " * Update frequency set at " + str(frequency) + "ms"
print " * Warning experiment show that python is too slow for processing at frequencies bellow 30ms"
proc = subprocess.Popen(COMMAND_LINE + [str(frequency)], stdout=subprocess.PIPE)


def update_values():
    global x_m_out, x_p_out, y_m_out, y_p_out, maximum_value
    proc.stdout.flush()
    stdout_line = proc.stdout.readline()

    if stdout_line[0:10] != 'TEST_PID::':
        return

    stdout_line = stdout_line[10:]
    x_m_out_str, x_p_out_str, y_m_out_str, y_p_out_str = stdout_line.split(' ')
    x_m_out = float(x_m_out_str)
    x_p_out = float(x_p_out_str)
    y_m_out = float(y_m_out_str)
    y_p_out = float(y_p_out_str)

    maximum_value = max(x_m_out, x_p_out, y_m_out, y_p_out)

def color_from_value(value):
    global maximum_value
    if maximum_value == 0:
        return (255, 0, 0)
    color_value = int((value/float(maximum_value))*255)
    color_value = int(value*(255/100.0))
    color_value = int(value*(255/50.0))-254
    return (color_value, color_value, color_value)


def draw():
    global x_m_out, x_p_out, y_m_out, y_p_out
    line_thickness = 4
    circle_radius = 40
    circle_thickness = 0

    pygame.draw.lines(screen, (0, 0, 0), False, [center_x_m, center_x_p], 4)
    pygame.draw.lines(screen, (0, 0, 0), False, [center_y_m, center_y_p], 4)
    pygame.draw.circle(screen, color_from_value(x_m_out), center_x_m, circle_radius, circle_thickness)
    pygame.draw.circle(screen, color_from_value(x_p_out), center_x_p, circle_radius, circle_thickness)
    pygame.draw.circle(screen, color_from_value(y_m_out), center_y_m, circle_radius, circle_thickness)
    pygame.draw.circle(screen, color_from_value(y_p_out), center_y_p, circle_radius, circle_thickness)

def main():
    pygame.init()
    screen.fill((255, 255, 255))

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()

        update_values()
        draw()
        pygame.display.update()
        pygame.display.flip()
        pygame.time.wait(frequency)


main()
