
##### Script to INSERT data into the EZTechMovie database tables #####

##### Delete all data from tables for testing purposes #####

DELETE FROM tbl_plans;
DELETE FROM tbl_moviedata;
DELETE FROM tbl_genredata;
DELETE FROM tbl_directors;
DELETE FROM tbl_actors;
DELETE FROM tbl_moviecast;
DELETE FROM tbl_moviedirectors;
DELETE FROM tbl_moviegenres;
DELETE FROM tbl_custdata;
DELETE FROM tbl_paymentinfo;
DELETE FROM tbl_custactivity_stream;
DELETE FROM tbl_custactivity_dvd;
DELETE FROM tbl_dvdrentalhistory;
DELETE FROM tbl_familyMembers;

##### INSERT statements #####

# (planID[AUTO], planService[varchar], planType[varchar], maxInstances[int], pricePerMonth[double])
INSERT INTO tbl_plans VALUES
(1,'Stream','Individual',1,7.99),
(2,'Stream','Friendly',2,11.99),
(3,'Stream','Family',4,15.99),
(4,'DVD','Individual',1,4.99),
(5,'DVD','Friendly',1,7.99),
(6,'DVD','Family',2,11.99);

# (movieID[AUTO], movieTitle[varchar], movieYear[int], numCast[int], movieRating[varchar])
INSERT INTO tbl_moviedata VALUES
(1,'2001: A Space Odyssey',1968,3,'G'),
(2,'The Godfather',1972,2,'R'),
(3,'Citizen Kane',1941,1,'PG'),
(4,'Raiders of the Lost Ark',1981,1,'PG'),
(5,'There Will Be Blood',2007,1,'R'),
(6,'Singin in the Rain',1952,2,'G'),
(7,'Goodfellas',1990,3,'R'),
(8,'The Dark Knight',2008,3,'PG-13'),
(9,'Jaws',1975,2,'PG'),
(10,'Star Wars: A New Hope',1977,3,'PG'),
(11,'Alien',1979,1,'R'),
(12,'Pulp Fiction',1994,3,'R'),
(13,'Spirited Away',2001,1,'PG'),
(14,'Blade Runner',1982,2,'R'),
(15,'Mad Max: Fury Road',2015,2,'R'),
(16,'The Blair Witch Project',1999,3,'R'),
(17,'The Texas Chainsaw Massacre',1974,2,'R'),
(18,'The Shining',1980,2,'R'),
(19,'Toy Story',1995,2,'G'),
(20,'Die Hard',1988,1,'R'),
(21,'The Thing',1982,2,'R'),
(22,'No Country for Old Men',2007,3,'R'),
(23,'Get Out',2017,2,'R'),
(24,'Across the Universe',2007,3,'PG-13'),
(25,'21 Jump Street',2012,2,'R');

# (genreID[AUTO], genreTitle[varchar])
INSERT INTO tbl_genredata VALUES
(1,'Action'),
(2,'Adventure'),
(3,'Comedy'),
(4,'Sci-Fi'),
(5,'Fantasy'),
(6,'Horror'),
(7,'Thriller'),
(8,'Mystery'),
(9,'Crime'),
(10,'Drama'),
(11,'Romance'),
(12,'Musical'),
(13,'Animation'),
(14,'Family'),
(15,'History'),
(16,'Biography');

# (directorID[AUTO], director_Fname[varchar], director_Mname[varchar], director_Lname[varchar])
INSERT INTO tbl_directors VALUES
(1,'Stanley',NULL,'Kubrick'),
(2,'Francis','Ford','Coppola'),
(3,'Orson',NULL,'Welles'),
(4,'Steven',NULL,'Spielberg'),
(5,'Paul','Thomas','Anderson'),
(6,'Gene',NULL,'Kelly'),
(7,'Stanley',NULL,'Donen'),
(8,'Martin',NULL,'Scorsese'),
(9,'Christopher',NULL,'Nolan'),
(10,'George',NULL,'Lucas'),
(11,'Ridley',NULL,'Scott'),
(12,'Quentin',NULL,'Tarantino'),
(13,'Hayao',NULL,'Miyazaki'),
(14,'George',NULL,'Miller'),
(15,'Daniel',NULL,'Myrick'),
(16,'Eduardo',NULL,'Sanchez'),
(17,'Kim',NULL,'Henkel'),
(18,'Tobe',NULL,'Hooper'),
(19,'John',NULL,'Lasseter'),
(20,'John',NULL,'McTiernan'),
(21,'John',NULL,'Carpenter'),
(22,'Joel',NULL,'Coen'),
(23,'Ethan',NULL,'Coen'),
(24,'Jordan',NULL,'Peele'),
(25,'Julie',NULL,'Taymor'),
(26,'Patrick',NULL,'Hasburgh'),
(27,'Stephen','J.','Cannell');

