
##### Clear the DB for testing purposes #####

SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS tbl_plans;
DROP TABLE IF EXISTS tbl_actors;
DROP TABLE IF EXISTS tbl_moviecast;
DROP TABLE IF EXISTS tbl_directors;
DROP TABLE IF EXISTS tbl_moviedirectors;
DROP TABLE IF EXISTS tbl_moviedata;
DROP TABLE IF EXISTS tbl_genredata;
DROP TABLE IF EXISTS tbl_moviegenres;
DROP TABLE IF EXISTS tbl_custdata;
DROP TABLE IF EXISTS tbl_paymentinfo;
DROP TABLE IF EXISTS tbl_custactivity_stream;
DROP TABLE IF EXISTS tbl_custactivity_dvd;
DROP TABLE IF EXISTS tbl_dvdrentalhistory;
DROP TABLE IF EXISTS tbl_familyMembers;

DROP TRIGGER IF EXISTS after_custAddPayMethod;
DROP TRIGGER IF EXISTS before_custRemovePayMethod;
DROP TRIGGER IF EXISTS before_custAddDevice;
DROP TRIGGER IF EXISTS after_custAddDevice;
DROP TRIGGER IF EXISTS after_custRemoveDevice;
DROP TRIGGER IF EXISTS before_custRentDVD;
DROP TRIGGER IF EXISTS after_custRentDVD;
DROP TRIGGER IF EXISTS after_custReturnDVD;
DROP TRIGGER IF EXISTS before_custAddFamMem;
DROP TRIGGER IF EXISTS after_custChangePlanType_FamilyToOther;

SET FOREIGN_KEY_CHECKS = 1;


##### CREATE Tables #####

/*
* Table contains all 6 possible plan options based on "planService" and "planType".
*/
CREATE TABLE IF NOT EXISTS tbl_plans (
    planID INT NOT NULL AUTO_INCREMENT,
    planService VARCHAR(20) NOT NULL COMMENT 'Stream or DVD',
    planType VARCHAR(20) NOT NULL COMMENT 'Individual, Friendly, or Family',
    maxActivity INT NOT NULL COMMENT 'Indicates how many devices a customer may stream to, or how many DVDs a customer may rent at one time,',
    pricePerMonth DOUBLE NOT NULL,
    PRIMARY KEY(planID)
);

/*
* Table contains list of all main cast members from all movies in the DB.
*/
CREATE TABLE IF NOT EXISTS tbl_actors (
    actorID INT NOT NULL AUTO_INCREMENT,
    actor_Fname VARCHAR(50) NOT NULL,
    actor_Mname VARCHAR(50),
    actor_Lname VARCHAR(50) NOT NULL,
    PRIMARY KEY(actorID)
);

/*
* Table associates each movie with its primary cast members.
*/
CREATE TABLE IF NOT EXISTS tbl_moviecast (
    movieID int NOT NULL,
    actorID int NOT NULL,
    PRIMARY KEY(movieID, actorID)
);

/*
* Table contains list of all directors associated with all movies in the DB.
*/
CREATE TABLE IF NOT EXISTS tbl_directors (
    directorID int NOT NULL AUTO_INCREMENT,
    director_Fname VARCHAR(50) NOT NULL,
    director_Mname VARCHAR(50),
    director_Lname VARCHAR(50) NOT NULL,
    PRIMARY KEY(directorID)
);

/*
* Table associates each movie with its director(s).
*/
CREATE TABLE IF NOT EXISTS tbl_moviedirectors (
    movieID int NOT NULL,
    directorID int NOT NULL,
    PRIMARY KEY(movieID, directorID)
);

/*
* Contains a list of all available movies.
*/
CREATE TABLE IF NOT EXISTS tbl_moviedata (
    movieID INT NOT NULL AUTO_INCREMENT,
    movieTitle VARCHAR(100) NOT NULL,
    movieYear INT NOT NULL,
    numCast INT NOT NULL,
    movieRating VARCHAR(20) NOT NULL,
    PRIMARY KEY(movieID)
);

