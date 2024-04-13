#ifndef SHELL_HEADER_H  // Replace with your unique guard name
#define SHELL_HEADER_H

typedef char * token;

#define PATH_ENV "PATH"

// PATH
// bash script.sh -c -y -x -> tokens=[bash, script.sh, -x, -y, -z]
// search for bash in PATH and current directory
// fork -> parent, child
// child -> exec(absolute path of executable file found with path, tokens)
// parent -> wait(NULL)
// user use & -> bash script.sh &
// parent doesn't wait for child to finish. Prompt for next command.
// user uses redirection -> bash script.sh > out.txt
// TODO

#endif
