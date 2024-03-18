
import matplotlib.pyplot as plt 
import csv 

import datetime
  
x = [] 
y = [] 
start = True
with open('potentio_1.csv','r') as csvfile: 
    plots = csv.reader(csvfile, delimiter = ',') 
    for row in plots:
        if (start):
            start = not start
            continue
        print(row)
        x.append(datetime.datetime.fromtimestamp(int(row[0]))
      .strftime('%Y-%m-%d %H:%M:%S')) 
        y.append(int(row[1])) 
  
plt.plot(x, y, color = 'g', label = "Potentio1") 
plt.xlabel('time') 
plt.ylabel('Potentio value') 
plt.title('Potentio value vs. time') 
plt.legend() 
plt.savefig("graf_python.png")
plt.show() 