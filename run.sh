
#!/bin/sh

CC="g++"
COMPILER_FLAGS="-Wall"
SOURCES="./src/*.c ./src/*.cpp"
LIBS="-lGL -ldl"
PROGRAM_NAME="gl"

Compile()
{
    $CC $COMPILER_FLAGS -I ./include/ `pkg-config --cflags glfw3` -o $PROGRAM_NAME $SOURCES `pkg-config --libs glfw3` $LIBS
}

Run()
{
    ./$PROGRAM_NAME
}

Clean()
{
    IS_EXECUTABLE_EXIST=$(ls -a -1 | grep -o $PROGRAM_NAME)
    if [ $IS_EXECUTABLE_EXIST == $PROGRAM_NAME ]; then
        EXECUTABLE_PATH=$(readlink -f $PROGRAM_NAME)
        echo -n "Remove executable : $EXECUTABLE_PATH"
        rm -f $PROGRAM_NAME
    fi
}

RunPrompt()
{
    echo -n "Compile first? (y/n) : "
    read RESULT
    case $RESULT in
        [yY]*   ) Compile && Run;;
        [nN]*   ) Run;;
        *   ) echo "Abort..."; exit;;
    esac
}

# --- Main --- #
if [ "$1" == "-c" ]; then
    Clean
else
    RunPrompt
fi

