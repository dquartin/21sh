#!/bin/bash

read -p "Please enter your commit :" COMMIT

git add *[.ch]
git commit -m "$COMMIT"
git push
