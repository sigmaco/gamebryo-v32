import sys
import types
import imp

import stackless
from BehaviorAPI import *

breakOn = 0

modelBreakpoints = {}
entityBreakpoints = {}

# replace this with config driven function name:
#         if (method == "TestPropSet"):
#            breakOn = 1


# redirection for error messages to send them to a "C" method that
#    can log them and also print out to console...
# Create a class to catch output
class OutputCatcher:
    # Constructor takes a reference to the real sys output
    # so we can use it to really write things out
    # Otherwise we would recursively call ourselves
    def __init__(self, output, prefix, isErrCatcher):
        self.Output = output
        self.Prefix = prefix
        self.err = isErrCatcher
        self.buffer = ""
        return

    # Method to actually capture the output and do what we
    # want to with it - like send it to a log file
    def write(self, message):
        self.buffer = self.buffer + "".join(message)
        if (self.buffer[-1] == '\n'):
            if (self.err==0):
                LogMessage(1, self.Prefix + self.buffer[:-1])
            else:
                LogError(1,  self.Prefix + self.buffer[:-1])
            self.buffer = ""
        self.Output.write(message)
        return

    def flush(self):
        self.Output.flush()
        return

# Redirect stdout to the output catcher
sys.stdout = OutputCatcher(sys.stdout, "STDOUT: ", 0)

# Redirect stderr to another output catcher
sys.stderr = OutputCatcher(sys.stderr, "STDERR: ", 1)


#Important note on this module!
# We initialize and import this module from "C" code.  If done more than once,
#  any global data placed here will be lost (i.e. reinitilaized each time).
#  Therefore, this module and ProcessTick() are only initialized in the scheduler
#  init code in order to be called repeatedly by the entities...
# we print the following so we can see how often this module is re-initialized...
LogMessage(2, "Scheduler.py initialized")

# Get the debugger connected.
inited = False



# Function StartBehavior()
# Parameters:
#     arg 0: module name of new behavior
#     arg 1: method name of new behavior
#     arg 2: entity id of the owning entity
#     arg 3: ParameterList of behavior arguments
# This function
#   1) imports the required module
#   2) starts execution of the specified behavior
#
def StartBehavior(module, method, entityID, params):

   #DT32279 Remove Trampoline and just pass f1(entityID, params) to stackless.tasklet.
   modObj = None

   def Trampoline():

      # now launch behavior as stackless tasklet (so can block as uthread)
      f1 = modObj.__dict__[method]     # get function object by method name
      # modObj was loaded in the main function below

      f1(entityID, params)

      return False

   moduleName = "Ese" + module
   logstr = "StartBehavior() attempting launch of Behavior " + moduleName + ":" + method
   LogMessage(2, logstr)

   fp, pathname, description = imp.find_module(moduleName)
   if (fp != None):
      try:
         modObj = imp.load_module(moduleName, fp, pathname, description)
      except:
         logstr = "Error: Error attempting to load module: " + moduleName
         LogMessage(1, logstr)
         logstr = "Error:  Traceback: " + str(sys.exc_info()[0])
         LogMessage(1, logstr)
         logstr = "Error:  Traceback: " + str(sys.exc_info()[1])
         LogMessage(1, logstr)
         if fp:
            fp.close()
      else:
         # if here, we were able to import (find and load) module
         methodFull = moduleName + "." + method
         logstr = "Starting new behavior: " + methodFull + ", entityID=" + hex(entityID)
         LogMessage(2, logstr)

         task = stackless.tasklet(Trampoline)()   # create and "bind/schedule"
         task.run() # get to the first suspend point

   else:
      logstr = "Unable to find module " + moduleName + ", path= " + pathname
      LogError(2, logstr)

   return


def ResumeCoroutine(task, params):
    return task.send(params)


def GetCoroutine():
    # create and return a channel
    return stackless.channel()


def YieldCoroutine(task):
    # Block the current thread on a receive
    return task.receive()



