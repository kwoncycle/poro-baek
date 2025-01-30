#!/usr/bin/python3
import sys, os
n = sys.argv[1]
n1 = n[:-3] + "000"

is_exist = os.path.isdir("/home/poro/PS/acmicpc/" + n1 + "/" + n)

if not is_exist:
    payload = "mkdir /home/poro/PS/acmicpc/" + n1 + "/" + n
    os.system(payload)

payload = "cd /home/poro/PS/acmicpc/" + n1 + "/" + n
os.system(payload)

is_exist = os.path.exists("/home/poro/PS/acmicpc/" + n1 + "/" + n + "/" + "solve.c++")

if not is_exist:
    payload = "cp /home/poro/PS/acmicpc/template/template.c++ " + "/home/poro/PS/acmicpc/" + n1 + "/" + n + "/" + "solve.c++"
    os.system(payload)

print("cd /home/poro/PS/acmicpc/" + n1 + "/" + n)