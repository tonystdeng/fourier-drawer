import math

file = open("./pytest.txt")
ft = []  
for point in file.readlines():
    point = tuple(map(float, point.split()))
    ft.append(point)
file.close()

pointnum = len(ft)
dt = 1 / pointnum

C = {}
for n in range(-50, 51):
    Cn_real = 0
    Cn_imag = 0
    for i, point in enumerate(ft):
        x, y = point
        angle = 2 * math.pi * n * i * dt
        Cn_real += (x * math.cos(angle) + y * math.sin(angle)) * dt
        Cn_imag += (y * math.cos(angle) - x * math.sin(angle)) * dt
    
    magnitude = math.sqrt(Cn_real**2 + Cn_imag**2)
    start_angle = math.atan2(Cn_imag,Cn_real)
    
    C[n] = (start_angle, magnitude)

CN={0:C[50]}
for i in range(1,50+1):
    CN[i]=C[i]
    CN[-i]=C[-i]
C=CN
with open("./svgs/pi.dc", "w") as file:
    for n, (start_angle, magnitude) in C.items():
        file.write(f"{start_angle}\n{magnitude}\n{n}\n")
    file.write("z")
