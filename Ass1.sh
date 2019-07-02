#!/bin/sh
# Batch: K9 Assignment 1: Shell Programming
# Expected to perform following operations on the DB: 1)Create,2) View, 3)Insert,4) Delete,5)Modify,6)Exit
# 17	33117	Stock Records	Item Name, Deadstock No., Purchase Order No.,Type(Consumable/NonConsumable)

echo "Welcome To Stock Records Database"
FLAG=0
declare -A NAME
declare -A DEADSTOCK_NO
declare -A ORDER_NO
declare -A TYPE
declare N
while [ "$FLAG" -eq "0" ]
do
    echo -e "\n1)Create\n2)View\n3)Insert\n4)Delete\n5)Modify\n6)Exit"
    echo -e -n "Enter Choice: "
    read CHOICE
    case "$CHOICE" in 
    "1") echo "Creating New Database"
        echo -e -n "Enter the number of records you will enter: "
        read N
        i=0
        while [ "$i" -lt "$N" ]
        do
            echo "Item No. $[i+1]"
            echo -e -n "Enter the item Name: "
            read NAME[$i]
            # echo "${NAME[$i]}"
            echo -e -n "Enter the Deadstock No.: "
            read DEADSTOCK_NO[$i]
            echo -e -n "Enter the Order No.: "
            read ORDER_NO[$i]
            echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
            read TYPE[$i]
            let i++
            done
        ;;
    "2") 
        echo "Viewing Database"
        echo -e "Displaying Database:\n"
        echo -e "ItemName\tDeadstock No.\tPurchase Order No.\tType"
        i=0
        while [ "$i" -lt "$N" ]
        do
            echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
            let i++
        done
        ;;
    "3") echo "Inserting Record"
        let i=N
        echo -e -n "Enter the item Name: "
        read NAME[$i]
        # echo "${NAME[$i]}"
        echo -e -n "Enter the Deadstock No.: "
        read DEADSTOCK_NO[$i]
        echo -e -n "Enter the Order No.: "
        read ORDER_NO[$i]
        echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
        read TYPE[$i]
        let N++
        ;;
    "4") echo "Deleting Record"
        echo -e "Enter the "
        ;;
    "5") echo "Modifying Record"
        ;;
    "6") echo "Exiting"
        FLAG=1
        ;;
    esac
done