#!/bin/bash


clear
YES=y
NO=n
echo "Welcome on 21sh"
echo "Hlely and Dquartin have pleasure to show you their shell"
echo "What is your login, new corrector ?"

read -p "enter your login> " LOGIN
echo
read -p "Ok, fine, your login is $LOGIN, right ?(y/n) " REP
if [ $REP = $NO ]
	then
		echo
		echo "Don't worry let's do it again"
	fi
echo -e "\n"
echo "Nice to meet you $LOGIN !"
echo "Hope you will enjoy our shell !"
