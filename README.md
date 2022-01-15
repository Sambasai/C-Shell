Usage:

1. make
2. ./a.out
3. enter "quit" to exit the shell

Files and their respective functions:

* main.c        - contains the main functioning of the shell including printing the backgound process' exit status, shell prompt, signal handling functions (ctrl+C, ctrl+Z and ctrl+D)
* functions.h   - contains all the required headers and functions, it also contains global variables/arrays used across the files
* cd.c          - cd command (same as shell functionality)
* pinfo.c       - pinfo command 
* echo.c        - echo command (same as shell functionality)
* pwd.c         - pwd command (same as shell functionality)
* ls.c          - ls command (same as shell functionality)
* fgbg.c        - handling background and foreground processes for commands which are executed through execvp
* repeat.c      - repeat command
* bg.c          - Handles the bg functionality (Changes the state of a stopped background job to running)
* exec.c        - Contains the main execution of the shell commands (calls all individual functions)
* fg.c          - Handles the fg functionality (Brings the running or stopped background job to the foreground, and changes its state to running)
* ioredir.c     - Handles the basic input/output redirection (more related stuff in exec.c including piping+ioredir)
* jobs.c        - Implements jobs functionality (prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number)
* repeat.c      - Implements repeat functionality (h executes a particular command in fixed time interval for a certain period.)
* sig.c         - Implements sig functionality (Takes the job number of a running job and sends the signal corresponding to signal number to that process)

Assumptions: (apart from the assumptions made in assignment pdf)

- I have assumed reasonable lengths of commands and file/directory names.
- The ranges of limits vary from 100-1000 throughout the shell in various functions.
