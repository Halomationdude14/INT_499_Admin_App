
# INT 499 Admin App Overview


**WARNING**: *App is not complete! Contains partial functionality!*


# Introduction

This is a simple terminal application written in C++ that allows users to manipulate data on a locally stored MySQL server.
The application uses the MySQL Connector/C++ to interact with the database, providing basic CRUD (Create, Read, Update, Delete) functionality.
There is very little information online on how to use the devxapi library, so this was partially intended to serve as a guide on how to use more recent versions of the MySQL Connector/C++ dependency.

I created this app based on the work done in my capstone course in college.
I created a simple C++ terminal program that added "movie data" to a fictional database in the first week.
I spent the next 4 weeks developing a MySQL database for a fictional company called "EZTechMovie".
During this project, I discovered the MySQL Connector/C++ dependency which is where I got the idea for this application.
After graduation, I started creating this app just to see if I could. It took much longer than anticipated, but I ended up learning a LOT from it.

To anyone who finds this sandbox/hobby project helpful in any way, let me know!  
Any recommendations for the app are very welcome too!


# Features

* Connect to a local MySQL database
* Read and display records from the database
* Create new records in the database
* (future*) Update existing records
* (future*) Delete records


# Prerequisites

Before you run the application, you'll need to install and set up a MySQL server locally on your machine.  
Create a database on the MySQL server and name it "eztechmoviedb".  
Use the scripts attached to this repository to configure the newly created database.


# Contributing

Contributions are welcome! Please fork the repository and create a pull request with your changes. For major changes, please open an issue first to discuss what you would like to change.


# Additional Notes

The app is only designed to work with locally installed MySQL servers, but can easily be reworked to connect to remote MySQL servers.  
The app was developed to support Windows computers but should work on other OSs like Linux or MacOS (not tested*).

