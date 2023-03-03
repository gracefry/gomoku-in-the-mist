#!/bin/bash
# Make sure script is executable with chmod +x test_driver.sh. 
# Finally, run the script with ./test_driver.sh.

# Compile the gitm program
gcc -o gitm gitm.c

# Loop through all the .in files in the current directory
for test_input in tests/*.in; do

    # Get the corresponding .out file
    test_output=${test_input%.in}.out
    
    # Run the program with the test input and capture the output
    program_output=$(./gitm < "$test_input")
    
    # Compare the program output to the expected output
    if diff -q "$test_output" <(echo "$program_output"); then
        # If they are the same, the test passed
        echo "$test_input passed"
    else
        # If they are different, print the difference
        echo "$test_input failed:"
        diff "$test_output" <(echo "$program_output")
    fi
    
done

# Remove the gitm program
rm gitm