# (actorID[AUTO], actor_Fname[varchar], actor_Mname[varchar], actor_Lname[varchar])
INSERT INTO tbl_actors VALUES
(1,'Keir',NULL,'Dullea'),
(2,'Gary',NULL,'Lockwood'),
(3,'William',NULL,'Sylvester'),
(4,'Marlon',NULL,'Brando'),
(5,'Al',NULL,'Pacino'),
(6,'James',NULL,'Caan'),
(7,'Herman','J.','Mankiewicz'),
(8,'Orson',NULL,'Welles'),
(9,'John',NULL,'Houseman'),
(10,'Harrison',NULL,'Ford'),
(11,'Karen',NULL,'Allen'),
(12,'Paul',NULL,'Freeman'),
(13,'Daniel',NULL,'Day-Lewis'),
(14,'Paul',NULL,'Dano'),
(15,'Ciaran',NULL,'Hinds'),
(16,'Gene',NULL,'Kelly'),
(17,'Donald',NULL,'O''Connor'),
(18,'Debbie',NULL,'Reynolds'),
(19,'Robert','De','Niro'),
(20,'Ray',NULL,'Liotta'),
(21,'Joe',NULL,'Pesci'),
(22,'Christian',NULL,'Bale'),
(23,'Heath',NULL,'Ledger'),
(24,'Aaron',NULL,'Eckhart'),
(25,'Roy',NULL,'Scheider'),
(26,'Robert',NULL,'Shaw'),
(27,'Richard',NULL,'Dreyfuss'),
(28,'Mark',NULL,'Hamill'),
(29,'Carrie',NULL,'Fisher'),
(30,'Sigourney',NULL,'Weaver'),
(31,'Tom',NULL,'Skerritt'),
(32,'John',NULL,'Hurt'),
(33,'John',NULL,'Travolta'),
(34,'Uma',NULL,'Thurman'),
(35,'Samuel','L.','Jackson'),
(36,'Daveigh',NULL,'Chase'),
(37,'Suzanne',NULL,'Pleshette'),
(38,'Miyu',NULL,'Irino'),
(39,'Rutger',NULL,'Hauer'),
(40,'Sean',NULL,'Young'),
(41,'Tom',NULL,'Hardy'),
(42,'Charlize',NULL,'Theron'),
(43,'Nicholas',NULL,'Hoult'),
(44,'Heather',NULL,'Donahue'),
(45,'Michael','C.','Williams'),
(46,'Joshua',NULL,'Leonard'),
(47,'Marilyn',NULL,'Burns'),
(48,'Edwin',NULL,'Neal'),
(49,'Allen',NULL,'Danziger'),
(50,'Jack',NULL,'Nicholson'),
(51,'Shelley',NULL,'Duvall'),
(52,'Danny',NULL,'Lloyd'),
(53,'Tom',NULL,'Hanks'),
(54,'Tim',NULL,'Allen'),
(55,'Don',NULL,'Rickles'),
(56,'Bruce',NULL,'Willis'),
(57,'Alan',NULL,'Rickman'),
(58,'Bonnie',NULL,'Bedelia'),
(59,'Kurt',NULL,'Russell'),
(60,'Wilford',NULL,'Brimley'),
(61,'Keith',NULL,'David'),
(62,'Tommy','Lee','Jones'),
(63,'Javier',NULL,'Bardem'),
(64,'Josh',NULL,'Brolin'),
(65,'Daniel',NULL,'Kaluuya'),
(66,'Allison',NULL,'Williams'),
(67,'Bradley',NULL,'Whitford'),
(68,'Evan','Rachel','Wood'),
(69,'Jim',NULL,'Sturgess'),
(70,'Joe',NULL,'Anderson'),
(71,'Johnny',NULL,'Depp'),
(72,'Dustin',NULL,'Nguyen'),
(73,'Peter',NULL,'Deluise');

