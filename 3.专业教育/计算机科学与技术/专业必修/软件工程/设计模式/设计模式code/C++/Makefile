C++ = /pub/hpcenterline/bin/CC -D__cfront21 -I. -I..

C++FLAGS= 

.SUFFIXES: .tex .C .o

.tex.o: 
	-mv -f $*.C $*.C.bak
	tex2CC ../$*.tex > $*.C
	$(C++) $(C++FLAGS) -c $*.C

#.C.o:
#	$(C++) $(C++FLAGS) -c $*.C

OBJS = \
 editor.o\
 List.o\
 maze.o\
 creational.o\
 abfactory.o\
 builder.o\
 factorymeth.o\
 prototype.o\
 singleton.o\
 adapter.o\
 bridge.o\
 decorator.o\
 facade.o\
 flyweight.o\
 proxy.o\
 chain.o\
 command.o\
 interpreter.o\
 iterator.o\
 mediator.o\
 memento.o\
 observer.o\
 state.o\
 strategy.o\
 visitor.o 

target:	$(OBJS)

Foundation.H: ../../foundation.tex
	-/bin/rm Foundation.H
	tex2CC ../../foundation.tex > Foundation.H

scenario.o: scenario.C ../../scenario.tex
	tex2CC ../../scenario.tex > $*.C
	-$(C++) $(C++FLAGS) -c -DSpell1 $*.C  
	-$(C++) $(C++FLAGS) -c $*.C  
foundation.o: ../../foundation.tex
	tex2CC ../../foundation.tex > $*.C
	tex2CC ../$*.tex > $*.C
	$(C++) $(C++FLAGS) -c $*.C
maze.o:
	-$(C++) $(C++FLAGS) -c $*.C  
	-$(C++) $(C++FLAGS) -DSingleton=1 -c $*.C  
creational.o: creational.C ../../creational.tex
abfactory.o: abfactory.C ../abfactory.tex
builder.o: builder.C ../builder.tex
factorymeth.o: factorymeth.C ../factorymeth.tex
	-$(C++) $(C++FLAGS) -DImplementation1=1 -c $*.C
	-$(C++) $(C++FLAGS) -DImplementation2=1 -c $*.C
	-$(C++) $(C++FLAGS) -DImplementation3=1 -c $*.C
prototype.o: prototype.C ../prototype.tex
	-$(C++) $(C++FLAGS) -DSampleCode1=1 -c $*.C
	-$(C++) $(C++FLAGS) -DSampleCode2=1 -c $*.C
singleton.o: singleton.C ../singleton.tex
	-$(C++) $(C++FLAGS) -DImplementation1=1 -c $*.C
	-$(C++) $(C++FLAGS) -DImplementation2=1 -c $*.C

adapter.o:  adapter.tex
composite.o: composite.C ../composite.tex
decorator.o: decorator.C ../decorator.tex
facade.o: facade.C ../facade.tex
flyweight.o: flyweight.C ../flyweight.tex
proxy.o: proxy.C ../proxy.tex
	-$(C++) $(C++FLAGS) -DImplementation=1 -c $*.C
	-$(C++) $(C++FLAGS) -DSampleCode=1 -c $*.C
chain.o: chain.C ../chain.tex
	-$(C++) $(C++FLAGS) -DImplementation=1 -c $*.C
	-$(C++) $(C++FLAGS) -DSampleCode=1 -c $*.C
command.o: command.C ../command.tex
interpreter.o: interpreter.C ../interpreter.tex
iterator.o: iterator.C ../iterator.tex
mediator.o: mediator.C ../mediator.tex
memento.o: memento.C ../memento.tex
observer.o: observer.C ../observer.tex
state.o: TCPClosed.C state.C ../state.tex
strategy.o: strategy.C ../strategy.tex
	-$(C++) $(C++FLAGS) -DConsequences1=1 -c $*.C
	-$(C++) $(C++FLAGS) -DConsequences2=1 -c $*.C
	-$(C++) $(C++FLAGS) -DImplementation=1 -c $*.C
	-$(C++) $(C++FLAGS) -DSampleCode=1 -c $*.C
visitor.o: visitor.C ../visitor.tex
	-$(C++) $(C++FLAGS) -DConsequences=1 -c $*.C
	-$(C++) $(C++FLAGS) -DImplementation=1 -c $*.C
	-$(C++) $(C++FLAGS) -DSampleCode=1 -c $*.C

depend:
	makedepend *.C $(C++FLAGS)



