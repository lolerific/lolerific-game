import sys
from var import *
from table import *

commands = []

class ConsoleCommand:
    def __init__(self, name, do, command, desc, usage):
        self.name = name
        self.do = do
        self.command = command
        self.desc = desc
        self.usage = usage
        commands.append(self)

current_command = None

def CC_Test(args):
    if len(args) == 0:
        return
    for item in args: print item

cc_test = ConsoleCommand('test', 'test', CC_Test, 'Test command', 'test [<args>]')

def CC_ShowUsage(args):
    if len(args) > 2 or len(args) < 1:
        print 'Usage: ' + current_command.usage
        return
    
    for item in commands:
        if item.do == args[0]:
            print 'Usage: ' + item.usage
            return
    print 'Command \'' + args[0] + '\' not found.'

cc_usage = ConsoleCommand('usage', 'usage', CC_ShowUsage, 'Shows how to use certain commands.', 'usage <command>')

def CC_Help(args):
    if len(args) >= 1 or len(args) < 0:
        CC_ShowUsage(['help'])
        return

    table = [['Name', 'Activate', 'Description', 'Usage']]
    for item in commands:
        table.append([item.name, item.do, item.desc, item.usage])

    out = sys.stdout
    pprint_table(out, table)

cc_help = ConsoleCommand('help', 'help', CC_Help, 'Shows a list of commands.', 'help')

if __name__ == '__main__':
    while True:
        cmd = raw_input(': ')
        if cmd == 'quit':
            break
        for item in commands:
            if item.do == cmd.split()[0]:
                current_command = item
                item.command(cmd.split()[1:])
        for item in variables:
            if item.name == cmd.split()[0]:
                if len(cmd.split()) > 2:
                    print 'Invalid argument set for \'' + cmd + '\' variable.'
                elif len(cmd.split()) == 1:
                    print item.name + ': ' + item.value
                    print 'Default: ' + item.default
                else:
                    item.change(cmd.split()[1])