/*
* Contains all genres related to our movies.
*/
CREATE TABLE IF NOT EXISTS tbl_genredata (
    genreID INT NOT NULL AUTO_INCREMENT,
    genreTitle VARCHAR(100) NOT NULL,
    PRIMARY KEY(genreID)
);

/*
* Associates each movie with a single genre.
*/
CREATE TABLE IF NOT EXISTS tbl_moviegenres (
    movieID INT NOT NULL,
    genreID INT NOT NULL,
    PRIMARY KEY(movieID, genreID)
);

/*
* Contains a list of all customers.
* For [custPlan] + [custPlanType] --> Not set NULL because members may cancel subscriptions at any time.
* For [payType] --> May be NULL; new customers who haven't signed up for a plan yet + customers may wish to remove old payment method to add a new one.
*                   This requires temporarily deleting the old one which leaves this value NULL.
*/
CREATE TABLE IF NOT EXISTS tbl_custdata (
    custID BIGINT NOT NULL AUTO_INCREMENT,
    custUser VARCHAR(30) NOT NULL,
    custPW VARCHAR(30) NOT NULL,
    custEmail VARCHAR(50) NOT NULL,
    planID INT COMMENT 'Stream = 1,2,3 | DVD = 4,5,6',
    activity INT COMMENT 'Number of active DVD rentals/Streaming devices',
    payType VARCHAR(20) COMMENT 'Credit or Debit',
    memStartDate varchar(20) NOT NULL COMMENT 'Format = mm/dd/yyyy',
    PRIMARY KEY(custID)
);

/*
* Payment methods include: Credit or Debit.
* NOTE: Not all existing customers will have a payment method set up.
*/
CREATE TABLE IF NOT EXISTS tbl_paymentinfo (
    custID BIGINT NOT NULL,
    cardNum BIGINT NOT NULL,
    expDate VARCHAR(10) NOT NULL COMMENT 'Format = "mm/yyyy"',
    CVV INT NOT NULL COMMENT 'Format = 3 to 4 digit number',
    Lender VARCHAR(50) NOT NULL COMMENT 'List the name of the issuer/lender for your credit card',
    nameOnCard VARCHAR(20) NOT NULL COMMENT 'List the name of the cardholder as seen on the card',
    payType VARCHAR(10) NOT NULL COMMENT 'Credit or Debit',
    PRIMARY KEY(custID, cardNum)
);

/*
* Table to keep track of customer's active streaming devices.
*/
CREATE TABLE IF NOT EXISTS tbl_custactivity_stream (
    custID BIGINT NOT NULL,
	deviceUUID VARCHAR(50) NOT NULL,
    PRIMARY KEY(custID,deviceUUID)
);

/*
* Table to keep track of customer's active DVD rental.
*/
CREATE TABLE IF NOT EXISTS tbl_custactivity_dvd (
    custID BIGINT NOT NULL,
	movieID INT NOT NULL,
    PRIMARY KEY(custID,movieID)
);

/*
* Table to keep track of which movies each customer has rented this month.
* NOTE: Realistically, this table would be cleared at midnight on the last day of every month.
*       I would imagine there would be another table that records every movie in the DB that each user has watched along with the date that the movie was last watched.
*       I do not have the time to implement such a feature, but we can use our imagination and pretend that it exists (:D).
*/
CREATE TABLE IF NOT EXISTS tbl_dvdrentalhistory (
    custID BIGINT NOT NULL,
    movieID INT NOT NULL,
    returnDate VARCHAR(20) NOT NULL,
    PRIMARY KEY(custID,movieID)
);

/*
* Table to keep track of family groups.
* If a customer is subscribed to either the DVD or Streaming Family plan, they can have up to 5 other members join their subscription.
*/
CREATE TABLE IF NOT EXISTS tbl_familyMembers (
    planManagerID BIGINT NOT NULL,
    famMemID BIGINT NOT NULL,
    PRIMARY KEY(famMemID)
);


##### Alter Tables with FOREIGN Keys #####

ALTER TABLE tbl_moviecast
ADD FOREIGN KEY(movieID)
REFERENCES tbl_moviedata(movieID)
ON DELETE CASCADE;

