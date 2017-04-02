STQAM Project
=============

Contributors;
- Kevin James
- Lara Janecka
- Laura Stericker


Testing
=======
Execute `verify.sh`. Logs can be found in `/tmp` with names
`testing-<username>-pi-<time>.log`. Use `clean.sh` to run make clean in all
directories.

To generate the output of a single test, run `make` in that test's directory.
Your output should be identical to the 'gold' file, ie. `cat <output_file> |
sort | diff - gold_x_xx` should return no lines difference.

You can manually run `make debug` to see the output of building with debug
flags enabled.

Submission
==========
Organize the 'pi' directory such that we can run `make` inside it and generate
`pipair` in the same directory.

We will untar your submission, copy the contents of the pi directory, run `make`,
copy over the skeleton files and the full test suite with six tests, and then
run `verify.sh`.

Note that each test is given 2 minutes. My prototype runs test3 in 2 seconds
and test6 (not given to you) in 25 seconds, and all other tests in tens or
hundreds of milliseconds.
