alter table Crashes add ServerIp varchar(50);
alter table Crashes add ServerName varchar(500);
alter table Crashes add FilePath varchar(500);
alter table Crashes add LogFile varchar(500);
alter table Crashes add DmpFile varchar(500);
alter table Crashes add TxtFile varchar(500);
alter table Crashes add CreateTime datetime;