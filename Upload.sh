#!/bin/bash

verif() #Verify we are inside a platformio folder
{
    [[ -f platformio.ini ]] && [[ -d .pio ]] 
    echo "all is good"
}

Set_lang() #Set the keymap
{
    cat << "EOF"
|==========================================
|        .--.                   .---.     |
|    .---|__|           .-.     |~~~|     |
| .--|===|--|_          |_|     |~~~|--.  |
| |  |===|  |'\     .---!~|  .--|   |--|  |
| |%%|   |  |.'\    |===| |--|%%|   |  |  |
| |%%|   |  |\.'\   |   | |__|  |   |  |  |
| |  |   |  | \  \  |===| |==|  |   |  |  |
| |  |   |__|  \.'\ |   |_|__|  |~~~|__|  |
| |  |===|--|   \.'\|===|~|--|%%|~~~|--|  |
| ^--^---'--^    `-'`---^-^--^--^---'--'  |
===========================================
|               SETUP LOCAL               |
===========================================
EOF
    sleep 2
    echo "------------------------------------------"
    echo "  Select your locale:"
    echo "------------------------------------------"
    echo "  1. en_US     5. be_BE     9. da_DK"
    echo "  2. en_UK     6. es_ES     10. pt_PT"
    echo "  3. de_DE     7. fi_FI     11. tr_TR"
    echo "  4. fr_FR     8. cz_CZ     12. it_IT"
    echo "  13. sv_SE                 99. Main"
    echo "------------------------------------------"
    echo "Choose your local :"
    read loc
    case $loc in
        1)
        locale=en_US
        ;;
        2)
        locale=en_UK
        ;;
        3)
        locale=de_DE
        ;;
        4)
        locale=fr_FR
        ;;
        5)
        locale=be_BE
        ;;
        6)
        locale=es_ES
        ;;
        7)
        locale=fi_FI
        ;;
        8)
        locale=cz_CZ
        ;;
        9)
        locale=da_DK
        ;;
        10)
        locale=pt_PT
        ;;
        11)
        locale=tr_TR
        ;;
        12)
        locale=it_IT
        ;;
        13)
        locale=sv_SE
        ;;
        99)
        ./Upload.sh
        ;;
        *)
        Set_lang
        
    esac
    
    pio lib install &> /dev/null

    echo "Removing Keyboard.cpp"
    rm .pio/libdeps/micro/Keyboard/src/Keyboard.cpp
    sleep 1

    echo "Generate locale"
    cat keymap/Keyboard1.cpp keymap/$locale.lang keymap/Keyboard2.cpp >> .pio/libdeps/micro/Keyboard/src/Keyboard.cpp
    sleep 1
    ./Upload.sh
}

build() #Build only and check error
{
    cat << "EOF"
======================================
|             _   ,--()              |
|            ( )-'-.------|>         |
|             "     `--[]            |
======================================
EOF
    echo 
    sleep 2
    pio run
}

upload() #Upload the firmware on the card
{
    cat << "EOF"
======================================
|           __                       |
|           | \                      |
|           =[_|h)--._____           |
|           =[+--,-------'           |
|           [|_/""                   |
|                                    |
======================================
EOF
    sleep 2
    pio run --target upload
}

main() #Main loop
{
    cat << "EOF"
======================================
|          _               _         |
|      ___(.)>   CUACK   <(.)___     |
|      \____)             (____/     |
|                                    |
|                                    |
======================================
EOF

verif
printf "Please select what you want to do"
echo
echo
printf "1): Set Lang\n2): Build\n3): Upload\n4): Exit\n"
printf "Enter the number of the task : " 
read task

case "$task" in
    1)
    Set_lang
    ;;
    2)
    build
    ;;
    3)
    upload
    ;;
    4)
    ;;
    *)
    echo "You need to enter a correct option (1, 2 , 3)"
    main
    ;;
esac
}

main