ALTER TABLE tbl_moviecast
ADD FOREIGN KEY(actorID)
REFERENCES tbl_actors(actorID)
ON DELETE CASCADE;

ALTER TABLE tbl_moviedirectors
ADD FOREIGN KEY(movieID)
REFERENCES tbl_moviedata(movieID)
ON DELETE CASCADE;

ALTER TABLE tbl_moviedirectors
ADD FOREIGN KEY(directorID)
REFERENCES tbl_directors(directorID)
ON DELETE CASCADE;

ALTER TABLE tbl_moviegenres
ADD FOREIGN KEY(movieID)
REFERENCES tbl_moviedata(movieID)
ON DELETE CASCADE;

ALTER TABLE tbl_moviegenres
ADD FOREIGN KEY(genreID)
REFERENCES tbl_genredata(genreID)
ON DELETE CASCADE;

ALTER TABLE tbl_paymentinfo
ADD FOREIGN KEY(custID)
REFERENCES tbl_custdata(custID)
ON DELETE CASCADE;

ALTER TABLE tbl_custdata AUTO_INCREMENT=1001;

ALTER TABLE tbl_custdata
ADD FOREIGN KEY(planID)
REFERENCES tbl_plans(planID)
ON DELETE CASCADE;

ALTER TABLE tbl_custactivity_stream
ADD FOREIGN KEY(custID)
REFERENCES tbl_custdata(custID)
ON DELETE CASCADE;

ALTER TABLE tbl_custactivity_dvd
ADD FOREIGN KEY(custID)
REFERENCES tbl_custdata(custID)
ON DELETE CASCADE;

ALTER TABLE tbl_custactivity_dvd
ADD FOREIGN KEY(movieID)
REFERENCES tbl_moviedata(movieID)
ON DELETE CASCADE;

ALTER TABLE tbl_dvdrentalhistory
ADD FOREIGN KEY(custID)
REFERENCES tbl_custdata(custID)
ON DELETE CASCADE;

ALTER TABLE tbl_dvdrentalhistory
ADD FOREIGN KEY(movieID)
REFERENCES tbl_moviedata(movieID)
ON DELETE CASCADE;

ALTER TABLE tbl_familyMembers
ADD FOREIGN KEY(planManagerID)
REFERENCES tbl_custdata(custID)
ON DELETE CASCADE;

ALTER TABLE tbl_familyMembers
ADD FOREIGN KEY(famMemID)
REFERENCES tbl_custdata(custID)
ON DELETE CASCADE;


##### Add TRIGGERS To Tables #####

# When a customer adds a payment method to [tbl_paymentinfo], must include payment type in [tbl_custdata].
CREATE TRIGGER IF NOT EXISTS after_custAddPayMethod
    AFTER INSERT ON tbl_paymentinfo
    FOR EACH ROW
BEGIN
    UPDATE tbl_custdata SET payType = NEW.payType
        WHERE tbl_custdata.custID = NEW.custID;
END;

# Before a payment method is removed from customer's account, update [tbl_custdata].
# Also removes the customer's planID if it exists.
CREATE TRIGGER IF NOT EXISTS before_custRemovePayMethod
    BEFORE DELETE ON tbl_paymentinfo
    FOR EACH ROW
BEGIN
    UPDATE tbl_custdata SET payType = NULL
        WHERE tbl_custdata.custID = OLD.custID;
    UPDATE tbl_custdata SET planID = NULL
        WHERE tbl_custdata.custID = OLD.custID;
END;

/*
* When a customer adds a new streaming device, verify they have not exceeded their plan limit.
* If within plan limit, allow insertion and update [activity] (+1) in [tbl_custdata].
* If exceeding plan limit, delete entry (activity -1).
*/
CREATE TRIGGER IF NOT EXISTS before_custAddDevice
    BEFORE INSERT ON tbl_custactivity_stream
    FOR EACH ROW
