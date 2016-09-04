import pylab
import sys
import subprocess
from pylab import *


max_y = 100
min_y = -100
max_plot = 100
step = 1

axis_x=pylab.arange(0,max_plot,step)
axis_y=pylab.array([0]*max_plot)

fig = pylab.figure(1)
ax = fig.add_subplot(111)
ax.grid(True)
ax.set_title("Orientation")
ax.set_xlabel("Time")
ax.set_ylabel("Values")
ax.axis([0,max_plot,min_y,max_y])

pitch_acc_graph=ax.plot(axis_x,axis_y,'-')
pitch_rot_graph=ax.plot(axis_x,axis_y,'-')
pitch_graph=ax.plot(axis_x,axis_y,'-')


#init values
pitch_acc_value = [0 for x in range(max_plot)]
pitch_rot_value = [0 for x in range(max_plot)]
pitch_value = [0 for x in range(max_plot)]


frequency = int(sys.argv[1])
lines_buffer = []

print "Launching the Visualisation of datas from Orientation manager"
print " * Update frequency set at " + str(frequency) + "ms"
print " * Warning experiment show that python is too slow for processing at frequencies bellow 30ms"
proc = subprocess.Popen(["./../source/orientation_visualisation", str(frequency)], stdout=subprocess.PIPE)


def update_values(arg):
    proc.stdout.flush()
    #stdout_lines = iter(proc.stdout.readline, "")
    stdout_line = proc.stdout.readline()

    if stdout_line[0:18] != 'TEST_ORIENTATION::':
        return

    stdout_line = stdout_line[18:]
    pitch_acc, pitch_rot, pitch = stdout_line.split(' ')
    pitch_acc_value.append(float(pitch_acc))
    pitch_rot_value.append(float(pitch_rot))
    pitch_value.append(float(pitch))


    pitch_acc_value.pop(0)
    pitch_rot_value.pop(0)
    pitch_value.pop(0)

def plot(arg):
    update_values(arg)
    axis=pylab.arange(len(pitch_value)-max_plot,len(pitch_value),1)

    pitch_acc_graph[0].set_data(axis,pylab.array(pitch_acc_value[-max_plot:]))
    pitch_rot_graph[0].set_data(axis,pylab.array(pitch_rot_value[-max_plot:]))
    pitch_graph[0].set_data(axis,pylab.array(pitch_value[-max_plot:]))

    ax.axis([axis.min(),axis.max(),min_y,max_y])
    pylab.get_current_fig_manager().canvas.draw()

plot_timer = fig.canvas.new_timer(interval=frequency)
plot_timer.add_callback(plot, ())
plot_timer.start()


pylab.show()
update_values(0)