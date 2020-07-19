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

## Mr N Instructions 19th July

I have pushed a modified version to make it easier for you to test.

To load each of the views, all you need to do is replace the view controller in line 23 of Alcolator.cpp. 

```23: nextView_.reset(new LoginView(*window_.get()));```

LoginView, MainView and AdminView are all valid controllers. (Polymorphism to the rescue :P)

Inside MainView and AdminView I have included commented-out 'LoadURL' lines with instructions. This is so you can load the other html files (such as main_bacmode, main_viewmode and admin_view) which will eventually become responsive using Vue.JS, eliminating the need for multiple files. 

I still need to deal with event handlers, so at the moment nothing will be clickable, moveable or closable. Alt+F4 is perfectly fine for the moment, or right clicking and closing the instance in the task bar. Make sure the console also closes.

Due to odd SDK behaviour (which I have reported), I advise you clear the contents of the build folder before the first time you build. For subsequent compilations of the solution you should have no trouble; the run.sh file will work as advertised.

Let me know if there are any issues.

*Created by Andrew Ogden (2020).*
