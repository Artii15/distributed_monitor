all:
	mpic++ -Wall src/*.cpp src/communicators/*.cpp \
	src/exceptions/*.cpp src/synchronizer/*.cpp \
	src/synchronizer/messages/*.cpp \
	main.cpp \
	src/resources_synchronizer/*.cpp \
	src/resources_synchronizer/messages/*.cpp \
	src/example/*.cpp \
	-o main -lpthread