# (movieID[int], actorID[int])
INSERT INTO tbl_moviecast VALUES
(1,1),
(1,2),
(1,3),
(2,4),
(2,5),
(2,6),
(3,7),
(3,8),
(4,10),
(4,11),
(4,12),
(5,13),
(5,14),
(5,15),
(6,16),
(6,17),
(6,18),
(7,19),
(7,20),
(7,21),
(8,22),
(8,23),
(8,24),
(9,25),
(9,26),
(9,27),
(10,28),
(10,29),
(11,30),
(11,31),
(11,32),
(12,33),
(12,34),
(12,35),
(13,36),
(13,37),
(13,38),
(14,39),
(14,40),
(15,41),
(15,42),
(15,43),
(16,44),
(16,45),
(16,46),
(17,47),
(17,48),
(17,49),
(18,50),
(18,51),
(18,52),
(19,53),
(19,54),
(19,55),
(20,56),
(20,57),
(20,58),
(21,59),
(21,60),
(21,61),
(22,62),
(22,63),
(22,64),
(23,65),
(23,66),
(23,67),
(24,68),
(24,69),
(24,70),
(25,71),
(25,72),
(25,73);

# (movieID[int], directorID[int])
INSERT INTO tbl_moviedirectors VALUES
(1,1),
(2,2),
(3,3),
(4,4),
(5,5),
(6,6),
(6,7),
(7,8),
(8,9),
(9,4),
(10,10),
(11,11),
(12,12),
(13,13),
(14,11),
(15,14),
(16,15),
(16,16),
(17,17),
(17,18),
(18,1),
(19,19),
(20,20),
(21,21),
(22,22),
(22,23),
(23,24),
(24,25),
(25,26),
(25,27);

# (movieID[int], genreID[int])
INSERT INTO tbl_moviegenres VALUES
(1,2),
(1,4),
(2,9),
(2,10),
(3,10),
(3,8),
(4,1),
(4,2),
(5,10),
(6,3),
(6,12),
(6,11),
(7,16),
(7,9),
(7,10),
(8,1),
(8,9),
(8,10),
(9,2),
(9,8),
(9,7),
(10,1),
(10,2),
(10,5),
(10,4),
(11,6),
(11,4),
(12,9),
(12,10),
(13,13),
(13,2),
(13,14),
(14,1),
(14,10),
(14,4),
(15,1),
(15,2),
(15,4),
(16,6),
(16,8),
(17,6),
(18,10),
(18,6),
(19,13),
(19,2),
(19,3),
(19,14),
(20,1),
(20,7),
(21,6),
(21,8),
(21,4),
(22,9),
(22,10),
(22,7),
(23,6),
(23,8),
(23,7),
(24,10),
(24,5),
(24,15),
(25,9),
(25,10),
(25,8);

