objects	=	wcrt.o

wcrt	:	$(objects)
	cc	-o	wcrt	$(objects)

wcrt.o	:	wcrt.c	wcrt.h
	cc	-c	wcrt.c

.PHONY	:	clean
clean	:
	-rm	wcrt	$(objects)