# parea3
Scanning and parsing in bison and flex

## PYTHON INDENTATION COMMENTS

The development of this functionality, together with testing some variations on the choice of the markers, is going on on parea3pyindent branch on Github.

The python indentation syntax is an obstacle for preprocessing.

Assume  the following example:

```
class foo1():

    def __init__(self, server, conn, addr):
        self.__bar1 = socket.getfqdn()
        try:
            self.__foo3 = bar3()
        except socket.error, err:

    def foo2(self):
        line = EMPTYSTRING.join(self.__line)
        print >> DEBUGSTREAM, 'Data:', repr(line)
        self.__line = []
        if self.__state == self.COMMAND:
            if not line:
                self.push('500 Error: bad syntax')
                return
            method = None
 ```

By adding ‘{‘ and ‘}’ markers in comments it is possible to impose the structure:

```
class foo1(): #{

    def __init__(self, server, conn, addr): #{
        self.__bar1 = socket.getfqdn()
        try: #{
            self.__foo3 = bar3() #}
        except socket.error, err: #}

    def foo2(self): #{
        line = EMPTYSTRING.join(self.__line)
        print >> DEBUGSTREAM, 'Data:', repr(line)
        self.__line = []
        if self.__state == self.COMMAND: #{
            if not line: #{
                self.push('500 Error: bad syntax')
                return #}
            method = None #}}}
```

When a decorated program is flattened:

```
class foo1(): #{

def __init__(self, server, conn, addr): #{
lf.__bar1 = socket.getfqdn()
try: #{
self.__foo3 = bar3() #}
xcept socket.error, err: #}

    def foo2(self): #{
line = EMPTYSTRING.join(self.__line)
print >> DEBUGSTREAM, 'Data:', repr(line)
        self.__line = []
        if self.__state == self.COMMAND: #{
 if not line: #{
self.push('500 Error: bad syntax')
return #}
            method = None #}}}
```

it is still possible to find the original structure.

Given a traditional python program it can be decorated by ‘indentation comments’ and a decorated program can be stripped of ‘indentation comments’. 
