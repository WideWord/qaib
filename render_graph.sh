#!/bin/zsh

mkdir graph

for i in {$1..$2}
do
  build/bin/qaib graph pop/$i.pop >graph/$i.dot
  dot -Tsvg graph/$i.dot -o graph/$i.svg
done

