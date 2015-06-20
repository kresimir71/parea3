#! /usr/bin/python2.7

class foo1():

    def __init__(self, server, conn, addr):
        self.__bar1 = socket.getfqdn()
        try:
            self.__foo3 = bar3()
        except socket.error, err:
            pass
                
    def foo2(self):
        line = EMPTYSTRING.join(self.__line)
        print >> DEBUGSTREAM, 'Data:', repr(line)
        self.__line = []
        if self.__state == self.COMMAND:
            if not line:
                self.push('500 Error: bad syntax')
                return
            method = None
