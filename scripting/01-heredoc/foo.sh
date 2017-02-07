#!/bin/sh

foo="bar"
bar="foo"
date=$(date)

cat << EOF
foo is $foo
bar is $bar
date is $date
EOF
