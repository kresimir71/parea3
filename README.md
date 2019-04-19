# parea3

Scanning and parsing in bison and flex.

This is a continuation of a project from 2003. See also the old source documented in a top-down requirements fashion.

## Old project from year 2003

Here I want to remind about my old project on c preprocessing. There the documentation contains the links between ‘the requirements’ and the source code. Hypertext documentation of a source from the year 2003 is an example of how I would like to write software documentation.

http://abec.info/cpp2html/doc.html

## python language lexical scanner

In order to test the python scanner library on a typical Linux system proceed as follows:

```
server=https://github.com/kresimir71/
project=parea3/archive/master.zip
wget "$server$project"
unzip master.zip
cd parea3-master
./configure
make install
pyscan3parea/pyscan3parea_test test.py
```

The test program will read test.py word by word and print exactly the same to the screen.

## PYTHON INDENTATION COMMENTS

The development of this functionality, together with testing some variations on the choice of the markers, is going on in parea3pyindent directory.

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
### Indent programs
The previous ‘indentation comments’ can be a suitable tool for producing an *indent* program for python although such utilities already exist, e.g.
https://github.com/jamiesonbecker/pyindent
https://pypi.org/project/indentpy/
