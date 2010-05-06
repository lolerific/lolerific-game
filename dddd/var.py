variables = []

def VR_CheckDomain(var, value):
    #FIXME: make better..
    if var.domain == []:
        return True
    for item in var.domain:
        if item == value:
            return True
    return False

class Variable:
    def __init__(self, name, default, domain):
        self.name = name
        self.value = default
        self.default = default
        self.domain = domain
        variables.append(self)

    def change(self, value):
        if not VR_CheckDomain(self, value):
            msg = ''
            for item in self.domain:
                msg += item + ', '
            print 'Domain: ' + msg
            return
        else:
            self.value = value

sv_test = Variable('sv_cheats', '0', ['1', '0'])
