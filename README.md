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

## 3. Build & run the application

Execute the `build.sh` file first, then the `run.sh` file to run the solution.

## Mr N Instructions 8th August

Here's this week's effort. Solution is effectively feature complete.

The process has barely changed. Take the include folder I sent you on Canvas and extract it into the root directory. (like alcolator/include/).
After that, create a 'build' folder in the root directory if it is not already there, build the solution using 'build.sh' and then you can run it with 'run.sh'. The shell scripts will take care of everything.

Only things missing are the ability to generate reports (not hard to do according to a google search) and the minimise button functionality. 

I have made you a user account with Administrator permissions. Details are below:

```
Username: t.nguyen
Password: tnguyen123
```

As an administrator you can switch between the admin panel and the experimenting panel. Click 'Experimenter' under the 'file' menu to switch to experimenting mode, and 'Administration' to do the reverse inside the experimenting panel. Data manipulation, calculation, searching, sorting, permissions logic, password security, you name it, it's been done :).

The app's main task is to assist research involving alcohol in a laboratory environment. The idea is to make it easier for researchers to calculate a predicted amount of alcohol to give someone for them to reach a certain BAC. The BAC that they will target will never be greater than 0.15. The calculator specifies alcohol volume not only in grams, but also in mls of a beverage type specified by the experimenter. After administering the alcohol to the subject, the experimenter is able to then add their actual recorded BAC. According to my client, subject codes will likely be in a 4-5 digit numeric form, with the experiment code at the beginning. I have factored that into the display.

Hope you like it!

*Created by Andrew Ogden (2020).*
