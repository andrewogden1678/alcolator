# Alcolator
### BAC Calculation in Laboratory Environments
## 1. Install the Prerequisites

Install the prerequisites from [here](https://docs.ultralig.ht/docs/installing-prerequisites) (Windows).

## 2. Clone and setup

Clone the application to your computer and create a build folder:

```shell
cd (path)/Alcolator
mkdir build
```

## 3. Run the application

Execute the `run.sh` file to build and run the solution.

## Mr N Instructions 1st August

Ready to test!

Process is no different than before, however I have emailed you a new sqlite3 folder.
Replace the contents of `include/sqlite3` with the files inside the zip folder.

After that, the run process is the same as before, just click on the run.sh file. It will handle the building, copying of dependencies and running of the program.

The login button will proceed to the main page. From there, I have (temporarily) mapped the 'file' button to a listener that lists the current Subjects in the database down the sidebar. The close buttons also work.

I have also fixed the compiler to always compile to 64 bit. Sometimes I found it was actually compiling a 32 bit binary which was causing all sorts of problems :).

Let me know if there are any issues. Also let me know if you would like a copy of the small console program I wrote to test my SQLite interface if you want to play around with the functionality I have implemented.

Hope you like so far :).

*Created by Andrew Ogden (2020).*
