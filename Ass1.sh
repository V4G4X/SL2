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
declare -A DEL_FLAG
declare N
let N=0
while [ "$FLAG" -eq "0" ]
do
    echo -e "\n1)Create\n2)View\n3)Insert\n4)Delete\n5)Modify\n6)Exit\n"
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
            echo -e -n "Enter the Deadstock No.: "
            read DEADSTOCK_NO[$i]
            echo -e -n "Enter the Order No.: "
            read ORDER_NO[$i]
            echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
            read TYPE[$i]
            let DEL_FLAG[$i]=0
            let i++
            done
        ;;
    "2") 
        echo "Viewing Database"
        echo -e "Displaying Database:\n"
        echo -e "ItemName\tDeadstock No.\tPurchase Order No.\tType"
        let i=0
        while [ "$i" -lt "$N" ]
        do
            if [ "${DEL_FLAG[$i]}" -eq "0" ]
            then
                echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
            fi
            let i++
        done
        ;;
    "3") echo "Inserting Record"
        let i=N
        echo -e -n "Enter the item Name: "
        read NAME[$i]
        echo -e -n "Enter the Deadstock No.: "
        read DEADSTOCK_NO[$i]
        echo -e -n "Enter the Order No.: "
        read ORDER_NO[$i]
        echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
        read TYPE[$i]
        let DEL_FLAG[$i]=0
        let N++
        ;;
    "4") echo "Deleting Record"
        echo -e "Enter the Purchase Order No."
        read PURNO
        let i=0
        while [ "$i" -lt "$N" ]
        do
            if [ "$PURNO" -eq "${ORDER_NO[$i]}" ]
            then
                echo -e "Deleting the following Record"
                echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
                let DEL_FLAG[$i]=1
                break 
            fi
            let i++
        done
        ;;
    "5") echo "Modifying Record"
        echo -e "Enter the Purchase Order No."
        read PURNO
        let i=0
        while [ "$i" -lt "$N" ]
        do
            if [ "$PURNO" -eq "${ORDER_NO[$i]}" ]
            then
                echo -e "Modifying the following Record"
                echo -e "${NAME[$i]}\t${DEADSTOCK_NO[$i]}\t${ORDER_NO[$i]}\t${TYPE[$i]}"
                echo -e -n "Enter the item Name: "
                read NAME[$i]
                echo -e -n "Enter the Deadstock No.: "
                read DEADSTOCK_NO[$i]
                echo -e -n "Enter the Order No.: "
                read ORDER_NO[$i]
                echo -e -n "Enter the item Type(Consumable/NonConsumable)\nEnter 0 for Consumable, 1 for Non-Consumable: "
                read TYPE[$i]
                let DEL_FLAG[$i]=0
                break 
            fi
            let i++
        done
        ;;
    "6") echo "Exiting"
        echo "Thank You for Using our Services"
        FLAG=1
        ;;
    *) echo "Incorrect Input Perhaps, Try again"
        ;;
    esac
done