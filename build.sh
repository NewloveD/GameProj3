# Output binary name
OUTPUT="maze.cgi"

# List all C++ source files
SRC="main.cpp function.cpp get_validate_input_protoMS.cpp"

# Compile the program
g++ -std=c++11 -o $OUTPUT $SRC

# Make it executable as a CGI script
chmod 755 $OUTPUT

echo "Build complete. Output file: $OUTPUT"
