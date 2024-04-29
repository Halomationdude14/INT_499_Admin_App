
##################################################################################################

########## Admin App Overview ##########

NOTE: (*) indicates that this feature has not been fully implemented yet in the MySQL database.

[Bootup_Screen] When program is initially started, user is greeted with...
	a. Company Logo
	b. Message "EZTechMovie Database Administration Console"
	c. Message "Enter Admin Credentials to Log Into the Console -->"
	d. Prompt: {Username/Email: }
	e. Prompt: {Password: }
	- NOTE: 1st version will not perform any type of user/pass validation (except to verify that at least 1 char was entered by the user). Will accept any input.
	- NOTE: Upon pressing <ENTER>, login screen is cleared and Main_Menu is displayed.
	- NOTE: Add a feature that allows the user to quit the application via a single button at any point in time. Display this on the screen.

[Main_Menu] User is provided with a list of options in numerical format.
	[1] Display Data
	[2] Modify Data
	[3] Admin Account
	[4] Sign Out

[Display_Data]
	[1] Movies
	[2] Plans
	[3] Customers
	[4] Error Logs*
	[\] Back

[Display_Movies] Displays list of each movie by title, year, and genre.
	[1] Select Movie by ID
		[`] Swap Mode (Display/Edit)
		[\] Back
	[\] Back

[Display_Plans] Display all available plans.
	[`] Swap Mode (Display/Edit)
	[\] Back

[Display_Customers] Display customer's ID, full name(*), plan title, and membership start date.
	[1] Select Customer by ID
		[`] Swap Mode (Display/Edit)
		[\] Back
	[\] Back

[Display_Error_Logs*] Display all error logs with timestamps.
	[`] Swap Mode (Display/Edit)
	[\] Back

[Modify_Data]
	[1] Movies
	[2] Plans
	[3] Customers
	[4] Error Logs*
	[\] Back

[Modify_Movies] Displays list of each movie by title, year, and genre.
	[1] Select Movie by ID
		[1] Edit Movie Info
		[2] Delete Movie
		[`] Swap Mode (Display/Edit)
		[\] Back
	[2] Add Movie
	[\] Back

[Modify_Plans] Display all available plans.
	[1] Select Plan by ID
		[1] Edit Plan Info
		[2] Delete Plan
		[\] Back
	[2] Add Plan
	[`] Swap Mode (Display/Edit)
	[\] Back

[Modify_Customers] Display customer's ID, full name(*), plan title, and membership start date.
	[1] Select Customer by ID
		[1] Edit Customer Info
		[2] Delete Customer
		[`] Swap Mode (Display/Edit)
		[\] Back
	[2] Add Customer
	[\] Back

[Modify_Error_Logs*] Display all error logs with timestamps.
	[1] Delete Log by ID
	[2] Delete All Logs
		[Confirmation Dialog]
		[Y] Yes
		[N] No
	[`] Swap Mode (Display/Edit)
	[\] Back

[Admin_Account]
	[1] Display Account Information
	[2] Modify Account Information
	[\] Back

[Account_Display]
	[Provide Password Again]
	[Display Account Info]
	[`] Swap Mode (Display/Edit)
	[\] Back

[Account_Modify]
	[Provide Password Again]
	"What Would You Like to Change?"
	[1] Username
	[2] Password
	[3] Email
	[`] Swap Mode (Display/Edit)
	[\] Back


##################################################################################################

########## Additional Notes ##########

1. For the MySQL DB scripts, need to add additional triggers.
	a. Handle the relations of movies, actors, and directors when a movie is removed from the DB.
	b. Prevent the removal of an actor/director if there is a movie that is linked to them.
2. May need to add procedures to work in tandem with the C++ code.
3. Need to create a table to store deleted customers.
4. IDEA: Provide functionality - Allow user to toggle between Display Mode and Edit Mode.
	- Could use [`] as the toggle button.
	- Default mode is "Display".
	- Display "Confirm Changes?" dialog when modifying data to prevent accidental mistakes.
5. Add table to store Admin user credentials.
