#这个Makefile所做的事情仅仅是让ex19依赖于object.o。还记得make可以根据扩展名构建不同的文件吗？
#这相当于告诉make执行下列事情：
#当我运行make时，默认的all会构建ex19。
#当它构建ex19时，也需要构建object.o，并且将它包含在其中。
#make并不能找到object.o，但是它能发现object.c文件，并且知道如何把.c文件变成.o文件，所以它就这么做了。
#一旦object.o文件构建完成，它就会运行正确的编译命令，从ex19.c和object.o中构建ex19。
CFLAGS=-Wall -g

all: ex19

ex19: object.o

clean:
	-rm -f ex19
	-rm -f object.o
