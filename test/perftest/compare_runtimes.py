from collections import defaultdict
from statistics import mean, median
from re import compile
from termcolor import colored
from argparse import ArgumentParser

argparser = ArgumentParser()
argparser.add_argument("-w", "--was")
argparser.add_argument("-n", "--now")
argparser.add_argument("-l", "--limit-percent", type=float)
args = argparser.parse_args()

pattern = r".+Test\s+#\d+:\s+(?P<test_name>\w+)\.\w+\s+\.\.\.\s+Passed\s+(?P<runtime>[0-9\.]+)\s+sec"
reg = compile(pattern)

def fetch_runtimes(text):
    test_runs = defaultdict(lambda: [])
    matches = [m.groupdict() for m in reg.finditer(text)]
    for match in matches:
        test_runs[match['test_name']].append(float(match['runtime']))
    return test_runs

def estimate_runtimes(text):
    estimated_runtimes = {}
    for test_name, runtimes in fetch_runtimes(text).items():
        estimated_runtimes[test_name] = mean(runtimes)
    return estimated_runtimes

text_was = open(args.was).read()
text_now = open(args.now).read()

runtimes_was = estimate_runtimes(text_was)
runtimes_now = estimate_runtimes(text_now)

for test_name, was_time in runtimes_was.items():
    if test_name in runtimes_now:
        now_time = runtimes_now[test_name]
        runtime_change_percent = (now_time - was_time) / was_time * 100
        color = "green" if runtime_change_percent < 0 else "red"
        if abs(runtime_change_percent) <= args.limit_percent:
            color = "light_grey"
        print(f"Test {test_name} runtime changed by {colored(str(runtime_change_percent) + '%', color, attrs=['bold'])}")
        print(f"Previous runtime: {was_time} sec, current runtime: {now_time}")

for test_name, was_time in runtimes_was.items():
    if test_name not in runtimes_now:
        print(colored(f"Deleted test {test_name} with runtime: {was_time}", "red"))

for test_name, now_time in runtimes_now.items():
    if test_name not in runtimes_was:
        print(colored(f"Added test {test_name} with runtime: {now_time}", "green"))
