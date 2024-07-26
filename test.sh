#!/bin/bash
zf_set() {
  if [ -z "$2" ]; then
    # it's not in zf_set x y form - try zf_set x=y
    VAR=$(echo "$1" | cut -f1 -d=)
    VAL=$(echo "$1" | cut -f2 -d=)
  else
    VAR="$1"
    VAL="$2"
  fi

  echo $VAR=$VAL
}

if [ -f $1 ]; then
  . $1 $2
fi
