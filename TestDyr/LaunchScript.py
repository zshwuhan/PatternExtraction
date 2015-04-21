import time
import subprocess
import os
import multiprocessing
fileWriteLock = multiprocessing.Lock()
globalFile = open("Results.txt", "w")
globalFile.close()
globalFile = open("Results.txt", "a")
gTimeout = 600

def Wait_timeout(proc, seconds):
    """Wait for a process to finish, or raise exception after timeout"""
    start = time.time()
    end = start + seconds
    interval = min(seconds / 1000.0, .25)
    while True:
        result = proc.poll()
        if result is not None:
            return result
        if time.time() >= end:
            raise RuntimeError("Process timed out")
        time.sleep(interval)

def Report(qualifier, results):
    fileWriteLock.acquire()
    globalFile.write(qualifier + ": " + results)
    fileWriteLock.release()

def Analyze(report):
    results = ''
    lineCount = 0
    for line in report:
        if "Excecution Time:" in line:
            results = str(lineCount) + ", " + line
            return results
        lineCount += 1
        

def ProcessManager(option):
    for i in range(2,8):
        qualifier = option + " " + str(i)
        output = qualifier + ".txt"
        save = open(output, "w")
        parameters = ["prefixSpan.exe", "Dataset3(4Var).csv", "50%", str(option), str(i)]
        p = subprocess.Popen( parameters, stdin=subprocess.PIPE, stdout=save)
        try:
            Wait_timeout(p, gTimeout)
            save.close()
            analytics = open(output, "r")
            results = Analyze(analytics)
            analytics.close()
        except RuntimeError:
            p.kill()
            results = "timeout\n"
            save.close()
        Report(qualifier, results)
        
def main():
    os.chdir("D:\Documents\Github\PatternExtraction\TestDyr")
    options = ["-minSseq", "-minSize", "-maxSize", "-maxSseq"]
    procList = []
    for option in options:
        proc = multiprocessing.Process(target=ProcessManager, args=[option])
        proc.start()
        procList.append(proc)
    for proc in procList:
        proc.join()
    print ('Tadaa!')
    globalFile.close()

if __name__=='__main__':
    main()
