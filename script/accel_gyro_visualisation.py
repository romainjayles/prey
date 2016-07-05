import pylab
import sys
import subprocess
from pylab import *


max_y = 20
min_y = -10
max_plot = 100
step = 1

axis_x=pylab.arange(0,max_plot,step)
axis_y=pylab.array([0]*max_plot)

fig = pylab.figure(1)
ax = fig.add_subplot(111)
ax.grid(True)
ax.set_title("Acceleration and Rotation")
ax.set_xlabel("Time")
ax.set_ylabel("Values")
ax.axis([0,max_plot,min_y,max_y])

accx_graph=ax.plot(axis_x,axis_y,'-')
accy_graph=ax.plot(axis_x,axis_y,'-')
accz_graph=ax.plot(axis_x,axis_y,'-')

rotx_graph=ax.plot(axis_x,axis_y,'-')
roty_graph=ax.plot(axis_x,axis_y,'-')
rotz_graph=ax.plot(axis_x,axis_y,'-')


#init values
accx_value = [0 for x in range(max_plot)]
accy_value = [0 for x in range(max_plot)]
accz_value = [0 for x in range(max_plot)]

rotx_value = [0 for x in range(max_plot)]
roty_value = [0 for x in range(max_plot)]
rotz_value = [0 for x in range(max_plot)]

frequency = int(sys.argv[1])
lines_buffer = []

print "Launching the Visualisation of datas from the gyroscope and accelerometer"
print " * Update frequency set at " + str(frequency) + "ms"
print " * Warning experiment show that python is too slow for processing at frequencies bellow 30ms"
proc = subprocess.Popen(["./../source/accel_gyro_visualisation", str(frequency)], stdout=subprocess.PIPE)


def update_values(arg):
    proc.stdout.flush()
    stdout_lines = iter(proc.stdout.readline, "")
    stdout_line = proc.stdout.readline()
    #for stdout_line in stdout_lines:
    #    if stdout_line is None :
    #        break
    #count += frequency
    #time_list.append(count)
    #datas.append(stdout_line)
    #if(len(datas) > buffer_size):
    #  datas.pop(0)
    #  time_list.pop(0)
    #print stdout_line
    #time.sleep(frequency/1000.0)
    accx, accy, accz, rotx, roty, rotz = stdout_line.split(' ')
    accx_value.append(float(accx))
    accy_value.append(float(accy))
    accz_value.append(float(accz))

    rotx_value.append(float(rotx))
    roty_value.append(float(roty))
    rotz_value.append(float(rotz))

    accx_value.pop(0)
    accy_value.pop(0)
    accz_value.pop(0)
    rotx_value.pop(0)
    roty_value.pop(0)
    rotz_value.pop(0)

def plot(arg):
    update_values(arg)
    axis=pylab.arange(len(accx_value)-max_plot,len(accx_value),1)

    accx_graph[0].set_data(axis,pylab.array(accx_value[-max_plot:]))
    accy_graph[0].set_data(axis,pylab.array(accy_value[-max_plot:]))
    accz_graph[0].set_data(axis,pylab.array(accz_value[-max_plot:]))

    rotx_graph[0].set_data(axis,pylab.array(rotx_value[-max_plot:]))
    roty_graph[0].set_data(axis,pylab.array(roty_value[-max_plot:]))
    rotz_graph[0].set_data(axis,pylab.array(rotz_value[-max_plot:]))

    ax.axis([axis.min(),axis.max(),min_y,max_y])
    pylab.get_current_fig_manager().canvas.draw()

plot_timer = fig.canvas.new_timer(interval=frequency)
plot_timer.add_callback(plot, ())
plot_timer.start()


pylab.show()
update_values(0)