BEGIN
	SET @planMax = (SELECT maxActivity FROM tbl_plans
	JOIN tbl_custdata ON tbl_custdata.planID = tbl_plans.planID
    WHERE tbl_custdata.custID = NEW.custID);

	SET @newActivity = (SELECT activity FROM tbl_custdata WHERE custID = NEW.custID) + 1;
    SET @custPlan = (SELECT planID FROM tbl_custdata WHERE custID = NEW.custID);

    # If customer has not signed up for a plan, they cannot stream to a device.
    IF (@custPlan IS NULL) THEN
        SET @err_msg = CONCAT('ERROR: Customer ', NEW.custID, ' has not signed up for a plan yet. Cannot stream to device.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
    END IF;
	
	# If customer has reached their limit, mark entry for deletion by setting [deviceUUID] to an empty string.
    IF (@newActivity > @planMax) THEN
        SET @err_msg = CONCAT('ERROR: Customer ', NEW.custID, ' is attempting to streaming to ', @newActivity, ' devices. Their plan only allows a max of ', @planMax, ' devices.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
	END IF;
END;

/*
* When a customer adds a streaming device to their account, update [activity] (+1) in [tbl_custdata].
*/
CREATE TRIGGER IF NOT EXISTS after_custAddDevice
    AFTER INSERT ON tbl_custactivity_stream
    FOR EACH ROW
BEGIN
    UPDATE tbl_custdata SET activity = (activity + 1) WHERE custID = NEW.custID;
END;

/*
* When a customer removes a streaming device from their account, update [activity] (-1) in [tbl_custdata].
*/
CREATE TRIGGER IF NOT EXISTS after_custRemoveDevice
    AFTER DELETE ON tbl_custactivity_stream
    FOR EACH ROW
BEGIN
    UPDATE tbl_custdata SET activity = (activity - 1) WHERE custID = OLD.custID;
END;

/*
* When a customer rents a DVD, verify they have not exceeded their plan limit.
* If within plan limit, allow insertion and update [activity] (+1) in [tbl_custdata].
* If exceeding plan limit, delete entry (activity -1).
*/
CREATE TRIGGER IF NOT EXISTS before_custRentDVD
    BEFORE INSERT ON tbl_custactivity_dvd
    FOR EACH ROW
BEGIN
	SET @planMax = (SELECT maxActivity FROM tbl_plans
	JOIN tbl_custdata ON tbl_custdata.planID = tbl_plans.planID
    WHERE tbl_custdata.custID = NEW.custID);

	SET @newActivity = (SELECT activity FROM tbl_custdata WHERE custID = NEW.custID) + 1;
	SET @custPlan = (SELECT planID FROM tbl_custdata WHERE custID = NEW.custID);

    # If customer has not signed up for a plan, they cannot rent a DVD.
    IF (@custPlan IS NULL) THEN
        SET @err_msg = CONCAT('ERROR: Customer ', NEW.custID, ' has not signed up for a plan yet. Cannot rent movie.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
    END IF;

	# Check if the customer has the DVD-Individual plan.
	IF (@custPlan = 4) THEN
		# If customer has already rented a DVD this month, delete entry.
		IF EXISTS (SELECT * FROM tbl_custactivity_dvd WHERE custID = NEW.custID) OR
		EXISTS (SELECT * FROM tbl_dvdrentalhistory WHERE custID = NEW.custID) THEN
			SET @err_msg = CONCAT('ERROR: Customer ', NEW.custID, ' cannot rent another movie. DVD-Individual plan only allows 1 movie rental per month.');
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
		END IF;
	END IF;
	
	# If customer has reached their limit, delete entry.
    IF (@newActivity > @planMax) THEN
        SET @err_msg = CONCAT('ERROR: Customer ', NEW.custID, ' cannot rent another movie. Renting ', @newActivity, ' movies exceeds plan limit of ', @planMax, ' rentals.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
	END IF;
END;

/*
* When a customer rents a DVD, update [activity] (+1) in [tbl_custdata].
*/
CREATE TRIGGER IF NOT EXISTS after_custRentDVD
    AFTER INSERT ON tbl_custactivity_dvd
    FOR EACH ROW
BEGIN
    UPDATE tbl_custdata SET activity = (activity + 1) WHERE custID = NEW.custID;
END;

/*
* When a customer returns a DVD, update [activity] (-1) in [tbl_custdata].
*/
CREATE TRIGGER IF NOT EXISTS after_custReturnDVD
    AFTER DELETE ON tbl_custactivity_dvd
    FOR EACH ROW
BEGIN
    SET @returnDate = CURDATE();
    SET @returnDate = DATE_FORMAT(@returnDate,'%m/%d/%Y');
    UPDATE tbl_custdata SET activity = (activity - 1) WHERE custID = OLD.custID;
    INSERT INTO tbl_dvdrentalhistory VALUES (OLD.custID,OLD.movieID,@returnDate);
END;

/*
* Before adding an existing customer to a family plan, verify the following:
*   Plan-Manager must be subscribed to a plan.
*   Plan-Manager plan must be "family" type.
*   Plan-Manager cannot add themselves to their own plan.
*   Family-Member cannot be a part of more than one family plan.
*   Family-Member cannot be subscribed to a plan.
*/
CREATE TRIGGER IF NOT EXISTS before_custAddFamMem
    BEFORE INSERT ON tbl_familyMembers
    FOR EACH ROW
BEGIN
    SET @custPlan = (SELECT planID FROM tbl_custdata WHERE custID = NEW.planManagerID);
    SET @currFamMems = (SELECT COUNT(*) FROM tbl_familyMembers WHERE planManagerID = NEW.planManagerID);
    SET @memberPlan = (SELECT planID FROM tbl_custdata WHERE custID = NEW.famMemID);

    # If customer has not signed up for a plan, they cannot stream to a device.
    IF (@custPlan IS NULL) THEN
        SET @err_msg = CONCAT('ERROR: Customer ', NEW.planManagerID, ' has not signed up for a plan yet. Cannot add family member.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
    END IF;

    # If customer is subscribed to a plan, but the plan is not "family" type, they cannot add members to existing subscription.
    IF NOT (@custPlan = 3 OR @custPlan = 6) THEN
        SET @err_msg = CONCAT('ERROR: Customer ', NEW.planManagerID, ' is not subscribed to a family plan. Cannot add family member.');
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
    ELSE
        # Prevents customers from adding themselves as a family member.
        IF (NEW.planManagerID = NEW.famMemID) THEN
            SET @err_msg = CONCAT('ERROR: Customer ', NEW.planManagerID, ' attempted to add themselves as a family member to their own plan. Action rejected.');
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
        END IF;

        # Prevents customers from adding more than 5 family members to their subscription.
        IF (@currFamMems = 5) THEN
            SET @err_msg = CONCAT('ERROR: Customer ', NEW.planManagerID, ' has 5 family members linked to their plan. Cannot add another family member.');
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
        END IF;

        # Prevents family member from being added if they're linked to a different family plan.
        IF EXISTS (SELECT * FROM tbl_familyMembers WHERE famMemID = NEW.famMemID) THEN
            SET @err_msg = CONCAT('ERROR: Member ', NEW.famMemID, ' cannot be added to family plan. They are linked to a different family plan.');
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
        END IF;

        # Prevents family member from being added if they are subscribed to any plan.
        IF NOT (@memberPlan IS NULL) THEN
            SET @err_msg = CONCAT('ERROR: Member ', NEW.famMemID, ' is subscribed to a plan. Cannot add family member.');
            SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = @err_msg;
        END IF;
    END IF;
END;

/*
* Trigger to remove all linked family members if the planManager changes their plan from a family plan to a non-family plan.
*/
CREATE TRIGGER IF NOT EXISTS after_custChangePlanType_FamilyToOther
    AFTER UPDATE ON tbl_custdata
    FOR EACH ROW
BEGIN
    # If the customer was subscribed to a family plan...
    IF (OLD.planID = 3 OR OLD.planID = 6) THEN
        # If the new plan is NOT a family plan...
        IF NOT (NEW.planID = 3 OR NEW.planID = 6) THEN
            DELETE FROM tbl_familyMembers WHERE planManagerID = OLD.custID;
        END IF;
    END IF;
END;