# (custID[AUTO], custUser[varchar], custPW[varchar], custEmail[varchar], planID[int], activity[int], payType[varchar], memStartDate[varchar])
INSERT INTO tbl_custdata VALUES
(1001,'AB@B@123','40Thieves','Ali.Baba@hotmail.com',1,0,NULL,'03/23/2019'),
(1002,'Bagsey13','@rken$tone','Bilbo.Baggins@yahoo.com',1,0,NULL,'11/01/2018'),
(1003,'FroFro8','0neR!ng','Frodo.Baggins@yahoo.com',1,0,NULL,'12/24/2023'),
(1004,'SailingSparrow','Bl@ckP3arl1492','WheresTheRum@outlook.com',2,0,NULL,'07/12/2022'),
(1005,'TheMockingjay','I<3P3t@','Katniss.Everdeen@district12.edu',2,0,NULL,'05/30/2007'),
(1006,'Margie6289','3Kids1Life','MSimpson@hotmail.com',2,0,NULL,'02/06/2024'),
(1007,'Winnefield637','P!gsareF!lthy','JulesW@gmail.com',3,0,NULL,'01/05/2020'),
(1008,'DarylZED','Cr0ssb0w','Daryl.Dixon@yahoo.com',3,0,NULL,'11/11/2011'),
(1009,'LazyDaisy','fl0w3rb0wz','DaisyDuckie@gmail.com',3,0,NULL,'02/12/2017'),
(1010,'BuffBuffay','Sm3llyC@t','Phoebe123456789@gmail.com',4,0,NULL,'01/26/2018'),
(1011,'GladJoe','C0m3di@n123','JGladstone@hotmail.com',4,0,NULL,'05/23/2001'),
(1012,'@gentJ@mes!','007007007','James.Bond@MI6.gov',4,0,NULL,'04/04/2021'),
(1013,'HGranger110100','TopoftheCl@33','Hermione.Granger@hogwarts.edu',5,0,NULL,'10/27/2016'),
(1014,'PetaBread','P@!ntingPr0','Peta.Mellark@district12.edu',5,0,NULL,'08/29/2001'),
(1015,'VoorheesSl@sh3r','Cryst@lL@k3','MamasBoy@gmail.com',5,0,NULL,'01/01/2001'),
(1016,'Suize247','St3ssed0ut','SusanMayer@outlook.com',6,0,NULL,'12/14/2021'),
(1017,'PrineBAir','OutY@Mouth','Will.Smith@hotmail.com',6,0,NULL,'09/10/2014'),
(1018,'GiffD@ddi3','Password123','someone@gmail.com',6,0,NULL,'04/20/1981'),
(1019,'PrvGump','password','Forrest.Gump@gmail.com',NULL,0,NULL,'03/17/2017'),
(1020,'Samara777','S3v3nD@ys','ghostgirl@outlook.com',NULL,0,NULL,'08/06/2023'),
(1021,'Ferbinator','summ3r247365','Ferb.Fletcher@gmail.com',NULL,0,NULL,'05/25/2009'),
(1022,'Sunshine007','Pefflif27','jane.doe@medicine.com',NULL,0,NULL,'01/01/2001'),
(1023,'Popstar99','Pdjuncture!2','johndoe@pharma.com',NULL,0,NULL,'02/05/2002'),
(1024,'Supernova123','12345Ab!','jane.smith@biotech.com',NULL,0,NULL,'03/10/2003'),
(1025,'Glitterball','FunPops_12','johndoe.research@gmail.com',NULL,0,NULL,'04/15/2004'),
(1026,'Stardust56','This_Is_A_Password09','jane.doe.research@yahoo.com',NULL,0,NULL,'05/20/2005'),
(1027,'Cosmicgirl99','0a9b8c7d$#','johndoe.research@hotmail.com',NULL,0,NULL,'06/25/2006'),
(1028,'Galaxygirl3000','XxTenaciousxX7','jane.smith.research@outlook.com',NULL,0,NULL,'07/30/2007'),
(1029,'Starlight88','7:derp*dds','johndoe.research@aol.com',NULL,0,NULL,'08/02/2008'),
(1030,'Celestialbeing','sadfsdfadfa','jane.doe.research@medicine.com',NULL,0,NULL,'09/06/2009'),
(1031,'Cosmicbreeze','kjkghjkghjkg','johndoe.research@pharma.net',NULL,0,NULL,'10/11/2010'),
(1032,'Interstellar1','hkjghjkeytufdghdf','jane.smith.research@biotech.org',NULL,0,NULL,'11/16/2011');

