#!/bin/sh
set -eu

g++ -std=c++17 -Wall -Wextra -pedantic main.cpp factory_creator.cpp -o /tmp/factory_flow_test_app
output=$(printf '1\nblue\nwhite\n5\n' | /tmp/factory_flow_test_app)

printf '%s\n' "$output" | grep -F 'Welcome to the Factory.'
printf '%s\n' "$output" | grep -F 'Available colors: black, red, green, yellow, blue, magenta, cyan, white, gray, purple, orange.'
printf '%s\n' "$output" | grep -F 'Box preview'
if printf '%s\n' "$output" | grep -F 'Line thickness:'; then
  exit 1
fi

empty_output=$(printf '' | /tmp/factory_flow_test_app)
printf '%s\n' "$empty_output" | grep -F 'Input ended. The factory is closing.'
