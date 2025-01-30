#!/usr/bin/env python3
#
# Testing tool for the Polygon Discovery problem
#
# Usage:
#
#   python3 testing_tool.py -f inputfile <program>
#
#
# Use the -f parameter to specify the input file, e.g. input.in.
# Format of the input file:
# - One line with a single integer:
#   - n, the number of vertices of the polygon P.
# - n lines with two integers per line:
#   - x_i, y_i are the coordinates of the i-th vertex of polygon P
#
# The coordinates of the polygon P must be given in counterclockwise order.
#
# E.g.:
# 3
# 1 1
# -2 -1
# 2 -2
#
# If you have a C++ solution stored in a file called "sol.cpp",
# you must first compile using "g++ sol.cpp -o sol" and then
# invoke the testing tool with:
#
#   python3 testing_tool.py -f input.in ./sol
#
# If you have a Python solution that you would run using
# "pypy3 solution.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py -f input.in pypy3 solution.py
#
# If you have a Java solution that you would run using
# "java MyClass", you could invoke the testing tool with:
#
#   python3 testing_tool.py -f input.in java MyClass
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#
# The tool attempts to detect and report common errors, but it is not guaranteed
# that a program that passes the testing tool will be accepted.

import argparse
import subprocess
import traceback


def write(p, line):
    assert p.poll() is None, "Program terminated early"
    print(f"Write: {line}", flush=True)
    p.stdin.write(f"{line}\n")
    p.stdin.flush()


def read(p):
    assert p.poll() is None, "Program terminated early"
    line = p.stdout.readline().strip()
    assert (
        line != ""
    ), "Read empty line or closed output pipe. Make sure that your program started successfully."
    print(f"Read: {line}", flush=True)
    return line


parser = argparse.ArgumentParser(
    description="Testing tool for the Polygon Discovery problem"
)
parser.add_argument(
    "-f",
    dest="inputfile",
    metavar="inputfile",
    default=None,
    type=argparse.FileType("r"),
    required=True,
    help="The input file to use.",
)
parser.add_argument("program", nargs="+", help="Invocation of your solution")

args = parser.parse_args()

with args.inputfile as f:
    lines = f.readlines()
    assert len(lines) > 0
    n = int(lines[0].strip())
    polygon = []
    for i in range(n):
        x, y = map(int, lines[1 + i].strip().split())
        polygon.append((x, y))
polygon_area = 0
for i in range(n):
    x1, y1 = polygon[i]
    x2, y2 = polygon[(i + 1) % n]
    polygon_area += x1 * y2 - x2 * y1
polygon_area *= 0.5
num_queries = 0
max_num_queries = 40096
max_query_value = 1000000000
accepted_error = 0.001
with subprocess.Popen(
    " ".join(args.program),
    shell=True,
    stdout=subprocess.PIPE,
    stdin=subprocess.PIPE,
    universal_newlines=True,
) as p:
    try:
        while True:
            request_args = list(read(p).split())
            if len(request_args) < 2:
                write(p, "error")
                assert False, "Invalid request1."
            request_type = request_args[0]
            if '?' == request_type:
                x1, y1, x2, y2 = map(int, request_args[1:])
                num_queries += 1
                if max_num_queries < num_queries:
                    write(p, "error")
                    assert False, "Too many queries."
                if max_query_value < max([abs(x1), abs(y1), abs(x2), abs(y2)]):
                    write(p, "error")
                    assert False, "Invalid request2."
                if x1 == x2 and y1 == y2:
                    write(p, "error")
                    assert False, "Invalid request3."
                num_zero = 0
                num_pos = 0
                num_neg = 0
                for (x, y) in polygon:
                    value = x * y1 + x1 * y2 + x2 * y - x1 * y - x2 * y1 - x * y2
                    if 0 < value:
                        num_pos += 1
                    elif value < 0:
                        num_neg += 1
                    else:
                        num_zero += 1
                if 2 <= num_zero and (not num_pos or not num_neg):
                    write(p, "infinity")
                elif 1 == num_zero and (not num_pos or not num_neg):
                    write(p, "1")
                elif not num_zero and (not num_pos or not num_neg):
                    write(p, "0")
                else:
                    write(p, "2")
            elif '!' == request_type:
                _, area = request_args
                area = float(area)
                if accepted_error <= abs(polygon_area - area):
                    write(p, "wrong")
                    assert False, "Wrong area."
                write(p, "correct")
                break
            else:
                write(p, "error")
                assert False, "Invalid request."

        assert (
            p.stdout.readline() == ""
        ), "Your submission printed extra data after writing the final output request."
        assert p.wait() == 0, "Your submission did not exit cleanly after finishing."

        print(f"\nSuccess.\n# of queries: {num_queries}\n")

    except AssertionError as e:
        print()
        print(f"Error: {e}")
        print()
        try:
            p.wait(timeout=2)
        except subprocess.TimeoutExpired:
            print("Killing your submission after 2 second timeout.")
            p.kill()

    except Exception as e:
        print()
        traceback.print_exc()
        print()
        try:
            p.wait(timeout=2)
        except subprocess.TimeoutExpired:
            print("Killing your submission after 2 second timeout.")
            p.kill()
        raise e

    finally:
        print(f"Exit code: {p.wait()}\n", flush=True)