# (custID[BIGINT], cardNum[BIGINT], expDate[varchar], CVV[int], Lender[varchar], nameOnCard[varchar], payType[varchar])
INSERT INTO tbl_paymentinfo VALUES
(1001,4984318766647687,'07/2026',236,'Visa','Aashi Heintz','Credit'),
(1002,4731538826210475,'03/2026',721,'Visa','Brayleigh Storey','Debit'),
(1003,4071385253678628,'06/2028',380,'Visa','Aliyana Dobbins','Credit'),
(1004,4670144446374636,'09/2025',756,'Visa','Rhea Leung','Debit'),
(1005,5335189494482819,'06/2026',173,'Mastercard','Tydus Beggs','Credit'),
(1006,5463307132859503,'03/2025',934,'Mastercard','Sunny Mcnally','Debit'),
(1007,5225164268499144,'09/2026',402,'Mastercard','Seerat Desilva','Credit'),
(1008,5147907825766693,'07/2028',281,'Mastercard','Jakari Bigelow','Debit'),
(1009,340845511368364,'01/2028',362,'American Express','Aubriana Altman','Credit'),
(1010,370558331547470,'10/2027',479,'American Express','Ensley Hammett','Debit'),
(1011,379440588846643,'08/2025',281,'American Express','Braxtyn Poston','Credit'),
(1012,347569397082583,'08/2027',704,'American Express','Diya Canales','Debit'),
(1013,6011955252179030,'09/2027',362,'Discover','Leonidas Cramer','Credit'),
(1014,6011240316333745,'03/2026',681,'Discover','Teresa Manley','Debit'),
(1015,6011339186207714,'07/2027',662,'Discover','Ollie Wilber','Credit'),
(1016,6542006577869133,'09/2026',929,'Discover','Liliana Barrett','Debit'),
(1017,3528013235281565,'06/2028',420,'JCB','Kiyan Brockman','Credit'),
(1018,3567317440673868,'02/2027',756,'JCB','Faith Carpenter','Debit');


/*
* cust 1001 | 1 - 0
* cust 1002 | 1 - 1
* cust 1003 | 1 - 1
* cust 1004 | 2 - 0
* cust 1005 | 2 - 1
* cust 1006 | 2 - 2
* cust 1007 | 4 - 2
* cust 1008 | 4 - 3
* cust 1009 | 4 - 4
*/

# (custID[BIGINT], deviceUUID[varchar])
INSERT INTO tbl_custactivity_stream VALUES
(1002,'239bd0d1-0a91-4876-85c7-7ef5c37dc55a'),
(1003,'12a6c2f3-5f41-4c5b-84e5-e6b2a67c8b8f'),
(1005,'c345bfe1-e106-43fd-9e25-87b72a9d6d7c'),
(1006,'9f18a5bd-8a22-4b9b-ae29-ff58aa48a6a1'),
(1006,'7e8e6515-0422-4e44-9b44-225053f66d0b'),
(1007,'b69b156c-9b2b-498e-987b-d77f8a5e4b91'),
(1007,'e5c9b30e-0a9c-4c51-bb9b-3a02ddfe5b8f'),
(1008,'d09b7b32-617f-46fc-9b8e-5be1621c3a94'),
(1008,'27a821d2-d6e7-4cb4-8e86-8ff6a28754ec'),
(1008,'3d8d7e7a-0c27-4c49-bb88-5708143e5787'),
(1009,'81c07ef2-2e97-4f61-a2e1-134d96b7d09d'),
(1009,'f4d20933-14f1-49c4-aa76-83600b3d9e7c'),
(1009,'648a1a17-3ed5-4872-aa95-2d042e7a0628'),
(1009,'7a81e2c5-656e-49e3-90e4-d57f3c6828c9');


/*
* cust 1010 | 1 - 0
* cust 1011 | 1 - 1
* cust 1012 | 1 - 1
* cust 1013 | 1 - 0
* cust 1014 | 1 - 1
* cust 1015 | 1 - 1
* cust 1016 | 2 - 0
* cust 1017 | 2 - 1
* cust 1018 | 2 - 2
*/

# (custID[BIGINT], movieID[int])
INSERT INTO tbl_custactivity_dvd VALUES
(1011,1),
(1012,2),
(1014,3),
(1015,4),
(1017,5),
(1018,6),
(1018,7);

# (planManagerID[BIGINT], famMemID[BIGINT])
INSERT INTO tbl_familyMembers VALUES
(1007,1019),
(1007,1020),
(1007,1021),
(1007,1022),
(1007,1023),
(1016,1024),
(1016,1025),
(1016,1026),
(1016,1027),
(1016,1028);

