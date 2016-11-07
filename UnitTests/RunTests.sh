# STYLES
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)
BOLD=$(tput bold)

# TERMINAL INFOS
TerminalWidth=$(tput cols)

# STATES
StringOK="[OK]"
ColorStringOK="${BOLD}${GREEN}${StringOK}${NORMAL}"
StringOKLength=${#StringOK}

StringError="[FAIL]"
ColorStringError="${BOLD}${RED}${StringError}${NORMAL}"
StringErrorLength=${#StringError}


SuccessfulTestReturn=1
ErrorTestReturn=0

# RUN
for Program in bin/*.exe
do
    ./$Program
    IsSuccessful=$?

    if [ "$IsSuccessful" -eq "$SuccessfulTestReturn" ]
    then
        PaddingWidth=$(($TerminalWidth - $StringOKLength - 1))
        printf "${GREEN}%-"$PaddingWidth"s${NORMAL} %s\n" $Program $ColorStringOK
    else
        PaddingWidth=$(($TerminalWidth - $StringOKLength - 3))
        printf "${RED}%-"$PaddingWidth"s${NORMAL} %s\n" $Program $ColorStringError
    fi
done
